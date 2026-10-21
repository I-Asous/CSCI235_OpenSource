# Lab 4: Claim an issue and ship it

**Goal:** Make a real contribution to the library: an algorithm or ADT, with tests, that passes CI and code review. **This is the part that goes on your resume.**

## 1. Pick an issue

Browse the [open issues](https://github.com/I-Asous/CSCI235/issues). Filter by label:

- `good first issue`: small and self-contained
- `recursion`, `sorting`, `stack`, `queue`, `linked-list`: match what we're covering in lecture
- `challenge`: bigger, for when you want something impressive to talk about in interviews

Comment **"I'd like to work on this"** and **wait to be assigned** before writing code. One person per issue.

Have an idea that isn't listed? Open a new issue with the **"Propose a new algorithm or ADT"** template.

## 2. Branch from a fresh `main`

```bash
git switch main
git pull upstream main
git push origin main
git switch -c issue-<number>-<short-name>      # e.g. issue-16-insertion-sort
```

## 3. Write the tests first (recommended)

Create `tests/algorithms/test_<name>.cpp` (or `tests/adt/...` for an ADT). Decide what "correct" means before you write the code:

- the normal case
- edge cases: empty input, one element, all duplicates, already sorted, reverse sorted…
- error cases: what should throw?

Running `make test` now should **fail to compile**, because the header doesn't exist yet. That's expected.

## 4. Write the code

Create the header named in the issue. Follow [CONTRIBUTING.md](../../CONTRIBUTING.md#code-conventions) and copy the style of `binary_search.hpp`.

```bash
make test ONLY=<name>      # run just your tests while you work
make test WERROR=1         # then everything, with warnings as errors
```

## 5. Commit in small, meaningful steps

```bash
git add tests/algorithms/test_insertion_sort.cpp
git commit -m "Add tests for insertion sort"
git add include/h235/algorithms/insertion_sort.hpp
git commit -m "Implement insertion sort"
```

Several small commits with clear messages beat one giant "done" commit. Reviewers (and future employers browsing your GitHub) can follow your thinking.

## 6. Push and open the PR

```bash
git push -u origin issue-16-insertion-sort
```

Open the PR against `I-Asous/CSCI235:main`. In the description, write **`Closes #16`**. GitHub will link the PR to the issue and close the issue automatically when the PR merges.

## 7. Get to green, then get reviewed

- If CI is ❌, click **Details**, read the log, fix it locally, commit, and push. Sanitizer errors name the exact line that leaked or overflowed.
- Request a review from a classmate (Lab 5 is the other side of this).
- Address every comment: either change the code, or reply explaining why not. Then **Resolve conversation**.
- If GitHub reports conflicts, rebase onto `upstream/main` ([Lab 3, Part B](03-merge-conflicts.md#part-b-when-your-pr-falls-behind-upstream)).

## 8. After merge

1. Sync and delete the branch (same as Lab 2, step 8).
2. Add a link to your merged PR in your `contributors/<you>.md` file. That's another small PR.
3. Update your resume: see [docs/resume.md](../resume.md).

## ✅ Checkpoint

- [ ] Your PR is merged, its issue closed automatically, and CI on `main` is green
- [ ] Your code has at least 3 meaningful test cases

Next: [Lab 5: Code review →](05-code-review.md)
