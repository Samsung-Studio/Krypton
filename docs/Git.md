# Git Internals: How Git Works (Beginner to Advanced)

Git is a **distributed version control system** that tracks changes in files, allowing multiple developers to collaborate. Unlike older systems like SVN, Git stores snapshots instead of file differences.

---

## 1. Understanding `.git` (The Heart of Git)
When you run `git init`, Git creates a `.git` directory, which contains everything required for version control.

```bash
mkdir myproject && cd myproject
git init
ls -la .git
```
You'll see:
```
.git/
  ├── HEAD
  ├── index
  ├── config
  ├── objects/
  ├── refs/
  ├── logs/
```

### Key Components Inside `.git/`
| File/Directory | Purpose |
|---------------|---------|
| `.git/HEAD` | Points to the current branch (`refs/heads/main`) |
| `.git/index` | The staging area (holds added but uncommitted changes) |
| `.git/objects/` | Stores all commits, blobs, trees, and tags |
| `.git/refs/` | Pointers to branches and tags |
| `.git/config` | Local repo configuration (username, remote URL, etc.) |

---

## 2. Git Objects (The Backbone of Git)
Git stores data as **objects** in `.git/objects/`. There are four types:

### 2.1 Blob (Binary Large Object)
- Represents the actual file content.
- Every unique file is stored only once (even if renamed).
- Identified by SHA-1 hash.

```bash
echo "Hello Git" | git hash-object --stdin -w
```

This stores the file as a **blob** and returns a hash like:
```
e69de29bb2d1d6434b8b29ae775ad8c2e48c5391
```

### 2.2 Tree (Represents a Directory)
- A **tree** links filenames to blobs.
- Git creates a new tree object for every commit.

```bash
git ls-tree HEAD
```

Example output:
```
100644 blob a7f5f35426b927411fc9231f31b5e088e3b0d23f   README.md
040000 tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904   src
```

### 2.3 Commit (Snapshot of a Repository)
A commit object contains:
- Tree (root directory at that point)
- Parent commit (previous commit hash)
- Author details
- Commit message

```bash
git cat-file -p HEAD
```

Example output:
```
tree f8d3...
parent a5b8...
author Tokyo <tokyo@example.com>
committer Tokyo <tokyo@example.com>
Added new feature
```

### 2.4 Tag (Reference to a Commit)
- Tags mark important commits (e.g., version releases).
- A lightweight tag is just a pointer.

```bash
git tag v1.0
git show v1.0
```

---

## 3. SHA-1 Hashing (How Git Ensures Integrity)
Every Git object is identified using a **SHA-1** hash (40 characters).

Example:
```bash
echo "Git Hashing" | git hash-object --stdin
# Output: 2ebd695a41b0...
```

The hash is calculated from the **content**. Even a minor change produces a completely different hash.

---

## 4. The Three Stages of Git
Every file in Git can be in one of these states:

| State | Description | Command |
|-------|------------|---------|
| **Working Directory** | Untracked/modified files | `git status` |
| **Staging Area (Index)** | Files added but not committed | `git add file.txt` |
| **Repository (Committed)** | Changes permanently recorded | `git commit -m "Message"` |

### Example Workflow:
```bash
echo "Hello" > file.txt   # Modify a file
git add file.txt          # Stage the file
git commit -m "First commit"  # Save to repository
```

---

## 5. The HEAD Pointer (Tracking Your Current Branch)
- `HEAD` is a pointer to the latest commit in the current branch.

```bash
cat .git/HEAD
# Output: ref: refs/heads/main
```

If you check out a commit directly, `HEAD` becomes **detached**:
```bash
git checkout <commit-hash>
cat .git/HEAD  # Output: <commit-hash>
```

---

## 6. Branching and Merging
- A **branch** is a lightweight pointer to a commit.

### Creating a Branch
```bash
git branch feature-branch
git checkout feature-branch
```

### Merging a Branch
```bash
git checkout main
git merge feature-branch
```

### Rebasing (Cleaner History)
```bash
git rebase main
```

---

## 7. The Index (Staging Area in Detail)
- The **index** (staging area) is a binary file (`.git/index`) storing staged files.

### Checking the Index:
```bash
git ls-files --stage
```

### How Git Tracks Changes:
| Action | Working Directory | Staging Area | Repository |
|--------|------------------|-------------|------------|
| Modify a file | ✅ Changed | ❌ Not staged | ❌ Not committed |
| `git add` | ✅ Changed | ✅ Staged | ❌ Not committed |
| `git commit` | ✅ Unmodified | ✅ Staged | ✅ Committed |

---

## 8. Garbage Collection (Cleaning Up Unused Data)
Git does automatic cleanups, but you can force it with:

```bash
git gc
```

This compresses objects into **packfiles** for efficiency.

---

## 9. Git Hooks (Automation Scripts)
Located in `.git/hooks/`, they trigger actions:

| Hook | Trigger |
|------|--------|
| `pre-commit` | Runs before `git commit` |
| `pre-push` | Runs before `git push` |
| `post-commit` | Runs after `git commit` |

Example: Prevent commits without a message:
```bash
echo 'if [ -z "$1" ]; then echo "Commit message required"; exit 1; fi' > .git/hooks/commit-msg
chmod +x .git/hooks/commit-msg
```

---

## 10. Conclusion
Git is a powerful version control system with a **DAG-based** commit structure, **SHA-1 hashing**, and an efficient **staging area**. Understanding its internals helps optimize performance and debug issues.

---

## 🔥 Bonus: Advanced Git Commands
```bash
git reflog              # View history of HEAD movements
git bisect start        # Find the commit that introduced a bug
git fsck                # Check repository integrity
git reset --hard HEAD~1 # Undo last commit
```

---