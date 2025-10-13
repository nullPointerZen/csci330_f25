# Troubleshooting & Advanced Setup Guide

## Common Issues and Solutions

### Docker Issues

#### Docker Desktop Won't Start

**Windows:**
```powershell
# Check if WSL2 is properly installed
wsl --status

# If WSL2 not installed:
wsl --install
# Restart computer

# Enable required Windows features
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
# Restart computer
```

**macOS:**
- System Preferences → Security & Privacy → Allow Docker
- If on M1/M2/M3: Ensure you downloaded Apple Silicon version
- Try: Restart Docker Desktop from menu bar

**Linux:**
```bash
# Check Docker service status
sudo systemctl status docker

# Start Docker if not running
sudo systemctl start docker
sudo systemctl enable docker

# If permission denied:
sudo usermod -aG docker $USER
newgrp docker  # Or log out and back in
```

#### Container Build Fails

```bash
# Clean up and rebuild
docker-compose down -v
docker system prune -af  # Warning: Removes all Docker data
docker-compose build --no-cache
```

#### Platform Warning on Apple Silicon

If you see "WARNING: The requested image's platform (linux/amd64) does not match the detected host platform":
- This is NORMAL and safe to ignore
- The container uses emulation (slightly slower but ensures compatibility)
- Your code will still work correctly

### Git Issues

#### Authentication Failed

**GitHub now requires tokens instead of passwords:**
1. Go to GitHub → Settings → Developer settings → Personal access tokens
2. Generate new token with "repo" permissions
3. Use token as password when pushing

**Configure credential storage:**
```bash
# Windows
git config --global credential.helper manager

# macOS
git config --global credential.helper osxkeychain

# Linux
git config --global credential.helper cache
```

#### Permission Denied (SSH)

```bash
# Generate SSH key
ssh-keygen -t ed25519 -C "your.email@university.edu"

# Add to ssh-agent
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

# Copy public key and add to GitHub
cat ~/.ssh/id_ed25519.pub
# Go to GitHub → Settings → SSH keys → Add new
```

#### Merge Conflicts

```bash
# See conflicting files
git status

# Open conflicted file and look for:
<<<<<<< HEAD
Your changes
=======
Other changes
>>>>>>> branch-name

# Edit file to resolve, then:
git add resolved-file.cpp
git commit -m "Resolve merge conflict"
```

#### Accidentally Committed Large Files

```bash
# Remove from history (if not pushed)
git reset HEAD~1
# Add to .gitignore
echo "*.exe" >> .gitignore
echo "build/" >> .gitignore
git add .gitignore
git commit -m "Add gitignore"
```

### VSCode Issues

#### Container Won't Open

1. Ensure Docker Desktop is running
2. Check for error notifications in VSCode
3. Try: Command Palette → "Dev Containers: Rebuild Container"
4. Nuclear option: Delete `.vscode` folder and recreate

#### Extensions Not Working in Container

```json
// Ensure .vscode/devcontainer.json includes:
{
  "extensions": [
    "ms-vscode.cpptools-extension-pack",
    "ms-vscode.cmake-tools"
  ]
}
```
Then rebuild container.

#### IntelliSense Not Working

1. Wait for C++ extension to fully load (check bottom status bar)
2. Command Palette → "C/C++: Reset IntelliSense Database"
3. Reload window: Command Palette → "Developer: Reload Window"

### Compilation Issues

#### "Command not found: g++"

```bash
# Verify you're inside container
hostname  # Should show container ID

# If not in container:
docker-compose run cpp-dev
# Or reopen in container via VSCode
```

#### "No such file or directory"

```bash
# Check current directory
pwd

# List files
ls -la

# Common issue: wrong path
cd /workspace/csci330_f25/assignments/CSCI330_YourName/week01
```

#### CMake Errors

```bash
# "CMakeLists.txt not found"
# Ensure you're in project directory with CMakeLists.txt
ls CMakeLists.txt

# Clean build directory
rm -rf build
mkdir build && cd build
cmake ..
```

### File and Path Issues

#### Spaces in Paths

```bash
# Wrong:
cd /path/with spaces/folder

# Correct:
cd "/path/with spaces/folder"
# Or:
cd /path/with\ spaces/folder
```

#### Windows Line Endings (^M characters)

```bash
# Fix file endings
dos2unix file.cpp

# Or globally for Git:
git config --global core.autocrlf input
```

#### Can't Find Files Between Host and Container

**Remember the mapping:**
- Host: `C:\Users\You\cpp` or `/Users/You/cpp`
- Container: `/home/student/workspace`

```bash
# In container, your files are at:
cd /workspace
ls
```

### Network and Firewall Issues

#### University Network Blocking Docker

- Use university VPN if available
- Contact IT for Docker whitelist
- Alternative: Use university lab computers

#### Antivirus Blocking Docker

**Windows Defender:**
- Add Docker Desktop to exclusions
- Exclude `C:\ProgramData\DockerDesktop`

**Other Antivirus:**
- Add Docker to trusted applications
- Temporarily disable for installation (re-enable after)

### Platform-Specific Issues

#### Windows: WSL2 Memory Usage

Create `.wslconfig` in your Windows user directory:
```ini
[wsl2]
memory=4GB
processors=2
```
Then restart WSL: `wsl --shutdown`

#### macOS: Disk Space

```bash
# Check Docker disk usage
docker system df

# Clean up unused data
docker system prune -a --volumes
```

#### Linux: Different Distributions

**Fedora/RHEL:**
```bash
sudo dnf install docker docker-compose
sudo systemctl start docker
```

**Arch:**
```bash
sudo pacman -S docker docker-compose
sudo systemctl start docker
```

**OpenSUSE:**
```bash
sudo zypper install docker docker-compose
sudo systemctl start docker
```

## Advanced Configuration

### Custom Docker Settings

Edit `docker-compose.yml` for more resources:
```yaml
services:
  cpp-dev:
    # ... existing config ...
    deploy:
      resources:
        limits:
          memory: 8G
          cpus: '4'
```

### Multiple Containers

Run multiple instances:
```bash
# Terminal 1
docker-compose run --name dev1 cpp-dev

# Terminal 2
docker-compose run --name dev2 cpp-dev
```

### Remote Development

Connect VSCode to remote server with Docker:
1. Install "Remote - SSH" extension
2. Connect to server
3. Open project and use Dev Containers as normal

## Quick Diagnosis Commands

```bash
# Check system
docker --version
docker-compose --version
git --version
code --version

# Check Docker status
docker ps                    # Running containers
docker images               # Available images
docker-compose ps           # Project containers

# Check Git status
git remote -v               # Remote connections
git branch                  # Current branch
git status                  # File changes

# Inside container checks
which g++                   # Compiler location
g++ --version              # Compiler version
cmake --version            # CMake version
pwd                        # Current directory
ls -la                     # List all files
```

## Getting More Help

### Before Asking for Help

1. **Copy the EXACT error message**
2. **Note what command you ran**
3. **Check this guide first**
4. **Google the error message**
5. **Try the verification commands above**

### When Asking for Help

Provide:
- Operating system and version
- Error message (screenshot or text)
- Command that caused error
- What you've already tried
- Output of diagnosis commands

### Resources

- Course Discord/Forum
- Office Hours
- Docker Documentation: https://docs.docker.com
- Git Documentation: https://git-scm.com/doc
- VSCode Docs: https://code.visualstudio.com/docs

## Emergency Recovery

If everything is broken:

1. **Save your code** (copy to safe location)
2. **Full reset:**
```bash
# Warning: This removes everything
docker system prune -af
docker volume prune -f
rm -rf ~/.docker
# Reinstall Docker Desktop
# Rebuild from scratch
```
3. **Restore your code** from backup
4. **Follow Quick Start Guide** again

---
Remember: Every developer encounters these issues. Persistence is key!