#pragma once

#include "Core/JsonValue.Types.h"
#include <type_traits>

namespace Core
{

class JsonValue;

template <typename T>
concept JsonFundamentalType = std::is_same_v<T, JsonNull> || std::is_same_v<T, JsonInt> ||
                              std::is_same_v<T, JsonDouble> || std::is_same_v<T, JsonString>;

template <typename TKey>
concept Stringlike = std::is_convertible_v<TKey, JsonString>;

template <typename T>
concept IntLike = std::is_convertible_v<T, JsonInt>;

template <typename T>
concept DoubleLike = std::is_convertible_v<T, JsonDouble>;

template <typename TValue>
concept ConvertibleToJson = std::is_convertible_v<std::remove_cvref_t<TValue>, JsonNull> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, JsonInt> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, JsonDouble> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, JsonString> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, JsonObject> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, JsonArray> ||
                            std::is_same_v<std::remove_cvref_t<TValue>, JsonValue>;

template <typename T>
concept JsonValueLike = std::is_same_v<std::remove_cvref_t<T>, JsonValue> || ConvertibleToJson<T>;

/**
*@link https://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
@description disables the templated ctor from being called instead of copy ctor
 **/
template <typename T, typename U>
using disable_if_same_or_derived = std::enable_if_t<!std::is_base_of_v<T, std::remove_reference_t<U>>>;

} // namespace Core