

#include "JsonC++/Core/JsonValue.h"
#include "JsonTypeHelpers.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>

template <typename T> class ComparersTest : public ::testing::Test
{
};

TYPED_TEST_SUITE(ComparersTest, Tests::Helpers::JsonComparableTo);

TYPED_TEST(ComparersTest, is_comparable_to_constructible_types)
{
    const auto value = TypeParam{};

    const auto json = Core::JsonValue{value};

    EXPECT_EQ(json, value);
}

TYPED_TEST(ComparersTest, comparision_to_itself_is_truthy)
{
    const auto json = Core::JsonValue{TypeParam{}};

    EXPECT_EQ(json, json);

}