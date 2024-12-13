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

        std::cout << "Name: " << rootObject.at("name").asString() << std::endl;
        std::cout << "Age: " << rootObject.at("age").asNumber() << std::endl;
        std::cout << "Is Student: " << (rootObject.at("isStudent").asBoolean() ? "true" : "false") << std::endl;

        const auto& address = rootObject.at("address").asObject();
        std::cout << "City: " << address.at("city").asString() << std::endl;
        std::cout << "ZIP: " << address.at("zip").asString() << std::endl;

        const auto& skills = rootObject.at("skills").asArray();
        std::cout << "Skills: ";
        for (const auto& skill : skills) {
            std::cout << skill.asString() << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
