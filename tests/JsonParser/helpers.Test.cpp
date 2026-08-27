

#include "helpers.h"
#include "gtest/gtest.h"

namespace Tests
{

TEST(JsonParser_Helpers_Test, is_digit)
{
    EXPECT_TRUE(JsonParser::Helpers::isDigit("1"));

    EXPECT_FALSE(JsonParser::Helpers::isDigit("h"));
}

TEST(JsonParser_Helpers_Test, is_colon)
{
    EXPECT_TRUE(JsonParser::Helpers::isColon(":"));

    EXPECT_FALSE(JsonParser::Helpers::isColon("p"));
}

TEST(JsonParser_Helpers_Test, is_double_quote)
{
    const auto val = R"(")";

    EXPECT_TRUE(JsonParser::Helpers::isDoubleQuote(val));

    EXPECT_FALSE(JsonParser::Helpers::isDoubleQuote("p"));
}

TEST(JsonParser_Helpers_Test, is_open_curly_bracket)
{
    const auto val = R"({)";

    EXPECT_TRUE(JsonParser::Helpers::isOpenCurlyBracket(val));

    EXPECT_FALSE(JsonParser::Helpers::isOpenCurlyBracket("p"));
}

TEST(JsonParser_Helpers_Test, is_closed_curly_bracket)
{
    const auto val = R"(})";

    EXPECT_TRUE(JsonParser::Helpers::isClosedCurlyBracket(val));

    EXPECT_FALSE(JsonParser::Helpers::isClosedCurlyBracket("p"));
}

TEST(JsonParser_Helpers_Test, is_open_sq_bracket)
{
    const auto val = R"([)";

    EXPECT_TRUE(JsonParser::Helpers::isOpenSqBracket(val));

    EXPECT_FALSE(JsonParser::Helpers::isOpenSqBracket("p"));
}

TEST(JsonParser_Helpers_Test, is_closed_sq_bracket)
{
    const auto val = R"(])";

    EXPECT_TRUE(JsonParser::Helpers::isClosedSqBracket(val));

    EXPECT_FALSE(JsonParser::Helpers::isClosedSqBracket("p"));
}

TEST(JsonParser_Helpers_Test, is_dot)
{
    const auto val = R"(.)";

    EXPECT_TRUE(JsonParser::Helpers::isDot(val));

    EXPECT_FALSE(JsonParser::Helpers::isDot("p"));
}

TEST(JsonParser_Helpers_Test, is_whitespace)
{
    const auto val = R"( )";

    EXPECT_TRUE(JsonParser::Helpers::isWhitespace(val));

    EXPECT_FALSE(JsonParser::Helpers::isWhitespace("p"));
}

TEST(HelpersTest, IsJsonNumberValidCharacter)
{

}

TEST(HelpersTest, IsJsonNumberInvalidCharacter)
{

}

} // namespace Tests