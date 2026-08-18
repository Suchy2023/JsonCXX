#pragma once

#include "Core/JsonValue.Concepts.h"
#include "Core/JsonValue.Types.h"
#include "JsonValue.h"
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace Core
{

inline JsonValue::JsonValue() noexcept
{
}

//check order:
    //bool
    //char
    //intergral??

template <JsonValueLike T, typename X> JsonValue::JsonValue(T &&value)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<T>, decltype(NULL)>)
    {
        m_data = std::monostate{};
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, JsonNull>)
    {
        m_data = std::monostate{};
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, bool>)
    {
        m_data = true;
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, int>)
    {
        m_data = std::forward<T>(value);
    }
    else if constexpr (std::is_floating_point_v<std::remove_cvref_t<T>>)
    {
        m_data = std::forward<T>(value);
    }
    else if constexpr (std::is_convertible_v<std::remove_cvref_t<T>, std::string>) // string like??
    {
        m_data = std::forward<T>(value);
    }
    else if constexpr (std::is_convertible_v<std::remove_cvref_t<T>, char>)
    {
        m_data = std::string{std::forward<T>(value)};
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, JsonObject>)
    {
        m_data = std::forward<T>(value);
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<T>, JsonArray>)
    {
        m_data = std::forward<T>(value);
    }
    else
    {
        static_assert(!std::is_same_v<T, T>);
    }
};

} // namespace Core