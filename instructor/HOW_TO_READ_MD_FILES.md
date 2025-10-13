# How to Read Course Documentation Files (.md)

All course materials are written in Markdown (.md) files. If you're seeing strange symbols like ### and ``` everywhere, this guide will help.

---

## Quick Fix: Making Files Readable

### Method 1: VSCode Markdown Preview (Recommended)
Once you have VSCode installed:
1. Open any .md file in VSCode
2. Press `Ctrl+Shift+V` (Windows/Linux) or `Cmd+Shift+V` (Mac)
3. The file will display formatted and easy to read

**Alternative:** Click the preview button (📄 with 🔍) in the top right corner of VSCode

### Method 2: Browser Viewer
1. Save the `markdown_viewer.html` file from Canvas
2. Open it in your web browser (Chrome, Firefox, Edge, Safari)
3. Drag any .md file onto the browser window
4. The file will display formatted

### Method 3: View on GitHub
If the files are on GitHub:
1. Navigate to the file on GitHub
2. GitHub automatically renders Markdown files
3. Much easier to read than raw text

---

## Understanding Raw Markdown Symbols

If you must read the raw text file, here's what the symbols mean:

| What You See | What It Means | Example |
|-------------|---------------|---------|
| `# Title` | Main heading | Chapter or section title |
| `## Subtitle` | Subheading | Section within chapter |
| `### Small Title` | Sub-subheading | Specific topic |
| ``` code ``` | Code block or commands | Stuff you type exactly |
| `- item` or `* item` | Bullet point list | Things to do or remember |
| `1. item` | Numbered list | Steps to follow in order |
| `**bold**` | Important text | Pay attention to this |
| `*italic*` | Emphasized text | Notable but not critical |
| `[text](link)` | Clickable link | Goes to a website |
| `> quote` | Quoted text or note | Additional information |
| Regular text | Normal instructions | Just read it normally |

---

## Examples

### What you see in raw Markdown:
```
## Step 1: Install Software

**Important:** You need admin access

1. Download from https://example.com
2. Run the installer
3. Enter this command:
   ```
   install --version latest
   ```

> Note: This may take 5 minutes
```

### What it means:
- "Step 1: Install Software" is a section header
- "Important: You need admin access" is a bold warning
- The numbered items are steps to follow in order
- `install --version latest` is a command to type exactly
- "Note: This may take 5 minutes" is additional information

---

## Common Confusion Points

### Code Blocks
When you see:
```
git clone https://github.com/username/repo.git
cd repo
```

This means:
- Type these commands exactly as shown
- Press Enter after each line
- Don't type the ``` marks

### File Paths
- `/Users/name/Desktop` - Mac/Linux path
- `C:\Users\name\Desktop` - Windows path
- `~/Desktop` - Shortcut for your user's Desktop

### Keyboard Shortcuts
- `Ctrl+C` means: Hold Ctrl key and press C
- `Cmd+Shift+P` means: Hold Cmd and Shift keys, then press P

---

## Best Practices

1. **Install VSCode early** - Makes reading all other files easier
2. **Use the preview feature** - Don't struggle with raw text
3. **Keep this guide handy** - Reference it when confused
4. **Ask for help** - If formatting is still confusing, ask in office hours

---

## Setting VSCode as Default for .md Files

### Windows:
1. Right-click any .md file
2. Select "Open with" → "Choose another app"
3. Select VSCode
4. Check "Always use this app"

### Mac:
1. Right-click any .md file
2. Select "Get Info"
3. Under "Open with" select VSCode
4. Click "Change All..."

### Linux:
1. Right-click any .md file
2. Select "Properties" → "Open With"
3. Select VSCode
4. Set as default

Now all .md files will open in VSCode automatically!

---

**Remember:** These files are meant to be viewed formatted, not as raw text. Once you set up VSCode with preview, everything becomes much clearer!