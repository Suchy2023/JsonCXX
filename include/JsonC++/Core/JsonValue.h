
#include "Core/JsonValue.Concepts.h"
#include "JsonError.h"
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
    Checkers
     **/
    template <typename T> bool is() const;
    bool isNull() const;
    bool isArray() const;
    bool isObject() const;

    /**
    Accessors
     **/
    template <JsonFundamentalType T> std::expected<std::reference_wrapper<T>, JsonError> as();
    template <JsonFundamentalType T> std::expected<std::reference_wrapper<const T>, JsonError> as() const;
    std::expected<std::reference_wrapper<JsonArray>, JsonError> asArray();
    std::expected<std::reference_wrapper<const JsonArray>, JsonError> asArray() const;
    std::expected<std::reference_wrapper<JsonObject>, JsonError> asObject();
    std::expected<std::reference_wrapper<const JsonObject>, JsonError> asObject() const;
    std::expected<std::reference_wrapper<JsonNull>, JsonError> asNull();
    std::expected<std::reference_wrapper<const JsonNull>, JsonError> asNull() const;

    //object mutators
    template <Stringlike TKey, JsonValuelike TValue>
    std::expected<bool, Core::JsonError> emplace(TKey &&key, TValue &&value);

    std::expected<JsonValue, Core::JsonError> get(const std::string &key) const;

    void remove();

    void update();

    // array methods

    void emplace_back();

    // checks if object has key
    std::expected<bool, Core::JsonError> has(const std::string &key) const;

    template <JsonValuelike T> bool strictlyEquals(T &&json) const;

  private:
    JsonVariant m_data{JsonNull{}};
};
} // namespace Core