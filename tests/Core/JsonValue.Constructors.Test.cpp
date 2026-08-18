
#include "Core/JsonValue.h"
#include "helpers/JsonTypeHelpers.h"
#include "gtest/gtest.h"
#include <string>
#include <type_traits>

namespace Tests
{

template <typename T> class JsonValue_Constructors_Test : public ::testing::Test
{
};

TYPED_TEST_SUITE(JsonValue_Constructors_Test, Helpers::JsonConstructibleFrom);

TYPED_TEST(JsonValue_Constructors_Test, is_nothrow_constructible_from)
{
    EXPECT_TRUE((std::is_nothrow_constructible_v<Core::JsonValue, TypeParam>));
}

TEST(JsonValue_Constructors_Test, is_nothrow_constructible)
{
    EXPECT_TRUE(std::is_nothrow_default_constructible_v<Core::JsonValue>);

    EXPECT_TRUE((std::is_nothrow_copy_constructible_v<Core::JsonValue>));

    EXPECT_TRUE((std::is_nothrow_move_constructible_v<Core::JsonValue>));

    EXPECT_TRUE((std::is_copy_assignable_v<Core::JsonValue>));

    EXPECT_TRUE((std::is_move_assignable_v<Core::JsonValue>));
}

} // namespace Tests
