# Git cheat sheet

## One-time setup

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
git clone https://github.com/<you>/CSCI235.git
git remote add upstream https://github.com/I-Asous/CSCI235.git
```

## Every task

```bash
git switch main && git pull upstream main && git push origin main   # sync
git switch -c issue-12-short-name                                   # branch
make test                                                           # test
git add <files> && git commit -m "Imperative summary"               # commit
git push -u origin issue-12-short-name                              # push, then open PR
```

## Looking around

| Command | Shows |
|---|---|
| `git status` | Current branch, changed and staged files |
| `git diff` / `git diff --staged` | Unstaged / staged changes |
| `git log --oneline --graph --all` | History of every branch |
| `git branch -a` | Local and remote branches |
| `git remote -v` | Where `origin` and `upstream` point |
| `git show <hash>` | One commit in full |
| `git blame <file>` | Who last changed each line |

## Fixing things

| Situation | Command |
|---|---|
| Discard edits to a file | `git restore <file>` |
| Unstage a file | `git restore --staged <file>` |
| Fix the last (unpushed) commit | `git commit --amend` |
| Put work aside | `git stash` / `git stash pop` |
| Undo a pushed commit safely | `git revert <hash>` |
| Bring a stale PR branch up to date | `git fetch upstream && git rebase upstream/main && git push --force-with-lease` |
| Abort a merge or rebase | `git merge --abort` / `git rebase --abort` |
| Find "lost" commits | `git reflog` |

## GitHub CLI shortcuts

```bash
gh repo fork I-Asous/CSCI235 --clone     # fork + clone + set upstream in one step
gh pr create --repo I-Asous/CSCI235      # open a PR from the terminal
gh pr checkout 42 --repo I-Asous/CSCI235 # check out a classmate's PR
gh pr status                             # your PRs and their CI status
```
