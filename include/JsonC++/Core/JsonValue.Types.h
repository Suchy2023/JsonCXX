#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Core {

    class JsonValue;

typedef std::monostate JsonNull;
typedef int JsonInt;
typedef double JsonDouble;
typedef std::string JsonString;

typedef std::vector<JsonValue> JsonArray;
typedef std::map<std::string, JsonValue, std::less<>> JsonObject;

typedef std::variant<JsonNull, JsonInt, JsonDouble, JsonArray, JsonObject,
                     JsonString>
    JsonVariant;
} // namespace Core