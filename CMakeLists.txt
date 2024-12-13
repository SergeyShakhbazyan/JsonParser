cmake_minimum_required(VERSION 3.26)
project(jsomProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(jsomProject main.cpp
        include/Tokenizer.h
        src/Tokenizer.cpp
        include/JsonValue.h
        src/JsonValue.cpp
        include/Parser.h
        src/Parser.cpp
)
