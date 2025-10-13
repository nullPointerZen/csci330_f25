# Chapter 17: Filesystems - Quick Help (Supplemental)

## Top 3 Filesystem Errors

### 1. Permission Denied
```cpp
try {
    fs::remove("protected_file.txt");
} catch (const fs::filesystem_error& e) {
    std::cout << "Error: " << e.what() << std::endl;
    // Handle gracefully
}
```

### 2. Path Not Found  
```cpp
if (fs::exists(path)) {
    // Safe to operate on path
} else {
    std::cout << "Path does not exist: " << path << std::endl;
}
```

### 3. Cross-platform Path Issues
```cpp
// ✅ Good: Use filesystem::path
fs::path p = fs::path("folder") / "file.txt";

// ❌ Bad: Hard-coded separators
std::string bad = "folder\\file.txt";  // Windows only
```

## Quick Fixes
- Always use try-catch for filesystem operations
- Check `fs::exists()` before operations
- Use `fs::path` for cross-platform compatibility

---

*This is a supplemental chapter - focus on core concepts first.*