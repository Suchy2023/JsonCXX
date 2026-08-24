#pragma once

#include "JsonError.h"
#include "JsonValue.Concepts.h"
#include "JsonValue.Types.h"
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

    template <JsonValueLike T, typename X = disable_if_same_or_derived<JsonValue, T>> JsonValue(T &&value);

    explicit JsonValue() noexcept;

    /**
    Checkers
     **/
    template <JsonValueType T> bool is() const;
    bool isNull() const;
    bool isArray() const;
    bool isObject() const;

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

    // object mutators

    /**
     * emplaces key:value pair in object
     * if current value isn't object, the object is created
     * discarding previous value
     *@returns reference to emplaced value
     **/
    template <Stringlike TKey, ConvertibleToJson TValue>
    std::expected<std::reference_wrapper<JsonValue>, Core::JsonError> emplace(TKey &&key, TValue &&value);

    std::expected<JsonValue, Core::JsonError> get(const std::string &key) const;

    void remove();

    void update();

    // array methods

    void emplace_back();

    // checks if object has key
    std::expected<bool, Core::JsonError> has(const std::string &key) const;

    // Comparers
    template <JsonValueLike T> bool strictlyEquals(T &&json) const;

    template <JsonValueLike T> bool operator==(T &&other) const;

  private:
    Value m_data{};
};
} // namespace Core
#include "JsonValue.Accessors.inl"
#include "JsonValue.Checkers.inl"
#include "JsonValue.Comparers.inl"
#include "JsonValue.Contructors.inl"
#include "JsonValue.Mutators.inl"
