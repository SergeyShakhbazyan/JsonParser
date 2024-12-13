#include <iostream>
#include "include/Parser.h"


int main() {

    std::string jsonInput = R"({
        "name": "John",
        "age": 30,
        "isStudent": false,
        "skills": ["C++", "Python", "JavaScript"],
        "address": {
            "city": "New York",
            "zip": "10001"
        }
    })";

    try {
        Tokenizer tokenizer(jsonInput);
        auto tokens = tokenizer.tokenize();

        Parser parser(tokens);
        JsonValue jsonRoot = parser.parse();

        const auto& rootObject = jsonRoot.asObject();

        for (const auto& [key, value] : rootObject) {
            std::cout << key << ": ";
            value.visit([](const std::string& output) { std::cout << output; });
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
