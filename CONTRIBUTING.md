# Krypton 🚀

## 💼 Contribution To The Project

### 🔧 Setting Up the Repository

- **Fork the Repository**
  - Click the **Fork** button on the [Krypton Repository](https://github.com/Samsung-Studio/Krypton.git)
- **Clone your forked repository**
  ```bash
  git clone https://github.com/<your-username>/Krypton.git
  cd Krypton
  ```

### 🔄 Keeping Your Repository Updated

- **Add the original repository as an upstream remote**
  ```bash
  git remote add upstream https://github.com/Samsung-Studio/Krypton.git
  ```
- **Fetch the latest changes from the main repo**
  ```bash
  git checkout dev
  git pull upstream dev
  ```

### 🛠️ Create a New Feature Branch

- Always work on a separate branch for each feature/fix:
  ```bash
  git checkout -b <feature-name>
  ```

### 💪 Make and Stage Your Changes

- Make your modifications and stage them:
  ```bash
  git add .
  ```

- Commit your changes with a meaningful message:
  ```bash
  git commit -m "Implemented Add Feature"
  ```

### 💾 Push Your Changes to GitHub

```bash
git push origin <feature-name>
```

---

## 🌟 Create a **Pull Request**

- Go to your **forked repository** on GitHub
- Click on **"Pull Requests"** → **"New Pull Request"**
- Select **base branch = `dev`** and **compare branch = `feature-name`**
- Add a **title** and **description** of what you changed
- Click on **“Create Pull Request”**

---

## 🛡️ Code Review and Merge Process

- Your **PR** will be reviewed by the maintainers
- If changes are requested, update your branch:
  ```bash
  git checkout <feature-name>
  git pull upstream dev
  git add .
  git commit -m "Fixed Review Issues"
  git push origin <feature-name>
  ```
- Once approved, a maintainer will merge your **PR** into `dev`

---

## 🌐 Keeping Your Fork Updated

- After a **PR** is merged, update your local repository:
  ```bash
  git checkout dev
  git pull upstream dev
  ```
- **Delete the old branch** before working on a new feature:
  ```bash
  git branch -d <feature-name>
  ```

Thanks for contributing! 🎉