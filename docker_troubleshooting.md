# Docker Troubleshooting Guide

## Common Docker Issues and Solutions

This guide covers the most frequent Docker problems students encounter and their step-by-step solutions.

---

## 🚨 Most Common Issue: Docker Desktop Not Running

**Problem**: Terminal shows "Cannot connect to the Docker daemon"

**Solution**: Docker Desktop must be started from the APPLICATION, not terminal!

### How to Start Docker Desktop:

**Windows:**
1. Click Start Menu → Search "Docker Desktop" → Click to launch
2. Wait for whale icon in system tray (bottom-right corner)
3. Icon should show "Docker Desktop is running"

**macOS:**
1. Open Finder → Applications → Double-click "Docker"
2. Wait for whale icon in menu bar (top-right corner)
3. Icon should show "Docker Desktop is running"

**Linux:**
- Docker runs as a service (no Desktop app needed)
- Start with: `sudo systemctl start docker`

⚠️ **Important**: Docker Desktop must be running BEFORE you use any `docker` or `docker-compose` commands in the terminal!

---

## Installation Issues

### Windows: "Docker Desktop won't start"

**Symptoms:**
- Docker Desktop shows error on startup
- "WSL 2 installation is incomplete" message

**Solutions:**
1. **Enable WSL 2:**
   ```powershell
   # Run in PowerShell as Administrator
   wsl --install
   wsl --set-default-version 2
   ```

2. **Enable Virtualization in BIOS:**
   - Restart computer → Enter BIOS/UEFI settings
   - Enable "Intel VT-x" or "AMD-V" virtualization
   - Save and exit

3. **Update Windows:**
   - Install all Windows updates
   - Restart and try Docker Desktop again

### macOS: "Docker Desktop requires a newer macOS version"

**Solutions:**
1. **Check macOS version:**
   ```bash
   sw_vers -productVersion
   ```
   
2. **If macOS < 10.15:**
   - Install Docker Toolbox (legacy solution)
   - Or upgrade macOS if possible

3. **Apple Silicon (M1/M2) Issues:**
   - Download Docker Desktop for Apple Silicon specifically
   - Enable "Use Rosetta for x86/amd64 emulation" in Docker settings

### Linux: "Permission denied" errors

**Symptoms:**
```bash
docker: permission denied while trying to connect to the Docker daemon socket
```

**Solutions:**
1. **Add user to docker group:**
   ```bash
   sudo usermod -aG docker $USER
   newgrp docker
   ```

2. **If still failing:**
   ```bash
   # Temporary fix (not recommended long-term)
   sudo chmod 666 /var/run/docker.sock
   ```

3. **Restart Docker service:**
   ```bash
   sudo systemctl restart docker
   ```

---

## Container Startup Issues

### "docker-compose command not found"

**For older Docker installations:**
```bash
# Check if docker-compose is separate
docker-compose --version

# If not installed, install it
sudo apt-get install docker-compose  # Linux
brew install docker-compose          # macOS with Homebrew
```

**For newer Docker installations:**
```bash
# Use docker compose (no hyphen) instead
docker compose up -d cpp-dev
docker compose exec cpp-dev bash
```

### "Service 'cpp-dev' failed to build"

**Symptoms:**
```
ERROR [internal] load metadata for docker.io/library/ubuntu:22.04
```

**Solutions:**
1. **Check internet connection:**
   ```bash
   ping docker.io
   ```

2. **Clear Docker cache:**
   ```bash
   docker system prune -a
   docker-compose build --no-cache cpp-dev
   ```

3. **Manual image pull:**
   ```bash
   docker pull ubuntu:22.04
   docker-compose up -d cpp-dev
   ```

### "Port already in use" or "Address already in use"

**Solutions:**
1. **Stop conflicting containers:**
   ```bash
   docker-compose down
   docker ps -a
   docker stop $(docker ps -aq)  # Stop all containers
   ```

2. **Change ports in docker-compose.yml** (if applicable):
   ```yaml
   ports:
     - "8081:8080"  # Use different host port
   ```

---

## Runtime Issues

### "Container keeps exiting immediately"

**Check container logs:**
```bash
docker-compose logs cpp-dev
```

**Common fixes:**
1. **Recreate container:**
   ```bash
   docker-compose down
   docker-compose up -d cpp-dev
   ```

2. **Check Dockerfile syntax:**
   - Ensure valid Ubuntu base image
   - Verify all RUN commands are correct

### "Can't access files inside container"

**Symptoms:**
- Files created outside container not visible inside
- Changes inside container don't persist

**Solutions:**
1. **Verify volume mounting:**
   ```bash
   docker-compose exec cpp-dev bash
   ls -la /home/student/workspace
   pwd
   ```

2. **Check docker-compose.yml volumes:**
   ```yaml
   volumes:
     - .:/home/student/workspace  # Current directory maps to workspace
   ```

3. **File permissions issue:**
   ```bash
   # Fix ownership inside container
   sudo chown -R student:student /home/student/workspace
   ```

### "Command 'g++' not found" inside container

**Solutions:**
1. **Verify container build:**
   ```bash
   docker-compose exec cpp-dev bash
   which g++
   g++ --version
   ```

2. **Rebuild container:**
   ```bash
   docker-compose down
   docker-compose build --no-cache cpp-dev
   docker-compose up -d cpp-dev
   ```

3. **Manual installation (temporary fix):**
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   ```

---

## Performance Issues

### "Docker uses too much disk space"

**Check disk usage:**
```bash
docker system df
```

**Clean up:**
```bash
# Remove unused containers, networks, images
docker system prune

# More aggressive cleanup (removes all unused images)
docker system prune -a

# Remove specific items
docker container prune  # Remove stopped containers
docker image prune      # Remove unused images
docker volume prune     # Remove unused volumes
```

### "Docker is very slow"

**Windows/macOS solutions:**
1. **Increase Docker Desktop resources:**
   - Docker Desktop → Settings → Resources
   - Increase CPU cores (2-4)
   - Increase memory (4-8 GB)

2. **Enable file sharing optimization:**
   - Docker Desktop → Settings → General
   - Enable "Use gRPC FUSE for file sharing"

3. **Use .dockerignore:**
   ```bash
   # Create .dockerignore file
   echo "node_modules\n.git\nbuild\n*.log" > .dockerignore
   ```

**Linux solutions:**
1. **Check available resources:**
   ```bash
   free -h          # Check memory
   df -h            # Check disk space
   top              # Check CPU usage
   ```

---

## Development Workflow Issues

### "Changes to code not reflected in container"

**Solutions:**
1. **Verify you're editing the right files:**
   ```bash
   # Check if files sync between host and container
   # Edit file on host
   echo "test" > test.txt
   
   # Check inside container
   docker-compose exec cpp-dev bash
   cat /home/student/workspace/test.txt
   ```

2. **Restart container if needed:**
   ```bash
   docker-compose restart cpp-dev
   ```

### "Can't install additional packages"

**Temporary solution (packages don't persist):**
```bash
docker-compose exec cpp-dev bash
sudo apt-get update
sudo apt-get install <package-name>
```

**Permanent solution (modify Dockerfile):**
```dockerfile
# Add to Dockerfile
RUN apt-get update && apt-get install -y \
    your-additional-package \
    && rm -rf /var/lib/apt/lists/*
```

Then rebuild:
```bash
docker-compose build --no-cache cpp-dev
```

### "Git not working inside container"

**Setup Git inside container:**
```bash
docker-compose exec cpp-dev bash
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

**SSH key setup for GitHub:**
```bash
# Generate SSH key inside container
ssh-keygen -t ed25519 -C "your.email@example.com"

# Copy public key to add to GitHub
cat ~/.ssh/id_ed25519.pub
```

---

## Emergency Recovery

### "Everything is broken, start fresh"

**Complete reset:**
```bash
# Stop all containers
docker-compose down

# Remove all containers and images
docker system prune -a

# Remove course-specific containers and images
docker rmi cpp-course:latest

# Rebuild from scratch
docker-compose build --no-cache cpp-dev
docker-compose up -d cpp-dev
```

### "Docker Desktop is unresponsive"

**Windows/macOS:**
1. Quit Docker Desktop completely
2. Restart Docker Desktop
3. If still unresponsive, restart computer

**Linux:**
```bash
sudo systemctl stop docker
sudo systemctl start docker
```

---

## Preventing Common Issues

### Best Practices

1. **Always work inside the container:**
   ```bash
   docker-compose exec cpp-dev bash
   # Do all C++ development here
   ```

2. **Stop cleanly when done:**
   ```bash
   exit  # Leave container
   docker-compose down  # Stop services
   ```

3. **Keep Docker Desktop updated:**
   - Check for updates monthly
   - Update when prompted

4. **Monitor disk space:**
   ```bash
   # Run weekly
   docker system prune
   ```

5. **Don't modify Docker files** unless instructed:
   - Dockerfile
   - docker-compose.yml
   - .dockerignore

### Quick Diagnostic Commands

```bash
# Check Docker status
docker --version
docker-compose --version

# Check running containers
docker ps

# Check container logs
docker-compose logs cpp-dev

# Check system resources
docker system df

# Test container access
docker-compose exec cpp-dev bash -c "echo 'Container is working'"
```

---

## Getting Help

### When to Ask for Help

1. **After trying these solutions** - Don't skip the troubleshooting steps
2. **With specific error messages** - Copy the exact error text
3. **With system information** - Include your OS, Docker version, and what you were trying to do

### Information to Include

```bash
# System info
uname -a                    # OS information
docker --version           # Docker version
docker-compose --version   # Compose version

# Problem context
docker ps -a               # Container status
docker-compose logs cpp-dev  # Error logs
```

### Course-Specific Help

- **Course forum** - Other students may have same issue
- **Office hours** - Instructor can help with complex problems
- **Email instructor** - Include all diagnostic information above

**Remember: Docker issues are usually fixable with the right approach!** 🐳