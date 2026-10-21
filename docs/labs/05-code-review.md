# Lab 5: Code review

**Goal:** Review two classmates' pull requests carefully and kindly. At a software company you'll read far more code than you write.

## 1. Find a PR to review

Open [pull requests](https://github.com/I-Asous/CSCI235/pulls) and pick one with green CI that has no reviews yet. Comment "Reviewing this" so two people don't pile onto the same PR.

## 2. Read the PR on GitHub

- **Conversation** tab: does the description explain the change? Does it say `Closes #N`?
- **Files changed** tab: read every line. Click the **+** next to a line to leave a comment there.

## 3. Check it out and run it locally

Reading isn't enough. Run it.

```bash
gh pr checkout 42 --repo I-Asous/CSCI235
# without gh:  git fetch upstream pull/42/head:pr-42 && git switch pr-42

make test
```

Try to break it. Write a quick extra test for an edge case the author missed. If it fails, that's a great review comment, and you can paste the test into it.

When you're done: `git switch main`.

## 4. What to look for

- **Correctness:** does it do what the issue asked? What about empty input, one element, duplicates?
- **Tests:** do they actually check the edge cases, or just the happy path?
- **Memory:** every `new` has a matching `delete`. Classes that own memory follow the Rule of Three.
- **Readability:** clear names, a comment explaining what the function does, no dead code or debugging `cout`s.
- **Scope:** does the PR change only what the issue needs?

## 5. Write good comments

| ❌ Unhelpful | ✅ Helpful |
|---|---|
| "This is wrong." | "If `items` is empty, `items.size() - 1` wraps around to a huge number on line 12. Could you add a test for `{}`?" |
| "Bad name." | "Nit: `t` → `temp` or `smallest` would make this loop easier to follow." |
| "LGTM" on a PR you didn't run | "Ran it locally with a 10,000-element reversed vector and it's fast. Approving." |

- Prefix tiny, optional points with **"Nit:"**.
- Use GitHub's **suggestion** button (the ± icon) to propose an exact replacement the author can accept in one click.
- Ask questions instead of making demands: "What happens if…?"
- Praise good things too.

## 6. Submit the review

Click **Review changes** (top right of the Files changed tab) and choose:

- **Comment:** questions or feedback, not blocking
- **Approve:** you ran it and you'd merge it
- **Request changes:** something must be fixed first

## ✅ Checkpoint

- [ ] You submitted reviews on **two** PRs, with at least one inline comment each
- [ ] For at least one, you checked out the branch and ran the tests locally

Next: [Lab 6: Undo and recover →](06-undo-and-recover.md)
