
#include "Core/JsonValue.h"
#include "Core/JsonValue.Types.h"
#include <gtest/gtest.h>
#include <string>
#include <variant>

TEST(JsonValue_Constructors_Test, default_constructor_makes_null)
{
    const auto json = Core::JsonValue{};

    EXPECT_TRUE(json.isNull());
}

TEST(JsonValue_Constructors_Test, constructible_from_null)
{
    const auto json1 = Core::JsonValue{std::monostate{}};

    const auto json2 = Core::JsonValue{NULL};

    EXPECT_TRUE(json1.isNull());

    EXPECT_TRUE(json2.isNull());
}

TEST(JsonValue_Constructors_Test, constructible_from_int)
{
    const auto json = Core::JsonValue{1};

    EXPECT_TRUE(json.is<int>());
}

TEST(JsonValue_Constructors_Test, constructible_from_double)
{
    const auto json = Core::JsonValue{21.3};

    EXPECT_TRUE(json.is<double>());
}

TEST(JsonValue_Constructors_Test, constructible_from_string_like)
{
    const auto json1 = Core::JsonValue{"wujek"};
    const auto json2 = Core::JsonValue{'1'};

    const std::string txt = "1212";

    const auto json3 = Core::JsonValue{txt};

    EXPECT_TRUE(json1.is<std::string>());
    EXPECT_TRUE(json2.is<std::string>());
    EXPECT_TRUE(json3.is<std::string>());
}

TEST(JsonValue_Constructors_Test, constructible_from_JsonObject)
{
    const Core::JsonObject jsonObject = {{"key", 1}};

    const auto json1 = Core::JsonValue{jsonObject};

    EXPECT_TRUE(json1.isObject());
}

TEST(JsonValue_Constructors_Test, constructible_from_JsonArray)
{
    const Core::JsonArray jsonArray = {{"key", 1}};

    const auto json1 = Core::JsonValue{jsonArray};

    EXPECT_TRUE(json1.isArray());
}

