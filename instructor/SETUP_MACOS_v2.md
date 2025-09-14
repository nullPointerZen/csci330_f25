# macOS Setup Guide - CSCI 330

**Total Time:** 15-25 minutes  
**Read only this guide** - Windows and Linux users have their own

---

## Before You Start

**You'll need:**
- macOS (any recent version)
- Admin password for your Mac
- Stable internet connection
- Your GitHub account

**What we're installing:**
1. Docker Desktop (container platform)
2. Development tools including Git
3. VSCode (code editor)

---

## Step 1: Check Your Mac Type (1 minute)

**Why:** Different Macs need different Docker versions

### Do this:
1. **Find your Mac type**
   - Click Apple logo (top left)
   - Click "About This Mac"
   - Look for "Chip" or "Processor"

2. **Remember which you have:**
   - **Apple M1/M2/M3** = Apple Silicon (newer Macs)
   - **Intel Core i5/i7/i9** = Intel (older Macs)

   ✅ **You're done with this step when:** You know if you have Apple Silicon or Intel

---

## Step 2: Install Docker Desktop (5 minutes)

**What it does:** Creates consistent C++ environment for everyone

### Do this:
1. **Download the RIGHT Docker version**
   - Go to: https://docker.com
   - Click big blue "Download for Mac" button
   - **IMPORTANT:** Choose the correct one:
     - If you have Apple M1/M2/M3: Click "Mac with Apple chip"
     - If you have Intel: Click "Mac with Intel chip"

2. **Install Docker**
   - Open Downloads folder
   - Double-click the Docker.dmg file
   - Drag Docker icon to Applications folder
   - Close the installer window

3. **Start Docker**
   - Open Applications folder (Command+Shift+A)
   - Double-click Docker
   - Click "Open" when Mac warns about downloaded app
   - Enter your Mac password when prompted
   - Wait for whale icon to appear in menu bar (top right)

4. **Configure Docker**
   - Click whale icon in menu bar
   - Click "Settings" (gear icon)
   - Click "Resources" on left
   - Move Memory slider to at least 4 GB
   - Click "Apply & Restart"

5. **Verify it worked**
   - Open Terminal (Command+Space, type "terminal", press Enter)
   - Type:
   ```
   docker --version
   ```
   
   ✅ **Success looks like:** "Docker version 24.x.x" (any number is fine)

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"Docker is damaged" or "can't be opened"**
- System Preferences → Security & Privacy
- Click "Open Anyway" next to Docker message

**Whale icon not appearing**
- Restart your Mac
- Try opening Docker from Applications again

**Apple Silicon warning about platform**
- This warning is NORMAL - just ignore it!
</details>

---

## Step 3: Install Development Tools (5 minutes)

**What it does:** Installs Git and other tools you need

### Do this:
1. **Install developer tools**
   In Terminal (if not open: Command+Space, type "terminal"):
   ```
   xcode-select --install
   ```
   - Click "Install" in the popup
   - Click "Agree" to license
   - Wait 5-10 minutes for download
   - **Don't close Terminal**

2. **Download VSCode**
   While tools install:
   - Go to: https://code.visualstudio.com
   - Click "Download for macOS"
   - Open Downloads folder
   - Double-click downloaded file
   - Drag VSCode to Applications folder

3. **Open VSCode and add extensions**
   - Open Applications (Command+Shift+A)
   - Double-click "Visual Studio Code"
   - Press Command+Shift+X (opens extensions)
   - Search and install each one:
     - C/C++ Extension Pack (by Microsoft)
     - Dev Containers (by Microsoft)
     - Docker (by Microsoft)

4. **Verify everything**
   Back in Terminal:
   ```
   git --version
   ```
   ```
   code --version
   ```
   
   ✅ **Success looks like:** Both commands show version numbers

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"xcrun: error" or tools won't install**
- Try the command again
- If still broken, restart Mac and try again

**"code: command not found"**
- Open VSCode
- Press Command+Shift+P
- Type "install code"
- Click "Shell Command: Install 'code' command in PATH"
</details>

---

## Step 4: Get Course Files (5 minutes)

**What it does:** Downloads the course materials to your computer

### Do this:
1. **Set up Git** (use YOUR actual name and email)
   In Terminal, type these (replace the text in quotes):
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
   In Terminal, copy/paste these lines one at a time:
   
   First, go to Desktop:
   ```
   cd ~/Desktop
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
   In Terminal:
   ```
   cd ~/Desktop/cpp
   ```

2. **Build the container** (this takes 3-5 minutes - be patient!)
   ```
   docker-compose build
   ```
   - You'll see lots of text scrolling - that's normal
   - **Apple Silicon Macs:** You'll see a platform warning - ignore it!
   - Get coffee while it builds

3. **Test it**
   ```
   docker run --rm cpp-course:latest g++ --version
   ```
   
   ✅ **Success looks like:** "g++ (GCC) 11.x.x"

### If something went wrong:
<details>
<summary>Click here for fixes</summary>

**"Cannot connect to Docker daemon"**
- Check whale icon in menu bar
- If not there, open Docker from Applications

**Build taking forever on Apple Silicon**
- This is normal! Your Mac is converting Intel code
- Go get lunch, it'll finish eventually

**"docker-compose: command not found"**
- Restart Docker Desktop
- Wait for whale icon to reappear
</details>

---

## Step 6: Connect VSCode to Docker (5 minutes)

**What it does:** Makes VSCode use your container automatically

### Do this:
1. **Open your project**
   In Terminal:
   ```
   cd ~/Desktop/cpp
   ```
   ```
   code .
   ```
   (The dot is important!) - it opens VSCode

2. **Create config folder**
   In VSCode:
   - Look at left sidebar (file explorer)
   - Right-click in empty area
   - Click "New Folder"
   - Name it: `.vscode` (with the dot!)

3. **Create config file**
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
   - Save with Command+S

4. **Start the container**
   - Press F1 (or Command+Shift+P)
   - Type: reopen in container
   - Click "Dev Containers: Reopen in Container"
   - First time takes 2-3 minutes - be patient!

5. **Test everything**
   When VSCode reloads:
   - Look at bottom left - should say "Dev Container: C++ Development"  
   - Click Terminal → New Terminal (or press Control+`)
   - In the terminal, type:
   ```
   g++ --version
   ```
   
   ✅ **Success looks like:** Terminal shows "g++ (GCC) 11.x.x"

6. **Run your first program**
   In the VSCode terminal, copy/paste:
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
1. Make sure Docker Desktop is running (check menu bar for whale)
2. Open Terminal
3. Type: `cd ~/Desktop/cpp && code .`
4. Press F1 → type "reopen" → select "Reopen in Container"
5. Start coding!

### Quick Reference:

| I want to... | Where? | Command/Action |
|-------------|--------|---------------|
| Write code | VSCode | Just type! |
| Compile code | VSCode Terminal | `g++ myfile.cpp -o myprogram` |
| Run program | VSCode Terminal | `./myprogram` |
| Save work | VSCode | Command+S |
| Submit homework | Terminal.app | `git add .` then `git commit -m "Done"` then `git push` |

### Which terminal do I use?
- **Terminal.app**: Git commands, opening projects
- **VSCode Terminal**: ALL C++ work (compiling, running)
- Easy way to remember: If VSCode is open, use its terminal

---

## Common Problems & Solutions

### "It's not working!"

1. **First, always try:**
   - Is Docker Desktop running? (check menu bar for whale)
   - Restart VSCode
   - Restart your Mac

2. **VSCode can't find container:**
   - Delete the `.vscode` folder
   - Recreate it following Step 6

3. **"Permission denied" errors:**
   - System Preferences → Security & Privacy → Privacy
   - Give Terminal and VSCode access to folders

4. **Apple Silicon platform warnings:**
   - These are NORMAL - just ignore them
   - Your code will still work perfectly

5. **Can't push to GitHub:**
   - GitHub now requires tokens instead of passwords
   - Go to GitHub → Settings → Personal Access Tokens
   - Generate one and use it as your password

6. **Terminal says "zsh" instead of "bash":**
   - This is normal on newer Macs
   - Both work the same for our purposes

### Still stuck?
- Take a screenshot of the error
- Note which step you're on  
- Ask in office hours or Discord/Forum

---

**Remember:** This seems like a lot, but you only do it once! Daily use takes 30 seconds.