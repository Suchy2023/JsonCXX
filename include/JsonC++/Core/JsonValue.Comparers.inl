
#pragma once

#include "Core/JsonValue.Types.h"
#include "JsonValue.h"

#include "JsonValue.Concepts.h"
#include <type_traits>
#include <variant>

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

template <JsonValueLike T> bool JsonValue::operator==(T &&other) const
{
    using U = std::remove_cvref_t<T>;

    if constexpr (std::is_same_v<U, Core::JsonValue>)
    {
        return m_data == other.m_data;
    }
    else
    {
        return std::visit([&](const auto& held) -> bool {
            if constexpr (std::is_same_v<std::remove_cvref_t<decltype(held)>, U>)
            {
                return held == other;
            }
            else
            {
                return false;
            }
        }, m_data);
    };

    return false;
}
} // namespace Core