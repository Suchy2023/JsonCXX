
#include "JsonC++/JsonParser/JsonParser.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>
#include <string_view>

// maybe implement it like this
// iterate over till the end of number
// count numbers to know what size allocate
// check for dots to allocate double or float
// count precision digits
// and use std::stoi std::stof std::stod
// std::from_chars ??

class DoubleValuesTest : public ::testing::TestWithParam<std::string>
{
};

TEST_P(DoubleValuesTest, parses_properly)
{
    const std::string_view value = GetParam();

    const char* iterator = value.begin();

    const char* end = value.end();

    const auto result = JsonParser::JsonParser::parseNumber(iterator, end);

    EXPECT_TRUE(result.is<double>());

    EXPECT_TRUE(result.as<double>() == std::stod(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Json, DoubleValuesTest, testing::Values<std::string>("42", "42.5"));