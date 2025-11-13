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
    std::shared_ptr<Document> doc;

public:
    Editor(const std::string& editor_name, std::shared_ptr<Document> d)
        : name(editor_name), doc(d) {
        std::cout << "Editor '" << name << "' opened document '" << doc->get_title() << "'\n";
    }

    ~Editor() {
        std::cout << "Editor '" << name << "' closed\n";
    }

    void edit(const std::string& new_content) {
        doc->set_content(new_content);
        std::cout << "Editor '" << name << "' edited the document\n";
    }

    void show_info() const {
        std::cout << "Editor '" << name << "' is working on '" << doc->get_title()
                  << "' (ref count = " << doc.use_count() << ")\n";
    }
};

class Viewer {
private:
    std::string name;
    std::shared_ptr<Document> doc;

public:
    Viewer(const std::string& viewer_name, std::shared_ptr<Document> d)
        : name(viewer_name), doc(d) {
        std::cout << "Viewer '" << name << "' opened document '" << doc->get_title() << "'\n";
    }

    ~Viewer() {
        std::cout << "Viewer '" << name << "' closed\n";
    }

    void view() const {
        std::cout << "Viewer '" << name << "' sees content: " << doc->get_content();
    }

    void show_ref_count() const {
        std::cout << "Viewer '" << name << "' sees ref count = " << doc.use_count() << "\n";
    }
};

int main() {
    auto document = std::make_shared<Document>("Report.txt", "Initial content");

    std::cout << "\nCreating editors and viewers...\n";
    {
        Editor editor1("Alice", document);
        Editor editor2("Bob", document);
        Viewer viewer1("Charlie", document);

        editor1.show_info();  // ref count = 4

        editor1.edit("Alice's changes");
        viewer1.view();

        {
            Viewer viewer2("Dave", document);
            viewer2.show_ref_count();  // ref count = 5
        }
        std::cout << "Dave's viewer destroyed\n";

        editor2.show_info();  // ref count = 4
    }
    std::cout << "All editors and viewers destroyed\n";

    std::cout << "Document ref count: " << document.use_count() << std::endl;

    return 0;
}