#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <string_view>
#include <vector>
#include <regex>
#include <unordered_map>
#include <memory>

class Tokenizer {
private:
    // Define contraction matching structure
    class ContractionMatcher {
    private:
        // Internal trie implementation using pointers to avoid circular references
        struct TrieNode {
            bool is_terminal = false;
            std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        };
        
        std::unique_ptr<TrieNode> root;
        
    public:
        ContractionMatcher();
        size_t match_contraction(std::string_view text) const;
    };
    
    static const ContractionMatcher contractions;

public:
    // Optimized whitespace tokenizer
    static std::vector<std::string> whitespace_tokenizer(std::string_view text);

    // Function to print tokens to an output stream
    void print_tokens(const std::vector<std::string>& tokens, std::ostream& os) const;
};

#endif // TOKENIZER_H