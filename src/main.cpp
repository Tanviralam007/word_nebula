#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include "../include/Tokenizer.h"

// Simple benchmark function
void benchmark_tokenizer(const std::string& text, int iterations = 1000) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        auto tokens = Tokenizer::whitespace_tokenizer(text);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    
    std::cout << "Tokenized " << iterations << " times in " 
              << elapsed.count() << " ms" << std::endl;
    std::cout << "Average: " << (elapsed.count() / iterations) << " ms per tokenization" << std::endl;
}

int main(int argc, char **argv) {
    // Input file path - read from input.txt by default
    std::string input_path = "G:/C++ Projects/Token/word_nebula/input.txt";
    std::string text;
    
    // Allow command-line override of input file
    if (argc > 1) {
        input_path = argv[1];
    }
    
    // Try to read from the input file
    std::ifstream input_file(input_path);
    if (input_file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(input_file)), 
                           std::istreambuf_iterator<char>());
        text = content;
        input_file.close();
        std::cout << "Read input from: " << std::filesystem::absolute(input_path).string() << std::endl;
    } else {
        std::cerr << "Warning: Could not open input file at " << std::filesystem::absolute(input_path).string() << std::endl;
        // Fallback to a minimal test text if input file can't be read
        text = "Tokenizer test. If you see this, input.txt couldn't be found or read!";
    }
    
    // Create tokenizer and process text
    Tokenizer tokenizer;
    auto tokens = Tokenizer::whitespace_tokenizer(text);
    
    // Output file path
    std::string output_path = "G:/C++ Projects/Token/word_nebula/output.txt";

    // Write tokens to output file
    std::ofstream output_file(output_path);
    if (output_file.is_open()) {
        output_file << "Tokenization result:" << std::endl;
        tokenizer.print_tokens(tokens, output_file);
        output_file.close();
        std::cout << "Tokenization results written to: " << std::filesystem::absolute(output_path).string() << std::endl;
    } else {
        std::cerr << "Error: Could not create output file at " << std::filesystem::absolute(output_path).string() << std::endl;
        // Fall back to console output if file creation failed
        std::cout << "Tokenization result:" << std::endl;
        tokenizer.print_tokens(tokens, std::cout);
    }
    
    // Run benchmark if text isn't too large
    if (text.length() < 10000) {
        std::cout << "\nRunning benchmark..." << std::endl;
        benchmark_tokenizer(text);
    }
    
    return 0;
}