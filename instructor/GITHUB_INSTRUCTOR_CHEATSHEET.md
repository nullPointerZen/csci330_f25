# GitHub Course Management Cheatsheet for Instructors

## 🎯 Quick Reference: Your Daily GitHub Workflow

### Your Repository Structure
```
cpp/
├── csci330_f25/           # PUBLIC - Students see this
│   ├── chapters/          # Course content
│   ├── assignments/       # Student submissions land here
│   └── assignment-templates/  # Starter code for students
└── instructor/            # PRIVATE - Only you see this
    ├── solutions/         # Your solution files
    └── *.md files         # Instructor guides (like this one)
```

---

## 📥 Managing Student Pull Requests

### Viewing PRs in GitHub Web Interface
1. Navigate to: `https://github.com/[your-username]/cpp/pulls`
2. You'll see list of pending student submissions
3. Click on any PR to review

### Viewing PRs in VSCode
1. Install "GitHub Pull Requests and Issues" extension (if not already)
2. Click GitHub icon in sidebar
3. See all PRs under "Pull Requests" section
4. Click to checkout and review locally

### Review Workflow Commands
```bash
# List all open PRs (from container)
gh pr list

# Check out a specific PR locally for testing
gh pr checkout [PR-number]

# Return to main branch after review
git checkout main

# View PR details
gh pr view [PR-number]
```

---

## 🔍 Reviewing Student Code

### Quick Review Process
```bash
# 1. Fetch student's PR (replace 42 with actual PR number)
gh pr checkout 42

# 2. Navigate to their submission
cd csci330_f25/assignments/CSCI330_Student_Name/week01/

# 3. Build and test their code
mkdir -p build && cd build
cmake .. && make
./tests/test_main

# 4. Return to main when done
git checkout main
```

### Leaving Feedback on GitHub
1. **In PR view**, click "Files changed" tab
2. **Hover over line numbers** to add inline comments
3. **Click "+" to comment** on specific lines
4. **Use "Start a review"** to batch comments
5. **Finish with**:
   - ✅ "Approve" - Assignment complete
   - 💬 "Comment" - General feedback
   - 🔄 "Request changes" - Needs fixes

### Common Feedback Templates
```markdown
# For good work:
Great implementation! Your use of [specific technique] shows good understanding.

# For needed improvements:
This works, but consider [specific improvement]. See chapter X for examples.

# For bugs:
There's an issue here: [describe bug]. Try [debugging suggestion].

# For incomplete work:
Please complete the TODO sections in [filename]. Refer to assignments.md for requirements.
```

---

## 🛡️ Branch Protection Setup (One-Time)

### Protect main branch from direct pushes:
1. Go to Settings → Branches
2. Add branch protection rule
3. Pattern: `main`
4. Check:
   - ✅ Require pull request reviews before merging
   - ✅ Dismiss stale pull request approvals
   - ✅ Include administrators (optional - keeps you honest too!)

---

## 📊 Tracking Student Progress

### See all student branches
```bash
# List all remote branches (shows student work)
git branch -r | grep "origin/"

# See recent activity
git log --oneline --graph --all --since="1 week ago"

# Check specific student's commits
git log --author="Student Name" --oneline
```

### Quick Status Checks
```bash
# See who has submitted for current week
ls -la csci330_f25/assignments/

# Check if student's tests pass
cd csci330_f25/assignments/CSCI330_Student_Name/week01/build/
ctest --output-on-failure
```

---

## 🎓 Common Instructor Tasks

### 1. Start of Semester
```bash
# Create and push semester branch
git checkout -b fall2025
git push -u origin fall2025

# Set up assignment schedule (in main branch)
# Update csci330_f25/assignments/README.md with due dates
```

### 2. Weekly Assignment Release
```bash
# Ensure templates are ready
ls csci330_f25/assignment-templates/chapter-XX/

# Students will copy these templates themselves
# Just verify they're complete and tested
```

### 3. Grading a Batch of Submissions
```bash
# Create a grading script (instructor/ directory)
cat > instructor/grade_week01.sh << 'EOF'
#!/bin/bash
for pr in $(gh pr list --limit 50 --json number -q '.[].number'); do
    echo "Checking PR #$pr"
    gh pr checkout $pr
    # Run tests, log results
    git checkout main
done
EOF
chmod +x instructor/grade_week01.sh
```

### 4. End of Assignment Period
```bash
# Close PR without merging (keeps main clean)
gh pr close [PR-number] --comment "Assignment reviewed and graded. Good work!"

# Or merge if you want to keep student work
gh pr merge [PR-number] --squash
```

---

## 🚫 What NOT to Share with Students

Keep these in `instructor/` directory only:
- Solution files
- Grading rubrics with point values
- Test cases beyond basic ones
- Administrative scripts
- This cheatsheet!

---

## 💡 Pro Tips for Course Management

### 1. Bulk Operations
```bash
# Review all PRs from specific date
gh pr list --search "created:>2024-01-15"

# Find all students who haven't submitted
comm -23 <(cat class_roster.txt | sort) \
         <(ls csci330_f25/assignments/ | sed 's/CSCI330_//' | sort)
```

### 2. Automated Feedback
```bash
# Set up GitHub Actions for auto-testing (optional)
# Create .github/workflows/test-submission.yml
# This runs tests automatically on PR creation
```

### 3. Quick Navigation Aliases
```bash
# Add to your .bashrc in container
alias cdassign='cd /workspace/csci330_f25/assignments'
alias cdinst='cd /workspace/instructor'
alias checkpr='gh pr list'
```

### 4. Monitoring Student Struggles
```bash
# See who's pushing frequently (might be struggling)
git shortlog -sn --since="3 days ago"

# Check for late-night commits (stress indicator)
git log --since="1 week ago" --until="now" \
    --pretty=format:"%h %an %ad" \
    --date=format:"%H:%M" | \
    awk '$3 >= "23:00" || $3 <= "06:00"'
```

---

## 📝 Sample Grading Workflow

```bash
# Monday: Check weekend submissions
gh pr list --label "week-01"

# For each PR:
gh pr checkout [number]
cd csci330_f25/assignments/[student]/
mkdir build && cd build && cmake .. && make && ctest

# Add feedback
gh pr review [number] --comment --body "Tests pass! See inline comments for style suggestions."

# Track in gradebook
echo "Student_Name,Week01,95" >> instructor/grades.csv

# Close PR
gh pr close [number] --comment "Graded: 95/100"
```

---

## 🔧 Troubleshooting Common Issues

### Student Can't Create PR
- Check they forked the repo
- Verify they're pushing to their fork first
- Ensure they have repo access

### PR Has Merge Conflicts
```bash
# Help student resolve
gh pr checkout [number]
git fetch origin main
git merge origin/main
# Fix conflicts
git add .
git commit -m "Resolve merge conflicts"
git push
```

### Student Accidentally Committed to Main
```bash
# Revert their commit
git revert [commit-hash]
git push

# Educate about branching
```

---

## 📊 Quick Commands Reference Card

| Task | Command |
|------|---------|
| List all PRs | `gh pr list` |
| Review PR #42 | `gh pr checkout 42` |
| Test student code | `cd [path] && ctest` |
| Leave feedback | `gh pr review 42 --comment --body "message"` |
| Close with grade | `gh pr close 42 --comment "Grade: X/100"` |
| See branches | `git branch -r` |
| Check activity | `git log --since="1 week"` |
| Return to main | `git checkout main` |

---

## 🎯 Your Typical Week

### Monday
- Review weekend PR submissions
- Test and grade batch submissions
- Post feedback on GitHub

### Wednesday
- Check mid-week submissions
- Identify struggling students
- Send encouragement/hints via PR comments

### Friday
- Final submission reviews
- Close graded PRs
- Prep next week's materials

---

## 📚 Additional Resources

- GitHub CLI docs: https://cli.github.com/manual/
- PR review best practices: https://docs.github.com/en/pull-requests/collaborating-with-pull-requests
- Your instructor guide: [INSTRUCTOR_GUIDE.md](./INSTRUCTOR_GUIDE.md)

---

**Remember**: Students learn professional Git workflow by doing. Your PR reviews teach them real-world code review practices they'll use in industry!

**Quick Help**: If something isn't covered here, try:
- `gh --help` for GitHub CLI commands
- `git --help` for Git commands
- Check other instructor/*.md files for course-specific guidance