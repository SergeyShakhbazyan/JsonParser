//
// Created by Sergey Shakhbazyan on 12.12.24.
//

#ifndef JSOMPROJECT_JSONVALUE_H
#define JSOMPROJECT_JSONVALUE_H

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

    template<typename Visitor>
    void visit(Visitor &&visitor) const {
        switch (type) {
            case Type::Null:
                visitor("null");
                break;
            case Type::Boolean:
                visitor(std::get<bool>(value) ? "true" : "false");
                break;
            case Type::Number:
                visitor(std::to_string(std::get<double>(value)));
                break;
            case Type::String:
                visitor("\"" + std::get<std::string>(value) + "\"");
                break;
            case Type::Object: {
                visitor("{");
                const auto &obj = std::get<std::map<std::string, JsonValue>>(value);
                for (auto it = obj.begin(); it != obj.end(); ++it) {
                    if (it != obj.begin()) {
                        visitor(", ");
                    }
                    visitor("\"" + it->first + "\": ");
                    it->second.visit(visitor);
                }
                visitor("}");
                break;
            }
            case Type::Array: {
                visitor("[");
                const auto &arr = std::get<std::vector<JsonValue>>(value);
                for (size_t i = 0; i < arr.size(); ++i) {
                    if (i > 0) {
                        visitor(", ");
                    }
                    arr[i].visit(visitor);
                }
                visitor("]");
                break;
            }
        }
    }

};



#endif //JSOMPROJECT_JSONVALUE_H
