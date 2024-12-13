//
// Created by Sergey Shakhbazyan on 13.12.24.
//

#ifndef JSOMPROJECT_PARSER_H
#define JSOMPROJECT_PARSER_H

#pragma once

#include "Tokenizer.h"
#include "JsonValue.h"
#include <vector>

class Parser{
private:
    std::vector<Token> tokens;
    size_t position;

    const Token& peek() const;
    void advance();

    JsonValue parseValue();

    JsonValue parseObject();
    JsonValue parseArray();
    JsonValue parseString();
    JsonValue parseNumber();
    JsonValue parseBoolean();
    JsonValue parseNull();

public:
    explicit Parser(const std::vector<Token>& m_tokens) : tokens(m_tokens), position(0){}
    JsonValue parse();
};

#endif //JSOMPROJECT_PARSER_H
