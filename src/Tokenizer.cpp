#include "../include/Tokenizer.h"
#include <sstream>
#include <iostream>

std::vector<std::string> Tokenizer::whitespace_tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        tokens.push_back(word);
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

std::vector<std::string> Tokenizer::print_tokens(const std::vector<std::string>& tokens) {
    for(const std::string& token : tokens){
        std::cout << token << " | ";
    }
    std::cout << std::endl;
    return tokens;
}

