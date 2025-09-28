#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include <map>
#include <optional>

// Basic string operations
void string_basics_demo() {
    std::cout << "=== String Basics Demo ===\n";

    // Create string with name
    std::string name = "Alice";

    // Create greeting by concatenation
    std::string greeting = "Hello, " + name;

    // Add exclamation mark
    greeting += "!";

    // Print length
    std::cout << "Length: " << greeting.length() << std::endl;

    // Print first and last characters
    if (!greeting.empty()) {
        std::cout << "First: " << greeting.front() << std::endl;
        std::cout << "Last: " << greeting.back() << std::endl;
    }

    // Convert to uppercase
    std::string uppercase_greeting = greeting;
    std::transform(uppercase_greeting.begin(), uppercase_greeting.end(),
                   uppercase_greeting.begin(),
                   [](char c) { return std::toupper(c); });
    std::cout << uppercase_greeting << std::endl;
}

// String searching and extraction
std::string extract_domain(const std::string& email) {
    size_t at_pos = email.find('@');
    if (at_pos != std::string::npos && at_pos + 1 < email.length()) {
        return email.substr(at_pos + 1);
    }
    return "";
}

std::string extract_filename(const std::string& path) {
    size_t last_slash = path.find_last_of("/\\");
    if (last_slash != std::string::npos && last_slash + 1 < path.length()) {
        return path.substr(last_slash + 1);
    }
    return path;  // No path separator found, return whole string
}

void string_extraction_demo() {
    std::cout << "\n=== String Extraction Demo ===\n";

    std::string email = "alice.smith@university.edu";
    std::string path = "/home/projects/cpp/main.cpp";

    std::cout << "Domain: " << extract_domain(email) << std::endl;
    std::cout << "Filename: " << extract_filename(path) << std::endl;
}

// String validation functions
bool is_valid_password(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool has_upper = false, has_lower = false, has_digit = false;

    for (char c : password) {
        if (std::isupper(c)) has_upper = true;
        if (std::islower(c)) has_lower = true;
        if (std::isdigit(c)) has_digit = true;
    }

    return has_upper && has_lower && has_digit;
}

bool is_palindrome(const std::string& text) {
    std::string cleaned;

    // Remove spaces and convert to lowercase
    for (char c : text) {
        if (!std::isspace(c)) {
            cleaned += std::tolower(c);
        }
    }

    // Check if palindrome
    size_t left = 0;
    size_t right = cleaned.length();

    while (left < right) {
        --right;
        if (cleaned[left] != cleaned[right]) {
            return false;
        }
        ++left;
    }

    return true;
}

void string_validation_demo() {
    std::cout << "\n=== String Validation Demo ===\n";

    std::cout << "Password1: " << (is_valid_password("Password1") ? "Valid" : "Invalid") << std::endl;
    std::cout << "weak: " << (is_valid_password("weak") ? "Valid" : "Invalid") << std::endl;

    std::cout << "racecar: " << (is_palindrome("racecar") ? "Palindrome" : "Not palindrome") << std::endl;
    std::cout << "hello: " << (is_palindrome("hello") ? "Palindrome" : "Not palindrome") << std::endl;
    std::cout << "A man a plan a canal Panama: " << (is_palindrome("A man a plan a canal Panama") ? "Palindrome" : "Not palindrome") << std::endl;
}

// CSV Parser
class CSVParser {
public:
    std::vector<std::string> parse_line(const std::string& line) {
        std::vector<std::string> fields;
        std::string current_field;
        bool in_quotes = false;
        bool quote_escaped = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            if (quote_escaped) {
                if (c == '"') {
                    current_field += '"';  // Add the escaped quote
                } else {
                    current_field += '"';  // Add the previous quote
                    current_field += c;    // Add current character
                }
                quote_escaped = false;
            } else if (c == '"') {
                if (in_quotes) {
                    // Check if this is an escaped quote
                    if (i + 1 < line.length() && line[i + 1] == '"') {
                        quote_escaped = true;
                    } else {
                        in_quotes = false;
                    }
                } else {
                    in_quotes = true;
                }
            } else if (c == ',' && !in_quotes) {
                fields.push_back(current_field);
                current_field.clear();
            } else {
                current_field += c;
            }
        }

        fields.push_back(current_field);
        return fields;
    }

    void print_parsed(const std::vector<std::string>& fields) {
        for (size_t i = 0; i < fields.size(); ++i) {
            std::cout << "Field " << i << ": '" << fields[i] << "'" << std::endl;
        }
    }
};

void csv_parser_demo() {
    std::cout << "\n=== CSV Parser Demo ===\n";

    CSVParser parser;

    std::string simple = "John,Doe,30,Engineer";
    std::string quoted = "John,\"Doe, Jr.\",30,\"Software Engineer\"";

    std::cout << "Simple CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(simple));

    std::cout << "\nQuoted CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(quoted));
}

// Text Analysis
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
                freq[std::tolower(c)]++;
            }
        }
        return freq;
    }

    std::string most_common_word() {
        std::map<std::string, int> word_freq;
        std::istringstream iss(text);
        std::string word;

        while (iss >> word) {
            // Remove punctuation and convert to lowercase
            std::string clean_word;
            for (char c : word) {
                if (std::isalpha(c)) {
                    clean_word += std::tolower(c);
                }
            }
            if (!clean_word.empty()) {
                word_freq[clean_word]++;
            }
        }

        auto max_it = std::max_element(word_freq.begin(), word_freq.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        return (max_it != word_freq.end()) ? max_it->first : "";
    }

    void print_statistics() {
        std::cout << "Words: " << count_words() << std::endl;
        std::cout << "Sentences: " << count_sentences() << std::endl;
        std::cout << "Most common word: " << most_common_word() << std::endl;

        std::cout << "Character frequencies:" << std::endl;
        auto freq = character_frequency();
        for (const auto& [ch, count] : freq) {
            std::cout << "  " << ch << ": " << count << std::endl;
        }
    }
};

void text_analysis_demo() {
    std::cout << "\n=== Text Analysis Demo ===\n";

    std::string text = "The quick brown fox jumps over the lazy dog. "
                       "The dog was sleeping in the sun. What a beautiful day!";

    TextAnalyzer analyzer(text);
    analyzer.print_statistics();
}

// Simple Template Engine
class TemplateEngine {
private:
    std::map<std::string, std::string> variables;

public:
    void set_variable(const std::string& name, const std::string& value) {
        variables[name] = value;
    }

    std::string render(const std::string& template_text) {
        std::string result = template_text;

        for (const auto& [name, value] : variables) {
            std::string placeholder = "{{" + name + "}}";
            size_t pos = 0;
            while ((pos = result.find(placeholder, pos)) != std::string::npos) {
                result.replace(pos, placeholder.length(), value);
                pos += value.length();
            }
        }

        return result;
    }

    std::string render_with_conditionals(const std::string& template_text) {
        std::string result = template_text;

        // Handle {{#if variable}}...{{/if}}
        size_t pos = 0;
        while ((pos = result.find("{{#if ", pos)) != std::string::npos) {
            size_t var_start = pos + 6;
            size_t var_end = result.find("}}", var_start);
            if (var_end == std::string::npos) break;

            std::string var_name = result.substr(var_start, var_end - var_start);
            size_t content_start = var_end + 2;
            size_t end_tag_pos = result.find("{{/if}}", content_start);
            if (end_tag_pos == std::string::npos) break;

            std::string content = result.substr(content_start, end_tag_pos - content_start);

            // Check if variable exists and is not empty
            bool show_content = false;
            auto it = variables.find(var_name);
            if (it != variables.end() && !it->second.empty()) {
                show_content = true;
            }

            std::string replacement = show_content ? content : "";
            result.replace(pos, end_tag_pos + 7 - pos, replacement);

            if (show_content) {
                pos += replacement.length();
            }
        }

        // Render variables
        return render(result);
    }
};

void template_engine_demo() {
    std::cout << "\n=== Template Engine Demo ===\n";

    TemplateEngine engine;
    engine.set_variable("name", "Alice");
    engine.set_variable("age", "25");
    engine.set_variable("city", "New York");

    std::string basic_template = "Hello {{name}}! You are {{age}} years old and live in {{city}}.";
    std::cout << engine.render(basic_template) << std::endl;

    std::string conditional_template =
        "Welcome {{name}}! "
        "{{#if age}}You are {{age}} years old. {{/if}}"
        "{{#if phone}}Your phone is {{phone}}. {{/if}}";

    std::cout << engine.render_with_conditionals(conditional_template) << std::endl;
}

// String Compression
class StringCompressor {
public:
    std::string run_length_encode(const std::string& input) {
        if (input.empty()) return "";

        std::string result;
        char current_char = input[0];
        int count = 1;

        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] == current_char) {
                count++;
            } else {
                result += current_char + std::to_string(count);
                current_char = input[i];
                count = 1;
            }
        }
        result += current_char + std::to_string(count);

        // Return original if compression doesn't help
        return (result.length() < input.length()) ? result : input;
    }

    std::string run_length_decode(const std::string& encoded) {
        std::string result;

        for (size_t i = 0; i < encoded.length(); i += 2) {
            if (i + 1 < encoded.length()) {
                char ch = encoded[i];
                int count = encoded[i + 1] - '0';  // Simple single-digit parsing
                result += std::string(count, ch);
            }
        }

        return result;
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

void string_compression_demo() {
    std::cout << "\n=== String Compression Demo ===\n";

    StringCompressor compressor;

    std::string test1 = "aaabbbccc";
    std::string test2 = "abcdef";

    std::cout << "Original: " << test1 << std::endl;
    std::string encoded1 = compressor.run_length_encode(test1);
    std::cout << "Encoded: " << encoded1 << std::endl;
    std::cout << "Decoded: " << compressor.run_length_decode(encoded1) << std::endl;

    std::cout << "\nOriginal: " << test2 << std::endl;
    std::string encoded2 = compressor.run_length_encode(test2);
    std::cout << "Encoded: " << encoded2 << std::endl;

    std::cout << "\nDuplicate removal:" << std::endl;
    std::cout << test1 << " -> " << compressor.remove_duplicates(test1) << std::endl;
    std::cout << "abccba -> " << compressor.remove_duplicates("abccba") << std::endl;
}

// Fuzzy String Matching
class FuzzyMatcher {
public:
    int levenshtein_distance(const std::string& s1, const std::string& s2) {
        size_t len1 = s1.length();
        size_t len2 = s2.length();

        // Create matrix for dynamic programming
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

        // Initialize base cases
        for (size_t i = 0; i <= len1; ++i) {
            dp[i][0] = static_cast<int>(i);
        }
        for (size_t j = 0; j <= len2; ++j) {
            dp[0][j] = static_cast<int>(j);
        }

        // Fill the matrix
        for (size_t i = 1; i <= len1; ++i) {
            for (size_t j = 1; j <= len2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i - 1][j],    // deletion
                                             dp[i][j - 1],    // insertion
                                             dp[i - 1][j - 1]}); // substitution
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
        std::vector<std::string> result;

        for (const auto& candidate : candidates) {
            if (similarity_ratio(query, candidate) >= threshold) {
                result.push_back(candidate);
            }
        }

        return result;
    }

    bool contains_pattern(const std::string& text, const std::string& pattern) {
        // Simple wildcard matching with *
        size_t text_idx = 0, pattern_idx = 0;

        while (text_idx < text.length() && pattern_idx < pattern.length()) {
            if (pattern[pattern_idx] == '*') {
                // Skip the * and try to match the rest
                pattern_idx++;
                if (pattern_idx >= pattern.length()) {
                    return true;  // Pattern ends with *, matches everything
                }

                // Find the next character after *
                char next_char = pattern[pattern_idx];
                while (text_idx < text.length() && text[text_idx] != next_char) {
                    text_idx++;
                }
            } else if (text[text_idx] == pattern[pattern_idx]) {
                text_idx++;
                pattern_idx++;
            } else {
                return false;
            }
        }

        return pattern_idx >= pattern.length();
    }
};

void fuzzy_matching_demo() {
    std::cout << "\n=== Fuzzy String Matching Demo ===\n";

    FuzzyMatcher matcher;

    std::cout << "Edit distance between 'kitten' and 'sitting': "
              << matcher.levenshtein_distance("kitten", "sitting") << std::endl;

    std::cout << "Similarity ratio between 'hello' and 'helo': "
              << matcher.similarity_ratio("hello", "helo") << std::endl;

    std::vector<std::string> words = {"hello", "world", "help", "hero", "hell", "welcome"};
    auto similar = matcher.find_similar("hello", words, 0.6);

    std::cout << "Words similar to 'hello':" << std::endl;
    for (const auto& word : similar) {
        std::cout << "  " << word << " (similarity: "
                  << matcher.similarity_ratio("hello", word) << ")" << std::endl;
    }

    std::cout << "\nPattern matching:" << std::endl;
    std::cout << "he*o matches hello: "
              << (matcher.contains_pattern("hello", "he*o") ? "Yes" : "No") << std::endl;
    std::cout << "he*o matches world: "
              << (matcher.contains_pattern("world", "he*o") ? "Yes" : "No") << std::endl;
}

int main() {
    string_basics_demo();
    string_extraction_demo();
    string_validation_demo();
    csv_parser_demo();
    text_analysis_demo();
    template_engine_demo();
    string_compression_demo();
    fuzzy_matching_demo();

    std::cout << "\n=== All string processing demos completed successfully ===\n";

    return 0;
}