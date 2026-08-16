
#pragma once

#include "JsonValue.h"

#include <expected>
#include <functional>

#include "Core/JsonValue.Checkers.inl"
#include "Core/JsonValue.Concepts.h"
namespace Core
{

template <JsonFundamentalType T> std::expected<std::reference_wrapper<T>, JsonError> JsonValue::as()
{
    if constexpr (is<T>())
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
    if constexpr (is<T>())
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
    if (isArray())
    {
        return std::ref(std::get<JsonArray>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

inline std::expected<std::reference_wrapper<const JsonArray>, JsonError> JsonValue::asArray() const
{
    if (isArray())
    {
        return std::cref(std::get<JsonArray>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

inline std::expected<std::reference_wrapper<const JsonObject>, JsonError> JsonValue::asObject() const
{
    if (isObject())
    {
        return std::cref(std::get<JsonObject>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

inline std::expected<std::reference_wrapper<JsonObject>, JsonError> JsonValue::asObject()
{
    if (isObject())
    {
        return std::ref(std::get<JsonObject>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

inline std::expected<std::reference_wrapper<JsonNull>, JsonError> JsonValue::asNull()
{
    if (isNull())
    {
        return std::ref(std::get<JsonNull>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
};

inline std::expected<std::reference_wrapper<const JsonNull>, JsonError> JsonValue::asNull() const
{
    if (isNull())
    {
        return std::cref(std::get<JsonNull>(m_data));
    }
    else
    {
        return std::unexpected(Core::JsonError::invalid_type);
    }
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