

#include "JsonC++/JsonParser/JsonParser.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "NumericHelpers.h"
#include "gtest/gtest.h"
#include <charconv>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace Tests
{

template <typename T> class ParseNumberMaxValueTest : public ::testing::Test
{
};

using U = testing::Types<int64_t, u_int64_t, double>;

TYPED_TEST_SUITE(ParseNumberMaxValueTest, U);

TYPED_TEST(ParseNumberMaxValueTest, returns_value_T_for_max_T)
{
    auto helper = Helpers::NumericHelper<TypeParam>{};

    const auto result = JsonParser::JsonParser::parseNumber(helper.max_string_iterator, helper.max_string_end);

    ASSERT_TRUE(result.has_value());

    ASSERT_TRUE(std::holds_alternative<TypeParam>(result.value()));

    const auto value = std::get<TypeParam>(result.value());

    using ResultType = std::remove_cvref_t<decltype(value)>;

    ASSERT_TRUE((std::is_same_v<ResultType, TypeParam>));

    EXPECT_TRUE(value == helper.max);
};

// ####################################

template <typename T> class ParseNumberIntegralRangeTest : public ::testing::Test
{
};

using W = testing::Types<int8_t, u_int8_t, int16_t, u_int16_t, int32_t, u_int32_t, int64_t, u_int64_t>;

TYPED_TEST_SUITE(ParseNumberIntegralRangeTest, W);

TYPED_TEST(ParseNumberIntegralRangeTest, returns_int64_for_min_T)
{
    using T = TypeParam;

    auto helper = Helpers::NumericHelper<T>{};

    const auto result = JsonParser::JsonParser::parseNumber(helper.min_string_iterator, helper.min_string_end);

    ASSERT_TRUE(result.has_value());

    ASSERT_NO_THROW(std::get<int64_t>(result.value()));

    const auto value = std::get<int64_t>(result.value());

    using ResultType = std::remove_cvref_t<decltype(value)>;

    ASSERT_TRUE((std::is_same_v<ResultType, int64_t>));

    EXPECT_TRUE(std::cmp_equal(value, helper.min));
}

class OverflowTest : public ::testing::TestWithParam<std::string>
{
};

TEST_P(OverflowTest, returns_double_for_overflow)
{
    const std::string param = GetParam();

    auto iterator = param.data();

    auto iteratorCopy = iterator;

    auto end = param.data() + param.size();

    const auto result = JsonParser::JsonParser::parseNumber(iterator, end);

    ASSERT_TRUE(result.has_value());

    ASSERT_TRUE(std::holds_alternative<double>(result.value()));

    const auto value = std::get<double>(result.value());

    double x{};

    std::from_chars(iteratorCopy, end, x);

    EXPECT_EQ(value, x);
}

const auto uintHelper = Helpers::NumericHelper<uint64_t>{};
const auto intHelper = Helpers::NumericHelper<int64_t>{};

INSTANTIATE_TEST_SUITE_P(ParseNumber, OverflowTest,
                         ::testing::Values<std::string>(uintHelper.max_string_overflowed,
                                                        intHelper.min_string_overflowed));

// ###################

class InvalidFormatTest : public ::testing::TestWithParam<std::string>
{
};

TEST_P(InvalidFormatTest, ReturnsInvalidFormatError)
{
    const std::string param = GetParam();

    auto iterator = param.data();
    auto end = param.data() + param.size();

    const auto result = JsonParser::JsonParser::parseNumber(iterator, end);

    ASSERT_FALSE(result.has_value());

    EXPECT_EQ(result.error(), JsonParser::JsonParserError::invalid_format);
}

INSTANTIATE_TEST_SUITE_P(ParseNumber, InvalidFormatTest,
                         ::testing::Values<std::string>("01", "-01", "+1", "1.", ".1", "1e", "1e+", "1,5", "NaN",
                                                        "Infinity", "-Infinity", "0x1A", "010", "1_000", "-.1", "+.1",
                                                        "__1__", "0b1", "0o", "0invalid", "invalid0", "-invalid0",
                                                        "-1invalid", "-", "1.1.1", "1e1.5", "1e+-5", "1ee5", "--1",
                                                        " 1", ".1-"));

class ValidFormaIntegralTest : public ::testing::TestWithParam<int64_t>
{
};

TEST_P(ValidFormaIntegralTest, ReturnsValidIntegralValue)
{
    const std::string stringified = std::to_string(GetParam());

    auto iterator = stringified.data();
    auto end = stringified.data() + stringified.size();

    const auto parsed = JsonParser::JsonParser::parseNumber(iterator, end);

    ASSERT_TRUE(parsed.has_value());

    ASSERT_TRUE(std::holds_alternative<int64_t>(parsed.value()));

    const auto value = std::get<int64_t>(parsed.value());

    EXPECT_TRUE(value == GetParam());
}

INSTANTIATE_TEST_SUITE_P(ParseNumber, ValidFormaIntegralTest, ::testing::Values<int64_t>(-900900, 0, 900900));

class ValidFormatDoubleTest : public ::testing::TestWithParam<double>
{
};

TEST_P(ValidFormatDoubleTest, ReturnsValidIntegralValue)
{
    char buf[64];

    auto [ptr, errc] = std::to_chars(buf, buf + sizeof(buf), GetParam());

    const std::string stringified{buf, ptr};

    auto iterator = stringified.data();
    auto end = stringified.data() + stringified.size();

    const auto parsed = JsonParser::JsonParser::parseNumber(iterator, end);

    ASSERT_TRUE(parsed.has_value());

    ASSERT_TRUE(std::holds_alternative<double>(parsed.value()));

    const auto value = std::get<double>(parsed.value());

    EXPECT_TRUE(value == GetParam());
}

INSTANTIATE_TEST_SUITE_P(ParseNumber, ValidFormatDoubleTest,
                         ::testing::Values<double>(-900900.0500, 0.0990901000101, 900900.55, -1.5e150, 127.92e14));

} // namespace Tests