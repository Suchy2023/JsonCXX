

#include "Core/JsonValue.h"
#include "Core/JsonValue.Types.h"
#include "gtest/gtest.h"

TEST(JsonValue_Comparers_Test, compares_to_itself)
{
    const auto json = Core::JsonValue{};

    EXPECT_TRUE(json == json);

    EXPECT_FALSE(json == 1);
}

TEST(JsonValue_Comparers_Test, compares_to_int)
{
    const int value = 1;

    const auto json = Core::JsonValue{value};

    EXPECT_TRUE(json == value);

    EXPECT_FALSE(json == "string");
}

TEST(JsonValue_Comparers_Test, compares_to_double)
{
    const double value = 20.2;

    const auto json = Core::JsonValue{value};

    EXPECT_TRUE(json == value);

    EXPECT_FALSE(json == 1);
}

TEST(JsonValue_Comparers_Test, compares_to_string)
{
    const std::string value = "text";

    const auto json = Core::JsonValue{value};

    EXPECT_TRUE(json == value);

    EXPECT_FALSE(json == 1);
}

TEST(JsonValue_Comparers_Test, compares_to_JsonObject)
{
    const Core::JsonObject value = {{"key", "value"}};

    const auto json = Core::JsonValue{value};

    EXPECT_TRUE(json == value);

    EXPECT_FALSE(json == "string");
}

TEST(JsonValue_Comparers_Test, compares_to_JsonArray)
{
    const Core::JsonArray value = {{"item1", "item2", "item3"}};

    const auto json = Core::JsonValue{value};

    EXPECT_TRUE(json == value);

    EXPECT_FALSE(json == 1);
}