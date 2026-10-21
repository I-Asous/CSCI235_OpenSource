# Lab 0: Setup

**Goal:** Git is installed, it knows who you are, and your computer can talk to GitHub.

## 1. Create a GitHub account

Go to <https://github.com/signup>.

> **Pick a professional username.** It will appear on your resume and in this project's history permanently. `jsmith-dev` works; `xXsn1perXx` does not.

Optional but worth it: apply for the free [GitHub Student Developer Pack](https://education.github.com/pack) with your Hunter email.

## 2. Install Git

| OS | Command |
|---|---|
| macOS | `xcode-select --install` (also installs `make` and `clang++`) |
| Windows | Install [WSL](https://learn.microsoft.com/windows/wsl/install), then inside Ubuntu: `sudo apt install git build-essential` |
| Linux | `sudo apt install git build-essential` |

Check it worked:

```bash
git --version
```

## 3. Tell Git who you are

Use the **same email** as your GitHub account so your commits are credited to you:

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
git config --global init.defaultBranch main
git config --global pull.rebase false
```

Check: `git config --global --list`

## 4. Connect to GitHub

The easiest way is the GitHub CLI:

```bash
# macOS:   brew install gh
# Ubuntu:  sudo apt install gh
gh auth login          # choose GitHub.com → HTTPS → "Login with a web browser"
```

<details>
<summary>Prefer SSH keys? Click here.</summary>

```bash
ssh-keygen -t ed25519 -C "you@example.com"     # press Enter to accept the defaults
cat ~/.ssh/id_ed25519.pub                       # copy this output
```

Paste it at GitHub → Settings → SSH and GPG keys → New SSH key, then test it:

```bash
ssh -T git@github.com     # "Hi <username>! You've successfully authenticated"
```

If you use SSH, clone with the `git@github.com:...` URLs instead of `https://...`.
</details>

## ✅ Checkpoint

- [ ] `git --version` prints a version
- [ ] `git config --global user.email` prints your GitHub email
- [ ] `gh auth status` (or `ssh -T git@github.com`) says you're logged in

Next: [Lab 1: Fork and clone →](01-fork-and-clone.md)
