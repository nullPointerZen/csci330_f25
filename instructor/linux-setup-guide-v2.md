# Linux Setup Guide – CSCI 330

**Time Required:** 10–20 minutes  
**Note:** This guide is for Linux users only (Ubuntu, Fedora, Arch, etc.). Windows and Mac have their own setup instructions.

---

## Before You Start

**You'll need:**
- A Linux system with sudo (admin) access
- A stable internet connection
- A GitHub account

**We will install:**
- Docker (to ensure the same environment for everyone)
- VSCode (your editor)
- Build tools (compilers, cmake, git, etc.)

---

## Step 1: Install Docker (5 minutes)

Docker gives us a consistent C++ setup.

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install docker.io docker-compose build-essential cmake git curl
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker $USER
```

### Fedora/RHEL
```bash
sudo dnf install docker docker-compose gcc-c++ cmake git
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker $USER
```

### Arch/Manjaro
```bash
sudo pacman -S docker docker-compose base-devel cmake git
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker $USER
```

### Final step for everyone:
```bash
newgrp docker
docker --version
```

✅ **Success:** You see something like `Docker version 20.x.x`

---

## Step 2: Install VSCode (3 minutes)

VSCode is your code editor.

### Option A (recommended – easiest):
```bash
sudo snap install code --classic
```

### Option B (manual download):
1. Go to https://code.visualstudio.com
2. Download the package for your distribution (.deb or .rpm)
3. Install it:
   ```bash
   # For .deb
   sudo dpkg -i code*.deb
   
   # For .rpm
   sudo rpm -i code*.rpm
   ```

### Add Extensions
Open VSCode and install:
- C/C++ Extension Pack (by Microsoft)
- Dev Containers (by Microsoft)
- Docker (by Microsoft)

Check installation:
```bash
code --version
```

✅ **Success:** VSCode shows a version number

---

## Step 3: Get Course Files (3 minutes)

We'll download the class repository from GitHub.

1. **Configure Git with your name and email:**
   ```bash
   git config --global user.name "Your Name"
   git config --global user.email "your.email@university.edu"
   ```

2. **Fork the course repo on GitHub** (click "Fork" on the top right).

3. **Clone your fork:**
   ```bash
   cd ~/Desktop
   git clone https://github.com/YOUR_USERNAME/cpp.git
   cd cpp
   ```

4. **Connect to the instructor's repo (for updates):**
   ```bash
   git remote add upstream https://github.com/INSTRUCTOR_USERNAME/cpp.git
   ```

5. **Verify:**
   ```bash
   git remote -v
   ```

✅ **Success:** You see `origin` (your fork) and `upstream` (course repo)

---

## Step 4: Build Your Development Container (5 minutes)

This creates your C++ environment.

```bash
cd ~/Desktop/cpp
docker-compose build
docker run --rm cpp-course:latest g++ --version
```

✅ **Success:** You see `g++ (GCC) 11.x.x`

---

## Step 5: Connect VSCode to Docker (5 minutes)

This step makes VSCode use the container automatically.

1. **Open your project:**
   ```bash
   cd ~/Desktop/cpp
   code .
   ```

2. **Create `.vscode/devcontainer.json` with this content:**
   ```json
   {
     "name": "C++ Development",
     "dockerComposeFile": "../docker-compose.yml",
     "service": "cpp-dev",
     "workspaceFolder": "/workspace",
     "extensions": [
       "ms-vscode.cpptools-extension-pack"
     ]
   }
   ```

3. **In VSCode, press F1 → "Reopen in Container"**  
   (first time takes a few minutes)

4. **Test:**
   ```bash
   g++ --version
   ```

✅ **Success:** `g++ (GCC) 11.x.x`

5. **Quick test program:**
   ```bash
   echo '#include <iostream>
   int main(){std::cout<<"Setup complete!\\n";}' > test.cpp
   g++ test.cpp -o test
   ./test
   ```

✅ **Success:** Prints `Setup complete!`

---

## Daily Use

1. Open terminal
2. Run:
   ```bash
   cd ~/Desktop/cpp && code .
   ```
3. In VSCode: F1 → Reopen in Container
4. Start coding!

---

## Quick Reference

| Action | Where | Command |
|--------|-------|---------|
| Write code | VSCode | Just type |
| Compile | VSCode terminal | `g++ myfile.cpp -o myprogram` |
| Run | VSCode terminal | `./myprogram` |
| Save | VSCode | Ctrl+S |
| Submit | System terminal | `git add . && git commit -m "Done" && git push` |

---

## Troubleshooting (Common Issues)

**Permission denied** → Add yourself to docker group again:
```bash
sudo usermod -aG docker $USER
newgrp docker
```

**Docker not running:**
```bash
sudo systemctl start docker
```

**VSCode won't connect** → Delete `.vscode` folder and redo Step 5

**GitHub push fails** → Use a Personal Access Token instead of a password

---

## Why Linux is the Easiest

- Docker runs natively (no virtualization layer)
- Package managers handle dependencies
- Terminal commands just work