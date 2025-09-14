# Claude Prompts for Students - Development Setup Guide
## Using Free Claude to Navigate Course Materials

These prompts help students work through the existing course setup documentation using free Claude as a reading/comprehension assistant.

---

## Prompt 1: Finding the Right Setup Guide
```
I'm taking CSCI 330 and need to set up my development environment. I have a course repository with these files in the setup folder:
- DEVELOPMENT_SETUP.md
- GIT_WORKFLOW.md
- docker-compose.yml
- Dockerfile
- test_integration.sh

I'm using [Windows/macOS/Linux]. Which file should I start with, and what order should I read them?
```

---

## Prompt 2: Understanding the Setup Steps
```
I'm reading DEVELOPMENT_SETUP.md for CSCI 330. It says I need:
1. C++ compiler (g++ 7+ or clang++ 6+)
2. CMake (3.10+)
3. Git
4. Text editor (VS Code recommended)

I'm on [Windows/macOS/Linux]. Can you explain what each of these does in simple terms and why I need them for the course?
```

---

## Prompt 3: Breaking Down Installation Instructions
```
The DEVELOPMENT_SETUP.md file has this section for [Windows/macOS/Linux]:
[PASTE THE RELEVANT SECTION HERE]

I'm confused about [specific part]. Can you:
1. Explain what this step is doing
2. Break it down into smaller steps
3. Tell me what success looks like for this step
```

---

## Prompt 4: Understanding Terminal Commands
```
The setup guide tells me to run these commands:
[PASTE COMMANDS HERE]

I'm not familiar with terminal/command line. Can you:
1. Explain what each command does
2. Tell me where I should run these (what directory)
3. What output I should expect to see
```

---

## Prompt 5: Verifying Each Step
```
I just completed [describe what you did, e.g., "installing g++ on Windows using MinGW"].

The guide says to verify with: [PASTE VERIFICATION COMMAND]

I got this output:
[PASTE YOUR OUTPUT]

Is this correct? If not, what might be wrong?
```

---

## Prompt 6: Understanding Git Workflow
```
I'm reading GIT_WORKFLOW.md and it mentions:
- Cloning the repository
- Creating a personal branch
- Making commits
- Pull requests

I've never used Git before. Can you explain these concepts using a simple analogy, like working on a group document?
```

---

## Prompt 7: Troubleshooting Setup Issues
```
I'm following DEVELOPMENT_SETUP.md for [Windows/macOS/Linux] and at the step where it says:
[PASTE THE STEP]

I get this error:
[PASTE EXACT ERROR]

What does this error mean and what should I check?
```

---

## Prompt 8: Understanding File Paths
```
The setup guide mentions paths like:
- /Users/Development/cpp (macOS/Linux)
- C:\Development\cpp (Windows)
- ~/assignments

I'm confused about:
1. What ~ means
2. Where I should actually create my folders
3. How to navigate to these locations in terminal

Can you explain file paths for beginners?
```

---

## Prompt 9: Project Structure Comprehension
```
The course repository has this structure:
assignments/
├── chapter_01/
├── chapter_02/
modules/
├── module-01/
├── module-02/

The guide says I should work in assignments/. Can you:
1. Explain this folder structure 
2. Tell me where my actual code files will go
3. Explain why organization matters for this course
```

---

## Prompt 10: Checking Your Progress
```
I think I've completed the setup. The DEVELOPMENT_SETUP.md has a "Verification" section that says to check:
[PASTE VERIFICATION STEPS]

Here's what I get for each check:
1. g++ --version: [YOUR OUTPUT]
2. cmake --version: [YOUR OUTPUT]
3. git --version: [YOUR OUTPUT]

Have I successfully completed the setup?
```

---

## Troubleshooting Prompts

### When Instructions Are Unclear:
```
In DEVELOPMENT_SETUP.md, there's this instruction:
[PASTE THE CONFUSING INSTRUCTION]

I don't understand what [specific part] means. Can you rephrase this in simpler terms for someone new to programming?
```

### When You're Not Sure Where You Are:
```
The setup guide assumes I know how to [do something, like "open a terminal" or "navigate to a directory"].

I don't know how to do this on [Windows/macOS/Linux]. Can you give me the basic steps?
```

### When Something Seems Missing:
```
I'm at this step in DEVELOPMENT_SETUP.md:
[PASTE THE STEP]

But I can't find [what you're looking for]. The guide seems to assume I have [something]. What might I be missing?
```

---

## Meta-Prompt (If Really Stuck):
```
I'm trying to set up my development environment for CSCI 330 using the course's DEVELOPMENT_SETUP.md file, but I'm completely lost.

My situation:
- Operating system: [Windows/macOS/Linux]
- What I've done so far: [LIST WHAT YOU'VE TRIED]
- Where I'm stuck: [DESCRIBE THE PROBLEM]

Can you help me create a checklist of what I need to do, starting from the very beginning?
```

---

## Tips for Students:

1. **Copy-Paste is Your Friend**: Copy exact text from the setup guides into your prompts
2. **Include Error Messages**: Always paste the EXACT error message, not a summary
3. **Be Specific**: Say which file you're reading and which section
4. **Work Sequentially**: Don't skip ahead - complete each step before moving on
5. **Ask for Analogies**: If technical concepts are confusing, ask Claude to explain using everyday examples

## Remember:
- Claude can't see your screen or access your files
- Claude helps you understand the instructions, not replace them
- The course materials are the source of truth
- When in doubt, ask your instructor or TA