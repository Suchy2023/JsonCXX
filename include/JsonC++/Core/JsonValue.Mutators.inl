

#include "Core/JsonValue.Concepts.h"
#include "Core/JsonValue.Types.h"
#include "JsonError.h"
#include "JsonValue.h"
#include <expected>

namespace Core
{
// object mutators
template <Stringlike TKey, JsonValuelike TValue>
std::expected<bool, Core::JsonError> JsonValue::emplace(TKey &&key, TValue &&value)
{
    if (!isObject())
    {
        m_data = JsonObject{};
    }

    return asObject().and_then(
        [key = std::forward<TKey>(key), value = std::forward<TValue>(value)](std::reference_wrapper<JsonObject> ref) {
            ref.get().emplace(std::move(key), std::move(value));

            return std::expected<bool, JsonError>{true};
        });
};

// array muttators


} // namespace Core