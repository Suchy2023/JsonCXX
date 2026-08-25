#pragma once

#include "JsonValue.Types.h"
#include <type_traits>

namespace Core
{

template <typename T>
concept JsonValueType =
    std::is_same_v<T, Json_Null> || 
    std::is_same_v<T, Json_Int8> || std::is_same_v<T, Json_Int16> ||
    std::is_same_v<T, Json_Int32> || std::is_same_v<T, Json_Int64> ||
    std::is_same_v<T, Json_UInt8> || std::is_same_v<T, Json_UInt16> ||
    std::is_same_v<T, Json_UInt32> || std::is_same_v<T, Json_UInt64> 
    || std::is_same_v<T, Json_Double> ||
     std::is_same_v<T, Json_Float> ||
    std::is_same_v<T, Json_String> || std::is_same_v<T, Json_Object> || std::is_same_v<T, Json_Array>;

template <typename TKey>
concept Stringlike = std::is_convertible_v<TKey, Json_String>;

template <typename T>
concept IntLike = std::is_convertible_v<T, Json_Int8>;

template <typename TValue>
concept ConvertibleToJson = std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Null> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Int8> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Int16> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Int32> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Int64> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_UInt8> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_UInt16> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_UInt32> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_UInt64> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Float> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Double> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_String> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Object> ||
                            std::is_convertible_v<std::remove_cvref_t<TValue>, Json_Array>;
template <typename T>
concept JsonValueLike = 
std::is_same_v<std::remove_cvref_t<T>, Value> ||
std::is_same_v<std::remove_cvref_t<T>, JsonValue> ||
                        ConvertibleToJson<T>;

/**
*@link https://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
@description disables the templated ctor from being called instead of copy ctor
 **/
template <typename T, typename U>
using disable_if_same_or_derived = std::enable_if_t<!std::is_base_of_v<T, std::remove_reference_t<U>>>;

} // namespace Core