# Chapter 16: Streams - Quick Help (Supplemental)

## Top 3 Stream Errors

### 1. File Not Opening
```cpp
std::ifstream file("data.txt");
if (!file) {  // Always check!
    std::cerr << "Cannot open file" << std::endl;
    return 1;
}
```

### 2. Stream State Issues
```cpp
int value;
while (stream >> value) {  // Stops on failure
    process(value);
}
// Check why it stopped
if (stream.eof()) {
    // Normal end
} else {
    // Error occurred
}
```

### 3. Formatting Persistence
```cpp
std::cout << std::setprecision(2) << 3.14159 << std::endl;  // 3.1
std::cout << 2.71828 << std::endl;  // Still 2.7! Formatting persists
```

## Quick Fixes
- Always check file opening: `if (!file)`
- Use RAII: files close automatically
- Reset formatting: `std::cout << std::resetiosflags(std::ios::floatfield)`

---

*This is a supplemental chapter - focus on core concepts first.*