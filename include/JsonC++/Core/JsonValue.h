#pragma once

#include "JsonError.h"
#include "JsonValue.Concepts.h"
#include "JsonValue.Types.h"
#include <cstddef>
#include <expected>
#include <functional>
#include <string>

namespace Core
{

class JsonValue
{

  public:
    /**
    Ctors
     **/

    template <JsonValueLike T, typename X = disable_if_same_or_derived<JsonValue, T>> JsonValue(T&& value);

    explicit JsonValue() noexcept;

    /**
    Checkers
     **/
    template <JsonValueType T> bool is() const;

    bool isInt8() const;
    bool isUInt8() const;

    bool isInt16() const;
    bool isUInt16() const;

    bool isInt32() const;
    bool isUInt32() const;

    bool isInt64() const;
    bool isUInt64() const;

    bool isFloat() const;
    bool isDouble() const;

    bool isNumber() const;
    bool isIntegral() const;
    bool isFloatingPoint() const;

    bool isBool() const;

    bool isNull() const;
    bool isArray() const;
    bool isObject() const;

    int getType() const;

    /**
    Accessors
     **/
    template <JsonValueType T> std::expected<std::reference_wrapper<T>, JsonError> as();
    template <JsonValueType T> std::expected<std::reference_wrapper<const T>, JsonError> as() const;

    std::expected<std::reference_wrapper<Json_Array>, JsonError> asArray();
    std::expected<std::reference_wrapper<const Json_Array>, JsonError> asArray() const;

    std::expected<std::reference_wrapper<Json_Object>, JsonError> asObject();
    std::expected<std::reference_wrapper<const Json_Object>, JsonError> asObject() const;

    std::expected<std::reference_wrapper<Json_Null>, JsonError> asNull();
    std::expected<std::reference_wrapper<const Json_Null>, JsonError> asNull() const;

    std::expected<std::reference_wrapper<Json_String>, JsonError> asString();
    std::expected<std::reference_wrapper<const Json_String>, JsonError> asString() const;

    std::expected<std::reference_wrapper<Json_String>, JsonError> asBool();
    std::expected<std::reference_wrapper<const Json_String>, JsonError> asBool() const;

    // object specialized
    /**
     * emplaces key:value pair in object
     * if current value isn't object, the object is created
     * discarding previous value
     *@returns reference to emplaced value
     **/
    template <Stringlike TKey, ConvertibleToJson TValue>
    std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> emplace(TKey&& key, TValue&& value);

    std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> get(const std::string& key);
    std::expected<std::reference_wrapper<const JsonValue>, Core::JsonError> get(const std::string& key) const;

    std::expected<bool, Core::JsonError> has(const std::string& key) const;

    // array specialized
    template<Stringlike TKey, ConvertibleToJson TValue>
    std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> emplaceBack(TKey&& key, TValue&& value);

    std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> at(std::size_t index);
    std::expected<std::reference_wrapper<const JsonValue>, Core::JsonError> at(std::size_t index) const;

    // Comparers
    template <JsonValueLike T> bool strictlyEquals(T&& json) const;

    template <JsonValueLike T> bool operator==(T&& other) const;

  private:
    Value m_data{};

    std::expected<std::reference_wrapper<const JsonValue>, JsonError> get_(const std::string& key) const;
};
} // namespace Core
#include "JsonValue.Accessors.inl"
#include "JsonValue.Checkers.inl"
#include "JsonValue.Comparers.inl"
#include "JsonValue.Contructors.inl"
#include "JsonValue.Mutators.inl"
