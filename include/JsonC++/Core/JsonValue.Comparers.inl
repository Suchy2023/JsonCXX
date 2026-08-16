
#pragma once

#include "JsonValue.h"

#include "JsonValue.Concepts.h"
#include <type_traits>

namespace Core
{

template <JsonValueLike T> bool JsonValue::strictlyEquals(T &&json) const
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

    if constexpr (std::is_same_v<std::remove_cvref_t<T>, Core::JsonValue>) {
        return this == &other;
    }

    

}
} // namespace Core