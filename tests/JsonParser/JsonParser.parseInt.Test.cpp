

#include "JsonC++/JsonParser/JsonParser.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>
#include <string_view>

class JsonParser_parseInt_Test : public ::testing::TestWithParam<std::string>
{
};

TEST_P(JsonParser_parseInt_Test, parses_small_ints_properlt)
{
    const std::string_view sv = GetParam();

    auto iterator = sv.begin();
    auto end = sv.end();

    const auto result = JsonParser::JsonParser::parseInt(iterator, end);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), std::stoi(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(nah, JsonParser_parseInt_Test,
                         ::testing::Values("0", "     0", "0       1" "1", "10", "100", "500", "1000", "2000", "5000", "2137", "1000000000", "  1",
                                           "       124", "                 900000"));