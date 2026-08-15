
#include "Core/JsonValue.Concepts.h"
#include "Core/JsonValue.Types.h"
#include "JsonValue.h"
#include <expected>

namespace Core
{
template <JsonValuelike T> bool JsonValue::strictlyEquals(T &&json) const
{
    if (json.template is<int>() && this->is<int>())
    {
        return json.template as<int>().value() == this->as<int>().value();
    }
};
} // namespace Core