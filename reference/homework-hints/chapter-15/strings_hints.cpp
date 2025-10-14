#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <regex>

// =============================================================================
// PROBLEM SET 1: STRING FUNDAMENTALS
// =============================================================================

namespace problem_set_1 {

// Problem 1.1: String Creation and Basic Operations
void problem_1_1() {
    std::cout << "\n=== Problem 1.1: String Creation and Basic Operations ===\n";

    // 1. Create a string with your name
    std::string name = "Alice";

    // 2. Create a greeting by concatenating "Hello, " with your name
    std::string greeting = "Hello, " + name;

    // 3. Add an exclamation mark at the end
    greeting += "!";

    // 4. Print the length of the greeting
    std::cout << "Length: " << greeting.length() << std::endl;

    // 5. Print the first and last characters
    std::cout << "First: " << greeting[0] << std::endl;
    std::cout << "Last: " << greeting[greeting.length() - 1] << std::endl;

    // 6. Convert to uppercase
    std::string upper_greeting = greeting;
    std::transform(upper_greeting.begin(), upper_greeting.end(),
                   upper_greeting.begin(), ::toupper);
    std::cout << upper_greeting << std::endl;
}

// Problem 1.2: String Searching and Extraction
std::string extract_domain(const std::string& email) {
    // Find the position of '@' character
    size_t at_pos = email.find('@');

    // If '@' not found, return empty string
    if (at_pos == std::string::npos) {
        return "";
    }

    // Extract substring from position after '@' to the end
    return email.substr(at_pos + 1);
}

std::string extract_filename(const std::string& path) {
    // Find the last occurrence of '/' (or '\\' for Windows)
    size_t last_slash = path.find_last_of("/\\");

    // If no slash found, the entire path is the filename
    if (last_slash == std::string::npos) {
        return path;
    }

    // Extract substring from position after last slash to the end
    return path.substr(last_slash + 1);
}

void problem_1_2() {
    std::cout << "\n=== Problem 1.2: String Searching and Extraction ===\n";

    std::string email = "alice.smith@university.edu";
    std::string path = "/home/projects/cpp/main.cpp";

    std::cout << "Domain: " << extract_domain(email) << std::endl;
    std::cout << "Filename: " << extract_filename(path) << std::endl;
}

// Problem 1.3: String Validation
bool is_valid_password(const std::string& password) {
    // Check length requirement
    if (password.length() < 8) {
        return false;
    }

    // Check for at least one uppercase, lowercase, and digit
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (char c : password) {
        if (std::isupper(c)) has_upper = true;
        if (std::islower(c)) has_lower = true;
        if (std::isdigit(c)) has_digit = true;
    }

    return has_upper && has_lower && has_digit;
}

bool is_palindrome(const std::string& text) {
    // Create a normalized version: lowercase, no spaces
    std::string normalized;
    for (char c : text) {
        if (!std::isspace(c)) {
            normalized += std::tolower(c);
        }
    }

    // Check if normalized string reads same forwards and backwards
    size_t len = normalized.length();
    for (size_t i = 0; i < len / 2; ++i) {
        if (normalized[i] != normalized[len - 1 - i]) {
            return false;
        }
    }

    return true;
}

void problem_1_3() {
    std::cout << "\n=== Problem 1.3: String Validation ===\n";

    // Test passwords
    std::cout << "Password1: " << (is_valid_password("Password1") ? "Valid" : "Invalid") << std::endl;
    std::cout << "weak: " << (is_valid_password("weak") ? "Valid" : "Invalid") << std::endl;

    // Test palindromes
    std::cout << "racecar: " << (is_palindrome("racecar") ? "Palindrome" : "Not palindrome") << std::endl;
    std::cout << "hello: " << (is_palindrome("hello") ? "Palindrome" : "Not palindrome") << std::endl;
    std::cout << "A man a plan a canal Panama: "
              << (is_palindrome("A man a plan a canal Panama") ? "Palindrome" : "Not palindrome") << std::endl;
}

void run_all() {
    problem_1_1();
    problem_1_2();
    problem_1_3();
}

} // namespace problem_set_1

// =============================================================================
// PROBLEM SET 2: TEXT PROCESSING
// =============================================================================

namespace problem_set_2 {

// Problem 2.1: CSV Parser
class CSVParser {
public:
    std::vector<std::string> parse_line(const std::string& line) {
        std::vector<std::string> fields;
        std::string current_field;
        bool in_quotes = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            if (c == '"') {
                // Check for escaped quote (two consecutive quotes)
                if (in_quotes && i + 1 < line.length() && line[i + 1] == '"') {
                    current_field += '"';
                    ++i; // Skip next quote
                } else {
                    // Toggle quote mode
                    in_quotes = !in_quotes;
                }
            } else if (c == ',' && !in_quotes) {
                // End of field
                fields.push_back(current_field);
                current_field.clear();
            } else {
                // Regular character
                current_field += c;
            }
        }

        // Add the last field
        fields.push_back(current_field);

        return fields;
    }

    void print_parsed(const std::vector<std::string>& fields) {
        for (size_t i = 0; i < fields.size(); ++i) {
            std::cout << "Field " << i << ": '" << fields[i] << "'" << std::endl;
        }
    }
};

void problem_2_1() {
    std::cout << "\n=== Problem 2.1: CSV Parser ===\n";

    CSVParser parser;

    // Test cases
    std::string simple = "John,Doe,30,Engineer";
    std::string quoted = "John,\"Doe, Jr.\",30,\"Software Engineer\"";
    std::string escaped = "John,\"He said \"\"Hello\"\"\",30,Engineer";

    std::cout << "Simple CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(simple));

    std::cout << "\nQuoted CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(quoted));

    std::cout << "\nEscaped quotes CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(escaped));
}

// Problem 2.2: Text Statistics
class TextAnalyzer {
private:
    std::string text;

public:
    TextAnalyzer(const std::string& input) : text(input) {}

    int count_words() {
        std::istringstream iss(text);
        std::string word;
        int count = 0;

        while (iss >> word) {
            count++;
        }

        return count;
    }

    int count_sentences() {
        int count = 0;

        for (char c : text) {
            if (c == '.' || c == '!' || c == '?') {
                count++;
            }
        }

        return count;
    }

    std::map<char, int> character_frequency() {
        std::map<char, int> freq;

        for (char c : text) {
            if (std::isalpha(c)) {
                // Convert to lowercase and count
                char lower = std::tolower(c);
                freq[lower]++;
            }
        }

        return freq;
    }

    std::string most_common_word() {
        std::map<std::string, int> word_freq;
        std::istringstream iss(text);
        std::string word;

        // Count word frequencies (case-insensitive)
        while (iss >> word) {
            // Remove punctuation from end of word
            while (!word.empty() && std::ispunct(word.back())) {
                word.pop_back();
            }

            // Convert to lowercase
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (!word.empty()) {
                word_freq[word]++;
            }
        }

        // Find most common word
        std::string most_common;
        int max_count = 0;

        for (const auto& pair : word_freq) {
            if (pair.second > max_count) {
                max_count = pair.second;
                most_common = pair.first;
            }
        }

        return most_common;
    }

    void print_statistics() {
        std::cout << "Words: " << count_words() << std::endl;
        std::cout << "Sentences: " << count_sentences() << std::endl;
        std::cout << "Most common word: " << most_common_word() << std::endl;

        std::cout << "Character frequencies:" << std::endl;
        auto freq = character_frequency();
        for (const auto& pair : freq) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
};

void problem_2_2() {
    std::cout << "\n=== Problem 2.2: Text Statistics ===\n";

    std::string text = "The quick brown fox jumps over the lazy dog. "
                       "The dog was sleeping in the sun. What a beautiful day!";

    TextAnalyzer analyzer(text);
    analyzer.print_statistics();
}

// Problem 2.3: Simple Template Engine
class TemplateEngine {
private:
    std::map<std::string, std::string> variables;

public:
    void set_variable(const std::string& name, const std::string& value) {
        variables[name] = value;
    }

    std::string render(const std::string& template_text) {
        std::string result = template_text;

        // Replace {{variable_name}} with values
        for (const auto& pair : variables) {
            std::string placeholder = "{{" + pair.first + "}}";
            size_t pos = 0;

            while ((pos = result.find(placeholder, pos)) != std::string::npos) {
                result.replace(pos, placeholder.length(), pair.second);
                pos += pair.second.length();
            }
        }

        return result;
    }

    std::string render_with_conditionals(const std::string& template_text) {
        std::string result = template_text;

        // First, replace simple variables
        result = render(result);

        // Handle {{#if variable_name}}text{{/if}}
        std::regex if_pattern(R"(\{\{#if ([^}]+)\}\}(.*?)\{\{/if\}\})");
        std::smatch match;
        std::string temp = result;
        result.clear();

        auto search_start = temp.cbegin();
        while (std::regex_search(search_start, temp.cend(), match, if_pattern)) {
            // Add text before the match
            result.append(search_start, match[0].first);

            // Check if variable exists and is not empty
            std::string var_name = match[1].str();
            if (variables.count(var_name) && !variables[var_name].empty()) {
                // Variable exists and is not empty, include the content
                std::string content = match[2].str();
                result += render(content); // Render any variables in the content
            }

            search_start = match[0].second;
        }
        result.append(search_start, temp.cend());

        // Handle {{#unless variable_name}}text{{/unless}}
        temp = result;
        result.clear();
        std::regex unless_pattern(R"(\{\{#unless ([^}]+)\}\}(.*?)\{\{/unless\}\})");

        search_start = temp.cbegin();
        while (std::regex_search(search_start, temp.cend(), match, unless_pattern)) {
            // Add text before the match
            result.append(search_start, match[0].first);

            // Check if variable does not exist or is empty
            std::string var_name = match[1].str();
            if (!variables.count(var_name) || variables[var_name].empty()) {
                // Variable doesn't exist or is empty, include the content
                std::string content = match[2].str();
                result += render(content);
            }

            search_start = match[0].second;
        }
        result.append(search_start, temp.cend());

        return result;
    }
};

void problem_2_3() {
    std::cout << "\n=== Problem 2.3: Simple Template Engine ===\n";

    TemplateEngine engine;
    engine.set_variable("name", "Alice");
    engine.set_variable("age", "25");
    engine.set_variable("city", "New York");

    std::string basic_template = "Hello {{name}}! You are {{age}} years old and live in {{city}}.";
    std::cout << "Basic template:\n" << engine.render(basic_template) << std::endl;

    std::string conditional_template =
        "Welcome {{name}}! "
        "{{#if age}}You are {{age}} years old. {{/if}}"
        "{{#unless phone}}Please provide your phone number. {{/unless}}";

    std::cout << "\nConditional template:\n"
              << engine.render_with_conditionals(conditional_template) << std::endl;
}

void run_all() {
    problem_2_1();
    problem_2_2();
    problem_2_3();
}

} // namespace problem_set_2

// =============================================================================
// PROBLEM SET 3: ADVANCED STRING OPERATIONS
// =============================================================================

namespace problem_set_3 {

// Problem 3.1: String Compression
class StringCompressor {
public:
    std::string run_length_encode(const std::string& input) {
        if (input.empty()) return "";

        std::ostringstream encoded;
        char current = input[0];
        int count = 1;

        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] == current) {
                count++;
            } else {
                encoded << current << count;
                current = input[i];
                count = 1;
            }
        }

        // Add the last character and count
        encoded << current << count;

        std::string result = encoded.str();

        // Return original if encoded version is not shorter
        return (result.length() < input.length()) ? result : input;
    }

    std::string run_length_decode(const std::string& encoded) {
        std::string decoded;

        for (size_t i = 0; i < encoded.length(); i += 2) {
            if (i + 1 < encoded.length()) {
                char character = encoded[i];
                int count = encoded[i + 1] - '0'; // Convert char digit to int

                // Handle multi-digit counts (if needed)
                if (i + 2 < encoded.length() && std::isdigit(encoded[i + 2])) {
                    count = count * 10 + (encoded[i + 2] - '0');
                    i++; // Skip extra digit
                }

                decoded.append(count, character);
            }
        }

        return decoded;
    }

    std::string remove_duplicates(const std::string& input) {
        if (input.empty()) return "";

        std::string result;
        result += input[0];

        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] != input[i - 1]) {
                result += input[i];
            }
        }

        return result;
    }
};

void problem_3_1() {
    std::cout << "\n=== Problem 3.1: String Compression ===\n";

    StringCompressor compressor;

    std::string test1 = "aaabbbccc";
    std::string test2 = "abcdef";
    std::string test3 = "aabbcc";

    std::cout << "Original: " << test1 << std::endl;
    std::string encoded1 = compressor.run_length_encode(test1);
    std::cout << "Encoded: " << encoded1 << std::endl;
    std::cout << "Decoded: " << compressor.run_length_decode(encoded1) << std::endl;

    std::cout << "\nOriginal: " << test2 << std::endl;
    std::string encoded2 = compressor.run_length_encode(test2);
    std::cout << "Encoded: " << encoded2 << " (not shorter, so kept original)" << std::endl;

    std::cout << "\nDuplicate removal:" << std::endl;
    std::cout << test1 << " -> " << compressor.remove_duplicates(test1) << std::endl;
    std::cout << "abccba -> " << compressor.remove_duplicates("abccba") << std::endl;
}

// Problem 3.2: Advanced Text Search
class FuzzyMatcher {
public:
    int levenshtein_distance(const std::string& s1, const std::string& s2) {
        const size_t len1 = s1.size();
        const size_t len2 = s2.size();

        // Create a 2D vector for dynamic programming
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

        // Initialize base cases
        for (size_t i = 0; i <= len1; ++i) {
            dp[i][0] = i;
        }
        for (size_t j = 0; j <= len2; ++j) {
            dp[0][j] = j;
        }

        // Fill the DP table
        for (size_t i = 1; i <= len1; ++i) {
            for (size_t j = 1; j <= len2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({
                        dp[i - 1][j],     // deletion
                        dp[i][j - 1],     // insertion
                        dp[i - 1][j - 1]  // substitution
                    });
                }
            }
        }

        return dp[len1][len2];
    }

    double similarity_ratio(const std::string& s1, const std::string& s2) {
        int distance = levenshtein_distance(s1, s2);
        size_t max_len = std::max(s1.length(), s2.length());

        if (max_len == 0) return 1.0;

        return 1.0 - (static_cast<double>(distance) / max_len);
    }

    std::vector<std::string> find_similar(const std::string& query,
                                         const std::vector<std::string>& candidates,
                                         double threshold = 0.6) {
        std::vector<std::string> results;

        for (const auto& candidate : candidates) {
            double similarity = similarity_ratio(query, candidate);
            if (similarity >= threshold) {
                results.push_back(candidate);
            }
        }

        return results;
    }

    bool contains_pattern(const std::string& text, const std::string& pattern) {
        // Convert pattern to regex: * becomes .*
        std::string regex_pattern;
        for (char c : pattern) {
            if (c == '*') {
                regex_pattern += ".*";
            } else if (c == '.' || c == '\\' || c == '+' || c == '?' ||
                       c == '[' || c == ']' || c == '(' || c == ')' ||
                       c == '{' || c == '}' || c == '^' || c == '$' || c == '|') {
                // Escape regex special characters
                regex_pattern += '\\';
                regex_pattern += c;
            } else {
                regex_pattern += c;
            }
        }

        std::regex re(regex_pattern);
        return std::regex_search(text, re);
    }
};

void problem_3_2() {
    std::cout << "\n=== Problem 3.2: Advanced Text Search ===\n";

    FuzzyMatcher matcher;

    std::cout << "Edit distance between 'kitten' and 'sitting': "
              << matcher.levenshtein_distance("kitten", "sitting") << std::endl;

    std::cout << "Similarity ratio between 'hello' and 'helo': "
              << matcher.similarity_ratio("hello", "helo") << std::endl;

    std::vector<std::string> words = {"hello", "world", "help", "hero", "hell", "welcome"};
    auto similar = matcher.find_similar("hello", words, 0.6);

    std::cout << "\nWords similar to 'hello' (threshold 0.6):" << std::endl;
    for (const auto& word : similar) {
        std::cout << "  " << word << " (similarity: "
                  << matcher.similarity_ratio("hello", word) << ")" << std::endl;
    }

    // Test pattern matching
    std::cout << "\nPattern matching:" << std::endl;
    std::cout << "he*o matches hello: "
              << (matcher.contains_pattern("hello", "he*o") ? "Yes" : "No") << std::endl;
    std::cout << "he*o matches world: "
              << (matcher.contains_pattern("world", "he*o") ? "Yes" : "No") << std::endl;
    std::cout << "c*t matches cat: "
              << (matcher.contains_pattern("cat", "c*t") ? "Yes" : "No") << std::endl;
}

void run_all() {
    problem_3_1();
    problem_3_2();
}

} // namespace problem_set_3

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "  CHAPTER 15: STRINGS - HOMEWORK HINTS\n";
    std::cout << "========================================\n";

    // Run all problem sets
    std::cout << "\n>>> PROBLEM SET 1: String Fundamentals <<<\n";
    problem_set_1::run_all();

    std::cout << "\n\n>>> PROBLEM SET 2: Text Processing <<<\n";
    problem_set_2::run_all();

    std::cout << "\n\n>>> PROBLEM SET 3: Advanced String Operations <<<\n";
    problem_set_3::run_all();

    std::cout << "\n========================================\n";
    std::cout << "  All problems demonstrated successfully!\n";
    std::cout << "========================================\n";

    return 0;
}

/*
=============================================================================
KEY LEARNING POINTS FOR CHAPTER 15: STRINGS
=============================================================================

1. STRING BASICS:
   - std::string is a dynamic container for character sequences
   - Use + or += for concatenation
   - Access characters with [] or at() (at() provides bounds checking)
   - length() or size() returns the number of characters

2. STRING SEARCHING:
   - find() searches for substring, returns position or std::string::npos
   - find_last_of() searches from the end
   - substr(pos, len) extracts a substring
   - Always check for std::string::npos before using position

3. STRING MANIPULATION:
   - Use std::transform with ::toupper or ::tolower for case conversion
   - Use std::isalpha, std::isdigit, etc. for character classification
   - String streams (std::istringstream) make parsing easier
   - Use std::getline for reading complete lines

4. TEXT PROCESSING:
   - Break complex parsing into smaller functions
   - Use state machines for handling quotes and escapes
   - std::map is great for frequency counting
   - Regular expressions (std::regex) handle complex patterns

5. PERFORMANCE TIPS:
   - Use const std::string& for parameters (avoid copies)
   - Reserve space with reserve() if you know final size
   - Use std::string_view for read-only string parameters (C++17)
   - Avoid repeated concatenation in loops (use ostringstream instead)

6. COMMON PATTERNS:
   - Tokenizing: Use std::istringstream or find() in a loop
   - Validation: Check each character or use regex
   - Transformation: Create new string or modify in-place
   - Comparison: Use == for exact match, custom logic for fuzzy match

7. BEST PRACTICES:
   - Always validate input (check for empty strings, bounds)
   - Handle edge cases (empty strings, single characters)
   - Use meaningful variable names for clarity
   - Consider case-sensitivity in comparisons
   - Document assumptions about input format

8. ADVANCED ALGORITHMS:
   - Levenshtein distance: Dynamic programming for edit distance
   - Run-length encoding: Count consecutive characters
   - Template systems: String replacement with variables
   - Fuzzy matching: Similarity ratios for approximate matches

=============================================================================
*/
