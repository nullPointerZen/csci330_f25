# CSCI 330 - Advanced C++ Programming

**🎯 Your Single Starting Point for the Course**

Welcome to modern C++ programming! This course teaches professional C++ development through hands-on projects, industry-standard tools, and real-world practices.

---

## 🚀 Getting Started (New Students)

### 1. **First Time Setup** ⚙️
- **📋 [Complete Environment Setup](setup/DEVELOPMENT_SETUP.md)** - Docker, VS Code, Git (30-45 min)
- **📖 [Learn Git Workflow](setup/GIT_WORKFLOW.md)** - Professional Pull Request submissions
- **✅ [Verify Your Setup](setup/test_integration.sh)** - Test that everything works

### 2. **Understand the Course Structure**
- **📚 [Course Chapters](#-course-chapters)** - 14 mandatory chapters + 4 optional
- **🎯 [Semester Project](project/)** - Build something substantial and portfolio-worthy
- **📝 [Assignment Submissions](assignments/)** - Professional Pull Request workflow

### 3. **Start Learning**
- **📖 Read textbook chapter FIRST** (Josh Lospinoso's "C++ Crash Course")
- **📋 Work through course materials** in each chapter directory
- **💻 Submit via Pull Request** when complete

---

## 📚 Course Chapters

### **Core Curriculum (Mandatory)**
All students complete these 14 chapters:

| Chapter | Topic | Directory | Focus |
|---------|-------|-----------|-------|
| **01** | Up and Running | [chapters/chapter-01/](chapters/chapter-01/) | Environment, first programs |
| **02** | Types and Memory | [chapters/chapter-02/](chapters/chapter-02/) | Fundamental types, debugging |
| **03** | References | [chapters/chapter-03/](chapters/chapter-03/) | Pointers and references |
| **04** | Object Lifecycle | [chapters/chapter-04/](chapters/chapter-04/) | Constructors, destructors, RAII |
| **05** | Runtime Polymorphism | [chapters/chapter-05/](chapters/chapter-05/) | Virtual functions, inheritance |
| **06** | Compile-Time Polymorphism | [chapters/chapter-06/](chapters/chapter-06/) | Templates, generic programming |
| **07** | Expressions | [chapters/chapter-07/](chapters/chapter-07/) | Operators, operator overloading |
| **08** | Statements | [chapters/chapter-08/](chapters/chapter-08/) | Control flow, exceptions |
| **09** | Functions | [chapters/chapter-09/](chapters/chapter-09/) | Lambdas, function objects |
| **11** | Smart Pointers | [chapters/chapter-11/](chapters/chapter-11/) | Modern memory management |
| **12** | Utilities | [chapters/chapter-12/](chapters/chapter-12/) | Standard library utilities |
| **13** | Containers | [chapters/chapter-13/](chapters/chapter-13/) | STL containers |
| **14** | Iterators | [chapters/chapter-14/](chapters/chapter-14/) | Iterator patterns |
| **15** | Strings | [chapters/chapter-15/](chapters/chapter-15/) | Text processing |

### **Supplemental Chapters (Optional)**
Choose based on time and interest:

| Chapter | Topic | Directory | When to Use |
|---------|-------|-----------|-------------|
| **10** | Testing | [supplemental/chapter-10/](supplemental/chapter-10/) | Professional testing practices |
| **16** | Streams | [supplemental/chapter-16/](supplemental/chapter-16/) | File I/O operations |
| **17** | Filesystems | [supplemental/chapter-17/](supplemental/chapter-17/) | File system manipulation |
| **18** | Algorithms | [supplemental/chapter-18/](supplemental/chapter-18/) | STL algorithms |

---

## 🎯 Semester Project

Build something substantial and portfolio-worthy over 15 weeks:

- **📋 [Project Overview](project/semester-project.md)** - Goals and requirements
- **💡 [Brainstorming Guide](project/brainstorming-guide.md)** - Find your perfect project
- **🏗️ [Project Phases](project/phases/)** - 5-phase development process
- **👥 [Peer Reviews](project/peer-review-forms.md)** - Collaborative feedback

---

## 📝 Assignment Submission

This course uses **professional Pull Request workflow**:

### Quick Submission Process
1. **Create feature branch**: `git checkout -b week01-assignment-name`
2. **Complete work** in your assignment directory
3. **Submit Pull Request** with complete template
4. **Address feedback** and iterate
5. **Merge when approved**

**📖 Complete Guide**: [assignments/README.md](assignments/README.md)

---

## 📖 Chapter Workflow

Every chapter follows the same structure for consistency:

### For Each Chapter:
1. **📚 Read textbook chapter FIRST** - Essential foundation
2. **📋 Review [lecture-notes.md](chapters/chapter-01/lecture-notes.md)** - Course-specific content  
3. **🧩 Complete [assignments.md](chapters/chapter-01/assignments.md)** - Hands-on practice
4. **🔧 Use [quick-help.md](chapters/chapter-01/quick-help.md)** - Troubleshooting and references
5. **🐛 Follow debugging guides** (where applicable)
6. **✅ Submit via Pull Request**

---

## 🛠️ Development Environment

### **Docker + VS Code** (Recommended)
- Consistent environment across all platforms
- Professional debugging tools
- Integrated testing framework

### **Quick Commands**
```bash
# Start environment
cd setup/
docker-compose up -d cpp-dev

# Enter container
docker-compose exec cpp-dev bash

# Build and test
mkdir build && cd build
cmake .. && make && ctest
```

**📖 Complete Setup Guide**: [setup/DEVELOPMENT_SETUP.md](setup/DEVELOPMENT_SETUP.md)

---

## 📚 Quick References

### Essential Resources
- **🔧 [Git Commands](reference/git-commands.md)** - Essential Git workflow commands
- **🆘 [Troubleshooting](setup/docker_troubleshooting.md)** - Common issues and solutions  
- **📋 [Assignment Templates](assignment-templates/)** - Starting code for projects

### Course Materials
- **📖 Textbook**: "C++ Crash Course" by Josh Lospinoso
- **💻 Development Environment**: Docker + VS Code + Git
- **🎯 Assessment**: Pull Request submissions + Semester project

---

## 🎓 Learning Approach

### **Reading-First Workflow** (Critical for Success)
1. **📖 Read textbook chapter** thoroughly first (1-2 hours)
2. **🎯 Review learning objectives** - Know what you're aiming for
3. **💻 Work through course materials** actively
4. **🧩 Complete assignments** with understanding focus
5. **✅ Submit and iterate** based on feedback

### **Time Management**
- **Budget 6-8 hours per chapter** (reading + assignments)
- **Plan 12-15 hours per week** for the full course
- **Don't rush** - understanding > speed
- **Ask for help** after 2+ hours stuck on same problem

---

## 🆘 Getting Help

### When You're Stuck
1. **📋 Check chapter [quick-help.md](chapters/chapter-01/quick-help.md)**
2. **🔍 Use VS Code debugger** - Visualize what's happening
3. **📖 Review [reference materials](reference/)**  
4. **👥 Ask classmates** or study groups
5. **🏢 Office hours** - Don't struggle alone!

### **2-Hour Rule**: If stuck on same problem for 2+ hours, seek help immediately.

---

## 🌟 Success Tips

- **🔄 Commit frequently** - Small, meaningful commits
- **🐛 Debug systematically** - Use the visual debugger
- **📚 Connect to textbook** - Course reinforces book concepts
- **💪 Challenge yourself** - Try optional chapters and advanced features
- **🤝 Collaborate professionally** - Help others, learn from feedback

---

**🎯 Ready to start?** Begin with [Chapter 1: Up and Running](chapters/chapter-01/) after completing your [environment setup](setup/DEVELOPMENT_SETUP.md).

**Questions?** Check the [reference materials](reference/) or ask in office hours!

---

*Course developed with professional Git workflow, Docker containerization, and industry best practices. Designed for students ready to master systems programming.*