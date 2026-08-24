

#include "JsonC++/Core/JsonValue.h"
#include "JsonC++/Core/JsonValue.Types.h"
#include "JsonTypeHelpers.h"
#include "gtest/gtest.h"
#include <expected>
#include <functional>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

namespace Tests
{

template <typename T> class JsonValue_Accessors_Test : public ::testing::Test
{
};

TYPED_TEST_SUITE(JsonValue_Accessors_Test, Helpers::JsonFundamentalType);

TYPED_TEST(JsonValue_Accessors_Test, as_works_for_proper_type)
{
    Core::JsonValue json = TypeParam{};

    const auto result = json.as<TypeParam>();

    EXPECT_TRUE(result.has_value());
}

TYPED_TEST(JsonValue_Accessors_Test, as_returns_non_const_ref_for_non_const_variable)
{
    Core::JsonValue json = TypeParam{};

    const auto result = json.as<TypeParam>();
 
    EXPECT_TRUE(result.has_value());

    using ResultType = std::remove_reference_t<decltype(result.value().get())>;

    EXPECT_FALSE(std::is_const_v<ResultType>);
}

TYPED_TEST(JsonValue_Accessors_Test, as_returns_const_ref_for_const_variable)
{
    const Core::JsonValue json = TypeParam{};

    const auto result = json.as<TypeParam>();

    EXPECT_TRUE(result.has_value());

    using ResultType = std::remove_reference_t<decltype(result.value().get())>;

    EXPECT_TRUE(std::is_const_v<ResultType>);
}

TEST(JsonValue_Accessors_Test, as_array_respects_const)
{
    const auto constJson = Core::JsonValue{Core::Json_Array{}};
    auto json = Core::JsonValue{Core::Json_Array{}};

    const auto constValue = constJson.asArray();
    const auto value = json.asArray();

    EXPECT_TRUE(constValue.has_value());
    EXPECT_TRUE(value.has_value());

    using ConstJsonResult = std::remove_reference_t<decltype(constValue.value().get())>;
    using JsonResult = std::remove_reference_t<decltype(value.value().get())>;

    EXPECT_TRUE(std::is_const_v<ConstJsonResult>);
    EXPECT_FALSE(std::is_const_v<JsonResult>);
}

TEST(JsonValue_Accessors_Test, as_object_respects_const)
{
    const auto constJson = Core::JsonValue{Core::Json_Object{}};
    auto json = Core::JsonValue{Core::Json_Object{}};

    const auto constValue = constJson.asObject();
    const auto value = json.asObject();

    EXPECT_TRUE(constValue.has_value());
    EXPECT_TRUE(value.has_value());

    using ConstJsonResult = std::remove_reference_t<decltype(constValue.value().get())>;
    using JsonResult = std::remove_reference_t<decltype(value.value().get())>;

    EXPECT_TRUE(std::is_const_v<ConstJsonResult>);
    EXPECT_FALSE(std::is_const_v<JsonResult>);
}

TEST(JsonValue_Accessors_Test, as_null_respects_const)
{
    const auto constJson = Core::JsonValue{Core::Json_Null{}};
    auto json = Core::JsonValue{Core::Json_Null{}};

    const auto constValue = constJson.asNull();
    const auto value = json.asNull();

    EXPECT_TRUE(constValue.has_value());
    EXPECT_TRUE(value.has_value());

    using ConstJsonResult = std::remove_reference_t<decltype(constValue.value().get())>;
    using JsonResult = std::remove_reference_t<decltype(value.value().get())>;

    EXPECT_TRUE(std::is_const_v<ConstJsonResult>);
    EXPECT_FALSE(std::is_const_v<JsonResult>);
};

TEST(JsonValue_Accessors_Test, results_in_error_on_non_object)
{    
    const auto json = Core::JsonValue{Core::Json_Null{}};

    const auto result = json.get("key");

    EXPECT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), Core::JsonError::invalid_type);
};

TEST(JsonValue_Accessors_Test, results_in_error_if_no_key_found)
{    
    const auto json = Core::JsonValue{Core::Json_Object{}};

    const auto result = json.get("key");

    EXPECT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), Core::JsonError::key_not_found);
};


} // namespace Tests