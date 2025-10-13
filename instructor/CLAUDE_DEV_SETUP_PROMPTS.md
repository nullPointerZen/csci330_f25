# Claude Prompts for Development Environment Setup
## For Students Using Free Claude Tier

Copy and paste these prompts one at a time into Claude to get help setting up your development environment.

---

## Prompt 1: Initial System Check
```
I need to set up a C++ development environment for my CSCI 330 course. My operating system is [INSERT: Windows/macOS/Linux]. 

Please provide:
1. A checklist of what software I need to install
2. System requirements I should verify
3. Any preliminary steps before installation
```

---

## Prompt 2: Installing a C++ Compiler

### For Windows Users:
```
I'm on Windows and need to install a C++ compiler for CSCI 330. Should I use:
1. MinGW-w64
2. MSYS2
3. Visual Studio Build Tools
4. WSL2 with g++

Please explain the best option for a beginner and provide step-by-step installation instructions.
```

### For macOS Users:
```
I'm on macOS and need to install a C++ compiler for CSCI 330. I've heard about Xcode Command Line Tools and Homebrew.

Please provide:
1. Step-by-step instructions to install Xcode Command Line Tools
2. How to verify the installation with terminal commands
3. Whether I need to install g++ separately via Homebrew
```

### For Linux Users:
```
I'm on [INSERT: Ubuntu/Debian/Fedora/other] Linux and need to install g++ and build-essential tools for CSCI 330.

Please provide:
1. The exact terminal commands to install the compiler
2. How to verify the installation
3. Any additional development tools I should install
```

---

## Prompt 3: Installing CMake
```
I need to install CMake for my C++ course. I'm using [INSERT: Windows/macOS/Linux].

Please provide:
1. The recommended way to install CMake on my system
2. Step-by-step installation instructions
3. How to verify CMake is installed correctly (what command to run)
4. How to check if I have the minimum required version (3.10+)
```

---

## Prompt 4: Installing Git
```
I need to install Git for version control in my CSCI 330 course. I'm using [INSERT: Windows/macOS/Linux].

Please provide:
1. Installation instructions for Git on my system
2. Basic Git configuration commands I should run after installation (setting name and email)
3. How to verify Git is installed correctly
4. How to generate an SSH key for GitHub (if needed)
```

---

## Prompt 5: Installing VS Code
```
I want to install Visual Studio Code as my code editor for C++ development. I'm using [INSERT: Windows/macOS/Linux].

Please provide:
1. Download link and installation steps for VS Code
2. Essential C++ extensions I should install (C/C++, CMake Tools, etc.)
3. Basic settings I should configure for C++ development
4. How to open a terminal within VS Code
```

---

## Prompt 6: Testing the Setup
```
I've installed g++, CMake, Git, and VS Code for my C++ course. I want to test if everything works.

Please provide:
1. A simple "Hello World" C++ program I can create
2. The terminal commands to compile it with g++
3. A simple CMakeLists.txt file to test CMake
4. Commands to build and run using CMake
5. How to initialize a Git repository and make my first commit
```

---

## Prompt 7: Troubleshooting Common Issues

### If Compiler Not Found:
```
When I run "g++ --version" in my terminal, I get "command not found" error. I'm on [INSERT: Windows/macOS/Linux] and I already installed [INSERT: what you installed].

How do I:
1. Check if it's a PATH issue
2. Add the compiler to my PATH
3. Verify the installation location
```

### If CMake Issues:
```
I'm getting an error when running CMake: [INSERT: exact error message]. I'm using [INSERT: Windows/macOS/Linux].

Please help me:
1. Understand what this error means
2. Fix the issue step by step
3. Verify the fix worked
```

### If VS Code Can't Find Compiler:
```
VS Code can't find my C++ compiler. The IntelliSense is showing errors even though my code compiles fine in the terminal. I'm using [INSERT: Windows/macOS/Linux].

How do I:
1. Configure VS Code to find my compiler
2. Set up the C++ extension properly
3. Fix IntelliSense configuration
```

---

## Prompt 8: Project Structure Setup
```
I need to set up the correct folder structure for my CSCI 330 assignments. The course uses this structure:
- assignments/chapter_XX/ for each chapter's work
- Each assignment needs src/, tests/, and CMakeLists.txt

Please provide:
1. Terminal commands to create this structure
2. A template CMakeLists.txt for a basic C++ project
3. How to organize multiple .cpp files
4. Git commands to track these folders
```

---

## Prompt 9: Working with Course Repository
```
My CSCI 330 course has a Git repository I need to clone. After cloning, I need to:
1. Create my own branch for assignments
2. Understand the difference between 'git add', 'git commit', and 'git push'
3. Know how to update my local copy when the instructor updates the main repository

Please explain these Git concepts simply and provide the exact commands I'll need.
```

---

## Prompt 10: Final Verification
```
I want to verify my entire C++ development environment is ready for CSCI 330. Please provide a checklist of commands I should run to verify:

1. Compiler (g++ or clang++) is installed and accessible
2. CMake is installed (version 3.10+)
3. Git is installed and configured
4. I can create, compile, and run a C++ program
5. I can use CMake to build a project
6. VS Code is set up with C++ extensions

For each item, give me the exact command to run and what output indicates success.
```

---

## Tips for Using These Prompts:

1. **Be Specific**: Always fill in the [INSERT] placeholders with your actual information
2. **Copy Error Messages**: If you get errors, copy the EXACT error message into your next prompt
3. **One Step at a Time**: Complete each installation before moving to the next
4. **Save Responses**: Copy Claude's responses to a document for future reference
5. **Ask Follow-ups**: If something isn't clear, ask Claude to explain in simpler terms

## Additional Help Prompts:

### If You're Stuck:
```
I'm trying to [INSERT: what you're trying to do] but I'm getting this error:
[PASTE: exact error message]

I've already tried:
1. [What you tried]
2. [What else you tried]

I'm using [INSERT: Windows/macOS/Linux]. Please help me fix this step by step.
```

### For Conceptual Understanding:
```
I don't understand [INSERT: concept like PATH variable, compiler, etc.] in the context of C++ development. Please explain:
1. What it is in simple terms
2. Why I need it for my course
3. A real-world analogy to help me understand
```