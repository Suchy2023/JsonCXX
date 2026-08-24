#pragma once

#include "JsonValue.Concepts.h"
#include "JsonValue.h"
#include <variant>

#include "JsonValue.Types.h"

namespace Core
{
template <JsonValueType T> bool JsonValue::is() const
{
    
}

inline bool JsonValue::isNull() const
{
    return is<Json_Null>();
}

inline bool JsonValue::isArray() const
{
    return is<Json_Array>();
}

inline bool JsonValue::isObject() const
{
    return is<Json_Object>();
}

// object checkers
inline std::expected<bool, Core::JsonError> JsonValue::has(const std::string &key) const
{
    return asObject()
        .and_then(
            [key](const Core::Json_Object object) { return std::expected<bool, Core::JsonError>(object.contains(key)); })
        .or_else([](const Core::JsonError &err) { return std::expected<bool, Core::JsonError>{std::unexpected(err)}; });
};

// array checkers
} // namespace Core