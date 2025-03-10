cmake_minimum_required(VERSION 3.10)
project(WordNebula)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/source/)

add_executable(word_nebula
    src/main.cpp
    src/Tokenizer.cpp
)