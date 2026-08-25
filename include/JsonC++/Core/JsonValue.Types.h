#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace Core
{

class JsonValue;

using Json_Null = std::monostate;
using Json_Bool = bool;

using Json_String = std::string;

using Json_Int8 = int8_t;
using Json_UInt8 = uint8_t;

using Json_Int16 = int16_t;
using Json_UInt16 = uint16_t;

using Json_Int32 = int32_t;
using Json_UInt32 = uint32_t;

using Json_Int64 = int64_t;
using Json_UInt64 = uint64_t;

using Json_Float = float;
using Json_Double = double;

using Json_Object_KeyValuePair = std::pair<std::string, JsonValue>;

using Json_Object = std::vector<Json_Object_KeyValuePair>;
using Json_Array = std::vector<JsonValue>;

using Value = std::variant<Json_Null, Json_Bool, Json_Int8, Json_UInt8, Json_Int16, Json_UInt16, Json_Int32,
                           Json_UInt32, Json_Int64, Json_UInt64, Json_Float, Json_Double, Json_String,
                           Json_Object, Json_Array>;

} // namespace Core