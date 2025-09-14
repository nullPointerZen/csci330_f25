# Quick Start Guide - CSCI 330 Development Setup

**Time Required:** 30-45 minutes  
**Goal:** Get your C++ development environment running

## Step 1: Install Required Software

### Windows
1. **Enable WSL2**: Open PowerShell as Administrator → Run `wsl --install` → Restart
2. **Install Docker Desktop**: Download from [docker.com](https://docker.com) → Use WSL2 option
3. **Install Git**: Download from [git-scm.com](https://git-scm.com)
4. **Install VSCode**: Download from [code.visualstudio.com](https://code.visualstudio.com)

### macOS
1. **Install Docker Desktop**: Download from [docker.com](https://docker.com)
   - M1/M2/M3 Macs: Choose "Apple Silicon" version
   - Intel Macs: Choose "Intel" version
2. **Install Git**: Run `xcode-select --install` in Terminal
3. **Install VSCode**: Download from [code.visualstudio.com](https://code.visualstudio.com)

### Linux (Ubuntu/Debian)
```bash
# Install Docker
sudo apt update
sudo apt install docker.io docker-compose
sudo systemctl start docker
sudo usermod -aG docker $USER
# Log out and back in for group changes

# Install Git and build tools
sudo apt install git build-essential cmake

# Install VSCode
sudo snap install code --classic
```

### Verification Checkpoint 1
```bash
docker --version  # Should show Docker version
git --version     # Should show Git version
code --version    # Should show VSCode version
```

## Step 2: Get Course Repository

```bash
# Configure Git (use your real name and email)
git config --global user.name "Your Name"
git config --global user.email "your.email@university.edu"

# Fork the course repo on GitHub first, then:
git clone https://github.com/YOUR_USERNAME/cpp.git
cd cpp

# Connect to course repository
git remote add upstream https://github.com/INSTRUCTOR_USERNAME/cpp.git
```

### Verification Checkpoint 2
```bash
git remote -v  # Should show both 'origin' and 'upstream'
```

## Step 3: Build Docker Environment

```bash
# In the cpp directory (where docker-compose.yml is located)
docker-compose build  # This takes 5-10 minutes first time
```

### Verification Checkpoint 3
```bash
docker run --rm cpp-course:latest g++ --version  # Should show g++ version
```

## Step 4: Install VSCode Extensions

Open VSCode and install (Ctrl/Cmd+Shift+X):
- C/C++ Extension Pack
- Dev Containers
- Docker
- GitLens

## Step 5: Create VSCode Configuration

Create `.vscode/devcontainer.json` in your cpp folder:
```json
{
  "name": "C++ Development",
  "dockerComposeFile": "../docker-compose.yml",
  "service": "cpp-dev",
  "workspaceFolder": "/workspace",
  "extensions": [
    "ms-vscode.cpptools-extension-pack",
    "ms-vscode.cmake-tools"
  ]
}
```

## Step 6: Start Development Environment

1. Open VSCode
2. Open your cpp folder
3. Press Ctrl/Cmd+Shift+P → Type "Dev Containers: Reopen in Container"
4. Wait for container to start (faster after first time)

### Verification Checkpoint 4
In VSCode terminal (should be inside container):
```bash
pwd                    # Should show /workspace
g++ --version         # Should show g++ compiler
cmake --version       # Should show cmake version
```

## Step 7: Test Your Setup

```bash
# Create a test program
echo '#include <iostream>
int main() { std::cout << "Setup complete!" << std::endl; }' > test.cpp

# Compile and run
g++ test.cpp -o test
./test  # Should output: Setup complete!
```

## Quick Command Reference

| Task | Command |
|------|---------|
| Start container | In VSCode: "Reopen in Container" |
| Build C++ code | `g++ file.cpp -o program` |
| Run program | `./program` |
| Check Git status | `git status` |
| Create branch | `git checkout -b branch-name` |
| Save changes | `git add .` then `git commit -m "message"` |

## Success Checklist
- [ ] Docker installed and running
- [ ] Git configured with your name/email
- [ ] Course repository cloned
- [ ] Docker container builds successfully
- [ ] VSCode opens in container
- [ ] Test program compiles and runs

## Need Help?

- **Container won't start?** Make sure Docker Desktop is running
- **Permission errors?** Linux users: ensure you're in docker group
- **Can't find files?** Your files are in `/workspace` inside container
- **Other issues?** See Troubleshooting Guide or ask in office hours

---
**Next Steps:** Read "Understanding Your Development Environment" for details about how everything works together.