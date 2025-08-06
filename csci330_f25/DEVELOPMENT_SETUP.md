# Development Environment Setup Guide

## Overview

This guide will help you set up a professional C++ development environment using Docker, Git, and VSCode. By the end of this setup, you'll have a consistent development environment that works the same way regardless of whether you're using Windows, macOS, or Linux.

**What you'll learn to use:**
- **Docker**: Creates a consistent development environment in a "container"
- **Git**: Tracks changes to your code and enables collaboration
- **VSCode**: A powerful code editor that integrates with Docker and Git

---

## Part 1: Required Software Installation

### 1.1 Install Docker Desktop

Docker creates isolated environments called "containers" where your code runs consistently across different computers.

#### For Windows Users:

1. **Enable WSL2** (Windows Subsystem for Linux):
   - Open PowerShell as Administrator
   - Run: `wsl --install`
   - Restart your computer when prompted

2. **Download Docker Desktop**:
   - Go to [docker.com](https://docker.com)
   - Download "Docker Desktop for Windows"
   - During installation, ensure "Use WSL 2 instead of Hyper-V" is checked
   - Restart when prompted

3. **Configure Docker Desktop**:
   - Open Docker Desktop
   - Go to Settings → Resources → WSL Integration
   - Enable integration with your default WSL distro
   - Allocate at least 4GB of memory

#### For macOS Users:

1. **Download Docker Desktop**:
   - Go to [docker.com](https://docker.com)
   - Choose the correct version:
     - **Apple Silicon (M1/M2/M3 Macs)**: Docker Desktop for Apple Silicon
     - **Intel Macs**: Docker Desktop for Intel
   - Drag the app to your Applications folder

2. **Configure Docker Desktop**:
   - Launch Docker Desktop
   - Go to Preferences → Resources → Advanced
   - Allocate at least 4GB of memory
   - Grant necessary permissions when prompted

### 1.2 Install VSCode and Extensions

VSCode is a free, powerful code editor that will integrate with your Docker environment.

1. **Download VSCode**:
   - Go to [code.visualstudio.com](https://code.visualstudio.com)
   - Download for your operating system

2. **Install Required Extensions**: Open VSCode and install these extensions (Ctrl+Shift+X on Windows, Cmd+Shift+X on macOS):
   - **C/C++ Extension Pack** (includes everything you need for C++)
   - **Dev Containers** (for Docker integration)
   - **Docker** (for managing containers)
   - **GitLens** (enhances Git capabilities)

### 1.3 Install Git

Git tracks changes to your code and enables you to submit assignments.

#### For Windows Users:
- Download from [git-scm.com](https://git-scm.com)
- Use default installation options
- **Important**: Configure line endings by running this in Command Prompt:
  ```
  git config --global core.autocrlf input
  git config --global core.eol lf
  ```

#### For macOS Users:

**Option 1**: Install via Homebrew (if you have it):
```bash
brew install git
```

**Option 2**: Install Xcode Command Line Tools:
```bash
xcode-select --install
```

#### Configure Git (All Platforms):

Set up your identity (use your real name and school email):
```bash
git config --global user.name "Your Full Name"
git config --global user.email "your.email@university.edu"
```

---

## Part 2: Setting Up Your Development Environment

### 2.1 Download the Course Repository

Clone the course repository to your computer:

```bash
# Navigate to where you want to store your coursework
cd Desktop  # or wherever you prefer

# Clone the course repository
git clone https://github.com/DEmcla/csci330_f25.git
cd csci330_f25
```

### 2.2 Build Your Docker Environment

This creates your C++ development environment:

```bash
# Build the Docker container (this may take a few minutes the first time)
docker-compose build

# Test that it works
docker-compose run cpp-dev
```

If successful, you should see a Linux command prompt inside the container. Type `exit` to return to your normal terminal.

### 2.3 Set Up VSCode Integration

Create a folder called `.vscode` in your project directory and add this file:

**Create `.vscode/devcontainer.json`:**
```json
{
  "name": "C++ Development",
  "dockerComposeFile": "../docker-compose.yml",
  "service": "cpp-dev",
  "workspaceFolder": "/workspace",
  "extensions": [
    "ms-vscode.cpptools-extension-pack",
    "ms-vscode.cmake-tools"
  ],
  "settings": {
    "terminal.integrated.defaultProfile.linux": "bash"
  }
}
```

---

## Part 3: Your Daily Development Workflow

### 3.1 Starting Your Development Environment

1. **Open your project in VSCode**:
   - Open VSCode
   - File → Open Folder
   - Select your course directory

2. **Start the development container**:
   - Press `Ctrl+Shift+P` (Windows) or `Cmd+Shift+P` (macOS)
   - Type "Dev Containers: Reopen in Container"
   - Select it and wait for the container to start

3. **You're ready to code!**
   - The terminal inside VSCode is now running in your Docker container
   - All your C++ tools are ready to use

### 3.2 Building and Testing Your Code

Navigate to an assignment directory and build:

```bash
# Go to assignment directory
cd /workspace/assignments/chapter_01

# Create build directory
mkdir -p build && cd build

# Configure the project
cmake ..

# Build your code
make

# Run tests (if available)
ctest --verbose
```

### 3.3 Basic Git Workflow

Git helps you track changes and submit assignments. Here's the basic workflow:

**Understanding Git Concepts:**
- **Repository (repo)**: A folder that Git is tracking
- **Commit**: A snapshot of your code at a specific time
- **Branch**: A separate line of development
- **Push**: Upload your changes to GitHub/GitLab

**Daily Git Commands:**

1. **Check the status of your files**:
   ```bash
   git status
   ```

2. **Create a new branch for your assignment** (do this for each assignment):
   ```bash
   git checkout -b assignment-01
   ```

3. **Add your changes**:
   ```bash
   # Add specific files
   git add src/main.cpp
   
   # Or add all changed files
   git add .
   ```

4. **Commit your changes**:
   ```bash
   git commit -m "Implement basic calculator functions"
   ```

5. **Push your work to the remote repository**:
   ```bash
   git push origin assignment-01
   ```

---

## Part 4: Assignment Submission Process

### 4.1 Completing an Assignment

1. **Create a branch for the assignment**:
   ```bash
   git checkout -b assignment-01
   ```

2. **Work on your code in the Docker environment**:
   - Use VSCode with the Dev Container
   - Build and test frequently
   - Commit your changes regularly

3. **Final submission**:
   ```bash
   # Make sure all your work is saved
   git add .
   git commit -m "Complete assignment 01 - final submission"
   git push origin assignment-01
   ```

4. **Submit to Canvas**:
   - Copy your repository URL from GitHub/GitLab
   - Submit in this format:
     ```
     Repository URL: https://github.com/yourusername/cpp-assignment-01
     Branch: assignment-01
     Commit Hash: [copy from Git or GitHub]
     ```

### 4.2 Getting the Commit Hash

**Option 1: From command line:**
```bash
git log --oneline -1
```

**Option 2: From GitHub/GitLab:**
- Go to your repository online
- Click on the branch you pushed
- Copy the commit hash shown

---

## Part 5: Troubleshooting Common Issues

### 5.1 Docker Issues

#### Windows-Specific Problems:

**Docker Desktop won't start:**
- Make sure WSL2 is enabled
- Check that "Windows Subsystem for Linux" and "Virtual Machine Platform" are enabled in Windows Features
- Restart Docker Desktop

**Permission errors:**
```bash
# In WSL2 terminal
sudo chown -R $USER:$USER /path/to/your/project
```

#### macOS-Specific Problems:

**Docker needs permissions:**
- Go to System Preferences → Security & Privacy → Privacy
- Grant Docker Desktop access to your folders

**Performance issues:**
- Increase memory allocation in Docker Desktop settings
- Enable "Use gRPC FUSE for file sharing"

### 5.2 VSCode Issues

**Container won't start:**
- Make sure Docker Desktop is running
- Try "Dev Containers: Rebuild Container" from Command Palette
- If still having issues:
  ```bash
  docker-compose down -v
  docker system prune -af
  ```

**Code completion not working:**
- Make sure you're working inside the container
- Try reloading: "Developer: Reload Window" from Command Palette

### 5.3 Git Issues

**"Repository not found" error:**
- Check that you have access to the repository
- Make sure you're using the correct URL
- Verify your Git credentials

**Merge conflicts:**
- Always work in separate branches for each assignment
- Ask for help if you see conflict messages

**Large files causing problems:**
- Never commit build artifacts (files in `build/` folders)
- Check your `.gitignore` file includes:
  ```
  build/
  *.o
  *.exe
  *.out
  ```

---

## Part 6: Getting Help

### 6.1 When Things Don't Work

1. **Read error messages carefully** - they often tell you exactly what's wrong
2. **Check the troubleshooting section above**
3. **Ask classmates** - they might have encountered the same issue
4. **Search online** - include the specific error message in your search
5. **Ask your instructor** - provide the specific error message and what you were trying to do

### 6.2 Best Practices

- **Commit your work frequently** - at least after completing each function or major change
- **Use descriptive commit messages** - "Fix calculator bug" is better than "update"
- **Test your code before submitting** - make sure it compiles and runs
- **Keep your repository organized** - don't commit unnecessary files
- **Start assignments early** - setup issues are easier to resolve when you have time

---

## Quick Reference

### Essential Commands

**Docker:**
```bash
# Build your environment
docker-compose build

# Start development container
docker-compose run cpp-dev

# If on Windows and having issues, try:
docker-compose run --platform linux/amd64 cpp-dev
```

**Git:**
```bash
# Check status
git status

# Create new branch
git checkout -b assignment-name

# Add and commit changes
git add .
git commit -m "Descriptive message"

# Push to remote
git push origin assignment-name
```

**Building C++ Code:**
```bash
# In assignment directory
mkdir build && cd build
cmake ..
make
ctest --verbose  # run tests
```

**VSCode:**
- **Windows**: Ctrl+Shift+P opens Command Palette
- **macOS**: Cmd+Shift+P opens Command Palette
- Use "Dev Containers: Reopen in Container" to start development environment

---

## Summary

You now have a professional C++ development environment that:
- Works consistently across different computers
- Integrates modern development tools
- Prepares you for industry-standard workflows
- Makes assignment submission straightforward

Remember: the initial setup might feel overwhelming, but once configured, this environment will make your C++ development much smoother throughout the course!