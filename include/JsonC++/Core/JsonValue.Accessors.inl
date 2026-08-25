
#pragma once

#include <algorithm>
#include <expected>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#include <variant>

#include "JsonC++/Core/JsonError.h"
#include "JsonC++/Core/JsonValue.Concepts.h"
#include "JsonC++/Core/JsonValue.Types.h"
#include "JsonC++/Core/JsonValue.h"

namespace Core
{

template <JsonValueType T> std::expected<std::reference_wrapper<T>, Core::JsonError> JsonValue::as()
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

template <JsonValueType T> std::expected<std::reference_wrapper<const T>, Core::JsonError> JsonValue::as() const
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
inline std::expected<std::reference_wrapper<Json_Array>, JsonError> JsonValue::asArray()
{
    return as<Json_Array>();
};

inline std::expected<std::reference_wrapper<const Json_Array>, JsonError> JsonValue::asArray() const
{
    return as<Json_Array>();
};

inline std::expected<std::reference_wrapper<const Json_Object>, JsonError> JsonValue::asObject() const
{
    return as<Json_Object>();
};

inline std::expected<std::reference_wrapper<Json_Object>, JsonError> JsonValue::asObject()
{
    return as<Json_Object>();
};

inline std::expected<std::reference_wrapper<Json_Null>, JsonError> JsonValue::asNull()
{
    return as<std::monostate>();
};

inline std::expected<std::reference_wrapper<const Json_Null>, JsonError> JsonValue::asNull() const
{
    return as<std::monostate>();
};

inline std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> JsonValue::get(const std::string& key)
{
    const auto result = get_(key);

    if (!result.has_value()){
        return std::unexpected(result.error());
    }

    return std::ref(const_cast<JsonValue&>(result.value().get()));
};

inline std::expected<std::reference_wrapper<const JsonValue>, Core::JsonError> JsonValue::get(
    const std::string& key) const
{
    return get_(key);
};

inline std::expected<std::reference_wrapper<const JsonValue>, JsonError> JsonValue::get_(const std::string& key) const
{
    if (!isObject())
    {
        return std::unexpected(JsonError::not_an_object);
    }

    auto AreKeysEqual = [&key](const Json_Object_KeyValuePair& other) -> bool {
        return other.first == key;
    };

    auto& object = std::get<Json_Object>(m_data);

    auto result = std::ranges::find_if(object, AreKeysEqual);

    if (result == object.end())
    {
        return std::unexpected(JsonError::key_not_found);
    }

    return std::cref(result->second);
}

} // namespace Core