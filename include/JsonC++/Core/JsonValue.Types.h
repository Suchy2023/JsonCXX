#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Core
{

union Value {
};

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

using Json_Object = std::map<std::string, Value>;
using Json_Array = std::vector<Value>;

} // namespace Core