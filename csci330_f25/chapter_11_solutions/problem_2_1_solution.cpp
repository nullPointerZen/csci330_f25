/*
 * Chapter 11, Problem 2.1: Document Sharing System
 * 
 * Solution: Document sharing with shared_ptr for multiple ownership
 * 
 * Key concepts demonstrated:
 * - shared_ptr for shared ownership
 * - Reference counting and use_count()
 * - Automatic cleanup when last reference is removed
 * - Passing shared_ptr by value vs by reference
 */

#include <memory>
#include <iostream>
#include <string>

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
    std::shared_ptr<Document> document;  // Shared ownership
    
public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> doc)
        : name(editor_name), document(std::move(doc)) {  // Move to avoid extra ref count increment
        std::cout << "Editor " << name << " opened" << std::endl;
    }
    
    ~Editor() {
        std::cout << "Editor " << name << " closed" << std::endl;
    }
    
    void edit(const std::string& new_content) {
        if (document) {
            document->set_content(new_content);
            std::cout << name << " edited document: " << new_content << std::endl;
        }
    }
    
    void show_info() const {
        if (document) {
            std::cout << name << " accessing '" << document->get_title() 
                      << "' (ref count: " << document.use_count() << ")" << std::endl;
        }
    }
};

class Viewer {
private:
    std::string name;
    std::shared_ptr<Document> document;  // Shared ownership
    
public:
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> doc)
        : name(viewer_name), document(std::move(doc)) {  // Move to avoid extra ref count increment
        std::cout << "Viewer " << name << " opened" << std::endl;
    }
    
    ~Viewer() {
        std::cout << "Viewer " << name << " closed" << std::endl;
    }
    
    void view() const {
        if (document) {
            std::cout << name << " viewing '" << document->get_title() 
                      << "': " << document->get_content() << std::endl;
        }
    }
    
    void show_ref_count() const {
        if (document) {
            std::cout << name << " sees ref count: " << document.use_count() << std::endl;
        }
    }
};

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

/*
 * Expected Output:
 * Document 'Report.txt' created
 * 
 * Creating editors and viewers...
 * Editor Alice opened
 * Editor Bob opened
 * Viewer Charlie opened
 * Alice accessing 'Report.txt' (ref count: 4)
 * Alice edited document: Alice's changes
 * Charlie viewing 'Report.txt': Alice's changes
 * Viewer Dave opened
 * Dave sees ref count: 5
 * Viewer Dave closed
 * Dave's viewer destroyed
 * Bob accessing 'Report.txt' (ref count: 4)
 * Editor Alice closed
 * Editor Bob closed
 * Viewer Charlie closed
 * All editors and viewers destroyed
 * Document ref count: 1
 * Document 'Report.txt' destroyed
 * 
 * Key concepts explained:
 * 
 * 1. Shared Ownership:
 *    - Multiple Editor and Viewer objects share ownership of the same Document
 *    - Document stays alive as long as any shared_ptr references it
 *    - Last shared_ptr automatically destroys the Document
 * 
 * 2. Reference Counting:
 *    - use_count() shows how many shared_ptr objects reference the same object
 *    - Count increases when shared_ptr is copied
 *    - Count decreases when shared_ptr is destroyed or reset
 * 
 * 3. Parameter Passing:
 *    - Constructor takes shared_ptr by value, then moves it to member variable
 *    - This is efficient and safe for transferring ownership
 *    - Alternative: take by const reference, but then must copy to member
 * 
 * 4. Automatic Cleanup:
 *    - When last shared_ptr is destroyed, Document destructor is called
 *    - No manual memory management needed
 *    - Exception-safe: cleanup happens even if exceptions are thrown
 */