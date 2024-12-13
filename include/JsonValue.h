//
// Created by Sergey Shakhbazyan on 12.12.24.
//

#ifndef JSOMPROJECT_JSONVALUE_H
#define JSOMPROJECT_JSONVALUE_H

#pragma once

#include <variant>
#include <map>

class JsonValue{
public:
    enum class Type{
        Null,
        Boolean,
        Number,
        String,
        Object,
        Array,
    };

private:
    Type type;
    std::variant<std::nullptr_t, bool, double, std::string, std::map<std::string, JsonValue>, std::vector<JsonValue>> value;

public:
    JsonValue();
    JsonValue(const bool& b);
    JsonValue(const double& d);
    JsonValue(const std::string& str);
    JsonValue(const std::map<std::string, JsonValue>& obj);
    JsonValue(const std::vector<JsonValue>& arr);

    Type getType() const;

    bool isNull() const;
    bool isBoolean() const;
    bool isNumber() const;
    bool isString() const;
    bool isObject() const;
    bool isArray() const;

    const bool& asBoolean() const;
    const double& asNumber() const;
    const std::string asString() const;
    const std::map<std::string, JsonValue>& asObject() const;
    const std::vector<JsonValue>& asArray() const;
};



#endif //JSOMPROJECT_JSONVALUE_H
