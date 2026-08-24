
#pragma once

#include "JsonC++/Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <cstddef>
#include <string>
namespace Tests::Helpers
{
using JsonFundamentalType =
    ::testing::Types<Core::Json_Null, Core::Json_Int64, Core::Json_Double,
                     Core::Json_String, Core::Json_Object, Core::Json_Array>;

using JsonConstructibleFrom =
    ::testing::Types<decltype(NULL), Core::Json_Null, int, double, std::string,
                     char, Core::Json_Object, Core::Json_Array>;

using JsonComparableTo = 
    ::testing::Types<Core::Json_Null, Core::Json_Int64, Core::Json_Double, Core::Json_String, Core::Json_Object, Core::Json_Array>;

} // namespace Tests::Helpers