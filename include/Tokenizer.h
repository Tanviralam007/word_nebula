#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <regex>

class Tokenizer{
    public:
        static std::vector<std::string> whitespace_tokenizer(const std::string& text);
        static std::vector<std::string> word_tokenizer(const std::string& text);
        static std::vector<std::string> char_tokenizer(const std::string& text);
        static std::vector<std::string> subword_tokenizer(const std::string& text);
        static std::vector<std::string> sentence_tokenizer(const std::string& text);
        static std::vector<std::string> regex_tokenizer(const std::string& text, const std::string& pattern);

        // function to print tokens to an output stream
        void print_tokens(const std::vector<std::string>& tokens, std::ostream& os) const;
};


#endif // TOKENIZER_H