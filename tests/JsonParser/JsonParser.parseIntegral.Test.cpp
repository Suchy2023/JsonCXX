

#include "JsonC++/JsonParser/JsonParser.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "gtest/gtest.h"
#include <cstdint>
#include <limits>
#include <string>

template <typename T> class JsonParser_ParseIntegral_Test : public ::testing::Test
{
};

using U = ::testing::Types<int8_t, uint8_t, short, unsigned short, int, unsigned int, long, unsigned long, long long,
                           unsigned long long>;

const auto TooBigNumber = std::to_string(std::numeric_limits<unsigned long long>::max()) + "0";
const auto TooSmallNumber = std::to_string(std::numeric_limits<long long>::min()) + "0";

TYPED_TEST_SUITE(JsonParser_ParseIntegral_Test, U);

TYPED_TEST(JsonParser_ParseIntegral_Test, works_for_max)
{
    const auto max = std::numeric_limits<TypeParam>::max();

    const std::string maxString = std::to_string(max);

    auto iterator = maxString.data();
    const auto end = maxString.data() + maxString.size();

    const auto result = JsonParser::JsonParser::parseIntegral<TypeParam>(iterator, end);

    EXPECT_TRUE(result.has_value());

    EXPECT_TRUE(result.value() == max);
}

TYPED_TEST(JsonParser_ParseIntegral_Test, returns_error_for_too_big)
{
    auto iterator = TooBigNumber.data();
    const auto end = TooBigNumber.data() + TooBigNumber.size();

    const auto result = JsonParser::JsonParser::parseIntegral<TypeParam>(iterator, end);

    EXPECT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), JsonParser::JsonParserError::out_of_range);
}

TYPED_TEST(JsonParser_ParseIntegral_Test, works_for_min)
{
    const auto min = std::numeric_limits<TypeParam>::min();

    const std::string minString = std::to_string(min);

    auto iterator = minString.data();
    const auto end = minString.data() + minString.size();

    const auto result = JsonParser::JsonParser::parseIntegral<TypeParam>(iterator, end);

    EXPECT_TRUE(result.has_value());

    EXPECT_TRUE(result.value() == min);
}

TYPED_TEST(JsonParser_ParseIntegral_Test, returns_error_for_too_small)
{
    auto iterator = TooSmallNumber.data();
    const auto end = TooSmallNumber.data() + TooSmallNumber.size();

    const auto result = JsonParser::JsonParser::parseIntegral<TypeParam>(iterator, end);

    EXPECT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), JsonParser::JsonParserError::out_of_range);
}

TEST(JsonParser_ParseIntegral_Test, ignores_trailing_whitespaces)
{
    const std::string value = "             200";

    auto iterator = value.data();

    const auto end = value.data() + value.size();

    const auto result = JsonParser::JsonParser::parseIntegral<int>(iterator, end);

    ASSERT_TRUE(result.has_value());

    EXPECT_TRUE(result.value() == 200);
}

TEST(JsonParser_ParseIntegral_Test, returns_error_if_encounters_dot)
{
    const std::string value = "150.5";

    auto iterator = value.data();

    const auto end = value.data() + value.size();

    const auto result = JsonParser::JsonParser::parseIntegral<int>(iterator, end);

    ASSERT_FALSE(result.has_value());

    EXPECT_TRUE(result.error() == JsonParser::JsonParserError::not_integral);
}

TEST(JsonParser_ParseIntegral_Test, returns_error_if_encounters_whitespace_after_any_digit)
{
    const std::string value = "150 5";

    auto iterator = value.data();

    const auto end = value.data() + value.size();

    const auto result = JsonParser::JsonParser::parseIntegral<int>(iterator, end);

    ASSERT_FALSE(result.has_value());

    EXPECT_TRUE(result.error() == JsonParser::JsonParserError::invalid_format);
}

TEST(JsonParser_ParseIntegral_Test, returns_error_if_trailing_zeros)
{
    const std::string value = "001";

    auto iterator = value.data();

    const auto end = value.data() + value.size();

    const auto result = JsonParser::JsonParser::parseIntegral<int>(iterator, end);

    ASSERT_FALSE(result.has_value());

    EXPECT_TRUE(result.error() == JsonParser::JsonParserError::invalid_format);
}

TEST(JsonParser_ParseIntegral_Test, works_for_zero)
{
    const std::string value = "0";

    auto iterator = value.data();

    const auto end = value.data() + value.size();

    const auto result = JsonParser::JsonParser::parseIntegral<int>(iterator, end);

    ASSERT_TRUE(result.has_value());

    EXPECT_TRUE(result.value() == 0);
}



