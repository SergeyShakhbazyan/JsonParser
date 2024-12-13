//
// Created by Sergey Shakhbazyan on 11.12.24.
//

#ifndef JSOMPROJECT_TOKENIZER_H
#define JSOMPROJECT_TOKENIZER_H

#endif //JSOMPROJECT_TOKENIZER_H

#pragma once

#include <string>
#include <vector>

enum class TokenType {
    CurlyOpen,      // '{'
    CurlyClose,     // '}'
    SquareOpen,     // '['
    SquareClose,    // ']'
    Comma,          // ','
    Colon,          // ':'
    String,         // "value"
    Number,
    True,
    False,
    Null
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
private:
    std::string input;
    size_t position;

    char peek() const;
    void advance(size_t cout = 1);
    std::string parseNumber();
    std::string parseString();
    bool startWith(const std::string& str) const;

public:
    explicit Tokenizer(const std::string& json) : input(json), position(0){}

    std::vector<Token> tokenize();

};