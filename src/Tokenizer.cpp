#include "../include/Tokenizer.h"
#include <sstream>
#include <cctype>
#include <iostream>
#include <array>

// Initialize the static contraction matcher
const Tokenizer::ContractionMatcher Tokenizer::contractions;

// Implementation of ContractionMatcher constructor
Tokenizer::ContractionMatcher::ContractionMatcher() {
    // Initialize root node
    root = std::make_unique<TrieNode>();
    
    // Common English contractions
    const std::array<std::string_view, 9> contraction_list = {
        "n't", "'ll", "'ve", "'re", "'d", "'m", "'s", "'t", "-"
    };
    
    // Build trie
    for (const auto& contraction : contraction_list) {
        TrieNode* current = root.get();
        for (char c : contraction) {
            if (!current->children[c]) {
                current->children[c] = std::make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        current->is_terminal = true;
    }
}

// Returns the length of the matched contraction, or 0 if no match
size_t Tokenizer::ContractionMatcher::match_contraction(std::string_view text) const {
    const TrieNode* current = root.get();
    size_t match_length = 0;
    
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        auto it = current->children.find(c);
        if (it == current->children.end()) {
            break;
        }
        
        current = it->second.get();
        if (current->is_terminal) {
            match_length = i + 1;
        }
    }
    
    return match_length;
}

std::vector<std::string> Tokenizer::whitespace_tokenizer(std::string_view text) {
    std::vector<std::string> tokens;
    // More accurate reservation based on average English word length (5 chars) + spaces
    tokens.reserve(text.length() / 6);
    
    // State machine states
    enum class State { WHITESPACE, WORD, PUNCTUATION };
    State state = State::WHITESPACE;
    
    size_t token_start = 0;
    
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        
        // Determine character type
        bool is_space = std::isspace(c);
        bool is_punct = std::ispunct(c);
        
        switch (state) {
            case State::WHITESPACE:
                if (!is_space) {
                    token_start = i;
                    state = is_punct ? State::PUNCTUATION : State::WORD;
                }
                break;
                
            case State::WORD:
                if (is_space) {
                    // End of word
                    tokens.emplace_back(text.substr(token_start, i - token_start));
                    state = State::WHITESPACE;
                }
                else if (is_punct) {
                    // Handle apostrophes for contractions
                    if (c == '\'') {
                        // Check if this is the start of a contraction
                        size_t contraction_length = contractions.match_contraction(text.substr(i));
                        if (contraction_length > 0) {
                            i += contraction_length - 1;
                            continue;
                        }
                    }
                    
                    // End word and start punctuation
                    tokens.emplace_back(text.substr(token_start, i - token_start));
                    token_start = i;
                    state = State::PUNCTUATION;
                }
                break;
                
            case State::PUNCTUATION:
                if (is_space) {
                    // End of punctuation
                    tokens.emplace_back(text.substr(token_start, i - token_start));
                    state = State::WHITESPACE;
                }
                else if (!is_punct) {
                    // End punctuation and start word
                    tokens.emplace_back(text.substr(token_start, i - token_start));
                    token_start = i;
                    state = State::WORD;
                }
                else if (c != text[token_start]) {
                    // New punctuation character
                    tokens.emplace_back(text.substr(token_start, i - token_start));
                    token_start = i;
                }
                break;
        }
    }
    
    // Handle remaining token
    if (state != State::WHITESPACE) {
        tokens.emplace_back(text.substr(token_start));
    }
    
    return tokens;
}

void Tokenizer::print_tokens(const std::vector<std::string>& tokens, std::ostream& out) const {
    for (const auto& token : tokens) {
        out << "[" << token << "] ";
    }
    out << std::endl;
}