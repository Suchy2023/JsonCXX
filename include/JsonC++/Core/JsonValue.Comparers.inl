
#pragma once

#include "JsonValue.Types.h"
#include "JsonValue.h"

#include "JsonValue.Concepts.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <variant>

namespace Core
{

template <JsonValueLike T> bool JsonValue::strictlyEquals(T&& json) const
{
    if constexpr (std::is_same_v<std::remove_cvref_t<T>, JsonValue>)
    {
        return m_data == json.m_data;
    }
    else
    {
    }
};

template <JsonValueLike T> bool JsonValue::operator==(T&& other) const
{
    if constexpr (std::is_same_v<std::remove_cvref_t<T>, JsonValue>)
    {
        return m_data == other.m_data;
    }
    else
    {
        if (const auto value = std::get_if<std::remove_cvref_t<T>>(&m_data))
        {
            return *value == other;
        }
        else
        {
            return false;
        }
    }
}
} // namespace Core