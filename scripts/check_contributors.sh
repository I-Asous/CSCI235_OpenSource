#!/usr/bin/env bash
# Validates files in contributors/. Run locally with:  ./scripts/check_contributors.sh
# In CI on a pull request, PR_AUTHOR and BASE_REF are set so we can also check that
# the author only added their own file.
set -euo pipefail

cd "$(dirname "$0")/.."
status=0

fail() {
    echo "::error file=$1::$2"
    echo "  x $1: $2"
    status=1
}

for path in contributors/*.md; do
    file=$(basename "$path")
    [[ "$file" == "README.md" || "$file" == _* ]] && continue

    if [[ ! "$file" =~ ^[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?\.md$ ]]; then
        fail "$path" "file name must be exactly your GitHub username followed by .md"
        continue
    fi
    user="${file%.md}"

    head -n 1 "$path" | grep -qE '^# [^ ]' \
        || fail "$path" "first line must be '# Your Name'"
    grep -qiF "**GitHub:** [@$user](https://github.com/$user)" "$path" \
        || fail "$path" "missing or mismatched line: - **GitHub:** [@$user](https://github.com/$user)"
    grep -qE '^- \*\*Semester:\*\* (Fall|Spring|Summer|Winter) 20[0-9]{2}$' "$path" \
        || fail "$path" "missing line like: - **Semester:** Fall 2026"
done

if [[ -n "${PR_AUTHOR:-}" && -n "${BASE_REF:-}" ]]; then
    while IFS= read -r added; do
        [[ -z "$added" ]] && continue
        expected="contributors/${PR_AUTHOR}.md"
        if [[ "$(echo "$added" | tr '[:upper:]' '[:lower:]')" != "$(echo "$expected" | tr '[:upper:]' '[:lower:]')" ]]; then
            fail "$added" "you can only add your own file ($expected)"
        fi
    done < <(git diff --name-only --diff-filter=A "origin/$BASE_REF...HEAD" -- contributors/)
fi

if [[ $status -eq 0 ]]; then
    echo "contributors/ looks good"
fi
exit $status
