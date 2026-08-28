

#include "char.helpers.h"
#include "gtest/gtest.h"
#include <string>

namespace Tests
{

struct CharTestHelper
{
    std::string name;
    std::function<bool(JsonParser::Helpers::ConstIteratorRef iterator)> function;
    std::vector<char> validValues{};
    std::vector<char> invalidValues{};
};

class JsonParserCharHelpersTest : public ::testing::TestWithParam<CharTestHelper>
{
};

TEST_P(JsonParserCharHelpersTest, ReturnsTrueForValidCharacter)
{
    const auto param = GetParam();

    const auto& function = param.function;
    const auto& validValues = param.validValues;
    const auto& invalidValues = param.invalidValues;

    for (auto valid : validValues)
    {
        EXPECT_TRUE(function(&valid));
    }

    for (auto invalid : invalidValues)
    {
        EXPECT_FALSE(function(&invalid));
    }
}

CharTestHelper CharTestHelperFactory(std::string name,
                                     std::function<bool(JsonParser::Helpers::ConstIteratorRef iterator)> function,
                                     std::vector<char> validValues, bool addPaddingToEveryValid = true,
                                     bool addUpperLowerToEveryValid = true)
{
    std::vector<char> invalidValues{};

    for (auto valid : validValues)
    {
        if (addPaddingToEveryValid)
        {
            invalidValues.push_back(valid + 1);
            invalidValues.push_back(valid - 1);
        }
        if (addUpperLowerToEveryValid)
        {
            invalidValues.push_back(valid + 32);
            invalidValues.push_back(valid - 32);
        }
    }

    return {.name = name, .function = function, .validValues = validValues, .invalidValues = invalidValues};
}

const auto TestParameters = ::testing::Values<CharTestHelper>(
    CharTestHelperFactory("IsBackSlash", JsonParser::Helpers::isBackSlash, {'\\'}),
    CharTestHelperFactory("IsforwardSlash", JsonParser::Helpers::isForwardSlash, {'/'}),
    CharTestHelperFactory("IsBackspaceEscapeChar", JsonParser::Helpers::isBackspaceEscapeChar, {'b'}),
    CharTestHelperFactory("IsFormFeedEscapeChar", JsonParser::Helpers::isFormFeedEscapeChar, {'f'}),
    CharTestHelperFactory("IsLineFeedEscapeChar", JsonParser::Helpers::isLineFeedEscapeChar, {'n'}),
    CharTestHelperFactory("IsCarriageReturnEscapeChar", JsonParser::Helpers::isCarriageReturnEscapeChar, {'r'}),
    CharTestHelperFactory("IsHorizontalTabEscapeChar", JsonParser::Helpers::isHorizontalTabEscapeChar, {'t'}),
    CharTestHelperFactory("IsHexEscapeChar", JsonParser::Helpers::isHexEscapeChar, {'u'}),
    CharTestHelperFactory("IsDigit", JsonParser::Helpers::isDigit, {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, false),
    CharTestHelperFactory("IsColor", JsonParser::Helpers::isColon, {':'}),
    CharTestHelperFactory("IsDoubleQuote", JsonParser::Helpers::isDoubleQuote, {'\"'}),
    CharTestHelperFactory("IsOpenCurlyBracket", JsonParser::Helpers::isOpenCurlyBracket, {'{'}),
    CharTestHelperFactory("IsClosedCurlyBracket", JsonParser::Helpers::isClosedCurlyBracket, {'}'}),
    CharTestHelperFactory("IsOpenSqBracket", JsonParser::Helpers::isOpenSqBracket, {'['}),
    CharTestHelperFactory("IsClosedSqBracket", JsonParser::Helpers::isClosedSqBracket, {']'}),
    CharTestHelperFactory("IsDot", JsonParser::Helpers::isDot, {'.'}),
    CharTestHelperFactory("IsWhitespace", JsonParser::Helpers::isWhitespace, {' '}),
    CharTestHelperFactory("IsMinusSign", JsonParser::Helpers::isMinusSign, {'-'}),
    CharTestHelperFactory("IsPlusSign", JsonParser::Helpers::isPlusSign, {'+'}),
    CharTestHelperFactory("IsExponentSign", JsonParser::Helpers::isExponentSign, {'e', 'E'}, true, false));

INSTANTIATE_TEST_SUITE_P(CharHelpersTest, JsonParserCharHelpersTest, TestParameters,
                         [](const ::testing::TestParamInfo<CharTestHelper>& info) { return info.param.name; });


} // namespace Tests