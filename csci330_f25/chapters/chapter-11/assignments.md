# Chapter 11: Smart Pointers - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 11 "Smart Pointers"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: Basic Smart Pointer Usage (45 minutes)

### Problem 1.1: Converting Raw Pointers to `unique_ptr` (15 minutes)

**Scenario**: You have a legacy class that uses raw pointers. Convert it to use `unique_ptr`.

**Given code**:
```cpp
#include <iostream>
#include <string>

class DataProcessor {
private:
    int* data;
    size_t size;

public:
    DataProcessor(size_t n) : size(n) {
        data = new int[n];
        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<int>(i * i);
        }
    }
    
    ~DataProcessor() {
        delete[] data;
    }
    
    // Copy constructor and assignment operator needed but missing!
    
    void print_data() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    
    int get_value(size_t index) const {
        if (index < size) return data[index];
        return -1;
    }
};
```

**Your Task**:
1. Convert the `DataProcessor` class to use `std::unique_ptr<int[]>` instead of raw pointers
2. Remove the destructor (no longer needed)
3. Test your implementation with this main function:

```cpp
int main() {
    DataProcessor processor(5);
    processor.print_data();
    
    DataProcessor processor2 = std::move(processor);  // Test move semantics
    processor2.print_data();
    
    std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
    return 0;
}
```

**Expected Output**:
```
0 1 4 9 16 
0 1 4 9 16 
Value at index 3: 9
```

### Problem 1.2: Factory Pattern with `unique_ptr` (15 minutes)

**Scenario**: Create a factory that produces different types of shapes using smart pointers.

**Your Task**:
```cpp
#include <memory>
#include <iostream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double area() const = 0;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() const override {
        std::cout << "Drawing circle with radius " << radius << std::endl;
    }
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void draw() const override {
        std::cout << "Drawing rectangle " << width << "x" << height << std::endl;
    }
    double area() const override {
        return width * height;
    }
};

class ShapeFactory {
public:
    // TODO: Implement this method
    static std::unique_ptr<Shape> create_shape(const std::string& type, double param1, double param2 = 0);
};
```

Complete the `create_shape` method that:
- Returns a `Circle` if type is "circle" (uses param1 as radius, ignores param2)
- Returns a `Rectangle` if type is "rectangle" (uses param1 as width, param2 as height)
- Returns `nullptr` for unknown types

Test with:
```cpp
int main() {
    auto circle = ShapeFactory::create_shape("circle", 5.0);
    auto rectangle = ShapeFactory::create_shape("rectangle", 3.0, 4.0);
    auto unknown = ShapeFactory::create_shape("triangle", 1.0, 2.0);
    
    if (circle) {
        circle->draw();
        std::cout << "Area: " << circle->area() << std::endl;
    }
    
    if (rectangle) {
        rectangle->draw();
        std::cout << "Area: " << rectangle->area() << std::endl;
    }
    
    if (!unknown) {
        std::cout << "Unknown shape type" << std::endl;
    }
    
    return 0;
}
```

### Problem 1.3: Resource Management with RAII (15 minutes)

**Scenario**: Create a file manager that automatically closes files using smart pointers and custom deleters.

**Your Task**:
```cpp
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

class FileManager {
private:
    // TODO: Use unique_ptr with custom deleter for FILE*
    std::unique_ptr<FILE, decltype(&std::fclose)> file;
    
public:
    // TODO: Implement constructor that opens file
    FileManager(const std::string& filename, const std::string& mode);
    
    // TODO: Implement write method
    bool write(const std::string& data);
    
    // TODO: Implement read method
    std::string read_line();
    
    // TODO: Implement method to check if file is open
    bool is_open() const;
};
```

**Requirements**:
1. Constructor should open the file and store it in the `unique_ptr`
2. Use a custom deleter that calls `std::fclose`
3. `write` should return true on success, false on failure
4. `read_line` should read one line from the file
5. File should automatically close when `FileManager` is destroyed

**Test your implementation**:
```cpp
int main() {
    {
        FileManager writer("test.txt", "w");
        if (writer.is_open()) {
            writer.write("Hello, Smart Pointers!\n");
            writer.write("RAII is awesome!\n");
        }
    }  // File automatically closed here
    
    {
        FileManager reader("test.txt", "r");
        if (reader.is_open()) {
            std::cout << "Line 1: " << reader.read_line();
            std::cout << "Line 2: " << reader.read_line();
        }
    }  // File automatically closed here
    
    return 0;
}
```

---

## Problem Set 2: Shared Ownership and Reference Counting (45 minutes)

### Problem 2.1: Document Sharing System (20 minutes)

**Scenario**: Build a document sharing system where multiple editors and viewers can access the same document.

**Your Task**:
```cpp
#include <memory>
#include <iostream>
#include <string>
#include <vector>

class Document {
private:
    std::string title;
    std::string content;
    
public:
    Document(const std::string& t, const std::string& c) 
        : title(t), content(c) {
        std::cout << "Document '" << title << "' created" << std::endl;
    }
    
    ~Document() {
        std::cout << "Document '" << title << "' destroyed" << std::endl;
    }
    
    const std::string& get_title() const { return title; }
    const std::string& get_content() const { return content; }
    void set_content(const std::string& new_content) { content = new_content; }
};

class Editor {
private:
    std::string name;
    // TODO: Add shared_ptr to Document
    
public:
    // TODO: Implement constructor
    Editor(const std::string& editor_name, std::shared_ptr<Document> doc);
    
    // TODO: Implement destructor that announces editor closing
    ~Editor();
    
    // TODO: Implement edit method
    void edit(const std::string& new_content);
    
    // TODO: Implement method to show document info and reference count
    void show_info() const;
};

class Viewer {
private:
    std::string name;
    // TODO: Add shared_ptr to Document
    
public:
    // TODO: Implement constructor  
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> doc);
    
    // TODO: Implement destructor that announces viewer closing
    ~Viewer();
    
    // TODO: Implement view method
    void view() const;
    
    // TODO: Implement method to show reference count
    void show_ref_count() const;
};
```

**Test your implementation**:
```cpp
int main() {
    auto document = std::make_shared<Document>("Report.txt", "Initial content");
    
    std::cout << "\nCreating editors and viewers...\n";
    {
        Editor editor1("Alice", document);
        Editor editor2("Bob", document);
        Viewer viewer1("Charlie", document);
        
        editor1.show_info();  // Should show ref count = 4 (document + 3 users)
        
        editor1.edit("Alice's changes");
        viewer1.view();
        
        {
            Viewer viewer2("Dave", document);
            viewer2.show_ref_count();  // Should show ref count = 5
        }
        std::cout << "Dave's viewer destroyed\n";
        
        editor2.show_info();  // Should show ref count = 4 again
    }
    std::cout << "All editors and viewers destroyed\n";
    
    std::cout << "Document ref count: " << document.use_count() << std::endl;
    
    return 0;
}  // Document should be destroyed here
```

### Problem 2.2: Caching System with Shared Resources (25 minutes)

**Scenario**: Implement a resource cache that shares expensive-to-create objects.

**Your Task**:
```cpp
#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>

class ExpensiveResource {
private:
    std::string id;
    int creation_cost;
    
public:
    ExpensiveResource(const std::string& resource_id) 
        : id(resource_id), creation_cost(100) {
        std::cout << "Creating expensive resource: " << id 
                  << " (cost: " << creation_cost << ")" << std::endl;
    }
    
    ~ExpensiveResource() {
        std::cout << "Destroying resource: " << id << std::endl;
    }
    
    const std::string& get_id() const { return id; }
    void use() const {
        std::cout << "Using resource: " << id << std::endl;
    }
};

class ResourceCache {
private:
    // TODO: Add map to store weak_ptr to resources
    std::unordered_map<std::string, std::weak_ptr<ExpensiveResource>> cache;
    
public:
    // TODO: Implement get_resource method
    std::shared_ptr<ExpensiveResource> get_resource(const std::string& id) {
        // Check if resource exists in cache and is still valid
        // If yes, return shared_ptr to existing resource
        // If no, create new resource, add to cache, and return it
    }
    
    // TODO: Implement method to show cache status
    void show_cache_status() const {
        std::cout << "Cache contains " << cache.size() << " entries:" << std::endl;
        for (const auto& pair : cache) {
            std::cout << "  " << pair.first << ": " 
                      << (pair.second.expired() ? "expired" : "active")
                      << std::endl;
        }
    }
    
    // TODO: Implement method to clean up expired entries
    void cleanup_expired() {
        // Remove expired weak_ptr entries from cache
    }
};
```

**Test your implementation**:
```cpp
int main() {
    ResourceCache cache;
    
    std::cout << "=== Test 1: Creating and sharing resources ===\n";
    {
        auto resource1 = cache.get_resource("res1");
        auto resource2 = cache.get_resource("res2");
        auto resource1_again = cache.get_resource("res1");  // Should reuse existing
        
        std::cout << "resource1 and resource1_again are same object: " 
                  << (resource1.get() == resource1_again.get()) << std::endl;
        
        resource1->use();
        resource2->use();
        resource1_again->use();
        
        cache.show_cache_status();
    }
    
    std::cout << "\n=== Test 2: Resources destroyed, cache cleanup ===\n";
    cache.show_cache_status();
    cache.cleanup_expired();
    cache.show_cache_status();
    
    std::cout << "\n=== Test 3: Creating resources after cleanup ===\n";
    auto resource3 = cache.get_resource("res1");  // Should create new resource
    cache.show_cache_status();
    
    return 0;
}
```

---

## Problem Set 3: Advanced Smart Pointer Scenarios (55 minutes)

### Problem 3.1: Breaking Circular References (25 minutes)

**Scenario**: Fix a circular reference problem in a tree data structure.

**Given problematic code**:
```cpp
#include <memory>
#include <vector>
#include <iostream>
#include <string>

// PROBLEMATIC VERSION - Creates circular references!
struct TreeNode {
    std::string data;
    std::shared_ptr<TreeNode> parent;  // Problem: creates cycle!
    std::vector<std::shared_ptr<TreeNode>> children;
    
    TreeNode(const std::string& value) : data(value) {
        std::cout << "TreeNode '" << data << "' created" << std::endl;
    }
    
    ~TreeNode() {
        std::cout << "TreeNode '" << data << "' destroyed" << std::endl;
    }
    
    void add_child(std::shared_ptr<TreeNode> child) {
        child->parent = shared_from_this();  // Creates circular reference!
        children.push_back(child);
    }
    
    void show_family() const {
        if (parent) {
            std::cout << data << "'s parent: " << parent->data << std::endl;
        } else {
            std::cout << data << " is root" << std::endl;
        }
        
        std::cout << data << "'s children: ";
        for (const auto& child : children) {
            std::cout << child->data << " ";
        }
        std::cout << std::endl;
    }
};
```

**Your Task**:
1. Fix the circular reference by changing the parent pointer to `weak_ptr`
2. Update any methods that use the parent pointer
3. Make the class inherit from `std::enable_shared_from_this<TreeNode>`
4. Add a safe method to get the parent (returns `shared_ptr` or `nullptr`)

**Test your fixed implementation**:
```cpp
int main() {
    std::cout << "=== Creating tree structure ===\n";
    {
        auto root = std::make_shared<TreeNode>("Root");
        auto child1 = std::make_shared<TreeNode>("Child1");
        auto child2 = std::make_shared<TreeNode>("Child2");
        auto grandchild = std::make_shared<TreeNode>("Grandchild");
        
        root->add_child(child1);
        root->add_child(child2);
        child1->add_child(grandchild);
        
        root->show_family();
        child1->show_family();
        grandchild->show_family();
        
        std::cout << "\n=== Testing parent access ===\n";
        if (auto parent = grandchild->get_parent()) {
            std::cout << "Grandchild's parent is: " << parent->data << std::endl;
        }
    }
    std::cout << "=== All nodes should be destroyed here ===\n";
    
    return 0;
}
```

**Expected behavior**: All TreeNode destructors should be called when the scope ends.

### Problem 3.2: Smart Pointer Integration Project (30 minutes)

**Scenario**: Create a media library system that demonstrates all three smart pointer types working together.

**Your Task**: Complete the following system:

```cpp
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>

class MediaFile {
private:
    std::string filename;
    size_t file_size;
    
public:
    MediaFile(const std::string& name, size_t size) 
        : filename(name), file_size(size) {
        std::cout << "Loaded media file: " << filename 
                  << " (" << file_size << " bytes)" << std::endl;
    }
    
    ~MediaFile() {
        std::cout << "Unloaded media file: " << filename << std::endl;
    }
    
    const std::string& get_filename() const { return filename; }
    size_t get_size() const { return file_size; }
    
    void play() const {
        std::cout << "Playing: " << filename << std::endl;
    }
};

class Playlist {
private:
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> files;
    
public:
    Playlist(const std::string& playlist_name) : name(playlist_name) {
        std::cout << "Created playlist: " << name << std::endl;
    }
    
    ~Playlist() {
        std::cout << "Destroyed playlist: " << name << std::endl;
    }
    
    void add_file(std::shared_ptr<MediaFile> file) {
        files.push_back(file);
        std::cout << "Added " << file->get_filename() << " to " << name << std::endl;
    }
    
    void play_all() const {
        std::cout << "Playing playlist: " << name << std::endl;
        for (const auto& file : files) {
            file->play();
        }
    }
    
    const std::string& get_name() const { return name; }
    size_t get_file_count() const { return files.size(); }
};

class MediaLibrary {
private:
    // TODO: Use unordered_map with string keys and shared_ptr<MediaFile> values
    std::unordered_map<std::string, std::shared_ptr<MediaFile>> media_files;
    
    // TODO: Use vector of unique_ptr<Playlist>
    std::vector<std::unique_ptr<Playlist>> playlists;
    
public:
    // TODO: Implement load_media_file
    std::shared_ptr<MediaFile> load_media_file(const std::string& filename, size_t size) {
        // If file already exists, return existing shared_ptr
        // Otherwise, create new MediaFile and store in map
    }
    
    // TODO: Implement create_playlist
    std::unique_ptr<Playlist> create_playlist(const std::string& name) {
        // Create new playlist and return unique_ptr
        // Note: Don't store in library - let caller manage
    }
    
    // TODO: Implement add_playlist_to_library
    void add_playlist_to_library(std::unique_ptr<Playlist> playlist) {
        // Move the playlist into the library's storage
    }
    
    // TODO: Implement get_media_file
    std::shared_ptr<MediaFile> get_media_file(const std::string& filename) {
        // Return shared_ptr to existing file, or nullptr if not found
    }
    
    // TODO: Implement show_library_status
    void show_library_status() const {
        std::cout << "\n=== Media Library Status ===" << std::endl;
        std::cout << "Media files: " << media_files.size() << std::endl;
        for (const auto& pair : media_files) {
            std::cout << "  " << pair.first << " (refs: " 
                      << pair.second.use_count() << ")" << std::endl;
        }
        
        std::cout << "Playlists: " << playlists.size() << std::endl;
        for (const auto& playlist : playlists) {
            std::cout << "  " << playlist->get_name() 
                      << " (" << playlist->get_file_count() << " files)" << std::endl;
        }
    }
};

class NowPlayingTracker {
private:
    // TODO: Use weak_ptr to avoid keeping media files alive unnecessarily
    std::weak_ptr<MediaFile> current_track;
    
public:
    // TODO: Implement set_current_track
    void set_current_track(std::shared_ptr<MediaFile> track) {
        // Store weak reference to current track
    }
    
    // TODO: Implement show_current_track
    void show_current_track() const {
        // Use lock() to safely access current track
        // Handle case where track might have been destroyed
    }
};
```

**Test your complete implementation**:
```cpp
int main() {
    MediaLibrary library;
    NowPlayingTracker tracker;
    
    std::cout << "=== Loading media files ===\n";
    auto song1 = library.load_media_file("song1.mp3", 4000000);
    auto song2 = library.load_media_file("song2.mp3", 3500000);
    auto song3 = library.load_media_file("song3.mp3", 4200000);
    
    std::cout << "\n=== Creating playlists ===\n";
    auto rock_playlist = library.create_playlist("Rock Hits");
    auto chill_playlist = library.create_playlist("Chill Vibes");
    
    rock_playlist->add_file(song1);
    rock_playlist->add_file(song3);
    chill_playlist->add_file(song2);
    chill_playlist->add_file(song1);  // Same file in multiple playlists
    
    library.add_playlist_to_library(std::move(rock_playlist));
    library.add_playlist_to_library(std::move(chill_playlist));
    
    library.show_library_status();
    
    std::cout << "\n=== Testing now playing tracker ===\n";
    tracker.set_current_track(song2);
    tracker.show_current_track();
    
    std::cout << "\n=== Removing local references ===\n";
    song1.reset();
    song2.reset();
    song3.reset();
    
    library.show_library_status();
    tracker.show_current_track();  // Should still work via playlists
    
    return 0;
}
```

---

## Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o smart_ptr_program program.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**VS Code Smart Pointer Debugging Tips:**
- Use Variables panel to see smart pointer reference counts
- Watch ownership transfer during `std::move` operations
- Set breakpoints in destructors to see when objects are cleaned up
- Monitor memory usage to verify no leaks with smart pointers

---

## Evaluation Criteria

**Total: 16 Points (4 points per outcome criteria)**

1. **Correctness** (4 points): Programs compile and work as specified
2. **Code Quality** (4 points): Clean, readable, well-organized code
3. **Best Practices** (4 points): Following C++ idioms and conventions
4. **Documentation** (4 points): Appropriate comments and clear output

---
