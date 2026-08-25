
#pragma once

#include "JsonC++/Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <cstddef>

namespace Tests::Helpers
{
using JsonFundamentalType = ::testing::Types<Core::Json_Null, Core::Json_Int64, Core::Json_Double, Core::Json_String,
                                             Core::Json_Object, Core::Json_Array>;

using JsonComparableTo =
    ::testing::Types<decltype(NULL), Core::Json_Null, Core::Json_Int8, Core::Json_Int16, Core::Json_Int32,
                     Core::Json_Int64, Core::Json_UInt8, Core::Json_UInt16, Core::Json_UInt32, Core::Json_UInt64,
                     Core::Json_Float, Core::Json_Double, Core::Json_String, Core::Json_Object, Core::Json_Array>;

using JsonConstructibleFrom = JsonComparableTo;

} // namespace Tests::Helpers