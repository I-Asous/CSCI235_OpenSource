# Lab 6: Undo and recover

**Goal:** Learn that almost nothing in Git is truly lost, and how to get out of the most common messes.

Practice each scenario on a throwaway branch: `git switch -c undo-practice`.

## "I changed a file and want the original back"

```bash
git restore path/to/file          # discard unstaged edits (cannot be undone!)
```

## "I staged something I didn't mean to"

```bash
git restore --staged path/to/file # unstage, keep the edits
```

## "My last commit message has a typo" / "I forgot a file"

```bash
git add forgotten-file.cpp
git commit --amend -m "Better message"
```

Only amend commits you haven't pushed yet. (If you have, you'll need `git push --force-with-lease`, so only do this on your own feature branch.)

## "I need to switch branches but I'm in the middle of something"

```bash
git stash            # put the work-in-progress aside
git switch other-branch
# ...
git switch -
git stash pop        # bring it back
```

## "I committed to `main` instead of a branch"

```bash
git switch -c my-feature          # new branch keeps the commit
git switch main
git reset --hard upstream/main    # move main back to match upstream
```

## "A commit that's already pushed broke something"

```bash
git revert <commit-hash>          # adds a NEW commit that undoes it; safe on shared branches
```

`revert` is for shared history. `reset` rewrites history, so use it only on branches nobody else has.

## "I did something terrible and lost commits"

```bash
git reflog                        # every place HEAD has been, including "deleted" commits
git switch -c rescue <hash-from-reflog>
```

## The three flavours of `reset`

| Command | Moves the branch | Staging area | Your files |
|---|---|---|---|
| `git reset --soft HEAD~1` | ✅ | kept | kept |
| `git reset HEAD~1` (`--mixed`) | ✅ | cleared | kept |
| `git reset --hard HEAD~1` | ✅ | cleared | **discarded** |

## ✅ Exercise

On `undo-practice`, make three commits. Then:

1. Amend the last commit's message.
2. `git reset --hard HEAD~2`, and confirm the commits are gone from `git log`.
3. Use `git reflog` to find them and recover them onto a new branch.
4. Delete the practice branches.

Done with the labs! See [how to put this on your resume](../resume.md).
