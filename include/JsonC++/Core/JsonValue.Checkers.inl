#pragma once

#include "Core/JsonValue.Concepts.h"
#include "JsonValue.h"
#include <variant>

#include "Core/JsonValue.Types.h"

namespace Core
{
template <JsonFundamentalType T> bool JsonValue::is() const
{
    return std::holds_alternative<T>(m_data);
}

inline bool JsonValue::isNull() const
{
    return is<JsonNull>();
}

inline bool JsonValue::isArray() const
{
    return is<JsonArray>();
}

inline bool JsonValue::isObject() const
{
    return is<JsonObject>();
}

// object checkers
inline std::expected<bool, Core::JsonError> JsonValue::has(const std::string &key) const
{
    return asObject()
        .and_then(
            [key](const Core::JsonObject object) { return std::expected<bool, Core::JsonError>(object.contains(key)); })
        .or_else([](const Core::JsonError &err) { return std::expected<bool, Core::JsonError>{std::unexpected(err)}; });
};

// array checkers
} // namespace Core