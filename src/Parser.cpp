//
// Created by Sergey Shakhbazyan on 13.12.24.
//

#include "../include/Parser.h"
#include <map>
#include <stdexcept>
#include <vector>
#include <string>

const Token &Parser::peek() const {
    if (position >= tokens.size()) {
        throw std::runtime_error("Unexpected end of tokens");
    }
    return tokens[position];
}

void Parser::advance() {
    if (position < tokens.size()) {
        ++position;
    } else {
        throw std::runtime_error("Cannot advance beyond the end of tokens");
    }
}

JsonValue Parser::parse() {
    return parseValue();
}

JsonValue Parser::parseValue() {
    const Token &token = peek();

    switch (token.type) {
        case TokenType::CurlyOpen:
            return parseObject();
        case TokenType::SquareOpen:
            return parseArray();
        case TokenType::String:
            return parseString();
        case TokenType::Number:
            return parseNumber();
        case TokenType::True:
        case TokenType::False:
            return parseBoolean();
        case TokenType::Null:
            return parseNull();
        default:
            throw std::runtime_error("Unexpected token: " + token.value);
    }
}

JsonValue Parser::parseObject() {
    std::map<std::string, JsonValue> obj;

    // Ensure we start with '{'
    if (peek().type != TokenType::CurlyOpen) {
        throw std::runtime_error("Expected '{' to start object");
    }
    advance();

    while (peek().type != TokenType::CurlyClose) {
        if (peek().type != TokenType::String) {
            throw std::runtime_error("Expected string key in object");
        }

        std::string key = peek().value;
        advance();

        if (peek().type != TokenType::Colon) {
            throw std::runtime_error("Expected ':' after key in object");
        }
        advance();

        obj[key] = parseValue();

        if (peek().type == TokenType::Comma) {
            advance();
        } else if (peek().type != TokenType::CurlyClose) {
            throw std::runtime_error("Expected ',' or '}' in object");
        }
    }

    // Consume '}'
    advance();
    return JsonValue(obj);
}

JsonValue Parser::parseArray() {
    std::vector<JsonValue> arr;

    // Ensure we start with '['
    if (peek().type != TokenType::SquareOpen) {
        throw std::runtime_error("Expected '[' to start array");
    }
    advance();

    while (peek().type != TokenType::SquareClose) {
        arr.push_back(parseValue());

        if (peek().type == TokenType::Comma) {
            advance();
        } else if (peek().type != TokenType::SquareClose) {
            throw std::runtime_error("Expected ',' or ']' in array");
        }
    }

    // Consume ']'
    advance();
    return JsonValue(arr);
}

JsonValue Parser::parseString() {
    const Token &token = peek();
    if (token.type != TokenType::String) {
        throw std::runtime_error("Expected string token");
    }
    advance();
    return JsonValue(token.value);
}

JsonValue Parser::parseNumber() {
    const Token &token = peek();
    if (token.type != TokenType::Number) {
        throw std::runtime_error("Expected number token");
    }
    advance();
    try {
        return JsonValue(std::stod(token.value));
    } catch (const std::exception &e) {
        throw std::runtime_error("Invalid number format: " + token.value);
    }
}

JsonValue Parser::parseBoolean() {
    const Token &token = peek();
    if (token.type == TokenType::True) {
        advance();
        return JsonValue(true);
    } else if (token.type == TokenType::False) {
        advance();
        return JsonValue(false);
    }
    throw std::runtime_error("Expected boolean token");
}

JsonValue Parser::parseNull() {
    const Token &token = peek();
    if (token.type != TokenType::Null) {
        throw std::runtime_error("Expected null token");
    }
    advance();
    return JsonValue();
}
