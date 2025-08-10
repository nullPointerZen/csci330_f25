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
- [ ] GitHub Desktop (GUI for Git)
- [ ] Docker Desktop for Windows
- [ ] Chocolatey Package Manager
- [ ] Anaconda Python Distribution
- [ ] Jupyter Notebooks (via Anaconda)
- [ ] PostgreSQL Database Server
- [ ] pgAdmin 4 Database Management Tool
- [ ] yEd Graph Editor (Diagramming Tool)

### **Programming Language Support**
- [ ] Python 3.11+ (via Anaconda)
- [ ] C++ Build Tools (MSVC/MinGW-w64)
- [ ] Java Development Kit (OpenJDK 17 LTS)
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

### **2. Git for Windows & GitHub Desktop**
**Version**: Latest stable (2.42+)  
**Installation**: Via Chocolatey

```powershell
# Install Git
choco install git -y

# Install GitHub Desktop
choco install github-desktop -y
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

**GitHub Desktop Configuration**:
- Default editor: Visual Studio Code
- Default shell: Git Bash
- Clone path: `C:\DevWorkspace\Projects`
- Enable automatic fetching

**Additional Components**:
- Git Bash integration
- Git GUI tools
- Windows Explorer context menu integration
- GitHub CLI (optional): `choco install gh -y`

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

### **4. Anaconda Python Distribution & Jupyter Notebooks**
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

# Create development environment with Jupyter
conda create -n dev python=3.11 jupyter pandas numpy matplotlib scipy seaborn scikit-learn -y

# Activate environment
conda activate dev

# Install Jupyter Lab and extensions
conda install -c conda-forge notebook jupyterlab jupyterlab-git -y

# Install additional Python packages
pip install requests beautifulsoup4 flask django pytest black

# Install Jupyter kernel for the environment
python -m ipykernel install --user --name dev --display-name "Python 3.11 (dev)"
```

**Jupyter Configuration**:
```powershell
# Generate Jupyter config
jupyter notebook --generate-config

# Set default browser and port
jupyter lab --generate-config

# Create desktop shortcut for Jupyter Lab
$WshShell = New-Object -comObject WScript.Shell
$Shortcut = $WshShell.CreateShortcut("$Home\Desktop\Jupyter Lab.lnk")
$Shortcut.TargetPath = "C:\ProgramData\Anaconda3\Scripts\jupyter-lab.exe"
$Shortcut.WorkingDirectory = "C:\DevWorkspace\Projects\Python"
$Shortcut.Save()
```

**Environment Configuration**:
- Default environment: `base` (Python 3.11+)
- Development environment: `dev` with scientific packages
- Jupyter Lab accessible via: `jupyter lab` or desktop shortcut
- Default notebook directory: `C:\DevWorkspace\Projects\Python`

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

### **9. pgAdmin 4**
**Version**: pgAdmin 4 (Latest)  
**Installation**: Via Chocolatey

```powershell
choco install pgadmin4 -y
```

**Configuration**:
- Default email: admin@admin.com
- Default password: admin
- Server connection pre-configured for localhost:5432
- Enable dark mode for reduced eye strain
- Set auto-refresh for query results

### **10. yEd Graph Editor**
**Version**: Latest stable  
**Installation**: Via Chocolatey

```powershell
choco install yed -y
```

**Purpose**: Professional diagramming tool for:
- UML diagrams (class, sequence, use case)
- Database ER diagrams
- Flowcharts and algorithms
- Software architecture diagrams
- Network topology diagrams

**Configuration**:
- Default save location: `C:\DevWorkspace\Resources\Diagrams`
- Enable auto-save every 5 minutes
- Install common diagram templates

**Additional Diagram Palettes**:
- UML Class Diagrams
- ER Notation
- BPMN (Business Process)
- Flowchart symbols
- Network shapes

**File Format Support**:
- Native yEd format (.graphml)
- Export to PNG, SVG, PDF, JPG
- Import from Visio (.vsdx)

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
│   │   └── Notebooks\
│   ├── CPP\
│   ├── Java\
│   └── Database\
├── Resources\
│   ├── Documentation\
│   ├── Templates\
│   └── Diagrams\
└── Tools\
    └── Scripts\
```

**PowerShell Script to Create Structure**:
```powershell
# Create development workspace
$workspacePath = "C:\DevWorkspace"
$folders = @(
    "Projects\Python",
    "Projects\Python\Notebooks",
    "Projects\CPP",
    "Projects\Java",
    "Projects\Database",
    "Resources\Documentation",
    "Resources\Templates",
    "Resources\Diagrams",
    "Tools\Scripts"
)

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
    "github-desktop",
    "docker-desktop", 
    "vscode",
    "openjdk17",
    "postgresql",
    "pgadmin4",
    "yed",
    "visualstudio2022buildtools",
    "visualstudio2022-workload-vctools",
    "nodejs"
)

foreach ($package in $chocoPackages) {
    choco install $package -y
}

# Note: Anaconda should be installed manually for full features
Write-Host "Please install Anaconda manually from https://www.anaconda.com/download" -ForegroundColor Yellow

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

#### **Python Environment & Jupyter**
```powershell
# Test Python
python --version
conda --version

# Test Jupyter installations
jupyter --version
jupyter lab --version
jupyter notebook --version

# Test Jupyter Lab launch
Start-Process "jupyter" -ArgumentList "lab", "--no-browser" -NoNewWindow
Start-Sleep -Seconds 3
# Check if Jupyter is running
$jupyterRunning = Get-Process | Where-Object {$_.ProcessName -like "*jupyter*"}
if ($jupyterRunning) { 
    Write-Host "Jupyter Lab is running OK" -ForegroundColor Green
    Stop-Process -Name "jupyter*" -Force
}

# Test package imports
python -c "import pandas, numpy, matplotlib, seaborn, sklearn, jupyter; print('Python packages OK')"
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

#### **GitHub Desktop**
```powershell
# Test GitHub Desktop installation
if (Test-Path "$env:LOCALAPPDATA\GitHubDesktop\GitHubDesktop.exe") {
    Write-Host "GitHub Desktop installed OK" -ForegroundColor Green
} else {
    Write-Host "GitHub Desktop not found" -ForegroundColor Red
}

# Test GitHub CLI (if installed)
gh --version
```

#### **yEd Graph Editor**
```powershell
# Test yEd installation
$yedPath = Get-ChildItem -Path "C:\Program Files*" -Filter "yed.exe" -Recurse -ErrorAction SilentlyContinue
if ($yedPath) {
    Write-Host "yEd installed at: $($yedPath.FullName)" -ForegroundColor Green
} else {
    Write-Host "yEd not found" -ForegroundColor Red
}
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
- Anaconda + Jupyter: ~5GB
- PostgreSQL: ~200MB + data storage (~2GB)
- pgAdmin 4: ~200MB
- VS Code + Extensions: ~500MB
- GitHub Desktop: ~250MB
- yEd Graph Editor: ~150MB
- Java JDK: ~300MB
- Node.js: ~150MB
- Workspace + Projects: ~10GB reserved

**Total Estimated**: ~50GB minimum, 75GB recommended

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

## 🔍 Comprehensive System Verification Script

**Save as `verify_lab_setup.ps1` and run to verify all components:**

```powershell
# Comprehensive Lab Setup Verification Script
# Run as Administrator for complete verification

Write-Host "=================================" -ForegroundColor Cyan
Write-Host "Lab Computer Verification Script" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan

$results = @{}

# Check Windows Version
Write-Host "`nChecking Windows Version..." -ForegroundColor Yellow
$winVer = (Get-WmiObject -class Win32_OperatingSystem).Caption
$results["Windows 11"] = if ($winVer -like "*Windows 11*") {"✓ Installed"} else {"✗ Not Found"}

# Check Core Tools
Write-Host "`nChecking Core Development Tools..." -ForegroundColor Yellow

# Git
$results["Git"] = if (Get-Command git -ErrorAction SilentlyContinue) {
    "✓ " + (git --version)
} else {"✗ Not Installed"}

# GitHub Desktop
$results["GitHub Desktop"] = if (Test-Path "$env:LOCALAPPDATA\GitHubDesktop\GitHubDesktop.exe") {
    "✓ Installed"
} else {"✗ Not Installed"}

# Docker
$results["Docker Desktop"] = if (Get-Command docker -ErrorAction SilentlyContinue) {
    "✓ " + (docker --version)
} else {"✗ Not Installed"}

# VS Code
$results["VS Code"] = if (Get-Command code -ErrorAction SilentlyContinue) {
    "✓ " + (code --version | Select-Object -First 1)
} else {"✗ Not Installed"}

# Python/Anaconda
$results["Python/Anaconda"] = if (Get-Command python -ErrorAction SilentlyContinue) {
    "✓ Python " + (python --version 2>&1).ToString().Split()[1]
} else {"✗ Not Installed"}

# Jupyter
$results["Jupyter Notebooks"] = if (Get-Command jupyter -ErrorAction SilentlyContinue) {
    "✓ " + (jupyter --version 2>&1 | Select-String "notebook" | Select-Object -First 1)
} else {"✗ Not Installed"}

# Java
$results["Java JDK"] = if (Get-Command java -ErrorAction SilentlyContinue) {
    "✓ " + ((java --version 2>&1) | Select-Object -First 1)
} else {"✗ Not Installed"}

# C++ Compiler
$results["C++ Compiler"] = if (Get-Command g++ -ErrorAction SilentlyContinue) {
    "✓ MinGW " + ((g++ --version 2>&1) | Select-Object -First 1)
} elseif (Get-Command cl -ErrorAction SilentlyContinue) {
    "✓ MSVC Installed"
} else {"✗ Not Installed"}

# PostgreSQL
$results["PostgreSQL"] = if (Get-Service -Name postgresql* -ErrorAction SilentlyContinue) {
    "✓ Service Running"
} else {"✗ Not Installed/Running"}

# pgAdmin
$results["pgAdmin 4"] = if (Test-Path "C:\Program Files*\pgAdmin*") {
    "✓ Installed"
} else {"✗ Not Installed"}

# yEd
$yedPath = Get-ChildItem -Path "C:\Program Files*" -Filter "yed.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
$results["yEd Graph Editor"] = if ($yedPath) {
    "✓ Installed"
} else {"✗ Not Installed"}

# Node.js
$results["Node.js"] = if (Get-Command node -ErrorAction SilentlyContinue) {
    "✓ " + (node --version)
} else {"✗ Not Installed"}

# Display Results
Write-Host "`n=================================" -ForegroundColor Cyan
Write-Host "Installation Status Report" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan

foreach ($component in $results.Keys | Sort-Object) {
    $status = $results[$component]
    if ($status -like "✓*") {
        Write-Host "$component : " -NoNewline
        Write-Host $status -ForegroundColor Green
    } else {
        Write-Host "$component : " -NoNewline
        Write-Host $status -ForegroundColor Red
    }
}

# Check VS Code Extensions
Write-Host "`n=================================" -ForegroundColor Cyan
Write-Host "VS Code Extensions Check" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan

if (Get-Command code -ErrorAction SilentlyContinue) {
    $requiredExtensions = @(
        "ms-python.python",
        "ms-toolsai.jupyter",
        "ms-vscode.cpptools",
        "vscjava.vscode-java-pack",
        "ms-azuretools.vscode-docker",
        "ckolkman.vscode-postgres"
    )
    
    $installedExtensions = code --list-extensions
    
    foreach ($ext in $requiredExtensions) {
        if ($installedExtensions -contains $ext) {
            Write-Host "✓ $ext" -ForegroundColor Green
        } else {
            Write-Host "✗ $ext (missing)" -ForegroundColor Red
        }
    }
}

# Check Workspace Directory
Write-Host "`n=================================" -ForegroundColor Cyan
Write-Host "Workspace Directory Check" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan

$workspacePath = "C:\DevWorkspace"
if (Test-Path $workspacePath) {
    Write-Host "✓ DevWorkspace exists" -ForegroundColor Green
    $subfolders = @(
        "Projects\Python\Notebooks",
        "Projects\CPP",
        "Projects\Java",
        "Projects\Database",
        "Resources\Diagrams"
    )
    foreach ($folder in $subfolders) {
        if (Test-Path "$workspacePath\$folder") {
            Write-Host "  ✓ $folder" -ForegroundColor Green
        } else {
            Write-Host "  ✗ $folder (missing)" -ForegroundColor Red
        }
    }
} else {
    Write-Host "✗ DevWorkspace not found" -ForegroundColor Red
}

# Summary
Write-Host "`n=================================" -ForegroundColor Cyan
Write-Host "Summary" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan

$installedCount = ($results.Values | Where-Object {$_ -like "✓*"}).Count
$totalCount = $results.Count
$percentage = [math]::Round(($installedCount / $totalCount) * 100, 1)

Write-Host "Components Installed: $installedCount / $totalCount ($percentage%)" -ForegroundColor $(if ($percentage -ge 90) {"Green"} elseif ($percentage -ge 70) {"Yellow"} else {"Red"})

if ($percentage -lt 100) {
    Write-Host "`nMissing components should be installed to ensure full lab functionality." -ForegroundColor Yellow
} else {
    Write-Host "`nAll components successfully installed! Lab is ready for use." -ForegroundColor Green
}

Write-Host "`nPress any key to exit..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
```

---

**This specification provides complete Windows 11 lab computer configuration for comprehensive development education including:**
- ✅ **Python Development** with Anaconda & Jupyter Notebooks
- ✅ **C++ Development** with VS Code & Build Tools
- ✅ **Java Development** with OpenJDK 17 LTS
- ✅ **Database Development** with PostgreSQL & pgAdmin 4
- ✅ **Version Control** with Git & GitHub Desktop
- ✅ **Containerization** with Docker Desktop
- ✅ **Diagramming** with yEd Graph Editor
- ✅ **Modern IDE** with VS Code & Extensions

**All key components verified and ready for deployment!** 🎯

---

*This comprehensive IT specification supports the simplified C++ course and broader programming curriculum with professional development tools and practices. Updated to include all requested components for Windows 11 lab environment.*