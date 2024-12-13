//
// Created by Sergey Shakhbazyan on 12.12.24.
//

#include "../include/JsonValue.h"
#include <sstream>
#include <stdexcept>

JsonValue::JsonValue() : type(Type::Null), value(nullptr){}

JsonValue::JsonValue(const bool& b) : type(Type::Boolean), value(b){}

JsonValue::JsonValue(const double& n) : type(Type::Number), value(n) {}

JsonValue::JsonValue(const std::string &str) : type(Type::String), value(str){}

JsonValue::JsonValue(const std::map<std::string, JsonValue> &obj) : type(Type::Object), value(obj){}

JsonValue::JsonValue(const std::vector<JsonValue> &arr) : type(Type::Array), value(arr){}

JsonValue::Type JsonValue::getType() const {
    return type;
}

bool JsonValue::isNull() const {
    return type == Type::Null;
}

bool JsonValue::isBoolean() const {
    return type == Type::Boolean;
}

bool JsonValue::isNumber() const {
    return type == Type::Number;
}

bool JsonValue::isString() const {
    return type == Type::String;
}

bool JsonValue::isObject() const {
    return type == Type::Object;
}

bool JsonValue::isArray() const {
    return type == Type::Array;
}

const bool &JsonValue::asBoolean() const {
    if (type != Type::Boolean){
        throw std::runtime_error("Value is not a boolean");
    }
    return std::get<bool>(value);
}

const double &JsonValue::asNumber() const {
    if (type != Type::Number){
        throw std::runtime_error("Value is not a number");
    }
    return std::get<double>(value);
}

const std::string JsonValue::asString() const {
    if (type != Type::String){
        throw std::runtime_error("Value is not a string");
    }
    return std::get<std::string>(value);
}

const std::map<std::string, JsonValue> &JsonValue::asObject() const {
    if (type != Type::Object){
        throw std::runtime_error("Value is not a object");
    }
    return std::get<std::map<std::string, JsonValue>>(value);
}

const std::vector<JsonValue> &JsonValue::asArray() const {
    if (type != Type::Array){
        throw std::runtime_error("Value is not a array");
    }
    return std::get<std::vector<JsonValue>>(value);
}






