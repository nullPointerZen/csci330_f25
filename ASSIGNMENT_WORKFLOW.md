# Assignment Workflow Overview - CSCI 330

## 🎯 Quick Reference: Assignment Workflow

### Directory Purpose Summary

| Directory | Purpose | Who Modifies |
|-----------|---------|--------------|
| `/modules/module-XX_chX/assignment-template/` | Starter code templates | Instructor only |
| `/assignments/CSCI330_Your_Name/` | Your completed work | You |
| `/modules/module-XX_chX/assignments.md` | Assignment descriptions | Read only |

## 📊 Complete Workflow Diagram

```
1. READ Assignment
   modules/module-01_ch1/assignments.md
              ↓
2. COPY Template
   modules/module-01_ch1/assignment-template/ ──copy──> assignments/CSCI330_John_Doe/week01/
              ↓
3. IMPLEMENT Solution
   Edit files in your directory
              ↓
4. TEST Your Code
   cd build && cmake .. && make && ./tests/test_main
              ↓
5. SUBMIT via Pull Request
   git push & create PR on GitHub
```

## 🔄 Step-by-Step Process

### 1️⃣ First Time Setup
```bash
# Create your personal directory (one time only)
mkdir -p assignments/CSCI330_FirstName_LastName
```

### 2️⃣ For Each Assignment
```bash
# Example for Week 1 Assignment

# a. Create branch
git checkout -b week01-assignment

# b. Copy template
cp -r modules/module-01_ch1/assignment-template/* assignments/CSCI330_FirstName_LastName/week01/

# c. Work on your solution
cd assignments/CSCI330_FirstName_LastName/week01/
# Edit source files, complete TODOs

# d. Build and test
mkdir build && cd build
cmake .. && make
./tests/test_main

# e. Commit your work
git add assignments/CSCI330_FirstName_LastName/week01/
git commit -m "Complete week 1 assignment: [description]"

# f. Push and create PR
git push origin week01-assignment
# Then create Pull Request on GitHub
```

## ⚠️ Common Mistakes to Avoid

### ❌ DON'T: Modify templates directly
```bash
# WRONG - Never edit template files
vim modules/module-01_ch1/assignment-template/src/main.cpp
```

### ✅ DO: Copy templates first
```bash
# RIGHT - Copy then edit
cp -r modules/module-01_ch1/assignment-template/* assignments/CSCI330_Your_Name/week01/
vim assignments/CSCI330_Your_Name/week01/src/main.cpp
```

### ❌ DON'T: Use inconsistent naming
```bash
# WRONG - Inconsistent formats
assignments/john_doe/           # Wrong: lowercase
assignments/JohnDoe/            # Wrong: no prefix
assignments/330_John/           # Wrong: wrong prefix
```

### ✅ DO: Use exact naming convention
```bash
# RIGHT - Consistent format
assignments/CSCI330_John_Doe/   # Correct format
```

## 🧪 Testing Clarification

### Assignment Tests (Your Code)
Located in each assignment template:
- `tests/test_main.cpp` - Tests YOUR implementation
- Run after implementing your solution
- Must pass before submission

### Environment Tests (Your Setup)
Located in setup directory:
- `setup/test_integration.sh` - Tests Docker, Git, compiler setup
- Run once after initial setup
- Not related to assignments

## 📝 Submission Checklist

Before creating your Pull Request:

- [ ] Code is in `assignments/CSCI330_FirstName_LastName/weekXX/`
- [ ] All template files were copied (not modified in place)
- [ ] Code compiles without errors
- [ ] All provided tests pass
- [ ] Commits have meaningful messages
- [ ] PR follows naming convention: "Week X Assignment - FirstName LastName"

## 🔗 Quick Links

- **Assignment Descriptions**: `/modules/module-XX_chX/assignments.md`
- **Starter Templates**: `/modules/module-XX_chX/assignment-template/`
- **Submission Guide**: `/assignments/README.md`
- **Git Help**: `/reference/git-commands.md`
- **Environment Setup**: `/setup/DEVELOPMENT_SETUP.md`

---

**Remember**: This workflow teaches professional software development practices. Following it correctly prepares you for industry work!