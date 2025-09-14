# Linux Setup Guide - CSCI 330

**Total Time:** 10-20 minutes  
**Read only this guide** - Windows and Mac users have their own

---

## Before You Start

**You'll need:**
- Any Linux distribution (Ubuntu, Fedora, Arch, etc.)
- Sudo access (admin privileges)
- Stable internet connection
- Your GitHub account

**What we're installing:**
1. Docker (container platform)
2. VSCode (code editor)
3. Build tools (if not already installed)

**Lucky you!** Linux setup is the easiest since you're already using a developer OS.

---

## Step 1: Install Docker (5 minutes)

**What it does:** Creates consistent C++ environment for everyone

### Ubuntu/Debian users (most common):
Copy and paste this entire block in terminal:
```bash
sudo apt update
sudo apt install docker.io docker-compose build-essential cmake git curl
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker $USER
```

### Fedora/RHEL users:
```bash
sudo dnf install docker docker-compose gcc-c++ cmake git
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker $USER
```

### Arch/Manjaro users:
```bash
sudo pacman -S docker docker-compose base-devel cmake git
sudo systemctl start docker
sudo systemctl enable docker  
sudo usermod -aG docker $USER
```

### For ALL distributions:
**IMPORTANT:** After running your commands above, type:
```bash
newgrp docker
```
(This lets you use Docker without sudo)

**Verify it worked:**
```bash
docker --version
```

✅ **Success looks like:** "Docker version 20.x.x" (any number is fine)

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"Permission denied" when running docker**
```bash
sudo usermod -aG docker $USER
newgrp docker
```

**"Cannot connect to Docker daemon"**
```bash
sudo systemctl start docker
sudo systemctl enable docker
```

**Package names don't work**
- Different distributions use different names
- Try: `docker-ce` instead of `docker`
- Or: `docker-engine` instead of `docker.io`
</details>

---

## Step 2: Install VSCode (3 minutes)

**What it does:** Your code editor that connects to Docker

### Option A: Using Snap (works everywhere):
```bash
sudo snap install code --classic
```

### Option B: Direct download:
1. Go to: https://code.visualstudio.com
2. Click "Download for Linux"
3. Choose your package type:
   - Ubuntu/Debian: Download .deb file
   - Fedora/RHEL: Download .rpm file

4. Install it:
   ```bash
   # For .deb files:
   sudo dpkg -i code*.deb
   
   # For .rpm files:
   sudo rpm -i code*.rpm
   ```

### Add extensions:
1. **Start VSCode:**
   ```bash
   code
   ```

2. **Install extensions** (press Ctrl+Shift+X):
   - Search and install these:
     - C/C++ Extension Pack (by Microsoft)
     - Dev Containers (by Microsoft)  
     - Docker (by Microsoft)

3. **Verify it worked:**
   ```bash
   code --version
   ```

✅ **Success looks like:** Shows version number

---

## Step 3: Get Course Files (3 minutes)

**What it does:** Downloads course materials to your computer

### Do this:
1. **Set up Git** (use YOUR actual name and email):
   ```bash
   git config --global user.name "Your Actual Name"
   git config --global user.email "your.email@university.edu"
   ```

2. **Fork the course repository**
   - Go to: https://github.com/INSTRUCTOR_USERNAME/cpp
   - Click "Fork" button (top right)
   - Wait for it to copy
   - You now have your own copy!

3. **Download your fork**
   Copy/paste these lines one at a time:
   
   Go to Desktop:
   ```bash
   cd ~/Desktop
   ```
   
   Clone (replace YOUR_USERNAME with your GitHub username):
   ```bash
   git clone https://github.com/YOUR_USERNAME/cpp.git
   ```
   
   Enter the folder:
   ```bash
   cd cpp
   ```

4. **Connect to course updates:**
   ```bash
   git remote add upstream https://github.com/INSTRUCTOR_USERNAME/cpp.git
   ```

5. **Verify it worked:**
   ```bash
   git remote -v
   ```
   
   ✅ **Success looks like:** Shows 4 lines with "origin" and "upstream"

---

## Step 4: Build Your Environment (5 minutes)

**What it does:** Creates your C++ development container

### Do this:
1. **Make sure you're in the right place:**
   ```bash
   cd ~/Desktop/cpp
   ```

2. **Build the container** (takes 3-5 minutes - be patient!):
   ```bash
   docker-compose build
   ```
   - You'll see lots of text scrolling - that's normal
   - Perfect time for a coffee break

3. **Test it:**
   ```bash
   docker run --rm cpp-course:latest g++ --version
   ```
   
   ✅ **Success looks like:** "g++ (GCC) 11.x.x"

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"Permission denied"**
```bash
groups | grep docker
```
If you don't see "docker" in the output:
```bash
sudo usermod -aG docker $USER
newgrp docker
```

**"docker-compose: command not found"**
```bash
# Ubuntu/Debian:
sudo apt install docker-compose

# Fedora:
sudo dnf install docker-compose
```

**Build fails**
```bash
sudo systemctl status docker
```
If docker isn't running:
```bash
sudo systemctl start docker
```
</details>

---

## Step 5: Connect VSCode to Docker (5 minutes)

**What it does:** Makes VSCode use your container automatically

### Do this:
1. **Open your project:**
   ```bash
   cd ~/Desktop/cpp
   code .
   ```
   (The dot is important!)

2. **Create config folder:**
   In VSCode:
   - Look at left sidebar (file explorer)
   - Right-click in empty area
   - Click "New Folder"
   - Name it: `.vscode` (with the dot!)

3. **Create config file:**
   - Right-click the `.vscode` folder  
   - Click "New File"
   - Name it: `devcontainer.json`
   - Copy and paste this EXACTLY:
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
   - Save with Ctrl+S

4. **Start the container:**
   - Press F1 (or Ctrl+Shift+P)
   - Type: reopen in container
   - Click "Dev Containers: Reopen in Container"
   - First time takes 2-3 minutes - be patient!

5. **Test everything:**
   When VSCode reloads:
   - Look at bottom left - should say "Dev Container: C++ Development"
   - Click Terminal → New Terminal (or press Ctrl+`)
   - In the terminal, type:
   ```bash
   g++ --version
   ```
   
   ✅ **Success looks like:** Terminal shows "g++ (GCC) 11.x.x"

6. **Run your first program:**
   In the VSCode terminal, copy/paste:
   ```bash
   echo '#include <iostream>
   int main() { std::cout << "Setup complete!\\n"; }' > test.cpp
   ```
   
   Then compile:
   ```bash
   g++ test.cpp -o test
   ```
   
   Then run:
   ```bash
   ./test
   ```
   
   ✅ **Success looks like:** "Setup complete!"

---

## You're Done! 🎉

### Daily routine (20 seconds):
1. Open terminal
2. Type: `cd ~/Desktop/cpp && code .`
3. Press F1 → type "reopen" → select "Reopen in Container"
4. Start coding!

### Quick Reference:

| I want to... | Where? | Command/Action |
|-------------|--------|---------------|
| Write code | VSCode | Just type! |
| Compile code | VSCode Terminal | `g++ myfile.cpp -o myprogram` |
| Run program | VSCode Terminal | `./myprogram` |
| Save work | VSCode | Ctrl+S |
| Submit homework | System Terminal | `git add .` then `git commit -m "Done"` then `git push` |

### Which terminal do I use?
- **System Terminal**: Git commands, opening projects, Docker management
- **VSCode Terminal**: ALL C++ work (compiling, running)
- Easy way to remember: If VSCode is open, use its terminal

---

## Common Problems & Solutions

### "It's not working!"

1. **First, always try:**
   ```bash
   sudo systemctl status docker
   ```
   If not running:
   ```bash
   sudo systemctl start docker
   ```

2. **VSCode can't find container:**
   - Delete the `.vscode` folder
   - Recreate it following Step 5

3. **Permission denied errors:**
   ```bash
   groups | grep docker
   ```
   If "docker" not shown:
   ```bash
   sudo usermod -aG docker $USER
   newgrp docker
   ```

4. **Firewall blocking Docker:**
   ```bash
   # Ubuntu/Debian:
   sudo ufw allow from 172.17.0.0/16
   
   # Fedora:
   sudo firewall-cmd --zone=trusted --add-interface=docker0
   ```

5. **SELinux issues (Fedora/RHEL):**
   ```bash
   sudo setenforce 0
   ```

6. **Can't push to GitHub:**
   - GitHub now requires tokens instead of passwords
   - Go to GitHub → Settings → Personal Access Tokens
   - Generate one and use it as your password

### Still stuck?
- Take a screenshot of the error
- Note which step you're on
- Include your Linux distribution and version
- Ask in office hours or Discord/Forum

---

## Why Linux Users Have It Easy

You picked the right OS for development! Here's why your setup was simpler:
- Docker runs natively (no virtualization layer)
- Package managers handle dependencies automatically
- Terminal is your friend, not your enemy
- Everything "just works" the way it's supposed to

**Remember:** This seems like a lot, but you only do it once! Daily use takes 20 seconds.