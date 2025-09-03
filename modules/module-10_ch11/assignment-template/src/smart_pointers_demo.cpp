// HW_11: Smart Pointers and RAII
// Time: 2.25 hours (45 minutes per problem set)
// Topics: RAII, unique_ptr, shared_ptr, weak_ptr

#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

// ============================================================================
// PROBLEM SET 1: RAII and Resource Management (45 minutes)
// ============================================================================

// TODO 1: RAII class for file handling
class FileManager {
private:
    std::FILE* file_;
    std::string filename_;
    
public:
    FileManager(const std::string& filename, const char* mode) 
        : filename_(filename) {
        file_ = std::fopen(filename.c_str(), mode);
        if (file_) {
            printf("  File '%s' opened successfully\n", filename_.c_str());
        } else {
            printf("  Failed to open file '%s'\n", filename_.c_str());
        }
    }
    
    ~FileManager() {
        if (file_) {
            std::fclose(file_);
            printf("  File '%s' automatically closed\n", filename_.c_str());
        }
    }
    
    // Delete copy operations to ensure exclusive ownership
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    bool is_open() const { return file_ != nullptr; }
    
    void write_line(const std::string& content) {
        if (file_) {
            std::fprintf(file_, "%s\n", content.c_str());
            std::fflush(file_);
        }
    }
};

void raii_fundamentals() {
    printf("=== RAII Fundamentals ===\n");
    
    // TODO: Demonstrate RAII with automatic resource cleanup
    printf("RAII File Management:\n");
    
    {
        FileManager fm("/tmp/test_raii.txt", "w");
        if (fm.is_open()) {
            fm.write_line("Hello RAII!");
            fm.write_line("Resources cleaned up automatically");
        }
        printf("  File operations complete\n");
        // File automatically closed when fm goes out of scope
    }
    
    printf("  Exited scope - file should be closed\n");
    
    printf("\n");
}

// TODO 2: Traditional pointer problems
class Resource {
private:
    std::string name_;
    int* data_;
    size_t size_;
    
public:
    Resource(const std::string& name, size_t size) 
        : name_(name), size_(size) {
        data_ = new int[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = static_cast<int>(i * 10);
        }
        printf("  Resource '%s' created (%zu elements)\n", name_.c_str(), size_);
    }
    
    ~Resource() {
        delete[] data_;
        printf("  Resource '%s' destroyed\n", name_.c_str());
    }
    
    // Copy operations for demonstration
    Resource(const Resource& other) 
        : name_(other.name_ + "_copy"), size_(other.size_) {
        data_ = new int[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        printf("  Resource '%s' copied\n", name_.c_str());
    }
    
    void display() const {
        printf("  Resource '%s': ", name_.c_str());
        for (size_t i = 0; i < std::min(size_, size_t(5)); i++) {
            printf("%d ", data_[i]);
        }
        if (size_ > 5) printf("...");
        printf("\n");
    }
};

void traditional_pointer_problems() {
    printf("=== Traditional Pointer Problems ===\n");
    
    // TODO: Show problems with raw pointers
    printf("Raw Pointer Issues:\n");
    
    Resource* resource1 = nullptr;
    Resource* resource2 = nullptr;
    
    try {
        resource1 = new Resource("Raw1", 5);
        resource1->display();
        
        resource2 = new Resource("Raw2", 3);
        resource2->display();
        
        // Simulate potential exception
        if (true) {  // Always true for demo
            printf("  Simulating early return/exception...\n");
            // Without proper cleanup, memory leaks occur
            delete resource1;  // Manual cleanup required
            delete resource2;  // Must remember to delete
        }
        
    } catch (...) {
        // Exception handling requires manual cleanup
        delete resource1;
        delete resource2;
        printf("  Exception handled, manual cleanup performed\n");
    }
    
    printf("  Raw pointer management complete (error-prone!)\n");
    printf("\n");
}

void smart_pointer_introduction() {
    printf("=== Smart Pointer Introduction ===\n");
    
    // TODO: Show how smart pointers solve the problems
    printf("Smart Pointer Benefits:\n");
    
    {
        // Smart pointers provide automatic cleanup
        std::unique_ptr<Resource> smart_res1 = 
            std::make_unique<Resource>("Smart1", 4);
        smart_res1->display();
        
        std::unique_ptr<Resource> smart_res2 = 
            std::make_unique<Resource>("Smart2", 3);
        smart_res2->display();
        
        printf("  Smart pointers manage memory automatically\n");
        // No explicit delete needed - automatic cleanup
    }
    
    printf("  Exited scope - all resources automatically cleaned up\n");
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: RAII and Resource Management ===\n\n");
    
    raii_fundamentals();
    traditional_pointer_problems();
    smart_pointer_introduction();
}

// ============================================================================
// PROBLEM SET 2: Unique and Shared Pointers (45 minutes)
// ============================================================================

// TODO 3: unique_ptr exclusive ownership
class Device {
private:
    std::string type_;
    int id_;
    bool active_;
    
public:
    Device(const std::string& type, int id) 
        : type_(type), id_(id), active_(true) {
        printf("  Device created: %s #%d\n", type_.c_str(), id_);
    }
    
    ~Device() {
        printf("  Device destroyed: %s #%d\n", type_.c_str(), id_);
    }
    
    void activate() { 
        active_ = true; 
        printf("  %s #%d activated\n", type_.c_str(), id_);
    }
    
    void deactivate() { 
        active_ = false; 
        printf("  %s #%d deactivated\n", type_.c_str(), id_);
    }
    
    void status() const {
        printf("  %s #%d: %s\n", type_.c_str(), id_, 
               active_ ? "ACTIVE" : "INACTIVE");
    }
};

std::unique_ptr<Device> create_device(const std::string& type, int id) {
    return std::make_unique<Device>(type, id);
}

void unique_ptr_usage() {
    printf("=== unique_ptr - Exclusive Ownership ===\n");
    
    // TODO: Basic unique_ptr operations
    printf("Basic unique_ptr Operations:\n");
    
    // Create unique_ptr
    std::unique_ptr<Device> printer = create_device("Printer", 101);
    printer->status();
    printer->activate();
    
    // Move ownership (unique_ptr cannot be copied)
    printf("\nTransferring ownership:\n");
    std::unique_ptr<Device> new_owner = std::move(printer);
    
    if (!printer) {
        printf("  Original pointer is now null\n");
    }
    
    if (new_owner) {
        printf("  New owner has the device:\n");
        new_owner->status();
    }
    
    // TODO: unique_ptr with arrays
    printf("\nUnique_ptr with Arrays:\n");
    
    std::unique_ptr<int[]> numbers = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * i;
    }
    
    printf("  Array contents: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // TODO: Custom deleter
    printf("\nCustom Deleter:\n");
    
    auto custom_deleter = [](Device* d) {
        printf("  Custom deleter called for device\n");
        delete d;
    };
    
    std::unique_ptr<Device, decltype(custom_deleter)> 
        special_device(new Device("Scanner", 102), custom_deleter);
    special_device->status();
    
    printf("\n");
}

// TODO 4: shared_ptr for shared ownership
class DataBuffer {
private:
    std::string name_;
    std::vector<int> data_;
    
public:
    DataBuffer(const std::string& name, size_t size) 
        : name_(name), data_(size) {
        for (size_t i = 0; i < size; i++) {
            data_[i] = static_cast<int>(i + 1);
        }
        printf("  DataBuffer '%s' created with %zu elements\n", 
               name_.c_str(), size);
    }
    
    ~DataBuffer() {
        printf("  DataBuffer '%s' destroyed\n", name_.c_str());
    }
    
    void display() const {
        printf("  Buffer '%s': ", name_.c_str());
        for (size_t i = 0; i < std::min(data_.size(), size_t(6)); i++) {
            printf("%d ", data_[i]);
        }
        if (data_.size() > 6) printf("...");
        printf("(size: %zu)\n", data_.size());
    }
    
    const std::vector<int>& get_data() const { return data_; }
};

void shared_ptr_usage() {
    printf("=== shared_ptr - Shared Ownership ===\n");
    
    // TODO: Basic shared_ptr operations
    printf("Reference Counting with shared_ptr:\n");
    
    std::shared_ptr<DataBuffer> buffer1 = 
        std::make_shared<DataBuffer>("SharedData", 8);
    
    printf("  Reference count: %ld\n", buffer1.use_count());
    buffer1->display();
    
    {
        // Share ownership
        std::shared_ptr<DataBuffer> buffer2 = buffer1;
        printf("  After sharing - Reference count: %ld\n", buffer1.use_count());
        
        std::shared_ptr<DataBuffer> buffer3 = buffer1;
        printf("  After second share - Reference count: %ld\n", buffer1.use_count());
        
        buffer2->display();
        buffer3->display();
        
        printf("  Exiting inner scope...\n");
        // buffer2 and buffer3 destroyed here
    }
    
    printf("  Back in outer scope - Reference count: %ld\n", buffer1.use_count());
    
    // TODO: shared_ptr with containers
    printf("\nShared_ptr in Containers:\n");
    
    std::vector<std::shared_ptr<DataBuffer>> buffers;
    
    auto shared_buffer = std::make_shared<DataBuffer>("VectorBuffer", 4);
    
    // Add to multiple containers
    buffers.push_back(shared_buffer);
    buffers.push_back(shared_buffer);
    buffers.push_back(shared_buffer);
    
    printf("  Buffer in vector 3 times - Reference count: %ld\n", 
           shared_buffer.use_count());
    
    // Access through container
    for (size_t i = 0; i < buffers.size(); i++) {
        printf("  Vector[%zu]: ", i);
        buffers[i]->display();
    }
    
    printf("\n");
}

void pointer_operations() {
    printf("=== Pointer Operations: Reset, Release, Get ===\n");
    
    // TODO: Demonstrate key operations
    printf("Key Operations:\n");
    
    std::unique_ptr<Device> device = std::make_unique<Device>("Tablet", 201);
    
    // get() - access raw pointer without transferring ownership
    Device* raw_ptr = device.get();
    if (raw_ptr) {
        printf("  get() returns raw pointer to: ");
        raw_ptr->status();
    }
    
    // reset() - replace managed object
    printf("  Calling reset() with new device...\n");
    device.reset(new Device("Laptop", 202));
    device->status();
    
    // release() - release ownership without destroying
    printf("  Calling release()...\n");
    Device* released = device.release();
    
    if (!device) {
        printf("  unique_ptr is now empty\n");
    }
    
    if (released) {
        printf("  Released pointer still valid: ");
        released->status();
        delete released;  // Must manually delete released pointer
    }
    
    // Shared pointer operations
    printf("\nShared Pointer Operations:\n");
    
    std::shared_ptr<DataBuffer> shared_buf = 
        std::make_shared<DataBuffer>("TestBuffer", 3);
    
    printf("  Initial reference count: %ld\n", shared_buf.use_count());
    
    // reset() with shared_ptr
    shared_buf.reset(new DataBuffer("NewBuffer", 5));
    printf("  After reset() with new buffer: %ld\n", shared_buf.use_count());
    shared_buf->display();
    
    // reset() to null
    shared_buf.reset();
    printf("  After reset() to null - pointer is %s\n", 
           shared_buf ? "valid" : "null");
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: Unique and Shared Pointers ===\n\n");
    
    unique_ptr_usage();
    shared_ptr_usage();
    pointer_operations();
}

// ============================================================================
// PROBLEM SET 3: Advanced Smart Pointer Usage (45 minutes)
// ============================================================================

// TODO 5: Circular reference problem and weak_ptr solution
// Forward declarations
class SafeParent;

class Child {
public:
    std::string name;
    std::weak_ptr<SafeParent> parent;  // Use weak_ptr to break circular reference
    
    Child(const std::string& n) : name(n) {
        printf("  Child '%s' created\n", name.c_str());
    }
    
    ~Child() {
        printf("  Child '%s' destroyed\n", name.c_str());
    }
    
    void display() const;  // Declaration only, definition after SafeParent
};

// Enable shared_from_this for SafeParent
class SafeParent : public std::enable_shared_from_this<SafeParent> {
public:
    std::string name;
    std::vector<std::shared_ptr<Child>> children;
    
    SafeParent(const std::string& n) : name(n) {
        printf("  SafeParent '%s' created\n", name.c_str());
    }
    
    ~SafeParent() {
        printf("  SafeParent '%s' destroyed\n", name.c_str());
    }
    
    void add_child(std::shared_ptr<Child> child) {
        children.push_back(child);
        child->parent = shared_from_this();
    }
    
    void display() const {
        printf("  SafeParent '%s' has %zu children:\n", name.c_str(), children.size());
        for (const auto& child : children) {
            child->display();
        }
    }
};

// Child::display() implementation after SafeParent is fully defined
void Child::display() const {
    printf("    Child '%s'", name.c_str());
    if (auto p = parent.lock()) {  // Convert weak_ptr to shared_ptr
        printf(" (parent: %s)\n", p->name.c_str());
    } else {
        printf(" (no parent)\n");
    }
}

void weak_ptr_usage() {
    printf("=== weak_ptr - Breaking Circular References ===\n");
    
    // TODO: Demonstrate circular reference problem (would cause memory leak)
    printf("Circular Reference Prevention:\n");
    
    {
        auto parent = std::make_shared<SafeParent>("Alice");
        printf("  Parent reference count: %ld\n", parent.use_count());
        
        auto child1 = std::make_shared<Child>("Bob");
        auto child2 = std::make_shared<Child>("Carol");
        
        parent->add_child(child1);
        parent->add_child(child2);
        
        printf("  After adding children - Parent reference count: %ld\n", 
               parent.use_count());
        
        parent->display();
        
        // Check weak_ptr functionality
        if (auto locked_parent = child1->parent.lock()) {
            printf("  Child1 can access parent: %s\n", locked_parent->name.c_str());
        }
        
        printf("  Exiting scope...\n");
        // All objects will be properly destroyed due to weak_ptr usage
    }
    
    printf("  All objects cleaned up (no memory leak)\n");
    
    // TODO: weak_ptr operations
    printf("\nweak_ptr Operations:\n");
    
    std::weak_ptr<DataBuffer> weak_buffer;
    
    {
        auto shared_buffer = std::make_shared<DataBuffer>("TempBuffer", 3);
        weak_buffer = shared_buffer;
        
        printf("  weak_ptr expired: %s\n", weak_buffer.expired() ? "true" : "false");
        printf("  weak_ptr use_count: %ld\n", weak_buffer.use_count());
        
        if (auto locked = weak_buffer.lock()) {
            printf("  Successfully locked weak_ptr:\n");
            locked->display();
        }
    }
    
    printf("  shared_ptr destroyed, checking weak_ptr:\n");
    printf("  weak_ptr expired: %s\n", weak_buffer.expired() ? "true" : "false");
    printf("  weak_ptr use_count: %ld\n", weak_buffer.use_count());
    
    if (auto locked = weak_buffer.lock()) {
        printf("  Lock successful\n");
    } else {
        printf("  Lock failed - object no longer exists\n");
    }
    
    printf("\n");
}

// TODO 6: Custom deleters for specialized cleanup
class FileHandle {
private:
    std::FILE* file_;
    std::string filename_;
    
public:
    FileHandle(const std::string& filename, const char* mode) 
        : filename_(filename) {
        file_ = std::fopen(filename.c_str(), mode);
        printf("  FileHandle opened: %s\n", filename_.c_str());
    }
    
    ~FileHandle() {
        if (file_) {
            std::fclose(file_);
            printf("  FileHandle closed: %s\n", filename_.c_str());
        }
    }
    
    bool is_valid() const { return file_ != nullptr; }
    void write(const std::string& data) {
        if (file_) {
            std::fprintf(file_, "%s", data.c_str());
        }
    }
};

void custom_deleters() {
    printf("=== Custom Deleters ===\n");
    
    // TODO: Custom deleter with logging
    printf("Custom Deleter for Logging:\n");
    
    auto logging_deleter = [](FileHandle* fh) {
        printf("  Custom deleter: About to delete FileHandle\n");
        delete fh;
        printf("  Custom deleter: FileHandle deleted\n");
    };
    
    {
        std::unique_ptr<FileHandle, decltype(logging_deleter)> 
            file_ptr(new FileHandle("/tmp/test_custom.txt", "w"), logging_deleter);
        
        if (file_ptr && file_ptr->is_valid()) {
            file_ptr->write("Hello from custom deleter!\n");
        }
        
        printf("  File operations complete, exiting scope...\n");
    }
    
    printf("  Custom deleter executed\n");
    
    // TODO: Custom deleter for arrays (though unique_ptr<T[]> is preferred)
    printf("\nCustom Deleter for Special Cleanup:\n");
    
    auto array_deleter = [](int* arr) {
        printf("  Custom array deleter: Cleaning up array\n");
        delete[] arr;
    };
    
    {
        std::shared_ptr<int> array_ptr(new int[5], array_deleter);
        
        // Initialize array through raw pointer access
        int* raw_array = array_ptr.get();
        for (int i = 0; i < 5; i++) {
            raw_array[i] = i * 10;
        }
        
        printf("  Array values: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", raw_array[i]);
        }
        printf("\n");
        
        printf("  Reference count: %ld\n", array_ptr.use_count());
    }
    
    printf("\n");
}

void performance_considerations() {
    printf("=== Performance Considerations ===\n");
    
    // TODO: When to use each pointer type
    printf("Pointer Type Selection Guidelines:\n");
    
    printf("  unique_ptr:\n");
    printf("    - Exclusive ownership, single owner\n");
    printf("    - Minimal overhead (same as raw pointer)\n");
    printf("    - Move-only semantics\n");
    printf("    - Use when: Clear single ownership model\n");
    
    printf("\n  shared_ptr:\n");
    printf("    - Reference counting overhead\n");
    printf("    - Thread-safe reference counting\n");
    printf("    - Use when: Multiple owners needed\n");
    printf("    - Avoid when: Single ownership is sufficient\n");
    
    printf("\n  weak_ptr:\n");
    printf("    - No ownership, observational access\n");
    printf("    - Breaks circular references\n");
    printf("    - Use when: Need to observe without owning\n");
    
    // TODO: Performance demonstration
    printf("\nPerformance Example:\n");
    
    const int iterations = 1000;
    
    // Unique pointer performance
    auto start_unique = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        auto ptr = std::make_unique<int>(i);
        (void)ptr;  // Suppress unused variable warning
    }
    auto end_unique = std::chrono::high_resolution_clock::now();
    
    // Shared pointer performance  
    auto start_shared = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        auto ptr = std::make_shared<int>(i);
        (void)ptr;  // Suppress unused variable warning
    }
    auto end_shared = std::chrono::high_resolution_clock::now();
    
    auto unique_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (end_unique - start_unique);
    auto shared_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (end_shared - start_shared);
    
    printf("  unique_ptr creation (%d iterations): %lld microseconds\n", 
           iterations, unique_duration.count());
    printf("  shared_ptr creation (%d iterations): %lld microseconds\n", 
           iterations, shared_duration.count());
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Advanced Smart Pointer Usage ===\n\n");
    
    weak_ptr_usage();
    custom_deleters();
    performance_considerations();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("    HW_11: Smart Pointers and RAII\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: RAII and Resource Management (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Unique and Shared Pointers (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Advanced Smart Pointer Usage (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}