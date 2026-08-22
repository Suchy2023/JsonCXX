#pragma once

#include "JsonValue.h"
#include "JsonValue.Types.h"
#include "JsonValue.Types.h"
#include "JsonError.h"
#include <expected>
#include <functional>

namespace Core
{
// object mutators
template <Stringlike TKey, ConvertibleToJson TValue>
std::expected<std::reference_wrapper<JsonValue>, Core::JsonError>
JsonValue::emplace(TKey &&key, TValue &&value)
{
  if (!isObject())
  {
    m_data = JsonObject{};
  }

  JsonObject obj;
  const auto x = obj.emplace("k", "");

  const auto y = x.first;

  const auto z = y->second;

  return asObject().and_then(
      [key = std::forward<TKey>(key),
       value = std::forward<TValue>(value)](JsonObject &object)
          -> std::expected<std::reference_wrapper<JsonValue>, JsonError>
      {
        const auto resultPair = object.emplace(std::move(key), std::move(value));

        if (!resultPair.second)
        {
            return std::unexpected(JsonError::could_not_emplace);
        }

        return resultPair.first->second;
      });
};

// array muttators

} // namespace Core