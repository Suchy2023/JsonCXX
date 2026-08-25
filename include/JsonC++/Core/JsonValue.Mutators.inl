#pragma once

#include "JsonError.h"
#include "JsonValue.Types.h"
#include "JsonValue.h"
#include <expected>
#include <functional>
#include <utility>

namespace Core
{

template <Stringlike TKey, ConvertibleToJson TValue>
std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> JsonValue::emplace(TKey&& key, TValue&& value)
{
    if (!isObject())
    {
        m_data = Json_Object{};
    }

    auto& object = std::get<Json_Object>(m_data);

    auto& emplaced = object.emplace_back(Json_Object_KeyValuePair{std::forward<TKey>(key), std::forward<TValue>(value)});    
    
    return emplaced.second;
}

template <Stringlike TKey, ConvertibleToJson TValue>
std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> JsonValue::emplaceBack(TKey&& key, TValue&& value)
{
}

} // namespace Core  