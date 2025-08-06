# Chapter 11: Smart Pointers - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Understand** the problems with raw pointers and why smart pointers solve them
2. **Master** `unique_ptr` for exclusive ownership and automatic memory management
3. **Apply** `shared_ptr` for shared ownership scenarios with reference counting
4. **Use** `weak_ptr` to break circular references and observe without owning
5. **Implement** RAII principles using smart pointers in real applications
6. **Debug** smart pointer ownership and reference counting using VS Code

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🧠 Core Concepts: Smart Pointers and RAII (2.5 hours)

### 1. Why Smart Pointers? The Raw Pointer Crisis

**Real-world scenario**: You're building a game and need to manage player inventory items:

```cpp
// The old way - raw pointers everywhere (DANGEROUS!)
class InventoryManager {
    std::vector<Item*> items;  // Who owns these?
public:
    void add_item(Item* item) {
        items.push_back(item);
    }
    
    ~InventoryManager() {
        // Do we delete the items? What if they're used elsewhere?
        for (Item* item : items) {
            delete item;  // CRASH if item used by other objects!
        }
    }
};

// The sharing nightmare
void share_item_poorly() {
    Item* sword = new Item("Magic Sword");
    
    Player player1;
    Player player2;
    
    player1.equip_weapon(sword);  // player1 thinks they own it
    player2.equip_weapon(sword);  // player2 thinks they own it too!
    
    // When players are destroyed... DOUBLE DELETE!
}

// The exception disaster
void process_inventory() {
    Item* items = new Item[100];  // Allocate inventory
    
    load_save_file();        // Could throw exception!
    validate_items(items);   // Could throw exception!
    
    delete[] items;  // This line might never execute -> MEMORY LEAK!
}
```

**The four horsemen of memory apocalypse:**
1. **Memory leaks** - "I forgot to delete" (most common)
2. **Double deletion** - "Who's supposed to delete this?" (instant crash)
3. **Dangling pointers** - "This points to freed memory" (corrupted data)
4. **Exception safety** - "Exception skipped my cleanup code" (subtle leaks)

**The solution**: Smart pointers handle ownership automatically, making these problems impossible.

### 2. Smart Pointers vs Python/Java Memory Management

| Aspect | C++ Smart Pointers | Python | Java |
|--------|-------------------|--------|------|
| **Memory Management** | Automatic via RAII | Garbage collection | Garbage collection |
| **Cleanup Timing** | Deterministic (scope-based) | Non-deterministic | Non-deterministic |
| **Performance** | Zero overhead | GC overhead | GC overhead |
| **Control** | Manual control, automatic safety | Fully automatic | Fully automatic |
| **Ownership Model** | Explicit ownership | Reference counting | GC manages references |

### 3. `unique_ptr` - "I Own This, Nobody Else Does"

**`unique_ptr` is like having a deed to a house - there's exactly one owner, and when the owner leaves, the house is automatically demolished:**

```cpp
#include <memory>
#include <iostream>

// Basic unique_ptr usage
void demonstrate_unique_ptr() {
    // Creation (preferred way)
    auto ptr = std::make_unique<int>(42);
    auto arr = std::make_unique<int[]>(100);
    
    // Usage - just like raw pointers
    *ptr = 50;
    arr[0] = 10;
    
    std::cout << "Value: " << *ptr << std::endl;
    
    // Automatic cleanup when ptr goes out of scope
    // No delete needed!
}

// Real-world example: Game object factory
class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update() = 0;
    virtual void render() const = 0;
};

class Player : public GameObject {
    std::string name;
    int health = 100;
public:
    Player(const std::string& player_name) : name{player_name} {
        std::cout << "Player " << name << " created\n";
    }
    
    ~Player() {
        std::cout << "Player " << name << " destroyed\n";
    }
    
    void update() override { /* update logic */ }
    void render() const override {
        std::cout << "Rendering player " << name << " (HP: " << health << ")\n";
    }
};

// Factory function - caller gets exclusive ownership
std::unique_ptr<GameObject> spawn_object(const std::string& type, const std::string& name) {
    if (type == "player") {
        return std::make_unique<Player>(name);  // Ownership transferred to caller
    }
    return nullptr;  // Unknown type
}

void game_loop() {
    auto player = spawn_object("player", "Alice");  // We now own this player
    if (player) {
        player->update();
        player->render();
    }
    // Player automatically destroyed when player goes out of scope
    std::cout << "End of game loop - automatic cleanup!\n";
}
```

**Key `unique_ptr` Properties:**
- **Exclusive ownership** - cannot be copied, only moved
- **Move semantics** - ownership can be transferred
- **Zero overhead** - same performance as raw pointers
- **Exception safe** - RAII guarantees cleanup

### 4. `shared_ptr` - Shared Ownership

**`shared_ptr` allows multiple owners through reference counting:**

```cpp
#include <memory>
#include <iostream>

class Document {
    std::string title, content;
public:
    Document(const std::string& t, const std::string& c) 
        : title(t), content(c) {
        std::cout << "Document '" << title << "' created" << std::endl;
    }
    
    ~Document() {
        std::cout << "Document '" << title << "' destroyed" << std::endl;
    }
    
    const std::string& get_title() const { return title; }
    void set_content(const std::string& new_content) { content = new_content; }
};

class Editor {
    std::shared_ptr<Document> doc;
    std::string name;
    
public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> d) 
        : name(editor_name), doc(std::move(d)) {}
    
    void edit(const std::string& new_content) {
        doc->set_content(new_content);
        std::cout << name << " edited document" << std::endl;
    }
    
    void show_ref_count() const {
        std::cout << "Document ref count: " << doc.use_count() << std::endl;
    }
};

void demonstrate_shared_ownership() {
    // Create shared document
    auto document = std::make_shared<Document>("Report", "Initial content");
    std::cout << "Initial ref count: " << document.use_count() << std::endl;
    
    {
        Editor editor1("Alice", document);
        Editor editor2("Bob", document);
        
        editor1.show_ref_count();  // Should show 3 (document + 2 editors)
        editor1.edit("Alice's changes");
        
        // Both editors share the same document
    }
    std::cout << "After editors destroyed: " << document.use_count() << std::endl;
    
    // Document destroyed when last shared_ptr goes out of scope
}
```

### 5. `weak_ptr` - Breaking Circular References

**Circular references can cause memory leaks even with `shared_ptr`:**

```cpp
// PROBLEMATIC VERSION - Creates circular references!
struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::shared_ptr<Parent> parent;  // Creates cycle!
    ~Child() { std::cout << "Child destroyed\n"; }
};

void create_memory_leak() {
    auto parent = std::make_shared<Parent>();
    auto child = std::make_shared<Child>();
    
    parent->child = child;
    child->parent = parent;  // Circular reference!
    
    // Neither destructor will ever be called!
}

// FIXED VERSION - Using weak_ptr
struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::weak_ptr<Parent> parent;  // Breaks the cycle!
    ~Child() { std::cout << "Child destroyed\n"; }
    
    void use_parent() {
        if (auto p = parent.lock()) {  // Convert to shared_ptr safely
            std::cout << "Parent is still alive" << std::endl;
        } else {
            std::cout << "Parent has been destroyed" << std::endl;
        }
    }
};
```

**`weak_ptr` Operations:**
- `lock()` - returns `shared_ptr` if object exists, `nullptr` if destroyed
- `expired()` - returns `true` if object has been destroyed
- `use_count()` - returns current reference count (same as shared_ptr)

### 6. When to Use Which Smart Pointer

| Use Case | Smart Pointer Choice | Example |
|----------|---------------------|---------|
| **Single owner** | `unique_ptr` | File handles, exclusive resources |
| **Factory functions** | `unique_ptr` | Object creation, return values |
| **Shared resources** | `shared_ptr` | Cached data, shared documents |
| **Observer pattern** | `weak_ptr` | Event listeners, UI callbacks |
| **Breaking cycles** | `weak_ptr` | Parent-child relationships |

### 7. Custom Deleters and Advanced Usage

**Sometimes you need custom cleanup behavior:**

```cpp
#include <functional>
#include <memory>
#include <cstdio>

// Custom deleter for C APIs
void file_example() {
    // Using function pointer deleter
    auto file = std::unique_ptr<FILE, decltype(&std::fclose)>(
        std::fopen("data.txt", "w"), &std::fclose);
    
    if (file) {
        std::fprintf(file.get(), "Hello, smart pointers!\n");
        // File automatically closed when unique_ptr is destroyed
    }
}

// Lambda deleter for custom cleanup
void lambda_deleter_example() {
    auto ptr = std::unique_ptr<int, std::function<void(int*)>>(
        new int(42),
        [](int* p) {
            std::cout << "Custom cleanup for value: " << *p << std::endl;
            delete p;
        });
    
    // Custom cleanup will be called automatically
}
```

---

## 💻 VS Code Debugging Smart Pointers (20 minutes)

### Setting Up Smart Pointer Debugging

**VS Code Configuration for Smart Pointer Visualization:**

1. **Enable detailed debug info in `tasks.json`:**
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "C++ Smart Pointer Debug Build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-std=c++17",
                "-g3",
                "-O0",
                "-Wall",
                "-Wextra",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

2. **Configure `launch.json` for memory debugging:**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Smart Pointers",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

### Smart Pointer Debugging Techniques

**Watch Variables Panel:**
- View `unique_ptr` and `shared_ptr` internal state
- Monitor reference counts in real-time
- See ownership transfers during `std::move`

**Useful Debug Expressions:**
```cpp
// Add these to Watch panel
ptr.get()           // Raw pointer value
ptr.use_count()     // Reference count (shared_ptr only)
weak_ptr.expired()  // Check if object destroyed
weak_ptr.lock()     // Attempt to get shared_ptr
```

**Breakpoint Strategies:**
```cpp
class DebugObject {
public:
    DebugObject(const std::string& name) : name_(name) {
        std::cout << "Created: " << name_ << std::endl;
        // Set breakpoint here to see object creation
    }
    
    ~DebugObject() {
        std::cout << "Destroyed: " << name_ << std::endl;
        // Set breakpoint here to see object destruction
    }
    
private:
    std::string name_;
};
```

---

## 🧩 Hands-On Problems (2.25 hours)

### Problem Set 1: Basic Smart Pointer Usage (45 minutes)

#### Problem 1.1: Game Save System Conversion (15 minutes)

**Convert this risky legacy save system to use smart pointers:**

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// BEFORE: Dangerous raw pointer version (memory leaks!)
/*
class GameSave {
private:
    int* player_stats;     // Raw pointer - who deletes this?
    char* save_name;       // Raw pointer - memory leak waiting to happen!
    size_t stat_count;
    
public:
    GameSave(const std::string& name, size_t stats) {
        save_name = new char[name.size() + 1];
        strcpy(save_name, name.c_str());
        
        player_stats = new int[stats];
        stat_count = stats;
        
        // Initialize with default values
        for (size_t i = 0; i < stats; ++i) {
            player_stats[i] = rand() % 100;
        }
    }
    
    ~GameSave() {
        delete[] save_name;      // Easy to forget!
        delete[] player_stats;   // What if exception thrown?
    }
};
*/

// AFTER: Safe smart pointer version
class GameSave {
private:
    std::unique_ptr<int[]> player_stats;  // Automatic cleanup!
    std::string save_name;                // No manual memory management
    size_t stat_count;
    
public:
    GameSave(const std::string& name, size_t stats) 
        : save_name{name}, stat_count{stats} {
        player_stats = std::make_unique<int[]>(stats);
        
        // Initialize with default values
        for (size_t i = 0; i < stats; ++i) {
            player_stats[i] = rand() % 100 + 1;  // HP, Mana, etc.
        }
        
        std::cout << "Created save file: " << save_name << std::endl;
    }
    
    // No destructor needed! Smart pointers handle cleanup automatically
    
    void display_stats() const {
        std::cout << "Save: " << save_name << " - Stats: ";
        for (size_t i = 0; i < stat_count; ++i) {
            std::cout << player_stats[i] << " ";
        }
        std::cout << std::endl;
    }
    
    int get_stat(size_t index) const {
        return (index < stat_count) ? player_stats[index] : 0;
    }
    
    void update_stat(size_t index, int value) {
        if (index < stat_count) {
            player_stats[index] = value;
        }
    }
};

int main() {
    std::cout << "=== Game Save System Demo ===\n";
    
    // Create save files
    GameSave save1("Hero_Quest", 5);  // 5 stats: HP, MP, STR, DEF, SPD
    GameSave save2("Mage_Adventure", 3);  // 3 stats: HP, MP, INT
    
    save1.display_stats();
    save2.display_stats();
    
    // Modify some stats
    save1.update_stat(0, 100);  // Set HP to 100
    save1.update_stat(1, 50);   // Set MP to 50
    
    std::cout << "\nAfter stat updates:\n";
    save1.display_stats();
    
    // Test move semantics (transferring ownership)
    std::cout << "\nTesting move semantics:\n";
    GameSave moved_save = std::move(save1);  // Ownership transferred
    moved_save.display_stats();
    
    std::cout << "\nPlayer HP: " << moved_save.get_stat(0) << std::endl;
    
    // All memory automatically cleaned up when objects go out of scope!
    std::cout << "End of main - automatic cleanup!\n";
    return 0;
}
```

#### Problem 1.2: Factory Pattern with Smart Pointers (15 minutes)

**Complete the shape factory:**

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
    static std::unique_ptr<Shape> create_shape(const std::string& type, double param1, double param2 = 0) {
        if (type == "circle") {
            return std::make_unique<Circle>(param1);
        } else if (type == "rectangle") {
            return std::make_unique<Rectangle>(param1, param2);
        }
        return nullptr;  // Unknown type
    }
};

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

#### Problem 1.3: RAII File Management (15 minutes)

**Create a file manager with custom deleters:**

```cpp
#include <memory>
#include <iostream>
#include <cstdio>
#include <string>

class FileManager {
private:
    std::unique_ptr<FILE, decltype(&std::fclose)> file;
    
public:
    FileManager(const std::string& filename, const std::string& mode) 
        : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {
        if (!file) {
            std::cout << "Failed to open file: " << filename << std::endl;
        }
    }
    
    bool write(const std::string& data) {
        if (!file) return false;
        return std::fputs(data.c_str(), file.get()) >= 0;
    }
    
    std::string read_line() {
        if (!file) return "";
        
        char buffer[256];
        if (std::fgets(buffer, sizeof(buffer), file.get())) {
            return std::string(buffer);
        }
        return "";
    }
    
    bool is_open() const {
        return file != nullptr;
    }
};

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

### Problem Set 2: Shared Ownership Scenarios (45 minutes)

#### Problem 2.1: Document Sharing System (25 minutes)

**Build a document sharing system:**

```cpp
#include <memory>
#include <iostream>
#include <string>

class Document {
private:
    std::string title, content;
    
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
    std::shared_ptr<Document> doc;
    
public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> d) 
        : name(editor_name), doc(std::move(d)) {
        std::cout << "Editor " << name << " opened document" << std::endl;
    }
    
    ~Editor() {
        std::cout << "Editor " << name << " closed" << std::endl;
    }
    
    void edit(const std::string& new_content) {
        doc->set_content(new_content);
        std::cout << name << " edited: " << new_content << std::endl;
    }
    
    void show_info() const {
        std::cout << name << " - Document: " << doc->get_title() 
                  << " (refs: " << doc.use_count() << ")" << std::endl;
    }
};

class Viewer {
private:
    std::string name;
    std::shared_ptr<Document> doc;
    
public:
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> d) 
        : name(viewer_name), doc(std::move(d)) {
        std::cout << "Viewer " << name << " opened document" << std::endl;
    }
    
    ~Viewer() {
        std::cout << "Viewer " << name << " closed" << std::endl;
    }
    
    void view() const {
        std::cout << name << " viewing: " << doc->get_content() << std::endl;
    }
    
    void show_ref_count() const {
        std::cout << "Document refs from " << name << ": " << doc.use_count() << std::endl;
    }
};

int main() {
    auto document = std::make_shared<Document>("Report.txt", "Initial content");
    
    std::cout << "\nCreating editors and viewers...\n";
    {
        Editor editor1("Alice", document);
        Editor editor2("Bob", document);
        Viewer viewer1("Charlie", document);
        
        editor1.show_info();  // Should show ref count = 4
        
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
}
```

#### Problem 2.2: Resource Cache with `weak_ptr` (20 minutes)

**Implement a cache that doesn't keep objects alive unnecessarily:**

```cpp
#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>

class ExpensiveResource {
private:
    std::string id;
    
public:
    ExpensiveResource(const std::string& resource_id) : id(resource_id) {
        std::cout << "Creating expensive resource: " << id << std::endl;
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
    std::unordered_map<std::string, std::weak_ptr<ExpensiveResource>> cache;
    
public:
    std::shared_ptr<ExpensiveResource> get_resource(const std::string& id) {
        auto it = cache.find(id);
        if (it != cache.end()) {
            if (auto existing = it->second.lock()) {
                std::cout << "Reusing existing resource: " << id << std::endl;
                return existing;
            } else {
                // Resource expired, remove from cache
                cache.erase(it);
            }
        }
        
        // Create new resource
        auto new_resource = std::make_shared<ExpensiveResource>(id);
        cache[id] = new_resource;  // Store weak reference
        return new_resource;
    }
    
    void show_cache_status() const {
        std::cout << "Cache contains " << cache.size() << " entries:" << std::endl;
        for (const auto& pair : cache) {
            std::cout << "  " << pair.first << ": " 
                      << (pair.second.expired() ? "expired" : "active") << std::endl;
        }
    }
    
    void cleanup_expired() {
        auto it = cache.begin();
        while (it != cache.end()) {
            if (it->second.expired()) {
                std::cout << "Removing expired cache entry: " << it->first << std::endl;
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }
};

int main() {
    ResourceCache cache;
    
    std::cout << "=== Test 1: Creating and sharing resources ===\n";
    {
        auto resource1 = cache.get_resource("res1");
        auto resource2 = cache.get_resource("res2");
        auto resource1_again = cache.get_resource("res1");  // Should reuse
        
        std::cout << "resource1 and resource1_again are same: " 
                  << (resource1.get() == resource1_again.get()) << std::endl;
        
        resource1->use();
        resource2->use();
        
        cache.show_cache_status();
    }
    
    std::cout << "\n=== Test 2: Resources destroyed, cache cleanup ===\n";
    cache.show_cache_status();
    cache.cleanup_expired();
    cache.show_cache_status();
    
    std::cout << "\n=== Test 3: Creating resources after cleanup ===\n";
    auto resource3 = cache.get_resource("res1");  // Should create new
    cache.show_cache_status();
    
    return 0;
}
```

### Problem Set 3: Advanced Smart Pointer Integration (55 minutes)

#### Problem 3.1: Fixing Circular References (25 minutes)

**Fix the circular reference in this tree structure:**

```cpp
#include <memory>
#include <vector>
#include <iostream>
#include <string>

// FIXED VERSION using weak_ptr for parent references
struct TreeNode : public std::enable_shared_from_this<TreeNode> {
    std::string data;
    std::weak_ptr<TreeNode> parent;  // Changed to weak_ptr to break cycle
    std::vector<std::shared_ptr<TreeNode>> children;
    
    TreeNode(const std::string& value) : data(value) {
        std::cout << "TreeNode '" << data << "' created" << std::endl;
    }
    
    ~TreeNode() {
        std::cout << "TreeNode '" << data << "' destroyed" << std::endl;
    }
    
    void add_child(std::shared_ptr<TreeNode> child) {
        child->parent = shared_from_this();  // Store weak reference to parent
        children.push_back(child);
    }
    
    std::shared_ptr<TreeNode> get_parent() {
        return parent.lock();  // Safe access to parent
    }
    
    void show_family() const {
        if (auto p = parent.lock()) {
            std::cout << data << "'s parent: " << p->data << std::endl;
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

#### Problem 3.2: Complete Media Library System (30 minutes)

**Integrate all three smart pointer types:**

```cpp
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

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
    std::unordered_map<std::string, std::shared_ptr<MediaFile>> media_files;
    std::vector<std::unique_ptr<Playlist>> playlists;
    
public:
    std::shared_ptr<MediaFile> load_media_file(const std::string& filename, size_t size) {
        auto it = media_files.find(filename);
        if (it != media_files.end()) {
            std::cout << "Returning existing file: " << filename << std::endl;
            return it->second;
        }
        
        auto new_file = std::make_shared<MediaFile>(filename, size);
        media_files[filename] = new_file;
        return new_file;
    }
    
    std::unique_ptr<Playlist> create_playlist(const std::string& name) {
        return std::make_unique<Playlist>(name);
    }
    
    void add_playlist_to_library(std::unique_ptr<Playlist> playlist) {
        playlists.push_back(std::move(playlist));
    }
    
    std::shared_ptr<MediaFile> get_media_file(const std::string& filename) {
        auto it = media_files.find(filename);
        return (it != media_files.end()) ? it->second : nullptr;
    }
    
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
    std::weak_ptr<MediaFile> current_track;
    
public:
    void set_current_track(std::shared_ptr<MediaFile> track) {
        current_track = track;
        std::cout << "Now playing: " << track->get_filename() << std::endl;
    }
    
    void show_current_track() const {
        if (auto track = current_track.lock()) {
            std::cout << "Currently playing: " << track->get_filename() << std::endl;
        } else {
            std::cout << "No track currently playing (or track was unloaded)" << std::endl;
        }
    }
};

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

## 🔧 Quick Reference & Troubleshooting

### Smart Pointer Decision Tree

```
Need memory management?
├─ Yes: Is there exactly one owner?
│  ├─ Yes: Use unique_ptr
│  └─ No: Are there multiple owners?
│     ├─ Yes: Use shared_ptr
│     └─ No: Need to observe without owning?
│        └─ Yes: Use weak_ptr
└─ No: Use stack objects or references
```

### Common Error Solutions

#### 1. Circular Reference Memory Leaks
```cpp
// ❌ Problem - Both objects keep each other alive
struct A { std::shared_ptr<B> b_ptr; };
struct B { std::shared_ptr<A> a_ptr; };  // Cycle!

// ✅ Solution - Break cycle with weak_ptr
struct A { std::shared_ptr<B> b_ptr; };
struct B { std::weak_ptr<A> a_ptr; };    // Breaks cycle
```

#### 2. Copying unique_ptr
```cpp
// ❌ Problem - unique_ptr cannot be copied
auto ptr1 = std::make_unique<int>(42);
auto ptr2 = ptr1;  // Compilation error!

// ✅ Solution - Use move semantics
auto ptr2 = std::move(ptr1);  // Transfers ownership
```

#### 3. Double Deletion
```cpp
// ❌ Problem - Two smart pointers managing same raw pointer
int* raw = new int(42);
std::unique_ptr<int> ptr1(raw);
std::unique_ptr<int> ptr2(raw);  // Both will delete!

// ✅ Solution - Use make_unique or share properly
auto ptr1 = std::make_unique<int>(42);
// For sharing:
auto shared1 = std::make_shared<int>(42);
auto shared2 = shared1;  // Safe sharing
```

#### 4. Using Expired weak_ptr
```cpp
// ❌ Problem - Accessing destroyed object
std::weak_ptr<int> weak;
{
    auto shared = std::make_shared<int>(42);
    weak = shared;
}
// shared is destroyed here
auto bad = weak.lock();  // Returns nullptr

// ✅ Solution - Always check before use
if (auto good = weak.lock()) {
    *good = 50;  // Safe to use
} else {
    // Handle expired case
}
```

### Performance Best Practices

1. **Prefer `make_unique` and `make_shared`** - more efficient and exception-safe
2. **Use `unique_ptr` by default** - upgrade to `shared_ptr` only when needed
3. **Pass smart pointers by reference** when not transferring ownership
4. **Use `weak_ptr` in observer patterns** to avoid keeping objects alive

### Custom Deleter Patterns

```cpp
// File handle management
auto file = std::unique_ptr<FILE, decltype(&fclose)>(
    fopen("file.txt", "r"), &fclose);

// Array deletion
auto arr = std::unique_ptr<int[]>(new int[100]);

// Custom cleanup function
auto resource = std::unique_ptr<Resource, void(*)(Resource*)>(
    acquire_resource(), &release_resource);
```

---

## ✅ Chapter 11 Success Checklist

### Smart Pointer Fundamentals
- [ ] Can explain why raw pointers are dangerous in C++
- [ ] Understand RAII principles and automatic cleanup
- [ ] Can choose the appropriate smart pointer for different scenarios
- [ ] Know when smart pointers are cleaned up (scope-based)

### `unique_ptr` Mastery
- [ ] Can create `unique_ptr` with `make_unique`
- [ ] Understand exclusive ownership and move semantics
- [ ] Can implement factory functions returning `unique_ptr`
- [ ] Can use custom deleters for special cleanup needs

### `shared_ptr` and Reference Counting
- [ ] Can create and share `shared_ptr` objects correctly
- [ ] Understand reference counting and `use_count()`
- [ ] Can implement shared resource scenarios
- [ ] Know the performance implications of shared ownership

### `weak_ptr` and Cycle Breaking
- [ ] Can identify circular reference problems
- [ ] Can use `weak_ptr` to break cycles in data structures
- [ ] Can safely access objects through `weak_ptr.lock()`
- [ ] Understand observer pattern with `weak_ptr`

---

## 🚀 What's Next?

**Chapter 12: STL Containers** will cover:
- vector, list, deque for sequences
- set, map for associative storage  
- unordered containers for hash-based storage
- Container adapters (stack, queue, priority_queue)

**You've mastered modern C++ memory management!** 🎉 Smart pointers provide automatic memory management while maintaining C++'s performance and control. You now understand how to write memory-safe C++ code that's as convenient as garbage-collected languages but with deterministic cleanup timing.

**Key Takeaway**: Smart pointers bridge the gap between C++'s manual memory control and the automatic memory management familiar from Python and Java. They give you "garbage collection" behavior with predictable, immediate cleanup when objects go out of scope.

---

*Remember: Smart pointers don't just prevent memory leaks - they encode ownership semantics directly in the type system, making your code's intent clear and your memory management automatic. When you see `unique_ptr`, you know there's exactly one owner. When you see `shared_ptr`, you know the resource is shared. When you see `weak_ptr`, you know it's an observer that doesn't affect lifetime.*