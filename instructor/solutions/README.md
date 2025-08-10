# Instructor Solutions - CSCI 330

## Academic Integrity Policy

All solution files are contained in this instructor-only directory to maintain academic integrity. Solutions are **released on assignment due dates** only.

## Solution Release Schedule

### Core Chapter Solutions
- **chapter_01_solutions/**: Released after Week 1 assignment due
- **chapter_02_solutions/**: Released after Week 2 assignment due
- **chapter_03_solutions/**: Released after Week 3 assignment due
- **chapter_04_solutions/**: Released after Week 4 assignment due
- **chapter_05_solutions/**: Released after Week 5 assignment due
- **chapter_06_solutions/**: Released after Week 6 assignment due
- **chapter_07_solutions/**: Released after Week 7 assignment due
- **chapter_08_solutions/**: Released after Week 8 assignment due
- **chapter_09_solutions/**: Released after Week 9 assignment due
- **chapter_11_solutions/**: Released after Week 11 assignment due
- **chapter_12_solutions/**: Released after Week 12 assignment due
- **chapter_13_solutions/**: Released after Week 13 assignment due
- **chapter_14_solutions/**: Released after Week 14 assignment due
- **chapter_15_solutions/**: Released after Week 15 assignment due

### Supplemental Chapter Solutions
Located in `supplemental-chapters/`:
- **chapter_10_solutions/**: Testing frameworks
- **chapter_16_solutions/**: Streams and I/O
- **chapter_17_solutions/**: Filesystem operations
- **chapter_18_solutions/**: STL algorithms

## Release Process

### Option 1: Selective Release (Recommended)
Copy individual solution files to student-accessible locations only after due dates:
```bash
# After Chapter 1 due date
cp instructor/solutions/chapter_01_solutions/* csci330_f25/chapter_01_solutions/
```

### Option 2: Branch-Based Release
Use separate Git branches for solution distribution:
- `main` branch: Student-accessible content (no solutions)
- `solutions-chapter-01` branch: Chapter 1 solutions released after due date
- `solutions-chapter-02` branch: Chapter 2 solutions released after due date

### Option 3: Timing-Based Access
Use Git hooks or automated systems to make solutions visible only after assignment deadlines.

## Directory Structure

```
instructor/solutions/
├── README.md                    # This file
├── chapter_01_solutions/        # Up and Running
├── chapter_02_solutions/        # Types and Memory
├── chapter_03_solutions/        # References
├── chapter_04_solutions/        # Object Lifecycle
├── chapter_05_solutions/        # Runtime Polymorphism
├── chapter_06_solutions/        # Compile-Time Polymorphism
├── chapter_07_solutions/        # Expressions
├── chapter_08_solutions/        # Statements
├── chapter_09_solutions/        # Functions
├── chapter_11_solutions/        # Smart Pointers
├── chapter_12_solutions/        # Utilities
├── chapter_13_solutions/        # Containers
├── chapter_14_solutions/        # Iterators
├── chapter_15_solutions/        # Strings
└── supplemental-chapters/       # Optional chapters
    ├── chapter_10_solutions/    # Testing
    ├── chapter_16_solutions/    # Streams
    ├── chapter_17_solutions/    # Filesystems
    └── chapter_18_solutions/    # Algorithms
```

## Important Notes

⚠️ **Keep Solutions Secure**: Never commit solutions to branches accessible by students before due dates.

✅ **Educational Use**: Solutions are for instructor reference and post-deadline student learning.

📅 **Timing Matters**: Early release of solutions undermines the learning process and assessment validity.

🔒 **Access Control**: Ensure proper repository permissions prevent student access to this directory.

---

**Course**: CSCI 330 - Advanced C++ Programming  
**Academic Year**: Fall 2025