# Lab 2: Your first pull request

**Goal:** Add yourself to `contributors/` and get the change merged into the real project.

## Concepts

| Term | Meaning |
|---|---|
| **Branch** | An independent line of work. `main` is the official one; you make your own for each task. |
| **Staging area** | The changes you've chosen (with `git add`) to go into the next commit |
| **Commit** | A saved snapshot with a message, an author, and a unique ID (hash) |
| **Push** | Upload your commits to a remote |
| **Pull request (PR)** | A request to merge your branch into someone else's repo. This is where review and CI happen. |

## 1. Start from an up-to-date `main`

```bash
git switch main
git pull upstream main      # get everyone else's merged work
```

## 2. Create a branch

```bash
git switch -c add-<your-username>
git branch                  # the * shows which branch you're on
```

## 3. Make the change

```bash
cp contributors/_TEMPLATE.md contributors/<your-username>.md
```

Open the file and fill it in. The file name and the GitHub line must use your **exact** username.

## 4. Stage and commit

```bash
git status                  # your file is listed as "untracked"
git add contributors/<your-username>.md
git status                  # now it's under "Changes to be committed"
git diff --staged           # exactly what will be committed
git commit -m "Add <Your Name> to contributors"
git log --oneline -3
```

> Use `git add <specific files>`, not `git add .`, so you don't accidentally commit stray files.

## 5. Push your branch to your fork

```bash
./scripts/check_contributors.sh     # the same check CI runs
git push -u origin add-<your-username>
```

`-u` links your local branch to the one on `origin`, so later you can just type `git push`.

## 6. Open the pull request

1. Go to your fork on GitHub. A yellow banner says **"Compare & pull request"**. Click it.
2. Check the arrows: **base repository: `I-Asous/CSCI235`, base: `main`** ← **head repository: `<you>/CSCI235`, compare: `add-<your-username>`**.
3. Fill in the template and click **Create pull request**.
4. Scroll down and watch the **CI checks** run. Wait for green ✅.

## 7. Respond to review

A reviewer may ask for changes. You don't open a new PR; you just push to the same branch:

```bash
# edit the file
git add contributors/<your-username>.md
git commit -m "Fix GitHub link in contributor file"
git push
```

The PR updates automatically. Reply to each comment and click **Resolve conversation** once you've addressed it.

## 8. After it's merged: sync and clean up

```bash
git switch main
git pull upstream main           # your change is now part of upstream
git push origin main             # bring your fork's main up to date too
git branch -d add-<your-username>
git push origin --delete add-<your-username>
```

## Common problems

| Symptom | Fix |
|---|---|
| `remote: Permission denied` when pushing | You cloned upstream instead of your fork. Run `git remote set-url origin https://github.com/<you>/CSCI235.git` |
| PR shows other people's changes too | You branched from an old `main`. See [Lab 3](03-merge-conflicts.md), Part B. |
| The `contributors` check is red | Click **Details** on the failing check and read the error. It tells you which line is wrong. |
| You committed to `main` by mistake | See [Lab 6](06-undo-and-recover.md), "I committed to the wrong branch". |

## ✅ Checkpoint

- [ ] Your PR is merged and your file appears on `I-Asous/CSCI235`
- [ ] Your fork's `main` matches upstream (GitHub says "This branch is up to date")

Next: [Lab 3: Merge conflicts →](03-merge-conflicts.md)
