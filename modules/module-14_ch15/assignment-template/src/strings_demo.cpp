// HW_15: Strings and Text Processing
// Time: 2.25 hours (45 minutes per problem set)
// Topics: std::string, string_view, regex, text processing

#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <chrono>

// ============================================================================
// PROBLEM SET 1: String Fundamentals (45 minutes)
// ============================================================================

void string_construction() {
    printf("=== String Construction and Initialization ===\n");
    
    // TODO 1: Various string construction methods
    printf("String Construction Methods:\n");
    
    // Default construction
    std::string empty_str;
    printf("  Default: '%s' (length: %zu)\n", empty_str.c_str(), empty_str.length());
    
    // C-string construction
    std::string from_cstr("Hello, World!");
    printf("  From C-string: '%s'\n", from_cstr.c_str());
    
    // Copy construction
    std::string copied(from_cstr);
    printf("  Copy constructed: '%s'\n", copied.c_str());
    
    // Substring construction
    std::string substring(from_cstr, 7, 5);  // "World"
    printf("  Substring(7, 5): '%s'\n", substring.c_str());
    
    // Fill construction
    std::string filled(10, 'A');
    printf("  Fill(10, 'A'): '%s'\n", filled.c_str());
    
    // TODO 2: String initialization (C++11)
    printf("\nString Initialization (C++11):\n");
    
    std::string brace_init{"Brace initialization"};
    printf("  Brace init: '%s'\n", brace_init.c_str());
    
    std::string assignment = "Direct assignment";
    printf("  Assignment: '%s'\n", assignment.c_str());
    
    // List initialization
    std::string list_init{'H', 'e', 'l', 'l', 'o'};
    printf("  List init: '%s'\n", list_init.c_str());
    
    printf("\n");
}

void string_operations() {
    printf("=== String Operations ===\n");
    
    // TODO 3: Basic string operations
    printf("Basic String Operations:\n");
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    
    // Concatenation
    std::string combined = str1 + ", " + str2 + "!";
    printf("  Concatenation: '%s'\n", combined.c_str());
    
    // Append operations
    std::string append_str = "C++";
    append_str += " is";
    append_str.append(" awesome");
    printf("  Append operations: '%s'\n", append_str.c_str());
    
    // TODO 4: String comparison
    printf("\nString Comparison:\n");
    
    std::string a = "apple";
    std::string b = "banana";
    std::string c = "apple";
    
    printf("  '%s' == '%s': %s\n", a.c_str(), c.c_str(), (a == c) ? "true" : "false");
    printf("  '%s' < '%s': %s\n", a.c_str(), b.c_str(), (a < b) ? "true" : "false");
    
    int compare_result = a.compare(b);
    printf("  a.compare(b): %d ", compare_result);
    if (compare_result < 0) printf("(a < b)\n");
    else if (compare_result > 0) printf("(a > b)\n");
    else printf("(a == b)\n");
    
    // TODO 5: String modification
    printf("\nString Modification:\n");
    
    std::string modify_str = "The quick brown fox";
    printf("  Original: '%s'\n", modify_str.c_str());
    
    // Insert
    modify_str.insert(4, "very ");
    printf("  After insert(4, 'very '): '%s'\n", modify_str.c_str());
    
    // Replace
    modify_str.replace(4, 5, "extremely");  // Replace "very " with "extremely"
    printf("  After replace(4, 5, 'extremely'): '%s'\n", modify_str.c_str());
    
    // Erase
    modify_str.erase(4, 10);  // Remove "extremely"
    printf("  After erase(4, 10): '%s'\n", modify_str.c_str());
    
    // Clear and assign
    modify_str.clear();
    modify_str.assign("New content");
    printf("  After clear and assign: '%s'\n", modify_str.c_str());
    
    printf("\n");
}

void string_memory_management() {
    printf("=== String Memory Management ===\n");
    
    // TODO 6: String capacity and memory
    printf("String Capacity and Memory:\n");
    
    std::string memory_str;
    printf("  Initial - Size: %zu, Capacity: %zu\n", 
           memory_str.size(), memory_str.capacity());
    
    // Add characters and watch capacity grow
    for (int i = 0; i < 20; i++) {
        memory_str += ('A' + i);
        if (i < 10 || i % 5 == 0) {  // Don't spam output
            printf("  Length %d - Size: %zu, Capacity: %zu\n", 
                   i + 1, memory_str.size(), memory_str.capacity());
        }
    }
    
    // Reserve space
    memory_str.reserve(100);
    printf("  After reserve(100) - Size: %zu, Capacity: %zu\n", 
           memory_str.size(), memory_str.capacity());
    
    // Shrink to fit
    memory_str.shrink_to_fit();
    printf("  After shrink_to_fit() - Size: %zu, Capacity: %zu\n", 
           memory_str.size(), memory_str.capacity());
    
    // TODO 7: String access methods
    printf("\nString Access Methods:\n");
    
    std::string access_str = "Programming";
    
    printf("  String: '%s'\n", access_str.c_str());
    printf("  Character access:\n");
    
    // Operator[] vs at()
    printf("    str[0] = '%c'\n", access_str[0]);
    printf("    str.at(0) = '%c'\n", access_str.at(0));
    
    // Front and back
    printf("    str.front() = '%c'\n", access_str.front());
    printf("    str.back() = '%c'\n", access_str.back());
    
    // Data pointer
    const char* data_ptr = access_str.data();
    printf("    str.data(): '%s'\n", data_ptr);
    
    // Substring
    std::string sub = access_str.substr(0, 7);  // "Program"
    printf("    substr(0, 7): '%s'\n", sub.c_str());
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: String Fundamentals ===\n\n");
    
    string_construction();
    string_operations();
    string_memory_management();
}

// ============================================================================
// PROBLEM SET 2: String Views and Efficiency (45 minutes)
// ============================================================================

void string_view_basics() {
    printf("=== String View Basics ===\n");
    
    // TODO 8: string_view construction and usage
    printf("String View Construction:\n");
    
    std::string original = "Hello, string_view world!";
    
    // Create string_view from string
    std::string_view sv_from_string(original);
    printf("  From string: '%s' (size: %zu)\n", 
           std::string(sv_from_string).c_str(), sv_from_string.size());
    
    // Create string_view from C-string
    std::string_view sv_from_cstr("C-string literal");
    printf("  From C-string: '%s'\n", std::string(sv_from_cstr).c_str());
    
    // Create substring view
    std::string_view sv_substr = sv_from_string.substr(7, 11);  // "string_view"
    printf("  Substring view: '%s'\n", std::string(sv_substr).c_str());
    
    // TODO 9: string_view operations
    printf("\nString View Operations:\n");
    
    std::string_view text = "The quick brown fox jumps";
    
    printf("  Original: '%s'\n", std::string(text).c_str());
    printf("  Length: %zu\n", text.length());
    printf("  Empty: %s\n", text.empty() ? "true" : "false");
    
    // Remove prefix/suffix
    text.remove_prefix(4);  // Remove "The "
    printf("  After remove_prefix(4): '%s'\n", std::string(text).c_str());
    
    text.remove_suffix(6);  // Remove " jumps"
    printf("  After remove_suffix(6): '%s'\n", std::string(text).c_str());
    
    // Find operations
    auto pos = text.find("brown");
    if (pos != std::string_view::npos) {
        printf("  find('brown') at position: %zu\n", pos);
    }
    
    printf("\n");
}

// TODO 10: Performance comparison function
void process_with_string(const std::string& str) {
    // Simulate some processing that doesn't modify the string
    size_t vowel_count = 0;
    for (char c : str) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowel_count++;
        }
    }
    (void)vowel_count;  // Suppress unused variable warning
}

void process_with_string_view(std::string_view sv) {
    // Same processing but with string_view (no copying)
    size_t vowel_count = 0;
    for (char c : sv) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowel_count++;
        }
    }
    (void)vowel_count;  // Suppress unused variable warning
}

void performance_optimization() {
    printf("=== Performance Optimization: string vs string_view ===\n");
    
    // TODO: Performance comparison
    printf("Performance Comparison:\n");
    
    std::string large_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                            "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                            "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.";
    
    const int iterations = 10000;
    
    // Test with std::string (copying)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        process_with_string(large_text);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto string_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test with std::string_view (no copying)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        process_with_string_view(large_text);
    }
    end = std::chrono::high_resolution_clock::now();
    auto string_view_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    printf("  std::string processing (%d iterations): %ld µs\n", 
           iterations, string_time.count());
    printf("  std::string_view processing (%d iterations): %ld µs\n", 
           iterations, string_view_time.count());
    
    if (string_view_time.count() > 0) {
        printf("  string_view is %.1fx faster\n", 
               static_cast<double>(string_time.count()) / string_view_time.count());
    }
    
    printf("\n");
}

// TODO 11: String algorithms with string_view
std::vector<std::string_view> split_string_view(std::string_view text, char delimiter) {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    size_t end = text.find(delimiter);
    
    while (end != std::string_view::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
        end = text.find(delimiter, start);
    }
    
    // Add the last token
    tokens.push_back(text.substr(start));
    
    return tokens;
}

std::string_view trim_string_view(std::string_view text) {
    // Remove leading whitespace
    auto start = text.find_first_not_of(" \t\n\r");
    if (start == std::string_view::npos) {
        return std::string_view{};  // All whitespace
    }
    
    // Remove trailing whitespace
    auto end = text.find_last_not_of(" \t\n\r");
    
    return text.substr(start, end - start + 1);
}

void string_algorithms() {
    printf("=== String Algorithms with string_view ===\n");
    
    // TODO: String splitting
    printf("String Splitting:\n");
    
    std::string csv_data = "apple,banana,cherry,date,elderberry";
    auto tokens = split_string_view(csv_data, ',');
    
    printf("  CSV data: '%s'\n", csv_data.c_str());
    printf("  Tokens:\n");
    for (const auto& token : tokens) {
        printf("    '%s'\n", std::string(token).c_str());
    }
    
    // TODO: String trimming
    printf("\nString Trimming:\n");
    
    std::string messy_text = "   Hello, World!   \n\t  ";
    std::string_view trimmed = trim_string_view(messy_text);
    
    printf("  Original: '%s' (length: %zu)\n", messy_text.c_str(), messy_text.length());
    printf("  Trimmed: '%s' (length: %zu)\n", 
           std::string(trimmed).c_str(), trimmed.length());
    
    // TODO: String searching and matching
    printf("\nString Searching:\n");
    
    std::string_view text = "The quick brown fox jumps over the lazy dog";
    
    // Count occurrences of a substring
    size_t count = 0;
    size_t pos = 0;
    std::string_view target = "the";
    
    while ((pos = text.find(target, pos)) != std::string_view::npos) {
        count++;
        pos += target.length();
    }
    
    printf("  Text: '%s'\n", std::string(text).c_str());
    printf("  Occurrences of 'the': %zu\n", count);
    
    // Case-insensitive search
    std::string lower_text;
    std::transform(text.begin(), text.end(), std::back_inserter(lower_text), ::tolower);
    std::string_view lower_view(lower_text);
    
    count = 0;
    pos = 0;
    while ((pos = lower_view.find(target, pos)) != std::string_view::npos) {
        count++;
        pos += target.length();
    }
    
    printf("  Case-insensitive occurrences of 'the': %zu\n", count);
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: String Views and Efficiency ===\n\n");
    
    string_view_basics();
    performance_optimization();
    string_algorithms();
}

// ============================================================================
// PROBLEM SET 3: Text Processing and Regex (45 minutes)
// ============================================================================

void regular_expressions() {
    printf("=== Regular Expressions ===\n");
    
    // TODO 12: Basic regex matching
    printf("Basic Regex Matching:\n");
    
    std::string text = "Contact us at support@example.com or sales@company.org";
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    
    printf("  Text: '%s'\n", text.c_str());
    printf("  Email pattern: [a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\n");
    
    // Find all matches
    std::sregex_iterator start(text.begin(), text.end(), email_pattern);
    std::sregex_iterator end;
    
    printf("  Found emails:\n");
    for (std::sregex_iterator i = start; i != end; ++i) {
        std::smatch match = *i;
        printf("    %s (position %zu-%zu)\n", 
               match.str().c_str(), match.position(), 
               match.position() + match.length());
    }
    
    // TODO 13: Regex validation
    printf("\nRegex Validation:\n");
    
    std::vector<std::string> phone_numbers = {
        "(555) 123-4567",
        "555-123-4567", 
        "555.123.4567",
        "5551234567",
        "123-45-6789",  // Invalid
        "555-12-34567"  // Invalid
    };
    
    std::regex phone_pattern(R"((\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{4}))");
    
    printf("  Phone number validation:\n");
    for (const auto& phone : phone_numbers) {
        bool valid = std::regex_match(phone, phone_pattern);
        printf("    '%s': %s\n", phone.c_str(), valid ? "VALID" : "INVALID");
    }
    
    // TODO 14: Regex replacement
    printf("\nRegex Replacement:\n");
    
    std::string document = "The year 2023 was followed by 2024, and 2025 comes next.";
    std::regex year_pattern(R"(\b(20\d{2})\b)");
    
    printf("  Original: '%s'\n", document.c_str());
    
    // Replace years with [YEAR]
    std::string redacted = std::regex_replace(document, year_pattern, "[YEAR]");
    printf("  Redacted: '%s'\n", redacted.c_str());
    
    // Replace with captured groups
    std::string formatted = std::regex_replace(document, year_pattern, "Year $1");
    printf("  Formatted: '%s'\n", formatted.c_str());
    
    printf("\n");
}

void text_parsing() {
    printf("=== Text Parsing and Tokenization ===\n");
    
    // TODO 15: CSV parsing
    printf("CSV Parsing:\n");
    
    std::string csv_line = "John Doe,30,Engineer,\"New York, NY\",75000";
    std::regex csv_pattern(R"((?:^|,)(\"[^\"]*\"|[^,]*))");
    
    printf("  CSV line: '%s'\n", csv_line.c_str());
    
    std::vector<std::string> fields;
    std::sregex_iterator iter(csv_line.begin(), csv_line.end(), csv_pattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        std::string field = iter->str(1);  // First capture group
        // Remove quotes if present
        if (field.front() == '"' && field.back() == '"') {
            field = field.substr(1, field.length() - 2);
        }
        fields.push_back(field);
    }
    
    printf("  Parsed fields:\n");
    for (size_t i = 0; i < fields.size(); i++) {
        printf("    Field %zu: '%s'\n", i + 1, fields[i].c_str());
    }
    
    // TODO 16: Log file parsing
    printf("\nLog File Parsing:\n");
    
    std::vector<std::string> log_entries = {
        "2024-01-15 10:30:45 [INFO] User login successful for user: admin",
        "2024-01-15 10:31:22 [ERROR] Database connection failed",
        "2024-01-15 10:32:01 [WARN] High memory usage detected: 85%",
        "2024-01-15 10:33:15 [INFO] Backup completed successfully"
    };
    
    std::regex log_pattern(R"((\d{4}-\d{2}-\d{2}) (\d{2}:\d{2}:\d{2}) \[(\w+)\] (.+))");
    
    printf("  Log entries:\n");
    for (const auto& entry : log_entries) {
        std::smatch match;
        if (std::regex_match(entry, match, log_pattern)) {
            printf("    Date: %s, Time: %s, Level: %s\n", 
                   match[1].str().c_str(), match[2].str().c_str(), match[3].str().c_str());
            printf("      Message: %s\n", match[4].str().c_str());
        }
    }
    
    printf("\n");
}

void advanced_text_processing() {
    printf("=== Advanced Text Processing ===\n");
    
    // TODO 17: Word frequency analysis
    printf("Word Frequency Analysis:\n");
    
    std::string text = "The quick brown fox jumps over the lazy dog. "
                      "The dog was lazy, but the fox was quick.";
    
    printf("  Text: '%s'\n", text.c_str());
    
    // Convert to lowercase and extract words
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    std::regex word_pattern(R"(\b[a-z]+\b)");
    
    std::map<std::string, int> word_count;
    std::sregex_iterator word_iter(text.begin(), text.end(), word_pattern);
    std::sregex_iterator word_end;
    
    for (; word_iter != word_end; ++word_iter) {
        word_count[word_iter->str()]++;
    }
    
    printf("  Word frequencies:\n");
    for (const auto& [word, count] : word_count) {
        printf("    '%s': %d\n", word.c_str(), count);
    }
    
    // TODO 18: Text transformation
    printf("\nText Transformation:\n");
    
    std::string original = "hello world from c++ programming";
    printf("  Original: '%s'\n", original.c_str());
    
    // Title case transformation
    std::string title_case = original;
    bool capitalize_next = true;
    
    for (char& c : title_case) {
        if (std::isspace(c)) {
            capitalize_next = true;
        } else if (capitalize_next) {
            c = std::toupper(c);
            capitalize_next = false;
        }
    }
    
    printf("  Title case: '%s'\n", title_case.c_str());
    
    // Reverse words
    std::istringstream iss(original);
    std::vector<std::string> words;
    std::string word;
    
    while (iss >> word) {
        words.push_back(word);
    }
    
    std::reverse(words.begin(), words.end());
    
    std::ostringstream reversed_stream;
    for (size_t i = 0; i < words.size(); i++) {
        if (i > 0) reversed_stream << " ";
        reversed_stream << words[i];
    }
    
    printf("  Reversed words: '%s'\n", reversed_stream.str().c_str());
    
    // TODO 19: String formatting and building
    printf("\nString Formatting and Building:\n");
    
    std::ostringstream formatter;
    formatter << "Student: " << "Alice" << ", ";
    formatter << "Grade: " << 95 << ", ";
    formatter << "GPA: " << std::fixed << std::setprecision(2) << 3.85;
    
    printf("  Formatted string: '%s'\n", formatter.str().c_str());
    
    // Template-based formatting
    std::string name = "Bob";
    int age = 25;
    double salary = 55000.75;
    
    std::string template_str = "Employee: {name}, Age: {age}, Salary: ${salary}";
    
    // Simple template replacement (not using std::format for compatibility)
    std::regex name_placeholder("\\{name\\}");
    std::regex age_placeholder("\\{age\\}");
    std::regex salary_placeholder("\\{salary\\}");
    
    std::string result = std::regex_replace(template_str, name_placeholder, name);
    result = std::regex_replace(result, age_placeholder, std::to_string(age));
    result = std::regex_replace(result, salary_placeholder, std::to_string(salary));
    
    printf("  Template result: '%s'\n", result.c_str());
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Text Processing and Regex ===\n\n");
    
    regular_expressions();
    text_parsing();
    advanced_text_processing();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("     HW_15: Strings and Text Processing\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: String Fundamentals (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: String Views and Efficiency (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Text Processing and Regex (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}