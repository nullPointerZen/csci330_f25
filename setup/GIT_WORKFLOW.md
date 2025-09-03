# CSCI 330 Git Workflow Guide

## Overview

This course uses a **professional Git workflow** with Pull Requests for all assignment submissions. This mirrors industry practices and will prepare you for software development careers while providing better feedback mechanisms for learning.

## Why Git Workflow?

**Industry Relevance**: Learn the same workflow used by professional software development teams  
**Code Review**: Get line-by-line feedback on your code  
**Portfolio Building**: Build a GitHub portfolio demonstrating collaboration skills  
**Version Control Mastery**: Master branching, merging, and conflict resolution  
**Timestamp Verification**: Git provides perfect academic integrity tracking  

## Initial Setup (One Time Only)

### 1. Fork the Course Repository

1. Navigate to the main course repository on GitHub
2. Click the "Fork" button in the upper right
3. This creates your personal copy of the course repository

### 2. Clone Your Fork

```bash
# Replace YOUR_USERNAME with your actual GitHub username (e.g., john_smith123)
git clone https://github.com/YOUR_USERNAME/csci330_f25.git
cd csci330_f25
```

**Example**: If your GitHub username is `jane_doe2024`, you would run:
```bash
git clone https://github.com/jane_doe2024/csci330_f25.git
```

### 3. Add Upstream Remote

```bash
# This allows you to pull updates from the main course repository
git remote add upstream https://github.com/DEmcla/csci330_f25.git

# Verify your remotes
git remote -v
# Should show:
# origin    https://github.com/YOUR_USERNAME/csci330_f25.git (fetch)
# origin    https://github.com/YOUR_USERNAME/csci330_f25.git (push)
# upstream  https://github.com/DEmcla/csci330_f25.git (fetch)
# upstream  https://github.com/DEmcla/csci330_f25.git (push)
```

### 4. Configure Git Identity

```bash
git config user.name "FirstName LastName - CSCI330"
git config user.email "your.email@university.edu"
```

### 5. Create Your Assignment Directory

```bash
# Replace FirstName and LastName with your actual name
mkdir -p csci330_f25/assignments/CSCI330_FirstName_LastName
```

**Example**: If your name is Jane Doe, you would run:
```bash
mkdir -p csci330_f25/assignments/CSCI330_Jane_Doe
```

## Weekly Assignment Workflow

### Step 1: Sync with Course Updates

**Before starting any assignment**, always sync with the latest course materials:

```bash
# Switch to main branch
git checkout main

# Pull latest changes from instructor
git pull upstream main

# Push updates to your fork
git push origin main
```

### Step 2: Create Feature Branch

Create a new branch for each assignment:

```bash
# Naming pattern: weekXX-brief-description
git checkout -b week01-pointers-basics

# Verify you're on the new branch
git branch
# * week01-pointers-basics  (current branch)
#   main
```

### Step 3: Set Up Assignment Files

```bash
# Copy assignment template to your directory
cp -r csci330_f25/modules/module-01_ch1/assignment-template/* csci330_f25/assignments/CSCI330_FirstName_LastName/week01/

# Navigate to your assignment directory
cd csci330_f25/assignments/CSCI330_FirstName_LastName/week01/
```

### Step 4: Complete Your Work

1. **Edit source files** in the `src/` directory
2. **Update documentation** in `docs/README.md`
3. **Write/modify tests** as needed
4. **Test frequently** using the Docker environment

### Step 5: Commit Your Work

Make frequent, meaningful commits:

```bash
# Add your changes
git add .

# Commit with descriptive message
git commit -m "Implement basic pointer arithmetic functions

- Add pointer_add() function with bounds checking
- Add pointer_subtract() with validation
- Include comprehensive test cases
- Update documentation with usage examples"

# Push to your fork
git push origin week01-pointers-basics
```

### Step 6: Submit Pull Request

1. Go to your fork on GitHub
2. GitHub will show "Compare & pull request" button
3. Click it and fill out the PR template completely
4. Submit the pull request

## Pull Request Requirements

### Title Format
```
Week X Assignment - FirstName LastName
```

### Required Information
- Complete the entire PR template
- Check all applicable checkboxes  
- Provide implementation summary
- Document testing performed
- List any challenges encountered
- Confirm academic integrity statement

### Code Requirements
- ✅ Code must compile without errors or warnings
- ✅ All tests must pass
- ✅ Follow course coding standards
- ✅ Include comprehensive documentation
- ✅ Proper error handling where applicable

## Code Review Process

### 1. Instructor Review
- Line-by-line code examination
- Feedback on implementation approach
- Suggestions for improvement
- Grade assessment

### 2. Addressing Feedback
If changes are requested:

```bash
# Make the requested changes in your local branch
# Then commit and push

git add .
git commit -m "Address PR feedback: fix memory leak in cleanup function"
git push origin week01-pointers-basics
```

The PR automatically updates with your new commits.

### 3. Approval and Merge
- Once approved, **you** merge your own PR
- Delete the feature branch after merging
- Grade is recorded in Canvas

## Branch Management

### After PR is Merged

```bash
# Switch back to main
git checkout main

# Pull the merged changes
git pull upstream main
git push origin main

# Delete the old feature branch
git branch -d week01-pointers-basics
git push origin --delete week01-pointers-basics
```

### For Next Assignment

```bash
# Always start from updated main
git checkout main
git pull upstream main
git checkout -b week02-dynamic-memory
```

## Common Git Commands

| Command | Purpose |
|---------|---------|
| `git status` | Show current branch and file status |
| `git branch` | List all branches |
| `git checkout main` | Switch to main branch |
| `git checkout -b feature-name` | Create and switch to new branch |
| `git add .` | Stage all changes |
| `git commit -m "message"` | Commit with message |
| `git push origin branch-name` | Push branch to your fork |
| `git pull upstream main` | Pull updates from course repo |

## Troubleshooting Common Issues

### Merge Conflicts
If you encounter conflicts when pulling upstream:

```bash
# See conflicted files
git status

# Edit files to resolve conflicts (look for <<<< ==== >>>>)
# After resolving:
git add .
git commit -m "Resolve merge conflicts"
```

### Forgot to Branch
If you accidentally worked on main:

```bash
# Create branch from current state
git checkout -b week01-pointers-basics

# Now your work is on the correct branch
```

### Need to Update Branch with Latest Main
```bash
# From your feature branch
git checkout main
git pull upstream main
git checkout your-feature-branch
git merge main
```

## Important Rules

### ⚠️ NEVER:
- Commit directly to main branch
- Share your GitHub fork URL with other students
- Copy code from other students' repositories
- Submit late without prior approval

### ✅ ALWAYS:
- Work in feature branches
- Fill out PR template completely
- Test your code thoroughly
- Keep your fork synchronized
- Use meaningful commit messages

## Academic Integrity

- **Individual Work**: All code must be your own
- **Timestamp Verification**: Git commits provide perfect tracking
- **Plagiarism Detection**: Commit history analysis detects copying
- **Collaboration Policy**: Follow course syllabus guidelines

## Getting Help

### Git Issues
- Check `quick-reference/git-commands.md`
- Use `git status` to understand current state
- Google error messages (very common in industry!)

### Assignment Questions
- Office hours
- Class discussion
- Course forum

### Technical Problems
- Course discussion forum
- Email with "CSCI330 URGENT" for emergencies

## FERPA Compliance

- **Public Code**: Your implementations are public (great for portfolios!)
- **Private Grades**: All grades and detailed feedback in Canvas
- **No Personal Info**: Never commit sensitive personal information

---

**Success Tip**: Start early, commit frequently, and don't hesitate to ask for help. This workflow becomes second nature with practice and will serve you well in your software development career!