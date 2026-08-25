#pragma once

#include "JsonC++/Core/JsonError.h"
#include "JsonValue.Concepts.h"
#include "JsonValue.h"

#include "JsonValue.Types.h"
#include <algorithm>
#include <expected>
#include <functional>
#include <memory>
#include <type_traits>
#include <variant>

namespace Core
{
template <JsonValueType T> bool JsonValue::is() const
{
    return std::holds_alternative<std::remove_cvref_t<T>>(m_data);
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
inline std::expected<bool, Core::JsonError> JsonValue::has(const std::string& key) const
{
    static std::function isSameKey = [&key](const Json_Object_KeyValuePair& other) { return other.first == key; };

    const auto& asObjectResult = asObject();

    if (!asObjectResult.has_value())
    {
        return std::unexpected(asObjectResult.error());
    }

    const auto& object = asObjectResult.value().get();

    return std::any_of(object.begin(), object.end(), isSameKey);
};

// array checkers
} // namespace Core