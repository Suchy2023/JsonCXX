#pragma once

#include "Core/JsonValue.Types.h"
#include <type_traits>
#include <variant>
#include "JsonValue.h"

namespace Core
{
    template<typename T>
    bool JsonValue::is() const {
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

  bool JsonValue::isNull() const { return std::holds_alternative<JsonNull>(m_data); }

  bool JsonValue::isArray() const { return std::holds_alternative<JsonArray>(m_data); }

  bool JsonValue::isObject() const { return std::holds_alternative<JsonObject>(m_data); }

  //object checkers
   std::expected<bool, Core::JsonError> JsonValue::has(const std::string &key) const
    {
        return asObject()
            .and_then([key](const Core::JsonObject object) {
                return std::expected<bool, Core::JsonError>(object.contains(key));
            })
            .or_else(
                [](const Core::JsonError &err) { return std::expected<bool, Core::JsonError>{std::unexpected(err)}; });
    };

  //array checkers
}