# C++ Development Environment Setup

**One-time setup for all course chapters**

This guide establishes the standard development environment used throughout the entire C++ course. Complete this setup once, then use it for all chapters.

---

## 🎯 What You'll Have After Setup

- **VS Code** with C++ support for editing and debugging
- **Docker** containerized C++ environment (no local compiler needed)
- **Consistent workflow** that works on Windows, macOS, and Linux
- **Ready for all chapters** - no additional setup required

---

## 🛠️ Installation (15 minutes)

### Step 1: Install VS Code
1. Download from [code.visualstudio.com](https://code.visualstudio.com)
2. Install with default settings
3. Launch VS Code

### Step 2: Install Docker Desktop
1. Download from [docker.com/products/docker-desktop](https://docker.com/products/docker-desktop)
2. Install with default settings
3. Launch Docker Desktop
4. Wait for it to fully start (Docker icon in system tray should be running)

### Step 3: Install VS Code Extensions
Open VS Code and install these extensions:
1. **C/C++** (by Microsoft) - Essential for C++ support
2. **Dev Containers** (by Microsoft) - For Docker integration
3. **C/C++ Extension Pack** (by Microsoft) - Includes additional tools

**How to install extensions:**
- Press `Ctrl+Shift+X` (Cmd+Shift+X on macOS)
- Search for each extension name
- Click "Install"

---

## 🚀 Quick Test (5 minutes)

Let's verify everything works:

### Step 1: Create Test Project
```bash
mkdir cpp-course-test
cd cpp-course-test
code .
```

### Step 2: Create Test File
Create `hello.cpp`:
```cpp
#include <iostream>
int main() {
    std::cout << "Development environment ready!" << std::endl;
    return 0;
}
```

### Step 3: Test Compilation
Open VS Code terminal (`Ctrl+`` ` or Terminal menu) and run:
```bash
g++ hello.cpp -o hello && ./hello
```

**Expected output:** `Development environment ready!`

---

## 📁 Project Structure (Standard for All Chapters)

Each chapter will use this consistent structure:
```
chapter_XX/
├── .vscode/
│   ├── tasks.json      # Build configuration
│   └── launch.json     # Debug configuration
├── src/
│   └── main.cpp        # Your code goes here
└── README.md           # Chapter-specific instructions
```

VS Code configuration files will be provided with each chapter for immediate use.

---

## 🔍 Essential VS Code Features

### Compilation Shortcuts
- **Build**: `Ctrl+Shift+B` (Cmd+Shift+B) - Compiles your code
- **Run**: `Ctrl+F5` (Cmd+F5) - Runs without debugging
- **Debug**: `F5` - Runs with debugging enabled

### Debugging Features
- **Set breakpoint**: Click left margin next to line numbers
- **Variables panel**: See variable values during debugging
- **Watch panel**: Monitor specific expressions
- **Call stack**: See function call hierarchy

### Helpful Shortcuts
- **Terminal**: `Ctrl+`` ` - Opens integrated terminal
- **Command palette**: `Ctrl+Shift+P` - Access all VS Code commands
- **File explorer**: `Ctrl+Shift+E` - Navigate project files
- **Problems panel**: `Ctrl+Shift+M` - See compilation errors

---

## 🐳 Docker Integration (Advanced)

For chapters that mention Docker (optional enhancement):

### Create Dockerfile
```dockerfile
FROM gcc:latest
WORKDIR /usr/src/app
COPY . .
RUN g++ -o main main.cpp
CMD ["./main"]
```

### Build and Run
```bash
docker build -t cpp-chapter .
docker run cpp-chapter
```

**Note**: Docker usage is optional. The standard setup works for all chapters.

---

## 🚨 Troubleshooting

### VS Code Issues
**Extensions not working?**
- Restart VS Code
- Check that C/C++ extension is enabled
- Try `Ctrl+Shift+P` → "C/C++: Reset IntelliSense Database"

**Build task not found?**
- Ensure `.vscode/tasks.json` exists in your project
- Check that file content matches provided configuration

### Compilation Issues
**"g++ not found" error?**
- **Windows**: Install "Microsoft C++ Build Tools" or Visual Studio
- **macOS**: Install Xcode command line tools: `xcode-select --install`
- **Linux**: Install build-essential: `sudo apt install build-essential`

**Include errors?**
- Verify file names match exactly (case-sensitive)
- Check that all required headers are included
- Ensure code syntax is correct

### Docker Issues
**Docker commands not working?**
- Ensure Docker Desktop is running
- Try: `docker run hello-world` to test basic functionality
- Restart Docker Desktop if needed

---

## ✅ Setup Complete!

You're now ready for all course chapters. Each chapter will:
1. Provide pre-configured `.vscode` files
2. Reference this setup guide if you need to troubleshoot
3. Focus on learning C++ concepts rather than environment issues

**Next steps:**
- Start with Chapter 1 if you're beginning the course
- Each chapter folder will have its own README with specific instructions
- Return to this guide only if you encounter environment issues

---

## 📖 Chapter Integration

This setup enables consistent development across all chapters:

- **Chapters 1-4**: Basic C++ concepts with debugging
- **Chapters 5-8**: Advanced features with step-through debugging
- **Chapters 9-12**: Complex projects with integrated development
- **Chapters 13-14**: STL usage with container/iterator visualization

The same VS Code + compiler workflow applies to everything!