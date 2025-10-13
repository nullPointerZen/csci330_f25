#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// Basic unique_ptr example - DataProcessor class
class DataProcessor {
private:
    std::unique_ptr<int[]> data;
    size_t size;

public:
    DataProcessor(size_t n) : size(n) {
        data = std::make_unique<int[]>(n);
        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<int>(i * i);
        }
    }

    // No need for explicit destructor - unique_ptr handles cleanup

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

// Factory pattern with unique_ptr
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
        return nullptr;
    }
};

// RAII File Manager with custom deleter
class FileManager {
private:
    std::unique_ptr<FILE, decltype(&std::fclose)> file;

public:
    FileManager(const std::string& filename, const std::string& mode)
        : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {
        if (!file) {
            throw std::runtime_error("Could not open file: " + filename);
        }
    }

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
        return file != nullptr;
    }
};

// Document sharing system with shared_ptr
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
    std::shared_ptr<Document> document;

public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> doc)
        : name(editor_name), document(doc) {
        std::cout << "Editor " << name << " created" << std::endl;
    }

    ~Editor() {
        std::cout << "Editor " << name << " destroyed" << std::endl;
    }

    void edit(const std::string& new_content) {
        if (document) {
            document->set_content(new_content);
            std::cout << name << " edited document" << std::endl;
        }
    }

    void show_info() const {
        if (document) {
            std::cout << "Editor " << name << " - Document: " << document->get_title()
                      << " (ref count: " << document.use_count() << ")" << std::endl;
        }
    }
};

class Viewer {
private:
    std::string name;
    std::shared_ptr<Document> document;

public:
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> doc)
        : name(viewer_name), document(doc) {
        std::cout << "Viewer " << name << " created" << std::endl;
    }

    ~Viewer() {
        std::cout << "Viewer " << name << " destroyed" << std::endl;
    }

    void view() const {
        if (document) {
            std::cout << name << " viewing: " << document->get_content() << std::endl;
        }
    }

    void show_ref_count() const {
        if (document) {
            std::cout << "Viewer " << name << " - ref count: " << document.use_count() << std::endl;
        }
    }
};

// Resource cache with weak_ptr
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
            if (auto resource = it->second.lock()) {
                std::cout << "Reusing cached resource: " << id << std::endl;
                return resource;
            } else {
                cache.erase(it);  // Remove expired entry
            }
        }

        auto resource = std::make_shared<ExpensiveResource>(id);
        cache[id] = resource;
        return resource;
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
        auto it = cache.begin();
        while (it != cache.end()) {
            if (it->second.expired()) {
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }
};

// Tree structure fixing circular references with weak_ptr
struct TreeNode : public std::enable_shared_from_this<TreeNode> {
    std::string data;
    std::weak_ptr<TreeNode> parent;  // Fixed: weak_ptr to break cycles
    std::vector<std::shared_ptr<TreeNode>> children;

    TreeNode(const std::string& value) : data(value) {
        std::cout << "TreeNode '" << data << "' created" << std::endl;
    }

    ~TreeNode() {
        std::cout << "TreeNode '" << data << "' destroyed" << std::endl;
    }

    void add_child(std::shared_ptr<TreeNode> child) {
        child->parent = shared_from_this();
        children.push_back(child);
    }

    std::shared_ptr<TreeNode> get_parent() {
        return parent.lock();  // Safely get parent if still alive
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

// Media library integration example
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
            std::cout << "File already loaded: " << filename << std::endl;
            return it->second;
        }

        auto file = std::make_shared<MediaFile>(filename, size);
        media_files[filename] = file;
        return file;
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
            std::cout << "No track currently playing (or track was deleted)" << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Basic unique_ptr Demo ===\n";
    {
        DataProcessor processor(5);
        processor.print_data();

        DataProcessor processor2 = std::move(processor);
        processor2.print_data();

        std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
    }

    std::cout << "\n=== Factory Pattern Demo ===\n";
    {
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
    }

    std::cout << "\n=== RAII File Manager Demo ===\n";
    {
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
    }

    std::cout << "\n=== Document Sharing Demo ===\n";
    {
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
    }

    std::cout << "\n=== Resource Cache Demo ===\n";
    {
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
    }

    std::cout << "\n=== Tree Structure Demo (Fixed Circular References) ===\n";
    {
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
    }

    std::cout << "\n=== Media Library Integration Demo ===\n";
    {
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
    }

    return 0;
}