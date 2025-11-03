#include <iostream>
#include <vector>
#include <string>

// Event handler function type
typedef void (*EventHandler)(const std::string& event_data);

// Implement different event handlers
void log_handler(const std::string& event_data) {
    std::cout << "[LOG] " << event_data << "\n";
}

void alert_handler(const std::string& event_data) {
    std::cout << "[ALERT] Critical event: " << event_data << "\n";
}

void debug_handler(const std::string& event_data) {
    std::cout << "[DEBUG] Event details: " << event_data << "\n";
}

class EventSystem {
private:
    std::vector<EventHandler> handlers;

public:
    void register_handler(EventHandler handler) {
        handlers.push_back(handler);
    }

    void fire_event(const std::string& event_data) const {
        for (auto& handler : handlers) {
            handler(event_data);
        }
    }

    size_t get_handler_count() const {
        return handlers.size();
    }
};

int main() {
    EventSystem event_system;

    std::cout << "Registering event handlers...\n";
    event_system.register_handler(log_handler);
    event_system.register_handler(alert_handler);
    event_system.register_handler(debug_handler);

    std::cout << "Handlers registered: " << event_system.get_handler_count() << "\n\n";

    std::string event1 = "User logged in";
    std::cout << "Firing event: \"" << event1 << "\"\n";
    event_system.fire_event(event1);
    std::cout << "\n";

    std::string event2 = "File uploaded";
    std::cout << "Firing event: \"" << event2 << "\"\n";
    event_system.fire_event(event2);
    std::cout << "\n";

    return 0;
}