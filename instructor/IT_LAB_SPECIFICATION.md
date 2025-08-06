# IT Lab Computer Configuration Specification

## 🖥️ Windows 11 Development Lab Setup

**Target Environment**: Computer lab for programming courses (Python, C++, Java, Database)  
**Operating System**: Windows 11 Pro/Education  
**Management**: Centralized deployment and maintenance  

---

## 📋 Software Installation Checklist

### **Core Development Tools**
- [ ] VS Code (Latest Stable)
- [ ] Git for Windows  
- [ ] Docker Desktop for Windows
- [ ] Chocolatey Package Manager
- [ ] Anaconda Python Distribution
- [ ] PostgreSQL Database Server
- [ ] pgAdmin Database Management Tool

### **Programming Language Support**
- [ ] Python (via Anaconda)
- [ ] C++ Build Tools (MSVC/MinGW-w64)
- [ ] Java Development Kit (OpenJDK)
- [ ] Node.js (for VS Code extensions)

---

## 🛠️ Detailed Installation Specifications

### **1. Chocolatey Package Manager**
**Purpose**: Windows package manager for automated software installation  
**Installation Method**: PowerShell (Run as Administrator)

```powershell
# Install Chocolatey
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Verify installation
choco --version
```

**Configuration**:
- Enable global confirmation prompts: `choco feature enable -n allowGlobalConfirmation`
- Set installation timeout: `choco config set commandExecutionTimeoutSeconds 14400`

### **2. Git for Windows**
**Version**: Latest stable (2.42+)  
**Installation**: Via Chocolatey

```powershell
choco install git -y
```

**Configuration Requirements**:
```bash
# Global Git configuration (run for each user)
git config --global user.name "Lab User"
git config --global user.email "lab@institution.edu"
git config --global init.defaultBranch main
git config --global core.autocrlf true
git config --global core.editor "code --wait"

# Configure credential manager
git config --global credential.helper manager-core
```

**Additional Components**:
- Git Bash integration
- Git GUI tools
- Windows Explorer context menu integration

### **3. Docker Desktop for Windows**
**Version**: Latest stable (4.20+)  
**Installation**: Via Chocolatey

```powershell
choco install docker-desktop -y
```

**System Requirements Verification**:
- Windows 11 version 21H2 or higher
- WSL 2 enabled
- Hyper-V enabled (Business/Pro editions)
- Hardware virtualization enabled in BIOS
- Minimum 4GB RAM, 8GB recommended

**Post-Installation Configuration**:
```powershell
# Enable WSL 2 (if not already enabled)
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# Set WSL 2 as default
wsl --set-default-version 2

# Install Ubuntu for WSL (recommended)
wsl --install -d Ubuntu
```

**Docker Configuration**:
- Use WSL 2 based engine
- Enable integration with default WSL distro
- Resource limits: 4GB RAM, 2 CPUs (adjustable)
- Start Docker Desktop on system boot

### **4. Anaconda Python Distribution**
**Version**: Latest (2023.07+)  
**Installation**: Direct download (NOT via Chocolatey for full features)

**Download Source**: https://www.anaconda.com/download  
**Installation Options**:
- Install for "All Users" (requires admin)
- Add Anaconda to PATH environment variable: **YES**
- Register Anaconda as default Python: **YES**
- Install location: `C:\ProgramData\Anaconda3`

**Post-Installation Setup**:
```powershell
# Update conda
conda update conda -y

# Create development environment
conda create -n dev python=3.11 jupyter pandas numpy matplotlib scipy -y

# Activate environment
conda activate dev

# Install additional packages
conda install -c conda-forge notebook jupyterlab -y
pip install requests beautifulsoup4 flask django
```

**Environment Configuration**:
- Default environment: `base` (Python 3.11+)
- Development environment: `dev` with common packages
- Jupyter Lab accessible via: `jupyter lab`

### **5. Visual Studio Code**
**Version**: Latest stable  
**Installation**: Via Chocolatey

```powershell
choco install vscode -y
```

**Required Extensions** (Auto-install via script):

#### **Python Development**
```json
{
  "recommendations": [
    "ms-python.python",
    "ms-python.vscode-pylance", 
    "ms-python.debugpy",
    "ms-toolsai.jupyter",
    "ms-toolsai.jupyter-keymap",
    "ms-toolsai.jupyter-renderers"
  ]
}
```

#### **C++ Development**
```json
{
  "recommendations": [
    "ms-vscode.cpptools",
    "ms-vscode.cpptools-extension-pack",
    "ms-vscode.cmake-tools",
    "ms-vscode.cpptools-themes"
  ]
}
```

#### **Java Development**
```json
{
  "recommendations": [
    "redhat.java",
    "vscjava.vscode-java-pack",
    "vscjava.vscode-maven",
    "vscjava.vscode-java-dependency"
  ]
}
```

#### **Docker & Containers**
```json
{
  "recommendations": [
    "ms-vscode-remote.remote-containers",
    "ms-vscode-remote.remote-wsl",
    "ms-azuretools.vscode-docker"
  ]
}
```

#### **Database & SQL**
```json
{
  "recommendations": [
    "ms-mssql.mssql",
    "ckolkman.vscode-postgres",
    "mtxr.sqltools",
    "mtxr.sqltools-driver-pg"
  ]
}
```

#### **General Development**
```json
{
  "recommendations": [
    "ms-vscode.vscode-json",
    "eamodio.gitlens",
    "ms-vscode.hexeditor",
    "esbenp.prettier-vscode",
    "bradlc.vscode-tailwindcss"
  ]
}
```

**Extension Installation Script**:
```powershell
# VS Code extension installation script
$extensions = @(
    "ms-python.python",
    "ms-python.vscode-pylance",
    "ms-python.debugpy", 
    "ms-toolsai.jupyter",
    "ms-vscode.cpptools",
    "ms-vscode.cpptools-extension-pack",
    "redhat.java",
    "vscjava.vscode-java-pack",
    "ms-vscode-remote.remote-containers",
    "ms-vscode-remote.remote-wsl",
    "ms-azuretools.vscode-docker",
    "ckolkman.vscode-postgres",
    "mtxr.sqltools",
    "mtxr.sqltools-driver-pg",
    "eamodio.gitlens"
)

foreach ($extension in $extensions) {
    code --install-extension $extension
}
```

### **6. C++ Build Tools**
**Installation Options**:

#### **Option A: Visual Studio Build Tools (Recommended)**
```powershell
choco install visualstudio2022buildtools -y
choco install visualstudio2022-workload-vctools -y
```

#### **Option B: MinGW-w64 (Alternative)**
```powershell
choco install mingw -y
```

**Verification**:
```powershell
# Test C++ compiler
g++ --version
# OR
cl.exe
```

### **7. Java Development Kit**
**Version**: OpenJDK 17 LTS  
**Installation**: Via Chocolatey

```powershell
choco install openjdk17 -y
```

**Environment Variables** (Auto-configured):
- `JAVA_HOME`: Points to JDK installation
- `PATH`: Includes JDK bin directory

**Verification**:
```powershell
java --version
javac --version
```

### **8. PostgreSQL Database**
**Version**: PostgreSQL 15.x  
**Installation**: Via Chocolatey

```powershell
choco install postgresql -y --params '/Password:postgres /Port:5432'
```

**Configuration**:
- Port: 5432 (default)
- Superuser: postgres
- Password: postgres (lab environment)
- Data directory: `C:\Program Files\PostgreSQL\15\data`
- Service: Auto-start

**Post-Installation**:
```sql
-- Create development database
CREATE DATABASE devdb;
CREATE USER devuser WITH PASSWORD 'devpass';
GRANT ALL PRIVILEGES ON DATABASE devdb TO devuser;
```

### **9. pgAdmin**
**Version**: pgAdmin 4 (Latest)  
**Installation**: Via Chocolatey

```powershell
choco install pgadmin4 -y
```

**Configuration**:
- Default email: admin@admin.com
- Default password: admin
- Server connection pre-configured for localhost:5432

---

## 🔧 System Configuration Requirements

### **Windows 11 Features to Enable**
```powershell
# Enable required Windows features
Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
Enable-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform
Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-All

# Enable Developer Mode
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock" /t REG_DWORD /f /v "AllowDevelopmentWithoutDevLicense" /d "1"
```

### **Firewall Configuration**
Allow through Windows Firewall:
- Docker Desktop
- PostgreSQL (port 5432)
- Jupyter Notebook (port 8888)
- VS Code Live Server extensions

### **User Account Configuration**
```powershell
# Add lab users to Docker Users group
Add-LocalGroupMember -Group "docker-users" -Member "LabUser"

# Add lab users to Performance Log Users (for Docker)
Add-LocalGroupMember -Group "Performance Log Users" -Member "LabUser"
```

---

## 📁 Directory Structure Setup

### **Development Workspace**
```
C:\DevWorkspace\
├── Projects\
│   ├── Python\
│   ├── CPP\
│   ├── Java\
│   └── Database\
├── Resources\
│   ├── Documentation\
│   └── Templates\
└── Tools\
    └── Scripts\
```

**PowerShell Script to Create Structure**:
```powershell
# Create development workspace
$workspacePath = "C:\DevWorkspace"
$folders = @("Projects\Python", "Projects\CPP", "Projects\Java", "Projects\Database", "Resources\Documentation", "Resources\Templates", "Tools\Scripts")

New-Item -Path $workspacePath -ItemType Directory -Force
foreach ($folder in $folders) {
    New-Item -Path "$workspacePath\$folder" -ItemType Directory -Force
}

# Set permissions for all users
icacls $workspacePath /grant "Users:(OI)(CI)F" /T
```

---

## 🚀 Automated Deployment Script

### **Master Installation Script**
```powershell
# Master deployment script for Windows 11 lab computers
# Run as Administrator

Write-Host "Starting lab computer configuration..." -ForegroundColor Green

# 1. Install Chocolatey
Write-Host "Installing Chocolatey..." -ForegroundColor Yellow
if (!(Get-Command choco -ErrorAction SilentlyContinue)) {
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
}

# 2. Install core packages via Chocolatey
Write-Host "Installing development tools..." -ForegroundColor Yellow
$chocoPackages = @(
    "git",
    "docker-desktop", 
    "vscode",
    "openjdk17",
    "postgresql",
    "pgadmin4",
    "visualstudio2022buildtools",
    "visualstudio2022-workload-vctools"
)

foreach ($package in $chocoPackages) {
    choco install $package -y
}

# 3. Enable Windows features
Write-Host "Enabling Windows features..." -ForegroundColor Yellow
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
dism.exe /online /enable-feature /featurename:Microsoft-Hyper-V-All /all /norestart

# 4. Install VS Code extensions
Write-Host "Installing VS Code extensions..." -ForegroundColor Yellow
$extensions = @(
    "ms-python.python",
    "ms-python.vscode-pylance",
    "ms-toolsai.jupyter",
    "ms-vscode.cpptools-extension-pack",
    "vscjava.vscode-java-pack",
    "ms-vscode-remote.remote-containers",
    "ms-azuretools.vscode-docker",
    "ckolkman.vscode-postgres",
    "eamodio.gitlens"
)

foreach ($extension in $extensions) {
    code --install-extension $extension
}

# 5. Create workspace directory
Write-Host "Creating development workspace..." -ForegroundColor Yellow
$workspacePath = "C:\DevWorkspace"
$folders = @("Projects\Python", "Projects\CPP", "Projects\Java", "Projects\Database", "Resources\Documentation", "Resources\Templates", "Tools\Scripts")

New-Item -Path $workspacePath -ItemType Directory -Force
foreach ($folder in $folders) {
    New-Item -Path "$workspacePath\$folder" -ItemType Directory -Force
}
icacls $workspacePath /grant "Users:(OI)(CI)F" /T

Write-Host "Lab computer configuration complete!" -ForegroundColor Green
Write-Host "Please reboot the computer to complete setup." -ForegroundColor Red
```

---

## 🔍 Testing & Verification

### **Post-Installation Testing Checklist**

#### **Python Environment**
```powershell
# Test Python
python --version
conda --version

# Test Jupyter
jupyter --version

# Test package imports
python -c "import pandas, numpy, matplotlib; print('Python packages OK')"
```

#### **C++ Environment**
```powershell
# Test C++ compiler
g++ --version

# Test compilation
echo '#include <iostream>' > test.cpp
echo 'int main() { std::cout << "C++ OK" << std::endl; return 0; }' >> test.cpp
g++ test.cpp -o test.exe
./test.exe
```

#### **Java Environment**
```powershell
# Test Java
java --version
javac --version

# Test compilation
echo 'public class Test { public static void main(String[] args) { System.out.println("Java OK"); } }' > Test.java
javac Test.java
java Test
```

#### **Docker Environment**
```powershell
# Test Docker
docker --version
docker run hello-world
```

#### **Database Environment**
```powershell
# Test PostgreSQL connection
psql -h localhost -U postgres -c "SELECT version();"
```

#### **VS Code Integration**
```powershell
# Test VS Code launch
code --version

# Test extensions
code --list-extensions
```

---

## 📊 Resource Requirements

### **Hardware Specifications**
- **CPU**: Intel i5/AMD Ryzen 5 or better (4+ cores)
- **RAM**: 16GB minimum, 32GB recommended
- **Storage**: 500GB SSD minimum
- **Network**: Gigabit Ethernet + WiFi

### **Disk Space Requirements**
- Windows 11: ~20GB
- Visual Studio Build Tools: ~3GB
- Docker Desktop: ~1GB + container storage (~10GB)
- Anaconda: ~5GB
- PostgreSQL: ~200MB + data storage
- VS Code + Extensions: ~500MB
- Workspace + Projects: ~5GB reserved

**Total Estimated**: ~45GB minimum, 60GB recommended

### **Network Requirements**
- Internet access for package downloads
- Institutional network access for Git repositories
- Port access: 5432 (PostgreSQL), 8888 (Jupyter), 3000-8000 (development servers)

---

## 🔐 Security Considerations

### **Group Policy Recommendations**
- Allow installation of approved software packages
- Restrict admin rights to specific IT accounts
- Enable Windows Defender with development tool exceptions
- Configure automatic updates for security patches only

### **User Account Management**
- Create standard user accounts for students
- Use local accounts (avoid domain complexity)
- Reset passwords each semester
- Clear user profiles periodically

### **Development Security**
- Configure Git with institutional email domains
- Set up basic firewall rules for development ports
- Enable code signing verification where possible
- Regular security updates for all development tools

---

## 📞 Support & Maintenance

### **Regular Maintenance Tasks**
- **Weekly**: Update VS Code extensions, check Docker images
- **Monthly**: Update Chocolatey packages, clean temp files
- **Semester**: Reset user profiles, update major software versions
- **Annually**: Full system refresh, hardware maintenance

### **Common Issues & Solutions**

#### **Docker Issues**
- **Problem**: "Docker Desktop is not running"
- **Solution**: Restart Docker Desktop service, check WSL 2 status

#### **VS Code Extension Issues**
- **Problem**: Extensions not loading
- **Solution**: Reset extension cache, reinstall problematic extensions

#### **Python Environment Issues**
- **Problem**: Package conflicts
- **Solution**: Reset conda environment, use virtual environments

#### **Database Connection Issues**
- **Problem**: PostgreSQL connection refused
- **Solution**: Check service status, verify port 5432 availability

### **Contact Information**
- **Primary Support**: IT Help Desk (ext. XXXX)
- **Development Tools**: Software Support Team (ext. XXXX)
- **Network Issues**: Network Operations (ext. XXXX)

---

## 📋 Deployment Timeline

### **Phase 1: Pilot Installation (Week 1)**
- Configure 3-5 pilot machines
- Test all software installations
- Verify functionality with instructor
- Document any issues or modifications needed

### **Phase 2: Full Lab Deployment (Week 2)**
- Deploy to all lab computers using automated script
- Verify each installation
- Create user accounts and workspace folders
- Final testing with student simulation

### **Phase 3: Documentation & Training (Week 3)**
- Create user guides for students and instructors
- Train support staff on maintenance procedures
- Establish monitoring and update procedures
- Prepare for semester launch

---

**This specification provides complete Windows 11 lab computer configuration for comprehensive development education including Python, C++, Java, database development, and modern DevOps practices with Docker and Git.** 🎯

---

*This IT specification supports the simplified C++ course and broader programming curriculum with professional development tools and practices.*