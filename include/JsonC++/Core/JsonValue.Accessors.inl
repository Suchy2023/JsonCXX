
#pragma once

#include "Core/JsonValue.Types.h"
#include "JsonValue.h"

#include <expected>
#include <functional>
#include <variant>

#include "Core/JsonValue.Checkers.inl"
#include "Core/JsonValue.Concepts.h"
namespace Core
{

template <JsonFundamentalType T> std::expected<std::reference_wrapper<T>, Core::JsonError> JsonValue::as()
{
    if (is<T>())
    {
        return std::ref(std::get<T>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

template <JsonFundamentalType T> std::expected<std::reference_wrapper<const T>, Core::JsonError> JsonValue::as() const
{
    if (is<T>())
    {
        return std::cref(std::get<T>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
}

inline std::expected<std::reference_wrapper<JsonArray>, JsonError> JsonValue::asArray()
{
    return as<JsonArray>();
};

inline std::expected<std::reference_wrapper<const JsonArray>, JsonError> JsonValue::asArray() const
{
    return as<JsonArray>();
};

inline std::expected<std::reference_wrapper<const JsonObject>, JsonError> JsonValue::asObject() const
{
    return as<JsonObject>();
};

inline std::expected<std::reference_wrapper<JsonObject>, JsonError> JsonValue::asObject()
{
    return as<JsonObject>();
};

inline std::expected<std::reference_wrapper<JsonNull>, JsonError> JsonValue::asNull()
{
    return as<std::monostate>();
};

inline std::expected<std::reference_wrapper<const JsonNull>, JsonError> JsonValue::asNull() const
{
    return as<std::monostate>();
};

inline std::expected<JsonValue, Core::JsonError> JsonValue::get(const std::string &key) const
{
    return asObject().and_then([&](const JsonObject &json) -> std::expected<JsonValue, JsonError> {
        if (has(key))
        {
            return json.at(key);
        }
        else
        {
            return std::unexpected(Core::JsonError::key_not_found);
        }
    });
};

} // namespace Core