

#include "Core/JsonValue.h"
#include "Core/JsonError.h"
#include "Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

TEST(JsonValue_Accessors_Test, as_returns_requested_type)
{
    const auto json = Core::JsonValue{};

    const auto result = json.as<Core::JsonNull>();

    EXPECT_TRUE(result.has_value());
};

TEST(JsonValue_Accessors_Test, as_returns_invalid_type_error)
{
    const auto json = Core::JsonValue{1};

    const auto result = json.as<std::string>();

    EXPECT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), Core::JsonError::invalid_type);
};

TEST(JsonValue_Accessors_Test, as_respects_const)
{
    const auto constJson = Core::JsonValue{1};

    const auto constResult = constJson.as<int>();

    EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(constResult.value().get())>>);
};

TEST(JsonValue_Accessors_Test, as_respects_non_const)
{
    auto nonConstJson = Core::JsonValue{"string"};

    const auto nonConstResult = nonConstJson.as<std::string>();

    EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(nonConstResult.value().get())>>);
};

TEST(JsonValue_Accessors_Test, as_helpers_work)
{
    auto const json = Core::JsonValue{Core::JsonObject{}};

    const auto result = json.asObject();

    EXPECT_TRUE(result.has_value());
};



