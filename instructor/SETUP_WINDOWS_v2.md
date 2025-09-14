# Windows Setup Guide - CSCI 330

**Total Time:** 20-30 minutes  
**Read only this guide** - Mac and Linux users have their own

---

## Before You Start

**You'll need:**
- Windows 10 or 11
- Admin access to your computer
- Stable internet connection
- Your GitHub account

**What we're installing:**
1. WSL2 (Linux inside Windows)
2. Docker Desktop (container platform)
3. Git (version control)
4. VSCode (code editor)

---

## Step 1: Install WSL2 (5 minutes)

**What it does:** Runs Linux inside Windows so everyone has the same environment

### Do this:
1. **Open PowerShell as Administrator**
   - Press Windows key
   - Type "powershell"
   - Right-click "Windows PowerShell"
   - Click "Run as administrator"

2. **Install WSL2**
   ```
   wsl --install
   ```
   - Press Enter and wait
   - When it says "restart required", restart your computer

3. **After restart** (Ubuntu window will open)
   - Create a username (lowercase, no spaces)
   - Create a password (you won't see it typing - that's normal)
   - Write these down!

4. **Verify it worked**
   Open PowerShell (regular, not admin) and type:
   ```
   wsl --status
   ```
   
   ✅ **Success looks like:** "Default Version: 2"

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"WSL not recognized"**
```
wsl --install
```
If that doesn't work, restart and try again.

**Ubuntu didn't open after restart**
- Open Microsoft Store
- Search "Ubuntu"
- Click "Open"
</details>

---

## Step 2: Install Docker Desktop (5 minutes)

**What it does:** Creates consistent C++ environment for everyone

### Do this:
1. **Download Docker Desktop**
   - Go to: https://docker.com
   - Click the big blue "Download Docker Desktop" button
   - Save the file

2. **Install Docker**
   - Run the downloaded file
   - When asked, CHECK: "Use WSL 2 instead of Hyper-V"
   - Click OK for restart

3. **After restart**
   - Docker Desktop opens automatically
   - Wait for whale icon in system tray (bottom right)
   - If terms appear, just accept them

4. **Configure Docker**
   - Click whale icon → Settings
   - Click "Resources" → "WSL Integration"
   - Turn ON the toggle for "Ubuntu"
   - Click "Apply & restart"

5. **Verify it worked**
   Open PowerShell and type:
   ```
   docker --version
   ```
   
   ✅ **Success looks like:** "Docker version 24.x.x" (any number is fine)

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**Docker won't start**
- Restart your computer (really, this fixes 90% of issues)

**Still broken?**
- Uninstall Docker Desktop
- Restart computer
- Install again
</details>

---

## Step 3: Install Git and VSCode (5 minutes)

**What they do:** Git tracks your code, VSCode is where you write it

### Do this:

#### Part A: Install Git
1. **Download Git**
   - Go to: https://git-scm.com
   - Click "Download for Windows"
   - Run the installer
   - Click "Next" for EVERYTHING (use all defaults)

2. **Configure Git for Windows**
   Open PowerShell and copy/paste these lines (press Enter after each):
   ```
   git config --global core.autocrlf input
   ```
   ```
   git config --global core.eol lf
   ```

#### Part B: Install VSCode
1. **Download VSCode**
   - Go to: https://code.visualstudio.com
   - Click "Download for Windows"
   - Run installer (all defaults are fine)

2. **Add Extensions**
   - Open VSCode
   - Press `Ctrl+Shift+X` (holds Ctrl and Shift, tap X)
   - Search and install these one by one:
     - C/C++ Extension Pack (by Microsoft)
     - Dev Containers (by Microsoft)
     - Docker (by Microsoft)
   - Close VSCode when done

3. **Verify it worked**
   Open PowerShell and type:
   ```
   git --version
   ```
   
   ✅ **Success looks like:** "git version 2.x.x"

---

## Step 4: Get Course Files (5 minutes)

**What it does:** Downloads the course materials to your computer

### Do this:
1. **Set up Git** (use YOUR actual name and email)
   Open PowerShell and type these (replace the text in quotes):
   ```
   git config --global user.name "Your Actual Name"
   ```
   ```
   git config --global user.email "your.email@university.edu"
   ```

2. **Fork the course repository**
   - Go to: https://github.com/INSTRUCTOR_USERNAME/cpp
   - Click "Fork" button (top right)
   - Wait for it to copy
   - You now have your own copy!

3. **Download your fork**
   In PowerShell, copy/paste these lines one at a time:
   
   First, go to Desktop:
   ```
   cd Desktop
   ```
   
   Then clone (replace YOUR_USERNAME with your GitHub username):
   ```
   git clone https://github.com/YOUR_USERNAME/cpp.git
   ```
   
   Enter the folder:
   ```
   cd cpp
   ```

4. **Connect to course updates**
   ```
   git remote add upstream https://github.com/INSTRUCTOR_USERNAME/cpp.git
   ```

5. **Verify it worked**
   ```
   git remote -v
   ```
   
   ✅ **Success looks like:** Shows 4 lines with "origin" and "upstream"

---

## Step 5: Build Your Environment (5 minutes)

**What it does:** Creates your C++ development container

### Do this:
1. **Make sure you're in the right place**
   In PowerShell:
   ```
   cd Desktop\cpp
   ```

2. **Build the container** (this takes 3-5 minutes - be patient!)
   ```
   docker-compose build
   ```
   - You'll see lots of text scrolling - that's normal
   - Get coffee while it builds

3. **Test it**
   ```
   docker run --rm cpp-course:latest g++ --version
   ```
   
   ✅ **Success looks like:** "g++ (GCC) 11.x.x"

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"docker-compose not found"**
- Close PowerShell
- Open new PowerShell
- Try again

**"Cannot connect to Docker"**
- Check whale icon in system tray
- If not there, start Docker Desktop from Start Menu
</details>

---

## Step 6: Connect VSCode to Docker (5 minutes)

**What it does:** Makes VSCode use your container automatically

### Do this:
1. **Open VSCode**
   - Open VSCode from Start Menu
   - Click File → Open Folder
   - Navigate to Desktop → cpp
   - Click "Select Folder"

2. **Create config file**
   - In VSCode, press `Ctrl+Shift+E` (opens file explorer on left)
   - Right-click in file area
   - Click "New Folder"
   - Name it: `.vscode` (with the dot!)
   - Right-click the .vscode folder
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
   - Save with `Ctrl+S`

3. **Start the container**
   - Press `F1` (or `Ctrl+Shift+P`)
   - Type: reopen in container
   - Click "Dev Containers: Reopen in Container"
   - First time takes 2-3 minutes - be patient!

4. **Test everything**
   When VSCode reloads:
   - Look at bottom left - should say "Dev Container: C++ Development"
   - Click Terminal → New Terminal (or press `Ctrl+``)
   - In the terminal, type:
   ```
   g++ --version
   ```
   
   ✅ **Success looks like:** Terminal shows "g++ (GCC) 11.x.x"

5. **Run your first program**
   In the terminal, copy/paste:
   ```
   echo '#include <iostream>
   int main() { std::cout << "Setup complete!\\n"; }' > test.cpp
   ```
   
   Then compile:
   ```
   g++ test.cpp -o test
   ```
   
   Then run:
   ```
   ./test
   ```
   
   ✅ **Success looks like:** "Setup complete!"

---

## You're Done! 🎉

### Daily routine (30 seconds):
1. Make sure Docker Desktop is running (check system tray)
2. Open VSCode
3. Open your cpp folder
4. Press F1 → type "reopen" → select "Reopen in Container"
5. Start coding!

### Quick Reference:

| I want to... | Where? | Command/Action |
|-------------|--------|---------------|
| Write code | VSCode | Just type! |
| Compile code | VSCode Terminal | `g++ myfile.cpp -o myprogram` |
| Run program | VSCode Terminal | `./myprogram` |
| Save work | VSCode | `Ctrl+S` |
| Submit homework | PowerShell | `git add .` then `git commit -m "Done"` then `git push` |

### Which terminal do I use?
- **PowerShell**: Git commands, checking versions
- **VSCode Terminal**: ALL C++ work (compiling, running)
- Easy way to remember: If VSCode is open, use its terminal

---

## Common Problems & Solutions

### "It's not working!"

1. **First, always try:**
   - Is Docker Desktop running? (check system tray for whale)
   - Restart VSCode
   - Restart computer

2. **VSCode can't find container:**
   - Delete the `.vscode` folder
   - Recreate it following Step 6

3. **Strange ^M characters:**
   - You skipped the Git configuration
   - Run these in PowerShell:
   ```
   git config --global core.autocrlf input
   git config --global core.eol lf
   ```

4. **"Permission denied":**
   - Don't put files in OneDrive folders
   - Use Desktop or Documents instead

### Still stuck?
- Take a screenshot of the error
- Note which step you're on
- Ask in office hours or Discord/Forum

---

**Remember:** This seems like a lot, but you only do it once! Daily use takes 30 seconds.