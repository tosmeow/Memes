# Git Repository Setup Guide

## Quick Setup (Choose Your Method)

### Method 1: GitHub CLI (Easiest)
```bash
# Install GitHub CLI (if not installed)
brew install gh

# Authenticate
gh auth login

# Create new repo on GitHub
gh repo create rust-learning --public --source=. --remote=origin

# Add and commit files
git add .
git commit -m "Initial commit: Rust learning workspace setup"

# Push to GitHub
git push -u origin main
```

---

### Method 2: HTTPS with Personal Access Token

#### Step 1: Create GitHub Repository
Go to GitHub.com → Click "+" → New repository
- Name: `rust-learning` (or your choice)
- Public or Private
- Don't initialize with README (we already have files)

#### Step 2: Get Personal Access Token
1. GitHub Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Generate new token
3. Select scopes: `repo` (full control of private repositories)
4. Copy the token (save it somewhere safe!)

#### Step 3: Add Remote and Push
```bash
# Add remote (replace YOUR_USERNAME and YOUR_REPO)
git remote add origin https://github.com/YOUR_USERNAME/rust-learning.git

# Configure credential caching (macOS keychain)
git config --global credential.helper osxkeychain

# Stage all files
git add .

# Commit
git commit -m "Initial commit: Complete Rust learning workspace

- 5 progressive learning modules (basics to DeFi)
- 18 runnable Rust projects
- Comprehensive documentation
- Examples tailored for quant/math background
- AMM simulator, blockchain demo, and more"

# Push (you'll be prompted for credentials)
git push -u origin main

# When prompted:
# Username: your_github_username
# Password: paste_your_personal_access_token
```

---

### Method 3: SSH Keys (Most Secure)

#### Step 1: Generate SSH Key (if you don't have one)
```bash
# Check if you already have keys
ls -la ~/.ssh

# If not, generate new key
ssh-keygen -t ed25519 -C "your_email@example.com"
# Press Enter for default location
# Set passphrase (recommended)

# Start SSH agent
eval "$(ssh-agent -s)"

# Add key to agent
ssh-add ~/.ssh/id_ed25519

# Copy public key to clipboard
pbcopy < ~/.ssh/id_ed25519.pub
# Or just display it:
cat ~/.ssh/id_ed25519.pub
```

#### Step 2: Add SSH Key to GitHub
1. Go to GitHub Settings → SSH and GPG keys
2. Click "New SSH key"
3. Title: "Mac - $(date +%Y)"
4. Paste the key (from clipboard or cat command above)
5. Click "Add SSH key"

#### Step 3: Test Connection
```bash
ssh -T git@github.com
# Should see: "Hi username! You've successfully authenticated..."
```

#### Step 4: Add Remote and Push
```bash
# Create repo on GitHub first (via web interface)

# Add remote with SSH URL (replace YOUR_USERNAME and YOUR_REPO)
git remote add origin git@github.com:YOUR_USERNAME/rust-learning.git

# Stage all files
git add .

# Commit
git commit -m "Initial commit: Complete Rust learning workspace

- 5 progressive learning modules (basics to DeFi)
- 18 runnable Rust projects
- Comprehensive documentation
- Examples tailored for quant/math background
- AMM simulator, blockchain demo, and more"

# Push
git push -u origin main
```

---

## Verify Setup

After pushing, verify everything worked:

```bash
# Check remote configuration
git remote -v

# Should show:
# origin  https://github.com/YOUR_USERNAME/rust-learning.git (fetch)
# origin  https://github.com/YOUR_USERNAME/rust-learning.git (push)
# OR for SSH:
# origin  git@github.com:YOUR_USERNAME/rust-learning.git (fetch)
# origin  git@github.com:YOUR_USERNAME/rust-learning.git (push)

# Check branch tracking
git branch -vv

# Should show:
# * main abc1234 [origin/main] Initial commit: Complete Rust learning workspace
```

---

## Future Workflow

After initial setup, your workflow will be:

```bash
# Make changes to code
nano 01-basics/hello_world/src/main.rs

# Check status
git status

# Stage changes
git add .
# Or stage specific files
git add 01-basics/hello_world/src/main.rs

# Commit with message
git commit -m "Update hello_world example"

# Push to GitHub
git push

# Pull latest changes (if working from multiple machines)
git pull
```

---

## Common Git Commands

```bash
# See what's changed
git status
git diff

# View commit history
git log
git log --oneline --graph

# Create and switch to new branch
git checkout -b feature/new-example

# Switch branches
git checkout main

# Merge branch
git merge feature/new-example

# Undo uncommitted changes
git checkout -- filename.rs
git restore filename.rs  # newer syntax

# Amend last commit
git commit --amend

# View remote repositories
git remote -v

# Update remote URL if needed
git remote set-url origin NEW_URL
```

---

## Troubleshooting

### "Authentication failed"
- **HTTPS**: Make sure you're using Personal Access Token, not your GitHub password
- **SSH**: Check `ssh -T git@github.com` to verify key is set up correctly

### "Permission denied (publickey)"
- SSH key not added to GitHub or ssh-agent
- Run: `ssh-add ~/.ssh/id_ed25519`

### "Fatal: remote origin already exists"
- Remove old remote: `git remote remove origin`
- Then add new one

### "Failed to push some refs"
- Pull first: `git pull origin main --rebase`
- Then push: `git push origin main`

### Forgot which authentication method I'm using
```bash
git remote get-url origin

# If starts with https:// → using HTTPS (token)
# If starts with git@github.com: → using SSH
```

---

## Configuration Files

Git configuration is stored in:

- **Global config**: `~/.gitconfig` (user-wide settings)
- **Local config**: `.git/config` (repository-specific)

View your configuration:
```bash
# View all settings
git config --list

# View specific settings
git config user.name
git config user.email
git config credential.helper

# Set user info (if not already set)
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

---

## Security Best Practices

1. **Never commit secrets**: API keys, passwords, private keys
2. **Use .gitignore**: Already configured for Rust projects
3. **Use SSH over HTTPS**: More secure for regular use
4. **Enable 2FA on GitHub**: Add extra security layer
5. **Rotate tokens**: Change Personal Access Tokens periodically
6. **Review before committing**: Always `git diff` before `git add`

---

## Next Steps

1. Choose authentication method above
2. Create GitHub repository (if not exists)
3. Add remote connection
4. Commit and push initial workspace
5. Start learning Rust!

Once set up, you can access your code from anywhere:
```bash
git clone https://github.com/YOUR_USERNAME/rust-learning.git
# Or with SSH:
git clone git@github.com:YOUR_USERNAME/rust-learning.git
```

---

## Quick Reference Card

```bash
# Initial Setup
git remote add origin URL
git push -u origin main

# Daily Workflow
git status
git add .
git commit -m "message"
git push

# Credentials (choose one)
git config --global credential.helper osxkeychain  # HTTPS
ssh-add ~/.ssh/id_ed25519                          # SSH
gh auth login                                       # GitHub CLI
```

---

**Recommended**: Use GitHub CLI (`gh`) for easiest setup, or SSH keys for best security.
