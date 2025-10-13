# C++ Programming Course - CSCI 330

A comprehensive C++ programming course based on "C++ Crash Course" by Josh Lospinoso.

## 📚 Course Structure

This repository contains complete course materials with **clear separation** between student and instructor resources:

### 🎓 For Students 
**📁 Main Directory: [`csci330_f25/`](csci330_f25/)**
- **📋 [README.md](csci330_f25/README.md)** - **START HERE** - Main student entry point
- **📖 [GIT_WORKFLOW.md](csci330_f25/GIT_WORKFLOW.md)** - Professional Pull Request submissions
- **⚙️ [DEVELOPMENT_SETUP.md](csci330_f25/DEVELOPMENT_SETUP.md)** - Environment setup guide  
- **📝 [assignments/](csci330_f25/assignments/)** - Submission guidelines and workspace
- **🔧 [quick-reference/](csci330_f25/quick-reference/)** - Git commands and troubleshooting
- **📚 Chapter Materials** - Lecture notes, assignments, quick help (no solutions)

### 👨‍🏫 For Instructors
**📁 Main Directory: [`instructor/`](instructor/)**
- **🔐 All Solutions** - Complete solution sets (hidden from students)
- **📋 Lesson Plans** - Teaching guides and timing
- **🎯 Assessment Tools** - Rubrics, Canvas integration
- **📊 Course Management** - Progress tracking, competency assessment

**🔒 Security Note**: Solutions are separated from student workspace to maintain academic integrity.

## 🚀 Quick Start

### 🎓 Students
1. **Fork this repository** on GitHub (for Pull Request submissions)
2. **Clone your fork**: `git clone https://github.com/YOUR_USERNAME/cpp.git`
3. **Enter the course directory**: `cd cpp/csci330_f25`
4. **📋 Read [`README.md`](csci330_f25/README.md)** - Main student entry point
5. **⚙️ Complete setup**: Follow [`DEVELOPMENT_SETUP.md`](csci330_f25/DEVELOPMENT_SETUP.md)
6. **📖 Learn Git workflow**: Review [`GIT_WORKFLOW.md`](csci330_f25/GIT_WORKFLOW.md)
7. **✅ Verify environment**: Run `./test_integration.sh`
8. **📚 Begin Chapter 1**: Read textbook chapter FIRST, then course materials

### 👨‍🏫 Instructors
1. **Review instructor materials**: [`instructor/`](instructor/) folder
2. **Course management**: [`instructor/INSTRUCTOR_GUIDE.md`](instructor/INSTRUCTOR_GUIDE.md)
3. **Canvas integration**: Available in instructor resources
4. **⚠️ Important**: Solutions are in [`instructor/`](instructor/) - keep separate from student access

## 📖 Course Structure

### 🎯 Core Chapters (1-9, 11-15) - Mandatory
1. **Up and Running** - Development environment, first programs
2. **Types** - Fundamental types, arrays, memory
3. **Reference Types** - Pointers and references  
4. **Object Lifecycle** - RAII, constructors, destructors
5. **Runtime Polymorphism** - Interfaces, virtual functions
6. **Compile-Time Polymorphism** - Templates
7. **Expressions** - Operators and expressions
8. **Statements** - Control flow
9. **Functions** - Function programming, lambdas
11. **Smart Pointers** - Modern memory management
12. **Utilities** - Standard library utilities
13. **Containers** - STL containers
14. **Iterators** - Iterator patterns
15. **Strings** - Modern C++ string handling and text processing

### 🔧 Supplemental Chapters (`supplemental-chapters/`) - Optional
10. **Testing** - Unit testing with Catch2
16. **Streams** - File I/O and formatted output
17. **Filesystems** - Cross-platform file operations
18. **Algorithms** - STL algorithms and data processing

### 📚 Additional Book Chapters - Not Included in Course
19. **Concurrency and Parallelism** - Multi-threading and parallel programming
20. **Network Programming with Boost.Asio** - Network communication
21. **Writing Applications** - Building complete applications

## 🛠️ Development Environment

The course supports three development approaches:
1. **Docker + VS Code** (Recommended) - Consistent environment with IDE features
2. **Docker CLI** - Pure command-line development
3. **Local Setup** - Traditional local compiler installation

All approaches are documented in the setup guide.

## 📂 Repository Structure

```
cpp/
├── README.md               # Course overview (you are here)
├── .github/                # Pull Request templates
├── csci330_f25/          # 🎓 STUDENT WORKSPACE
│   ├── README.md           # Main student entry point
│   ├── GIT_WORKFLOW.md     # Pull Request submission guide
│   ├── DEVELOPMENT_SETUP.md# Environment setup
│   ├── assignments/        # Student submission workspace
│   ├── assignment-templates/# Assignment starting code
│   ├── quick-reference/    # Git commands & troubleshooting
│   ├── chapter_XX_*.md     # Lecture notes, assignments, quick help
│   └── test_integration.sh # Environment verification
└── instructor/            # 👨‍🏫 INSTRUCTOR ONLY
    ├── INSTRUCTOR_GUIDE.md # Course management
    ├── chapter_XX_solutions/# Complete solutions (hidden)
    ├── chapter_XX_lesson_plan.md# Teaching guides
    └── [assessment tools]   # Rubrics, Canvas integration
```

**🔒 Academic Integrity**: Solutions are separated from student workspace.

## 🎯 Learning Objectives

- Master modern C++ (C++17/20)
- Understand memory management and RAII
- Apply object-oriented and generic programming
- Develop debugging and testing skills
- Use professional development tools (Git, Docker, CMake)

## 📝 Prerequisites

- Basic programming experience (any language)
- Familiarity with command line
- Computer with 4GB+ RAM

## 🤖 Course Development Process

This course was developed through an innovative AI-assisted collaborative process using Claude AI (Anthropic). The development methodology combined human pedagogical expertise with AI-powered analysis and organization:

### **Development Phases**
- **📊 Content Analysis**: AI reviewed existing course materials for redundancy, clarity, and pedagogical effectiveness
- **👥 Student Experience Design**: Created learner personas to identify gaps and improve accessibility  
- **🏗️ Structure Optimization**: Streamlined 50+ scattered files into coherent, navigable modules
- **🔧 Infrastructure Integration**: Coordinated Docker, VS Code, Git, and Canvas LMS components
- **📚 Documentation Generation**: Created comprehensive student and instructor guides
- **🔄 Iterative Refinement**: Multiple feedback cycles ensuring educational quality

### **Key Improvements Achieved**
- **70% reduction in file complexity** while preserving all educational content
- **Unified development environment** with Docker + VS Code integration
- **Multiple learning pathways** for different student needs and contexts
- **Professional-grade tooling** from day one (Git workflow, debugging, testing)
- **Competency-based assessments** focusing on practical skills

### **Human-AI Collaboration Model**
- **Human Expertise**: Provided domain knowledge, pedagogical requirements, and quality judgment
- **AI Assistance**: Handled systematic implementation, pattern recognition, and comprehensive documentation
- **Iterative Process**: Continuous feedback loops ensured educational goals and professional standards were met

### **AI as Tool Philosophy**
**AI is a tool, nothing more.** It is through the deliberate use of this tool that we are able to understand its strengths and limitations. In this course development:
- **AI Strengths**: Pattern recognition, systematic implementation, comprehensive documentation generation
- **AI Limitations**: No pedagogical judgment, no domain expertise, no understanding of student needs, tendency to over-generate content and create distractions from core objectives
- **Human Control**: All educational decisions, quality standards, and learning outcomes remained under human direction

This approach demonstrates how thoughtful AI integration can enhance educational resource development while maintaining the human expertise essential for effective teaching.

## 🤝 Contributing

This is a course repository. For corrections or suggestions:
1. Open an issue describing the improvement
2. Submit pull requests for fixes

## 📄 License

Educational materials for academic use. Based on "C++ Crash Course" by Josh Lospinoso.

## 🔗 Resources

- [C++ Reference](https://en.cppreference.com/)
- [Book: C++ Crash Course](https://cppcrash.com/)
- [Docker Documentation](https://docs.docker.com/)
- [CMake Documentation](https://cmake.org/documentation/)

---

**Course Version**: Fall 2025
**Last Updated**: December 2024