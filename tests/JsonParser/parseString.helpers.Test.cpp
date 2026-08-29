

#include "parseString.helpers.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace Tests
{
struct ParseStringTestHelper
{
    JsonParser::Helpers::EscapedCharacters escapedChar{};
    std::vector<std::string> validValues{};
    std::vector<std::string> invalidValues{};
};

class ParseStringHelpersTest : public ::testing::TestWithParam<ParseStringTestHelper>
{
};

TEST_P(ParseStringHelpersTest, WorksProperly)
{
    const ParseStringTestHelper helper = GetParam();

    const std::vector<std::string>& validValues = helper.validValues;
    const std::vector<std::string>& invalidValues = helper.invalidValues;
    const JsonParser::Helpers::EscapedCharacters& escapedChar = helper.escapedChar;

    for (auto valid : validValues)
    {
        const auto iterator = valid.data();
        const auto end = valid.data() + valid.size();

        EXPECT_TRUE(JsonParser::Helpers::isEscaped(escapedChar, iterator, end));
    }

    for (auto invalid : invalidValues)
    {
        const auto iterator = invalid.data();
        const auto end = invalid.data() + invalid.size();

        EXPECT_FALSE(JsonParser::Helpers::isEscaped(escapedChar, iterator, end));
    }
}

const auto TestParams = ::testing::Values<ParseStringTestHelper>(
    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::quotation_mark,
                          .validValues = {"\\\""},
                          .invalidValues = {"\\'"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::back_slash,
                          .validValues = {"\\\\"},
                          .invalidValues = {"//", "\\\""}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::forward_slash,
                          .validValues = {"\\/"},
                          .invalidValues = {"\\\\"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::backspace,
                          .validValues = {"\\b"},
                          .invalidValues = {"\\a"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::form_feed,
                          .validValues = {"\\f"},
                          .invalidValues = {"\\n", "\\e"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::line_feed,
                          .validValues = {"\\n"},
                          .invalidValues = {"\\f", "\\e"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::carriage_return,
                          .validValues = {"\\r"},
                          .invalidValues = {"\\f", "\\e"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::tab,
                          .validValues = {"\\t"},
                          .invalidValues = {"\\f", "\\e"}},

    ParseStringTestHelper{.escapedChar = JsonParser::Helpers::EscapedCharacters::hex,
                          .validValues = {"\\u0000", "\\u0041", "\\uFFFF", "\\uabcd", "\\uABCD", "\\uAbCd", "\\uD800",
                                          "\\uDBFF", "\\uDC00", "\\uDFFF", "\\u007F", "\\u0080", "\\u00FF", "\\u1234"},
                          .invalidValues = {"\\u", "\\u1", "\\u12", "\\u123", "\\u12G4", "\\u12$4", "\\u12 4",
                                            "\\u12\\t4", "\\u12g4", "\\U0041", "\\u12"}}
    );

INSTANTIATE_TEST_SUITE_P(PREFIX, ParseStringHelpersTest, TestParams);
} // namespace Tests