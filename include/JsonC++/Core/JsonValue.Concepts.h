#pragma once

#include "Core/JsonValue.Types.h"
#include <string>
#include <type_traits>

namespace Core {

template <typename TKey, typename TValue>
concept TKeyString = requires(TKey key, TValue value) {
  requires std::is_convertible_v<TKey, std::string>;
};

template<typename T>
concept JsonFundamentalType = 
    std::is_same_v<T, JsonNull> ||
    std::is_same_v<T, JsonInt> ||
    std::is_same_v<T, JsonDouble> ||
    std::is_same_v<T, JsonString>;

} // namespace Core