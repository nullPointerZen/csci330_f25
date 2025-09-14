# Understanding Your Development Environment

This guide explains how your C++ development environment works and why we use containers.

## Why Containers? The "Write Once, Run Anywhere" Problem

### The Problem Without Containers
Every student has different hardware and software:
- Windows 11 vs Windows 10 vs macOS vs Linux
- Different C++ compiler versions
- Different library installations
- Different system configurations

**Result:** Code that works perfectly on your computer might fail on your classmate's or the grading server.

### The Container Solution
Docker provides an identical Linux environment for everyone:
- Same Ubuntu version
- Same g++ compiler (version 11)
- Same libraries and tools
- Same file system structure

**Result:** If your code works in the container, it works everywhere.

## How Containers Work

### Container vs Virtual Machine
- **Virtual Machine:** Full operating system, heavy (10+ GB), slow to start
- **Container:** Shares host OS kernel, lightweight (< 1 GB), starts in seconds

### File Sharing: The Volume Mount

Your files exist in parallel:
```
Your Computer                    Docker Container
-------------                    ----------------
C:\Users\You\cpp         <--->   /home/student/workspace
(or /Users/You/cpp)              (Linux path inside container)
```

**The Magic:** Docker automatically syncs these locations. Edit anywhere, changes appear everywhere.

## Command Explanations

### Understanding Command Flags

```bash
# Command Breakdown: mkdir -p build
mkdir     # Make directory command
-p        # Create parent directories if needed
build     # The directory name to create

# Without -p: mkdir fails if parent doesn't exist
# With -p: creates entire path as needed
```

```bash
# Command Breakdown: docker run --rm cpp-course:latest g++ --version
docker run          # Run a command in container
--rm               # Remove container after it exits (cleanup)
cpp-course:latest  # The image to use
g++ --version      # The command to run inside container
```

```bash
# Command Breakdown: git add .
git       # Version control system
add       # Stage changes for commit
.         # Current directory (all files)
```

## Path Navigation

### Understanding Paths

```bash
# Absolute paths (start from root)
/home/student/workspace     # Linux style
C:\Users\YourName\cpp      # Windows style

# Relative paths (from current location)
./file.cpp                 # File in current directory
../parent                  # Go up one directory
../../grandparent         # Go up two directories
```

### Special Path Symbols
- `.` = Current directory
- `..` = Parent directory
- `~` = Home directory (Linux/Mac)
- `/` = Root directory (Linux/Mac) or path separator
- `\` = Path separator (Windows only)

## Git Workflow Concepts

### Repository Structure
```
Remote (GitHub)
├── upstream (course repo) - Instructor's version
└── origin (your fork)     - Your copy

Local (Your Computer)
└── cpp (cloned repo)      - Working copy
```

### Git Terms Explained
- **Repository (repo):** A folder tracked by Git
- **Fork:** Your personal copy of someone else's repository
- **Clone:** Download a repository to your computer
- **Commit:** Save a snapshot of your changes
- **Branch:** An independent line of development
- **Push:** Upload commits to remote repository
- **Pull:** Download commits from remote repository
- **Pull Request:** Request to merge your changes into another repository

### Basic Git Workflow
1. **Create branch** for your work
2. **Make changes** to files
3. **Stage changes** with `git add`
4. **Commit changes** with `git commit`
5. **Push branch** to GitHub
6. **Create Pull Request** for submission

## Terminal Types and When to Use Them

### Windows Users
- **PowerShell (Admin):** For system changes (WSL install)
- **Command Prompt:** For basic Windows commands
- **WSL2 Terminal:** For Linux commands outside Docker
- **VSCode Terminal (in container):** For all C++ development

### macOS Users
- **Terminal.app:** For system commands and Git
- **VSCode Terminal (in container):** For all C++ development

### Linux Users
- **System Terminal:** For system commands and Git
- **VSCode Terminal (in container):** For all C++ development

## Building C++ Code

### The Build Process
```
Source Code (.cpp) → Compiler (g++) → Executable Program
```

### Using CMake (for larger projects)
```bash
mkdir build     # Create build directory
cd build       # Enter build directory
cmake ..       # Configure project (.. means parent directory)
make          # Build the project
./program     # Run the executable
```

### Direct Compilation (for simple programs)
```bash
g++ main.cpp -o program    # Compile main.cpp into program
./program                  # Run the program
```

## Container Entry Methods

### Method 1: VSCode Dev Containers (Recommended)
- **When:** Daily development work
- **How:** "Reopen in Container" in VSCode
- **Why:** Full IDE features, integrated terminal

### Method 2: Docker Compose Run
- **When:** Quick compilation or testing
- **How:** `docker-compose run cpp-dev`
- **Why:** No VSCode needed, quick access

### Method 3: Docker Exec
- **When:** Container already running
- **How:** `docker exec -it csci330_f25-cpp-dev bash`
- **Why:** Connect to existing container session

## File Organization

### Course Structure
```
cpp/
├── docker-compose.yml           # Container configuration
├── .vscode/
│   └── devcontainer.json       # VSCode container settings
├── csci330_f25/
│   ├── setup/                  # Setup files and Dockerfile
│   ├── modules/                # Course materials
│   └── assignments/
│       └── CSCI330_YourName/   # Your work goes here
└── .git/                       # Git tracking (hidden)
```

### Assignment Structure
```
CSCI330_YourName/
├── week01/
│   ├── src/          # Source code
│   ├── include/      # Header files
│   ├── build/        # Compiled files (git-ignored)
│   └── CMakeLists.txt
└── week02/
    └── ...
```

## Daily Workflow Summary

1. **Start your day:**
   - Open Docker Desktop
   - Open VSCode
   - Reopen in Container

2. **Work on assignment:**
   - Create/switch to feature branch
   - Write code
   - Build and test frequently
   - Commit changes regularly

3. **Submit work:**
   - Push to GitHub
   - Create Pull Request
   - Address feedback

4. **End your day:**
   - Commit any remaining changes
   - Push to GitHub
   - Close VSCode (container stops automatically)

## Key Concepts to Remember

1. **Containers ensure consistency** - Everyone has identical environment
2. **Files are shared** - Edit locally, compile in container
3. **Git tracks everything** - Commit early and often
4. **Branches isolate work** - One branch per assignment
5. **Pull Requests submit work** - Professional workflow

---
**Need help with problems?** See the Troubleshooting Guide  
**Ready to code?** You understand the fundamentals!