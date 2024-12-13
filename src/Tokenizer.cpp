//
// Created by Sergey Shakhbazyan on 11.12.24.
//

#pragma once
#include "../include/Tokenizer.h"

char Tokenizer::peek() const {
    return input[position];
}

void Tokenizer::advance(size_t cout) {
    position += cout;
}

std::string Tokenizer::parseNumber() {
    size_t start = position;

    while(isdigit(peek()) || peek() == '.' || peek() == '-' || peek() == 'e' || peek() == 'E'){
        advance();
    }

    return input.substr(start, position - start);
}

std::string  Tokenizer::parseString() {
    if (peek() != '"'){
        throw std::runtime_error("Expected opening double quote for string");
    }
    advance();
    size_t start = position;

    if (position >= input.size()){
        throw std::runtime_error("Unterminated string in JSON");
    }

    while (peek() != '"'){
        if (position >= input.size()) {
            throw std::runtime_error("Unterminated string in JSON");
        }
        advance();
    }

    std::string result = input.substr(start, position - start);
    advance();

    return result;
}

bool Tokenizer::startWith(const std::string &str) const {
    if (position + str.size() > input.size()){
        return false;
    }

    if (input.substr(position, str.size()) != str){
        return false;
    }

    size_t nextPosition = position + str.size();

    while (nextPosition < input.size() && isspace(input[nextPosition])){
        ++nextPosition;
    }

    if (nextPosition < input.size()){
        char nextChar = input[nextPosition];

        if (nextChar == ',' || nextChar == '}' || nextChar == ']') {
            return true;
        }
        return false;
    }

    return true;
}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;

    while(position < input.size()){
        char c = peek();

        if (std::isspace(c)){
            advance();
            continue;
        }

        switch (c) {
            case '{':
                tokens.push_back({TokenType::CurlyOpen, "{"});
                advance();
                break;
            case '}':
                tokens.push_back({TokenType::CurlyClose, "}"});
                advance();
                break;
            case '[':
                tokens.push_back({TokenType::SquareOpen, "["});
                advance();
                break;
            case ']':
                tokens.push_back({TokenType::SquareClose, "]"});
                advance();
                break;
            case ':':
                tokens.push_back({TokenType::Colon, ":"});
                advance();
                break;
            case ',':
                tokens.push_back({TokenType::Comma, ","});
                advance();
                break;
            case '"':
                tokens.push_back({TokenType::String, parseString()});
                break;
            default:
                if(isdigit(c) || c == '-'){
                    tokens.push_back({TokenType::Number, parseNumber()});
                }else if(startWith("true")){
                    tokens.push_back({TokenType::True, "true"});
                    advance(4);
                }else if(startWith("false")) {
                    tokens.push_back({TokenType::False, "false"});
                    advance(5);
                }else if(startWith("null")){
                    tokens.push_back({TokenType::Null, "null"});
                    advance(4);
                }else{
                    throw std::runtime_error("Unexpected character in Json at position: " + std::to_string(position));
                }
                break;
        }
    }
    return tokens;
}