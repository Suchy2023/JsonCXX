#pragma once

#include "JsonValue.Concepts.h"
#include "JsonValue.Types.h"
#include "JsonValue.h"
#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace Core
{

inline JsonValue::JsonValue() noexcept
{
}

template <JsonValueLike T, typename X> JsonValue::JsonValue(T&& value)
{
    m_data = std::forward<T>(value);
};

} // namespace Core