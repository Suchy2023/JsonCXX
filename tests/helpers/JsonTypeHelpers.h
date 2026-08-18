
#pragma once

#include "Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <cstddef>
#include <string>
namespace Tests::Helpers
{
using JsonFundamentalType =
    ::testing::Types<Core::JsonNull, Core::JsonInt, Core::JsonDouble,
                     Core::JsonString, Core::JsonObject, Core::JsonArray>;

using JsonConstructibleFrom =
    ::testing::Types<decltype(NULL), Core::JsonNull, int, double, std::string,
                     char, Core::JsonObject, Core::JsonArray>;

using JsonComparableTo = 
    ::testing::Types<Core::JsonNull, Core::JsonInt, Core::JsonDouble, Core::JsonString, Core::JsonObject, Core::JsonArray>;

} // namespace Tests::Helpers