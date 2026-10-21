#!/usr/bin/env bash
# Instructor tool: creates one GitHub issue per row of scripts/issues.tsv.
# Safe to re-run; issues whose title already exists are skipped.
#
#   ./scripts/seed_issues.sh --dry-run          # print what would be created
#   ./scripts/seed_issues.sh OWNER/REPO         # create issues (needs `gh auth login`)
set -euo pipefail

cd "$(dirname "$0")/.."

DRY_RUN=0
REPO=""
for arg in "$@"; do
    case "$arg" in
        --dry-run) DRY_RUN=1 ;;
        *) REPO="$arg" ;;
    esac
done
if [[ $DRY_RUN -eq 0 && -z "$REPO" ]]; then
    echo "usage: $0 [--dry-run] OWNER/REPO" >&2
    exit 1
fi

create_labels() {
    local spec
    for spec in \
        "good first issue|7057ff|Small, self-contained; great for a first contribution" \
        "recursion|1d76db|Recursion unit" \
        "sorting|0e8a16|Sorting unit" \
        "searching|5319e7|Searching unit" \
        "stack|fbca04|Uses or builds a stack" \
        "queue|f9d0c4|Uses or builds a queue" \
        "linked-list|c2e0c6|Works with chains of nodes" \
        "adt|b60205|A new abstract data type" \
        "challenge|d93f0b|Larger task; expect more review" \
        "proposal|ededed|Student-proposed addition" \
        "bug|d73a4a|Something is broken"; do
        IFS='|' read -r name color desc <<<"$spec"
        gh label create "$name" --repo "$REPO" --color "$color" --description "$desc" --force >/dev/null
    done
}

issue_body() {
    local name="$1" file="$2" signature="$3" description="$4"
    local header="include/h235/$file"
    local test_dir="algorithms"
    [[ "$file" != algorithms/* ]] && test_dir="adt"
    local test_file="tests/$test_dir/test_${name}.cpp"

    cat <<EOF
## Task

$description

\`\`\`cpp
namespace h235 {
$signature
}
\`\`\`

## Files to create

- \`$header\`
- \`$test_file\`

The [binary search example](../blob/main/include/h235/algorithms/binary_search.hpp) and [its tests](../blob/main/tests/algorithms/test_binary_search.cpp) show exactly what a finished contribution looks like.

## Definition of done

- [ ] Code lives in \`namespace h235\` and has a \`/** @brief ... */\` comment with \`@param\`, \`@return\` and \`@throws\` as needed
- [ ] At least 3 \`TEST_CASE\`s: the normal case, edge cases (empty, one element, ...), and error cases if any
- [ ] \`make test\` passes locally and CI is green ✅
- [ ] No memory leaks (CI runs with sanitizers)
- [ ] PR description contains \`Closes #<this issue number>\`
- [ ] At least one approving review from a classmate, plus instructor/TA approval

## How to claim this issue

Comment **"I'd like to work on this"** and wait to be assigned before starting. One person per issue.
New to the workflow? Read [CONTRIBUTING.md](../blob/main/CONTRIBUTING.md).
EOF
}

if [[ $DRY_RUN -eq 0 ]]; then
    create_labels
    existing=$(gh issue list --repo "$REPO" --state all --limit 1000 --json title --jq '.[].title')
fi

count=0
while IFS=$'\t' read -r name labels file signature description; do
    title="Add $name"
    if [[ $DRY_RUN -eq 1 ]]; then
        echo "=== $title  [$labels]"
        issue_body "$name" "$file" "$signature" "$description" | head -n 8
        echo
    elif grep -qxF "$title" <<<"$existing"; then
        echo "skip (exists): $title"
        continue
    else
        gh issue create --repo "$REPO" --title "$title" --label "$labels" \
            --body "$(issue_body "$name" "$file" "$signature" "$description")" >/dev/null
        echo "created: $title"
    fi
    count=$((count + 1))
done < <(tail -n +2 scripts/issues.tsv)

echo "$count issue(s) processed"
