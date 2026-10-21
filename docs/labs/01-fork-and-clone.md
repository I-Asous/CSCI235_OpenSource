# Lab 1: Fork and clone

**Goal:** Get your own copy of the project, build it, and understand the three copies of the code.

## Concepts

| Term | Meaning |
|---|---|
| **Repository (repo)** | A project folder plus its entire history |
| **Fork** | Your personal copy of someone else's repo, *on GitHub*. You can push to it; you can't push to theirs. |
| **Clone** | A copy of a repo *on your computer* |
| **Remote** | A nickname for a repo URL. By convention, `origin` is your fork and `upstream` is the original. |

```
upstream  I-Asous/CSCI235     ── fork ──▶   origin  <you>/CSCI235
                                                 │
                                               clone
                                                 ▼
                                           local folder on your laptop
```

## 1. Fork

On <https://github.com/I-Asous/CSCI235>, click **Fork** (top right), then **Create fork**.
You now have `https://github.com/<your-username>/CSCI235`.

## 2. Clone your fork (not the original!)

```bash
cd ~                      # or wherever you keep projects
git clone https://github.com/<your-username>/CSCI235.git
cd CSCI235
```

## 3. Add the original repo as `upstream`

Your fork doesn't update itself when classmates' PRs get merged. The `upstream` remote is how you pull in their work.

```bash
git remote add upstream https://github.com/I-Asous/CSCI235.git
git remote -v
```

You should see four lines: `origin` (fetch and push) pointing to **your** fork, and `upstream` (fetch and push) pointing to **I-Asous**.

## 4. Build and run the tests

```bash
make test
```

All tests should say `PASS`.

## 5. Look around

```bash
git status                 # which branch am I on? anything changed?
git log --oneline --graph  # the history (press q to quit)
git log --oneline -- include/h235/LinkedStack.hpp   # history of one file
git show HEAD              # the most recent commit in full
```

Open `include/h235/algorithms/binary_search.hpp` and `tests/algorithms/test_binary_search.cpp`. Every contribution you make will follow this pattern.

## ✅ Checkpoint

- [ ] `git remote -v` shows both `origin` (your username) and `upstream` (I-Asous)
- [ ] `make test` passes
- [ ] You can explain the difference between a fork and a clone

Next: [Lab 2: Your first pull request →](02-first-pull-request.md)
