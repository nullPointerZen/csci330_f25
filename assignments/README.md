# Assignment Submissions - CSCI 330

This directory contains student assignment submissions using a professional Git workflow with Pull Requests.

## 📁 Related Directories

- **`/modules/module-XX_chX/assignment-template/`** - Starter code for each assignment (copy from here)
- **`/assignments/`** - Student submissions (your work goes here)
- **`/setup/test_integration.sh`** - Test your development environment
- **See also**: Each module's `assignments.md` for specific requirements

## Directory Structure

Each student creates their own directory following this naming pattern:
```
assignments/
└── CSCI330_FirstName_LastName/
    ├── week01/
    ├── week02/
    ├── week03/
    └── [additional weeks as assigned]
```

## Submission Workflow

### Initial Setup (One Time Only)

1. **Fork the Repository**
   - Go to the main course repository on GitHub
   - Click "Fork" to create your personal copy
   - Clone your fork locally:
     ```bash
     git clone https://github.com/YOUR_USERNAME/COURSE_REPO_NAME.git
     cd COURSE_REPO_NAME
     ```

2. **Add Upstream Remote**
   ```bash
   git remote add upstream https://github.com/INSTRUCTOR_USERNAME/COURSE_REPO_NAME.git
   ```

3. **Configure Git Identity**
   ```bash
   git config user.name "FirstName LastName - CSCI330"
   git config user.email "your.email@university.edu"
   ```

4. **Create Your Assignment Directory**
   ```bash
   mkdir -p assignments/CSCI330_FirstName_LastName
   ```

### Weekly Assignment Submission Process

For each assignment, follow these steps:

1. **Sync with Course Updates**
   ```bash
   git checkout main
   git pull upstream main
   git push origin main
   ```

2. **Create Assignment Branch**
   ```bash
   git checkout -b week01-assignment-name
   # Example: git checkout -b week01-pointers-basics
   ```

3. **Complete Your Work**
   - Copy assignment template to your directory:
     ```bash
     # IMPORTANT: Replace FirstName_LastName with your actual name
     cp -r modules/module-01_ch1/assignment-template/* assignments/CSCI330_FirstName_LastName/week01/
     ```
   - Navigate to your working directory:
     ```bash
     cd assignments/CSCI330_FirstName_LastName/week01/
     ```
   - Implement your solution (complete the TODOs in the source files)
   - Build and test your code:
     ```bash
     mkdir build && cd build
     cmake .. && make
     ./tests/test_main  # Run the tests
     ```
   - Commit regularly with meaningful messages

4. **Submit Pull Request**
   ```bash
   git add assignments/CSCI330_FirstName_LastName/week01/
   git commit -m "Complete Week 1 assignment: [brief description]"
   git push origin week01-assignment-name
   ```
   
   Then on GitHub:
   - Navigate to your fork
   - Click "Compare & pull request"
   - Fill out the PR template completely
   - Submit for review

### Pull Request Requirements

Your PR must include:
- **Clear Title**: "Week X Assignment - FirstName LastName"
- **Complete Description**: Use the provided template
- **All Required Files**: Source code, documentation, tests
- **Working Code**: Must compile and run without errors
- **Proper Directory Structure**: Files in correct student directory

### Code Review Process

1. **Instructor Review**: I will review your code and provide feedback
2. **Requested Changes**: Address any issues and update your PR
3. **Approval**: Once approved, you may merge your own PR
4. **Grading**: Final grades recorded in Canvas

### Important Rules

- ⚠️ **Never commit directly to main branch**
- ⚠️ **Always work in feature branches**
- ⚠️ **One assignment per Pull Request**
- ⚠️ **No late submissions without prior approval**
- ⚠️ **Keep your fork synchronized with upstream**

### Academic Integrity

- Work must be your own
- Git history provides timestamp verification
- Collaboration policies follow course syllabus
- Plagiarism detection includes commit analysis

### Getting Help

- Git issues: See `quick-reference/git-commands.md`
- Assignment questions: Office hours or class discussion
- Technical problems: Course discussion forum
- Emergency: Email instructor with "CSCI330 URGENT" in subject

## FERPA Compliance Note

While your code is in public repositories (valuable for your portfolio), all grades and detailed feedback remain in Canvas to protect your privacy.

---

**Remember**: This workflow teaches industry-standard development practices. Master it now and you'll be prepared for professional software development!