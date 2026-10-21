# Lab 3: Merge conflicts

**Goal:** Cause a conflict on purpose, read it, and resolve it calmly, first with `merge` and then with `rebase`.

A **conflict** happens when two branches change the same lines and Git can't decide which version wins. It isn't an error. Git is asking you to decide.

> Part A happens entirely in **your own fork**. Nothing you do here affects anyone else.

## Part A: Create and resolve a merge conflict

### 1. Set up two branches that disagree

```bash
git switch main
git switch -c practice-base
mkdir -p practice
printf 'The best data structure is: ???\n' > practice/favorite.txt
git add practice/favorite.txt
git commit -m "Add practice file"

git switch -c team-stack
printf 'The best data structure is: the stack\n' > practice/favorite.txt
git commit -am "Vote for stack"

git switch practice-base
git switch -c team-queue
printf 'The best data structure is: the queue\n' > practice/favorite.txt
git commit -am "Vote for queue"
```

Look at the picture:

```bash
git log --oneline --graph --all
```

### 2. Merge one branch into the other

```bash
git switch team-stack
git merge team-queue
```

```
CONFLICT (content): Merge conflict in practice/favorite.txt
Automatic merge failed; fix conflicts and then commit the result.
```

### 3. Read the conflict

```bash
git status
cat practice/favorite.txt
```

```
<<<<<<< HEAD
The best data structure is: the stack
=======
The best data structure is: the queue
>>>>>>> team-queue
```

- Between `<<<<<<< HEAD` and `=======` is **your current branch's** version.
- Between `=======` and `>>>>>>> team-queue` is **the incoming** version.

### 4. Resolve it

Edit the file so it says exactly what you want, and **delete all three marker lines**. For example:

```
The best data structures are: the stack and the queue
```

Then finish the merge:

```bash
git add practice/favorite.txt
git commit                 # Git pre-fills a message; save and close
git log --oneline --graph --all
```

> Changed your mind halfway through? `git merge --abort` puts everything back the way it was.

### 5. Clean up

These branches were just for practice. Don't push them.

```bash
git switch main
git branch -D practice-base team-stack team-queue
```

## Part B: When your PR falls behind upstream

This is the conflict you'll actually hit. You open a PR, and while it's waiting, other PRs get merged into upstream. Usually GitHub can still merge it. But if someone changed the same lines, GitHub says **"This branch has conflicts that must be resolved."**

Fix it by **rebasing**: replaying your commits on top of the latest upstream.

```bash
git switch my-feature-branch
git fetch upstream
git rebase upstream/main
```

If there's a conflict, resolve it exactly as in Part A, then:

```bash
git add <file>
git rebase --continue        # repeat for each conflicting commit
# or: git rebase --abort to give up and return to where you started
```

Rebasing rewrites your branch's history, so a normal push will be rejected. Use:

```bash
git push --force-with-lease
```

`--force-with-lease` refuses to overwrite commits on the remote that you haven't seen, which makes it the safe version of `--force`.

> **Merge or rebase?** Both work. `git merge upstream/main` adds a merge commit and never needs a force-push. `git rebase upstream/main` gives a clean, straight history. Either way, **never rebase `main` or a branch other people are working on.**

## ✅ Checkpoint

- [ ] You resolved a conflict and `git log --graph` shows the merge commit
- [ ] You can explain what `<<<<<<<`, `=======`, and `>>>>>>>` mean
- [ ] You know when `--force-with-lease` is needed and why plain `--force` is dangerous

Next: [Lab 4: Claim an issue and ship it →](04-claim-an-issue.md)
