#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// =============================================================================
// PROBLEM SET 1: BASIC SMART POINTER USAGE
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 1.1: Converting Raw Pointers to unique_ptr
// -----------------------------------------------------------------------------

class DataProcessor {
private:
    // Instead of raw pointer, use unique_ptr with array deleter
    std::unique_ptr<int[]> data;
    size_t size;

public:
    DataProcessor(size_t n) : data(std::make_unique<int[]>(n)), size(n) {
        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<int>(i * i);
        }
    }

    // No destructor needed! unique_ptr handles cleanup automatically

    // unique_ptr is move-only, so copy operations are deleted by default
    // This is safer than forgetting to implement them with raw pointers

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

void test_problem_1_1() {
    std::cout << "=== Problem 1.1: unique_ptr Array Management ===\n";

    DataProcessor processor(5);
    processor.print_data();

    // Move semantics work automatically with unique_ptr
    DataProcessor processor2 = std::move(processor);
    processor2.print_data();

    std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
    std::cout << std::endl;
}

// -----------------------------------------------------------------------------
// Problem 1.2: Factory Pattern with unique_ptr
// -----------------------------------------------------------------------------

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
    // Factory method returns unique_ptr for clear ownership transfer
    static std::unique_ptr<Shape> create_shape(const std::string& type,
                                               double param1,
                                               double param2 = 0) {
        if (type == "circle") {
            // make_unique is the preferred way to create unique_ptr
            return std::make_unique<Circle>(param1);
        } else if (type == "rectangle") {
            return std::make_unique<Rectangle>(param1, param2);
        }
        // Return nullptr for unknown types
        return nullptr;
    }
};

void test_problem_1_2() {
    std::cout << "=== Problem 1.2: Factory Pattern with unique_ptr ===\n";

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

    std::cout << std::endl;
}

// -----------------------------------------------------------------------------
// Problem 1.3: Resource Management with RAII and Custom Deleters
// -----------------------------------------------------------------------------

class FileManager {
private:
    // unique_ptr with custom deleter for FILE*
    // The deleter type must be part of the unique_ptr type
    std::unique_ptr<FILE, decltype(&std::fclose)> file;

public:
    // Constructor opens file and stores it with custom deleter
    FileManager(const std::string& filename, const std::string& mode)
        : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {
        // file will be nullptr if fopen fails
        if (file) {
            std::cout << "File '" << filename << "' opened successfully\n";
        } else {
            std::cout << "Failed to open file '" << filename << "'\n";
        }
    }

    // Destructor automatically calls fclose through unique_ptr's deleter

    bool write(const std::string& data) {
        if (!file) return false;
        return std::fputs(data.c_str(), file.get()) != EOF;
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
        // unique_ptr can be checked like a regular pointer
        return file != nullptr;
    }
};

void test_problem_1_3() {
    std::cout << "=== Problem 1.3: RAII with Custom Deleters ===\n";

    // Write to file
    {
        FileManager writer("test.txt", "w");
        if (writer.is_open()) {
            writer.write("Hello, Smart Pointers!\n");
            writer.write("RAII is awesome!\n");
        }
    }  // File automatically closed here by unique_ptr's deleter

    // Read from file
    {
        FileManager reader("test.txt", "r");
        if (reader.is_open()) {
            std::cout << "Line 1: " << reader.read_line();
            std::cout << "Line 2: " << reader.read_line();
        }
    }  // File automatically closed here

    std::cout << std::endl;
}

// =============================================================================
// PROBLEM SET 2: SHARED OWNERSHIP AND REFERENCE COUNTING
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 2.1: Document Sharing System
// -----------------------------------------------------------------------------

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
    std::shared_ptr<Document> doc;  // Shared ownership of document

public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> document)
        : name(editor_name), doc(document) {
        std::cout << "Editor '" << name << "' opened document" << std::endl;
    }

    ~Editor() {
        std::cout << "Editor '" << name << "' closed" << std::endl;
    }

    void edit(const std::string& new_content) {
        std::cout << name << " editing document..." << std::endl;
        doc->set_content(new_content);
    }

    void show_info() const {
        std::cout << "Editor '" << name << "': " << doc->get_title()
                  << " (refs: " << doc.use_count() << ")" << std::endl;
    }
};

class Viewer {
private:
    std::string name;
    std::shared_ptr<Document> doc;  // Shared ownership of document

public:
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> document)
        : name(viewer_name), doc(document) {
        std::cout << "Viewer '" << name << "' opened document" << std::endl;
    }

    ~Viewer() {
        std::cout << "Viewer '" << name << "' closed" << std::endl;
    }

    void view() const {
        std::cout << name << " viewing: " << doc->get_content() << std::endl;
    }

    void show_ref_count() const {
        std::cout << "Viewer '" << name << "': Reference count = "
                  << doc.use_count() << std::endl;
    }
};

void test_problem_2_1() {
    std::cout << "=== Problem 2.1: Document Sharing System ===\n";

    auto document = std::make_shared<Document>("Report.txt", "Initial content");

    std::cout << "\nCreating editors and viewers...\n";
    {
        Editor editor1("Alice", document);
        Editor editor2("Bob", document);
        Viewer viewer1("Charlie", document);

        // Should show ref count = 4 (document + 3 users)
        editor1.show_info();

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

    std::cout << std::endl;
}  // Document destroyed here

// -----------------------------------------------------------------------------
// Problem 2.2: Caching System with weak_ptr
// -----------------------------------------------------------------------------

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
    // Use weak_ptr to avoid keeping resources alive unnecessarily
    // weak_ptr doesn't contribute to reference count
    std::unordered_map<std::string, std::weak_ptr<ExpensiveResource>> cache;

public:
    std::shared_ptr<ExpensiveResource> get_resource(const std::string& id) {
        // Check if resource exists in cache
        auto it = cache.find(id);

        if (it != cache.end()) {
            // Try to lock the weak_ptr to get a shared_ptr
            // lock() returns shared_ptr if object still exists, nullptr otherwise
            auto resource = it->second.lock();

            if (resource) {
                std::cout << "Cache hit: Reusing resource '" << id << "'" << std::endl;
                return resource;
            } else {
                std::cout << "Cache expired: Resource '" << id << "' was destroyed" << std::endl;
            }
        } else {
            std::cout << "Cache miss: Creating new resource '" << id << "'" << std::endl;
        }

        // Create new resource
        auto new_resource = std::make_shared<ExpensiveResource>(id);

        // Store weak_ptr in cache (doesn't keep resource alive)
        cache[id] = new_resource;

        return new_resource;
    }

    void show_cache_status() const {
        std::cout << "Cache contains " << cache.size() << " entries:" << std::endl;
        for (const auto& pair : cache) {
            std::cout << "  " << pair.first << ": "
                      << (pair.second.expired() ? "expired" : "active")
                      << std::endl;
        }
    }

    void cleanup_expired() {
        std::cout << "Cleaning up expired cache entries..." << std::endl;

        // Remove expired weak_ptr entries
        // Use erase-remove idiom with iterator loop
        for (auto it = cache.begin(); it != cache.end(); ) {
            if (it->second.expired()) {
                std::cout << "  Removing expired entry: " << it->first << std::endl;
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }
};

void test_problem_2_2() {
    std::cout << "=== Problem 2.2: Resource Caching with weak_ptr ===\n";

    ResourceCache cache;

    std::cout << "=== Test 1: Creating and sharing resources ===\n";
    {
        auto resource1 = cache.get_resource("res1");
        auto resource2 = cache.get_resource("res2");
        auto resource1_again = cache.get_resource("res1");  // Should reuse

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
    auto resource3 = cache.get_resource("res1");  // Should create new
    cache.show_cache_status();

    std::cout << std::endl;
}

// =============================================================================
// PROBLEM SET 3: ADVANCED SMART POINTER SCENARIOS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 3.1: Breaking Circular References with weak_ptr
// -----------------------------------------------------------------------------

// FIXED VERSION using weak_ptr to break circular reference
struct TreeNode : public std::enable_shared_from_this<TreeNode> {
    std::string data;
    std::weak_ptr<TreeNode> parent;  // Use weak_ptr to break cycle!
    std::vector<std::shared_ptr<TreeNode>> children;

    TreeNode(const std::string& value) : data(value) {
        std::cout << "TreeNode '" << data << "' created" << std::endl;
    }

    ~TreeNode() {
        std::cout << "TreeNode '" << data << "' destroyed" << std::endl;
    }

    void add_child(std::shared_ptr<TreeNode> child) {
        // shared_from_this() returns shared_ptr to this object
        // Safe because we inherit from enable_shared_from_this
        child->parent = shared_from_this();
        children.push_back(child);
    }

    // Safe method to get parent - returns shared_ptr or nullptr
    std::shared_ptr<TreeNode> get_parent() const {
        return parent.lock();  // Convert weak_ptr to shared_ptr safely
    }

    void show_family() const {
        // Use lock() to safely access parent
        if (auto parent_ptr = parent.lock()) {
            std::cout << data << "'s parent: " << parent_ptr->data << std::endl;
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

void test_problem_3_1() {
    std::cout << "=== Problem 3.1: Breaking Circular References ===\n";

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

    std::cout << std::endl;
}

// -----------------------------------------------------------------------------
// Problem 3.2: Media Library Integration Project
// -----------------------------------------------------------------------------

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
    // shared_ptr for files that can be shared across playlists
    std::unordered_map<std::string, std::shared_ptr<MediaFile>> media_files;

    // unique_ptr for playlists - library has exclusive ownership
    std::vector<std::unique_ptr<Playlist>> playlists;

public:
    std::shared_ptr<MediaFile> load_media_file(const std::string& filename, size_t size) {
        // Check if file already loaded
        auto it = media_files.find(filename);
        if (it != media_files.end()) {
            std::cout << "File '" << filename << "' already loaded, reusing...\n";
            return it->second;
        }

        // Create new media file
        auto file = std::make_shared<MediaFile>(filename, size);
        media_files[filename] = file;
        return file;
    }

    std::unique_ptr<Playlist> create_playlist(const std::string& name) {
        // Create and return unique_ptr - caller takes ownership
        return std::make_unique<Playlist>(name);
    }

    void add_playlist_to_library(std::unique_ptr<Playlist> playlist) {
        // Transfer ownership to library via move
        playlists.push_back(std::move(playlist));
    }

    std::shared_ptr<MediaFile> get_media_file(const std::string& filename) {
        auto it = media_files.find(filename);
        if (it != media_files.end()) {
            return it->second;
        }
        return nullptr;
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
    // weak_ptr doesn't keep track alive - avoids extending lifetime
    std::weak_ptr<MediaFile> current_track;

public:
    void set_current_track(std::shared_ptr<MediaFile> track) {
        current_track = track;
        std::cout << "Now playing: " << track->get_filename() << std::endl;
    }

    void show_current_track() const {
        // Always use lock() to safely access weak_ptr
        if (auto track = current_track.lock()) {
            std::cout << "Current track: " << track->get_filename() << std::endl;
        } else {
            std::cout << "No track currently playing (or track was unloaded)" << std::endl;
        }
    }
};

void test_problem_3_2() {
    std::cout << "=== Problem 3.2: Media Library Integration ===\n";

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

    // Transfer ownership to library
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

    std::cout << std::endl;
}

// =============================================================================
// MAIN FUNCTION - COMPREHENSIVE DEMONSTRATION
// =============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "CHAPTER 11: SMART POINTERS - HOMEWORK HINTS\n";
    std::cout << "========================================\n\n";

    // Problem Set 1: Basic Smart Pointer Usage
    test_problem_1_1();
    test_problem_1_2();
    test_problem_1_3();

    // Problem Set 2: Shared Ownership and Reference Counting
    test_problem_2_1();
    test_problem_2_2();

    // Problem Set 3: Advanced Smart Pointer Scenarios
    test_problem_3_1();
    test_problem_3_2();

    std::cout << "========================================\n";
    std::cout << "ALL TESTS COMPLETED\n";
    std::cout << "========================================\n";

    return 0;
}

/*
=============================================================================
KEY LEARNING POINTS: SMART POINTERS
=============================================================================

1. UNIQUE_PTR - EXCLUSIVE OWNERSHIP
   - Use for single ownership scenarios
   - Move-only semantics (no copying)
   - Zero overhead compared to raw pointers
   - Perfect for RAII and factory patterns
   - Can use custom deleters for C resources (FILE*, etc.)

2. SHARED_PTR - SHARED OWNERSHIP
   - Use when multiple owners need access
   - Reference counting tracks ownership
   - Thread-safe reference counting
   - Slightly more overhead than unique_ptr
   - Use make_shared for efficiency

3. WEAK_PTR - NON-OWNING REFERENCE
   - Breaks circular references
   - Doesn't contribute to reference count
   - Must lock() before accessing
   - Perfect for caches and observer patterns
   - Returns nullptr when object is destroyed

4. COMMON PATTERNS
   - Factory: Return unique_ptr for ownership transfer
   - Sharing: Use shared_ptr for multiple owners
   - Caching: Use weak_ptr to avoid keeping objects alive
   - Trees: weak_ptr for parent pointers breaks cycles
   - RAII: unique_ptr with custom deleters for C resources

5. BEST PRACTICES
   - Prefer make_unique/make_shared over new
   - Use unique_ptr by default
   - Only use shared_ptr when sharing is needed
   - Use weak_ptr to break circular references
   - Never manually delete smart pointer memory
   - enable_shared_from_this for shared_from_this()

6. MEMORY SAFETY
   - Automatic cleanup - no memory leaks
   - Exception safe - RAII guarantees cleanup
   - No dangling pointers with proper usage
   - Type-safe - no void* casts needed
   - Move semantics prevent accidental copies

7. PERFORMANCE
   - unique_ptr: Zero overhead
   - shared_ptr: Atomic reference counting overhead
   - weak_ptr: Must lock() to access (small overhead)
   - make_shared: Single allocation for object + control block

=============================================================================
*/
