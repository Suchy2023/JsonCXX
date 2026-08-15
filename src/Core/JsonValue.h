
#include "JsonError.h"
#include <expected>
#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace Core {

template <typename T>
concept SupportedJsonType =
    std::disjunction_v<std::is_same<T, std::monostate>, std::is_same<T, int>,
                       std::is_same<T, double>, std::is_same<T, std::string>>;

template <typename TKey, typename TValue>
concept TKeyString = requires(TKey key, TValue value) {
  requires std::is_convertible_v<TKey, std::string>;
};

class JsonValue {

  typedef std::monostate JsonNull;
  typedef int JsonInt;
  typedef double JsonDouble;
  typedef std::string JsonString;

  typedef std::vector<JsonValue> JsonArray;
  typedef std::map<std::string, JsonValue, std::less<>> JsonObject;

  typedef std::variant<JsonNull, JsonInt, JsonDouble, JsonArray, JsonObject,
                       JsonString>
      JsonVariant;

public:
  template <typename T> bool is() const {
    if constexpr (std::is_same_v<T, JsonNull>) {
      return std::holds_alternative<JsonNull>(m_data);
    } else if constexpr (std::is_same_v<T, JsonInt>) {
      return std::holds_alternative<JsonInt>(m_data);
    } else if constexpr (std::is_same_v<T, JsonDouble>) {
      return std::holds_alternative<JsonDouble>(m_data);
    } else if constexpr (std::is_same_v<T, JsonString>) {
      return std::holds_alternative<JsonString>(m_data);
    } else {
      static_assert(!std::is_same_v<T, T>, "Unsupported type");
    }
  }

  bool isArray() const { return std::holds_alternative<JsonArray>(m_data); }

  bool isObject() const { return std::holds_alternative<JsonObject>(m_data); }

  bool isNull() const { return std::holds_alternative<JsonNull>(m_data); }

  template <SupportedJsonType T>
  std::expected<std::reference_wrapper<T>, Core::JsonError> as() {

    if constexpr (is<T>()) {
      return std::ref(std::get<T>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  template <SupportedJsonType T>
  std::expected<std::reference_wrapper<const T>, Core::JsonError> as() const {
    if constexpr (is<T>()) {
      return std::cref(std::get<T>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  }

  // returns non-const lvalue ref
  std::expected<std::reference_wrapper<JsonArray>, JsonError> asArray() {
    if (isArray()) {
      return std::ref(std::get<JsonArray>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  // returns const lvalue ref
  std::expected<std::reference_wrapper<const JsonArray>, JsonError>
  asArray() const {
    if (isArray()) {
      return std::cref(std::get<JsonArray>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  std::expected<std::reference_wrapper<const JsonObject>, JsonError>
  asObject() const {
    if (isObject()) {
      return std::cref(std::get<JsonObject>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  std::expected<std::reference_wrapper<JsonObject>, JsonError> asObject() {
    if (isObject()) {
      return std::ref(std::get<JsonObject>(m_data));
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  const std::expected<JsonNull, JsonError> asNull() const {
    if (isNull()) {
      return std::get<JsonNull>(m_data);
    } else {
      return std::unexpected(Core::JsonError::invalid_type);
    }
  };

  JsonValue() {}

  template <typename TKey, typename TValue>
    requires TKeyString<TKey, TValue>
  std::expected<bool, Core::JsonError> emplace(TKey &&key, TValue &&value) {

    if (!isObject())
    {
      m_data = JsonObject{};
    }

    return asObject().and_then(
        [key = std::forward<TKey>(key), value = std::forward<TValue>(value)](
            std::reference_wrapper<JsonObject> ref) {
          ref.get().emplace(std::move(key), std::move(value));

          return std::expected<bool, Core::JsonError>{true};
        });
  };

  std::expected<JsonValue, Core::JsonError> 
  get(const std::string &key) const {
    return asObject().and_then([]() {



    });
  };

  void remove();

  void update();

  // array methods

  void emplace_back();

  // checks if object has key
  std::expected<bool, Core::JsonError> has(const std::string &key) const {
    return asObject()
        .and_then([key](const Core::JsonValue::JsonObject object) {
          return std::expected<bool, Core::JsonError>(object.contains(key));
        })
        .or_else([](const Core::JsonError &err) {
          return std::expected<bool, Core::JsonError>{std::unexpected(err)};
        });
  };

  template <typename T> bool strictlyEquals(T &&json) const {
    if (!std::is_same_v<std::remove_cvref_t<T>, Core::JsonValue>) {
      return false;
    }
  };

private:
   JsonVariant m_data{JsonNull{}};
};
} // namespace Core