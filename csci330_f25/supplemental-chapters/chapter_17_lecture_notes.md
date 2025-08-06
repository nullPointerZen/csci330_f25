# Chapter 17: Filesystems - Complete Guide (Supplemental)

## 🎯 Learning Objectives (5 minutes)

**This is a supplemental chapter** - master core concepts and streams before exploring filesystems.

By the end of this chapter, you will:
- **Navigate filesystems programmatically** - List directories, check file properties
- **Handle paths safely** - Use std::filesystem::path for cross-platform compatibility
- **Manipulate files and directories** - Create, copy, move, and delete filesystem objects
- **Process directories recursively** - Walk directory trees efficiently
- **Handle filesystem errors** - Deal with permissions and access issues gracefully

**Time Commitment**: ~3 hours (supplemental)

---

## 📚 Core Concepts

### Python/Java Developers: Filesystem Comparison

| Operation | Python | Java | C++ |
|-----------|---------|------|-----|
| **Check file exists** | `os.path.exists()` | `Files.exists()` | `std::filesystem::exists()` |
| **List directory** | `os.listdir()` | `Files.list()` | `std::filesystem::directory_iterator` |
| **File size** | `os.path.getsize()` | `Files.size()` | `std::filesystem::file_size()` |
| **Create directory** | `os.makedirs()` | `Files.createDirectories()` | `std::filesystem::create_directories()` |
| **Copy file** | `shutil.copy()` | `Files.copy()` | `std::filesystem::copy_file()` |

**Key Insight**: C++17's `std::filesystem` provides modern, cross-platform filesystem operations.

---

## 1. Filesystem Library Basics

### Path Handling

```cpp
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    // Cross-platform path construction
    fs::path p1 = "folder/file.txt";
    fs::path p2 = fs::path("folder") / "file.txt";  // Preferred
    
    // Path components
    fs::path full_path = "/home/user/documents/report.pdf";
    std::cout << "Root: " << full_path.root_path() << std::endl;        // /
    std::cout << "Parent: " << full_path.parent_path() << std::endl;    // /home/user/documents
    std::cout << "Filename: " << full_path.filename() << std::endl;     // report.pdf
    std::cout << "Stem: " << full_path.stem() << std::endl;             // report
    std::cout << "Extension: " << full_path.extension() << std::endl;   // .pdf
    
    return 0;
}
```

### File Status and Properties

```cpp
#include <filesystem>
#include <iostream>
#include <chrono>

namespace fs = std::filesystem;

void show_file_info(const fs::path& p) {
    try {
        if (fs::exists(p)) {
            std::cout << "File: " << p << std::endl;
            
            // File type
            if (fs::is_regular_file(p)) {
                std::cout << "  Type: Regular file" << std::endl;
                std::cout << "  Size: " << fs::file_size(p) << " bytes" << std::endl;
            } else if (fs::is_directory(p)) {
                std::cout << "  Type: Directory" << std::endl;
            } else if (fs::is_symlink(p)) {
                std::cout << "  Type: Symbolic link" << std::endl;
            }
            
            // Last write time
            auto ftime = fs::last_write_time(p);
            std::cout << "  Last modified: " << std::chrono::duration_cast<std::chrono::seconds>(
                ftime.time_since_epoch()).count() << " seconds since epoch" << std::endl;
                
        } else {
            std::cout << "File does not exist: " << p << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Filesystem error: " << e.what() << std::endl;
    }
}
```

---

## 2. Directory Operations

### Listing Directory Contents

```cpp
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void list_directory(const fs::path& dir_path) {
    try {
        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
            std::cout << "Contents of " << dir_path << ":" << std::endl;
            
            for (const auto& entry : fs::directory_iterator(dir_path)) {
                std::cout << "  " << entry.path().filename();
                
                if (entry.is_directory()) {
                    std::cout << "/";
                } else if (entry.is_regular_file()) {
                    std::cout << " (" << entry.file_size() << " bytes)";
                }
                std::cout << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Recursive directory listing
void list_recursively(const fs::path& dir_path, int depth = 0) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
            // Print with indentation based on depth
            std::string indent(entry.depth() * 2, ' ');
            std::cout << indent << entry.path().filename() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

### Creating and Managing Directories

```cpp
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void directory_operations() {
    try {
        // Create single directory
        fs::path new_dir = "test_folder";
        if (fs::create_directory(new_dir)) {
            std::cout << "Created directory: " << new_dir << std::endl;
        }
        
        // Create directory hierarchy
        fs::path nested = "parent/child/grandchild";
        if (fs::create_directories(nested)) {
            std::cout << "Created directory tree: " << nested << std::endl;
        }
        
        // Remove directory (must be empty)
        if (fs::remove(new_dir)) {
            std::cout << "Removed directory: " << new_dir << std::endl;
        }
        
        // Remove directory tree recursively
        std::uintmax_t removed = fs::remove_all("parent");
        std::cout << "Removed " << removed << " files/directories" << std::endl;
        
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

---

## 3. File Operations

### Copying and Moving Files

```cpp
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void file_operations() {
    try {
        fs::path source = "source.txt";
        fs::path dest = "destination.txt";
        fs::path backup = "backup.txt";
        
        // Copy file
        if (fs::exists(source)) {
            fs::copy_file(source, dest);
            std::cout << "Copied " << source << " to " << dest << std::endl;
            
            // Copy with options
            fs::copy_file(source, backup, fs::copy_options::overwrite_existing);
            std::cout << "Created backup copy" << std::endl;
        }
        
        // Move/rename file
        fs::path new_name = "renamed.txt";
        if (fs::exists(dest)) {
            fs::rename(dest, new_name);
            std::cout << "Renamed " << dest << " to " << new_name << std::endl;
        }
        
        // Remove file
        if (fs::remove(backup)) {
            std::cout << "Removed backup file" << std::endl;
        }
        
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

---

## 4. Practical Applications

### File Search Utility

```cpp
#include <filesystem>
#include <iostream>
#include <string>
#include <regex>

namespace fs = std::filesystem;

class FileSearcher {
public:
    void find_files_by_extension(const fs::path& root, const std::string& extension) {
        try {
            std::cout << "Searching for *" << extension << " files in " << root << std::endl;
            
            for (const auto& entry : fs::recursive_directory_iterator(root)) {
                if (entry.is_regular_file() && entry.path().extension() == extension) {
                    std::cout << "Found: " << entry.path() << " ("
                              << entry.file_size() << " bytes)" << std::endl;
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cout << "Search error: " << e.what() << std::endl;
        }
    }
    
    void find_files_by_pattern(const fs::path& root, const std::string& pattern) {
        try {
            std::regex regex_pattern(pattern);
            std::cout << "Searching for files matching pattern: " << pattern << std::endl;
            
            for (const auto& entry : fs::recursive_directory_iterator(root)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().filename().string();
                    if (std::regex_match(filename, regex_pattern)) {
                        std::cout << "Found: " << entry.path() << std::endl;
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cout << "Search error: " << e.what() << std::endl;
        } catch (const std::regex_error& e) {
            std::cout << "Regex error: " << e.what() << std::endl;
        }
    }
};

int main() {
    FileSearcher searcher;
    
    // Find all .cpp files
    searcher.find_files_by_extension(".", ".cpp");
    
    // Find files matching pattern
    searcher.find_files_by_pattern(".", R"(test_.*\.cpp)");
    
    return 0;
}
```

---

## 🧩 Quick Problems

### Problem 1: Directory Size Calculator
Calculate the total size of all files in a directory tree.

### Problem 2: Duplicate File Finder
Find files with the same content in different locations.

### Problem 3: Backup Utility
Create a simple backup program that copies changed files.

See [chapter_17_problems.md](chapter_17_problems.md) for detailed problems.

---

## ✅ Success Checklist

- [ ] Can navigate filesystem paths safely
- [ ] List directory contents recursively
- [ ] Create and remove directories
- [ ] Copy, move, and delete files
- [ ] Handle filesystem errors gracefully
- [ ] Build practical file utilities

---

## 🚀 What's Next

**Filesystem operations are essential** for many applications. Combined with streams (Chapter 16), you can build powerful file processing tools.

**Continue with**: Chapter 18 (Algorithms) or apply these skills to build file management utilities.

---

*This is a supplemental chapter - master core concepts first, then return to explore filesystem programming.*