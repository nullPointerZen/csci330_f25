# Chapter 1: Complete Development Setup Guide

## Quick Start Options

Choose your development approach based on your needs:

| Approach | Best For | Setup Time |
|----------|----------|------------|
| **Docker + VS Code** (Recommended) | Most students | 20 min |
| **Docker Only** | Command-line users | 10 min |
| **Local Setup** | Quick start, offline work | 15 min |

---

## Option 1: Docker + VS Code (Recommended)

### Step 1: Install Docker

#### Windows 10/11:
1. Download [Docker Desktop](https://docker.com)
2. Install with default settings
3. **Important**: Enable WSL2 backend when prompted
4. Restart if required
5. **Start Docker Desktop**: Click the Docker Desktop icon from Start Menu or Desktop
6. Wait for Docker icon in system tray to show "Docker Desktop is running"
7. Verify: Open PowerShell, run `docker --version`

#### macOS:
1. Download [Docker Desktop](https://docker.com)
2. Drag Docker.app to Applications
3. **Start Docker Desktop**: Open Docker from Applications folder (Finder → Applications → Docker)
4. Accept terms when prompted
5. Wait for Docker icon in menu bar to show "Docker Desktop is running"
6. Verify: Open Terminal, run `docker --version`

#### Linux (Ubuntu/Debian):
```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo usermod -aG docker $USER
newgrp docker
docker --version
```

### Step 2: Install VS Code
1. Download from [code.visualstudio.com](https://code.visualstudio.com)
2. Install these extensions:
   - C/C++ (Microsoft)
   - Remote Development (Microsoft)

### Step 3: Clone Course Repository
```bash
git clone https://github.com/YOUR_INSTRUCTOR/csci330_f25.git
cd csci330_f25
```

### Step 4: Open in Container
1. Open VS Code: `code .`
2. When prompted, click "Reopen in Container"
3. Wait for container to build (first time only)

### Step 5: Start Coding
```bash
# In VS Code terminal (Ctrl+`)
cd assignment-templates/HW_01
mkdir -p build && cd build
cmake ..
make
./hello_world
```

---

## Option 2: Docker Command Line Only

### Step 1: Install Docker
Follow Docker installation from Option 1 above.

### Step 2: Get Course Repository
```bash
git clone https://github.com/YOUR_INSTRUCTOR/csci330_f25.git
cd csci330_f25
```

### Step 3: Start Development Environment
```bash
docker-compose up -d cpp-dev
docker-compose exec cpp-dev bash
```

### Step 4: Development Workflow
```bash
# Navigate to assignment
cd assignment-templates/HW_01

# Edit with nano or vim
nano src/main.cpp

# Build and run
mkdir -p build && cd build
cmake .. && make
./hello_world

# Run tests
make test
```

---

## Option 3: Local Development Setup

### Windows Setup
1. Install MinGW-w64 from [mingw-w64.org](https://www.mingw-w64.org/)
2. Add `C:\mingw64\bin` to PATH
3. Install VS Code with C/C++ extension
4. Verify: `g++ --version`

### macOS Setup
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Or via Homebrew
brew install gcc cmake
```

### Linux Setup
```bash
sudo apt update
sudo apt install build-essential cmake gdb
```

### VS Code Configuration
Create `.vscode/tasks.json` in your project:
```json
{
  "version": "2.0.0",
  "tasks": [{
    "type": "cppbuild",
    "label": "Build active file",
    "command": "g++",
    "args": ["-std=c++17", "-g", "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}"],
    "group": {"kind": "build", "isDefault": true}
  }]
}
```

---

## CMake Build System

All assignments use CMake for consistent builds across platforms.

### Basic Workflow
```bash
# Configure (once per project)
mkdir -p build && cd build
cmake ..

# Build (after code changes)
make

# Run program
./program_name

# Run tests
make test
```

### Project Structure
```
HW_01/
├── CMakeLists.txt    # Build configuration
├── src/              # Source code
│   └── main.cpp
├── tests/            # Unit tests
│   └── test_main.cpp
└── build/            # Build output (don't commit)
```

---

## GitHub Assignment Workflow

### Step 1: Fork Assignment
1. Go to assignment repository (instructor provides link)
2. Click "Fork" button
3. Your fork: `github.com/YOUR_USERNAME/HW_01`

### Step 2: Clone and Work
```bash
git clone https://github.com/YOUR_USERNAME/HW_01.git
cd HW_01
# Start Docker or open in VS Code
```

### Step 3: Commit Changes
```bash
git add src/main.cpp
git commit -m "Implement hello world functionality"
git push origin main
```

### Step 4: Submit Pull Request
1. Go to your fork on GitHub
2. Click "Pull Request" → "New Pull Request"
3. Write clear description of what you implemented
4. Submit for grading

---

## Essential Commands Reference

### Docker Commands
```bash
docker-compose up -d cpp-dev      # Start container
docker-compose exec cpp-dev bash  # Enter container
docker-compose down               # Stop container
exit                             # Leave container (doesn't stop it)
```

### Build Commands
```bash
cmake ..        # Configure build
make           # Compile program
make test      # Run unit tests
make clean     # Clean build files
```

### Git Commands
```bash
git status                    # Check changes
git add <file>               # Stage changes
git commit -m "message"      # Save changes
git push origin main         # Upload to GitHub
```

### VS Code Shortcuts
| Action | Windows/Linux | macOS |
|--------|--------------|-------|
| Terminal | Ctrl+` | Cmd+` |
| Build | Ctrl+Shift+B | Cmd+Shift+B |
| Debug | F5 | F5 |
| Command Palette | Ctrl+Shift+P | Cmd+Shift+P |

---

## Debugging

### Command Line (gdb)
```bash
gdb ./program
(gdb) break main
(gdb) run
(gdb) next
(gdb) print variable_name
(gdb) quit
```

### VS Code
1. Click left of line number to set breakpoint
2. Press F5 to start debugging
3. Use debug controls:
   - F10: Step Over
   - F11: Step Into
   - Shift+F11: Step Out

---

## Troubleshooting

### Docker Desktop Not Running?
**Windows**: 
- Click Start Menu → Docker Desktop
- Look for whale icon in system tray (bottom-right)
- Right-click icon → "Dashboard" to see status

**macOS**:
- Open Finder → Applications → Docker
- Look for whale icon in menu bar (top-right)
- Click icon to see status

**Both**: Docker Desktop must show "Running" before using terminal commands

### Docker Issues
```bash
# Container won't start
docker-compose down
docker-compose up -d cpp-dev

# Permission denied
sudo usermod -aG docker $USER  # Linux only
newgrp docker
```

### Build Issues
```bash
# CMake errors
rm -rf build/*
cmake ..
make

# Executable not found
chmod +x program_name  # Make executable
```

### VS Code Issues
- Reload window: Ctrl+Shift+P → "Developer: Reload Window"
- Reset IntelliSense: Ctrl+Shift+P → "C/C++: Reset IntelliSense Database"

---

## Pre-Submission Checklist

Before submitting any assignment:

- [ ] Code compiles without errors
- [ ] Program runs correctly
- [ ] All unit tests pass
- [ ] Code is properly formatted
- [ ] Changes are committed and pushed
- [ ] Pull request created with clear description

---

## Quick Help

**Can't compile?**
```bash
# Check you're in build directory
pwd  # Should show .../build
# Reconfigure if needed
cmake .. && make
```

**Can't find files?**
```bash
# Check current directory
ls -la
# Navigate to assignment
cd assignment-templates/HW_01
```

**Tests failing?**
```bash
# Run verbose tests
ctest --verbose
# Check test requirements in assignment description
```

**Ready to start Chapter 1 with professional tools!** 🚀