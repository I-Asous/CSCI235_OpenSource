# Instructor guide

How to run this project with a class. Students don't need to read this.

## Design

- **Upstream is a real, public library.** Student work gets merged into it permanently, which is why it's worth putting on a resume.
- **Every task lives in its own files.** Each issue maps to a new header and a new test file, and each contributor file is named after its owner. The Makefile discovers tests automatically. So 40 students can open PRs at the same time without conflicting in upstream.
- **Conflict practice happens in each student's own fork** (Lab 3, Part A), so it's guaranteed and can't break anyone else.
- **CI is the first reviewer.** It runs g++ and clang++ with `-Werror` plus ASan/UBSan, and it checks contributor files. TAs only look at green PRs.

## One-time repo setup

1. **Make the repo public.** Forks of private repos are restricted, and a private repo can't go on a resume. Consider moving it to a course organization (for example `hunter-csci235`) so it outlives any one instructor account. If you rename or move it, search and replace `I-Asous/CSCI235` across the docs.
2. **Push this scaffold** and confirm the CI badge on the README turns green.
3. **Protect `main`** (Settings → Rules → Rulesets → New branch ruleset, target `main`):
   - Require a pull request before merging, with **1 approval** (2 if you want a peer and a TA)
   - Dismiss stale approvals when new commits are pushed
   - Require review from Code Owners. Add TAs to [`.github/CODEOWNERS`](../.github/CODEOWNERS).
   - Require status checks: `test (g++)`, `test (clang++)`, `contributors`
   - Leave **"require branches to be up to date" off**. Because tasks don't overlap, it's unnecessary, and with 40 students it would force constant rebasing.
   - Block force pushes
4. **Merge settings** (Settings → General → Pull Requests): allow **squash merging** only. Squash commits keep the student as the author, so their contributions graph still credits them.
5. **Actions settings:** under "Fork pull request workflows", require approval only for first-time contributors.
6. **Seed the issues:**
   ```bash
   gh auth login
   ./scripts/seed_issues.sh --dry-run
   ./scripts/seed_issues.sh I-Asous/CSCI235
   ```
   This creates labels plus about 45 issues from [`scripts/issues.tsv`](../scripts/issues.tsv). Add rows to scale up to your class size; re-running skips existing issues.

## Suggested schedule

| Week | Lab | Deliverable |
|---|---|---|
| 1 | 0 + 1 | Screenshot of `git remote -v` and passing `make test` |
| 2 | 2 | Merged contributor-file PR |
| 3 | 3 | Screenshot of `git log --graph` showing the resolved merge |
| 4–7 | 4 | Claimed issue → merged PR with tests (time it to the matching lecture unit) |
| 4–7 | 5 | Two submitted reviews on classmates' PRs |
| 8 | 6 | Exercise completed (honor system, or a reflog screenshot) |

## Grading ideas

Everything is visible on GitHub, so grade from the artifacts:

- `gh pr list --repo I-Asous/CSCI235 --state merged --author <student>`
- `gh api repos/I-Asous/CSCI235/pulls/<n>/reviews` to see who reviewed what
- Lab 4 rubric: tests cover edge cases · code is correct and leak-free · commit history is meaningful · review feedback was addressed

## Running the class

- **Assigning issues:** assign on the first "I'd like to work on this" comment. Unassign after a week of inactivity.
- **Stuck PRs:** a red CI check is the student's job to fix. Point them at the Details log before debugging for them.
- **Duplicate work:** close it kindly with a link to the earlier PR, and offer an unclaimed issue.
- **Merge cadence:** merge in batches (for example twice a week) so students regularly see upstream move and practice syncing.

## Each new semester

- Students in the new cohort fork the same repo and build on everything earlier classes merged.
- Add new rows to `issues.tsv`: harder ADTs, or "add a missing test for X" issues on existing code.
- Tag a release at the end of each term (`git tag fall-2026 && git push upstream fall-2026`) so students can link to the version they contributed to.
