#include "../include/Tokenizer.h"
#include <sstream>
#include <cctype>
#include <iostream>
#include <unordered_set>
#include <fstream>

const std::unordered_set<std::string> contractions = {
    "n't", "'ll", "'ve", "'re", "'d", "'m", "'s", "'t", "-"
};

std::vector<std::string> Tokenizer::whitespace_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    tokens.reserve(text.size() / 5);

    size_t start = 0, length = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        char current_char = text[i];

        if (std::isspace(current_char)) {
            if (length > 0) {
                tokens.emplace_back(text.substr(start, length));
                length = 0;
            }
        } 
        else if (std::ispunct(current_char)) {
            if (current_char == '\'' && i + 1 < text.size()) {
                std::string suffix = text.substr(i);

                for (const auto& contraction : contractions) {
                    if (suffix.substr(0, contraction.size()) == contraction) {
                        length += contraction.length();
                        i += contraction.length() - 1;
                        break;
                    }
                }
            } 
            else {
                if (length > 0) {
                    tokens.emplace_back(text.substr(start, length));
                    length = 0;
                }
                tokens.emplace_back(std::string(1, current_char));
            }
        } 
        else {
            if (length == 0) start = i;
            length++;
        }
    }

    if (length > 0) {
        tokens.emplace_back(text.substr(start, length));
    }

    return tokens;
}

std::vector<std::string> Tokenizer::word_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    std::string token;

    for(char ch : text){
        if(std::isalpha(ch)){
            token += ch;
        }else{
            if(!token.empty()){
                tokens.push_back(token);
                token.clear();
            }
            if(!std::isspace(ch)){
                tokens.push_back(std::string(1, ch));
            }
        }
    }

    if(!token.empty()){
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::string> Tokenizer::char_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;

    for(char ch : text){
        tokens.push_back(std::string(1, ch));
    }
    return tokens;
}

std::vector<std::string> Tokenizer::subword_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    
    // breaking words into halves
    for(size_t i = 0; i < text.length(); i += 2){
        std::string subword = text.substr(i, 2);
        tokens.push_back(subword);
    }
    return tokens;
}

std::vector<std::string> Tokenizer::sentence_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    std::string sentence;

    for(char ch : text){
        if(ch == '.' || ch == '!' || ch == '?'){
            tokens.push_back(sentence);
            sentence.clear();
        }else{
            sentence += ch;
        }
    }

    if(!sentence.empty()){
        tokens.push_back(sentence);
    }
    return tokens;
}

std::vector<std::string> Tokenizer::regex_tokenizer(const std::string& text, const std::string& pattern) {
    std::vector<std::string> tokens;
    std::regex regex(pattern);
    std::sregex_token_iterator iter(text.begin(), text.end(), regex, -1);
    std::sregex_token_iterator end;

    while(iter != end){
        tokens.push_back(*iter);
        ++iter;
    }

    return tokens;
}

void Tokenizer::print_tokens(const std::vector<std::string>& tokens, std::ostream& out) const {
    for (const auto& token : tokens) {
        out << "[" << token << "] ";
    }
    out << std::endl;  
}

