
#include "char.helpers.h"
#include <cctype>

namespace JsonParser::Helpers
{

bool isBackSlash(ConstIteratorRef iterator)
{
    return *iterator == 92;
}

bool isForwardSlash(ConstIteratorRef iterator)
{
    return *iterator == '/';
}

bool isBackspaceEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 'b';
}

bool isFormFeedEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 'f';
}

bool isLineFeedEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 'n';
}

bool isCarriageReturnEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 'r';
}

bool isHorizontalTabEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 't';
}

bool isHexEscapeChar(ConstIteratorRef iterator)
{
    return *iterator == 'u';
}

bool isDigit(ConstIteratorRef iterator)
{
    return std::isdigit(*iterator);
}

bool isColon(ConstIteratorRef iterator)
{
    return *iterator == ':';
}

bool isDoubleQuote(ConstIteratorRef iterator)
{
    return *iterator == 34;
}

bool isOpenCurlyBracket(ConstIteratorRef iterator)
{
    return *iterator == '{';
}

bool isClosedCurlyBracket(ConstIteratorRef iterator)
{
    return *iterator == '}';
}

bool isOpenSqBracket(ConstIteratorRef iterator)
{
    return *iterator == '[';
}

bool isClosedSqBracket(ConstIteratorRef iterator)
{
    return *iterator == ']';
}

bool isDot(ConstIteratorRef iterator)
{
    return *iterator == '.';
}

bool isWhitespace(ConstIteratorRef iterator)
{
    return *iterator == 32;
}

bool isMinusSign(ConstIteratorRef iterator)
{
    return *iterator == '-';
}

bool isPlusSign(ConstIteratorRef iterator)
{
    return *iterator == '+';
}

bool isExponentSign(ConstIteratorRef iterator)
{
    return *iterator == 'e' || *iterator == 'E';
}

} // namespace JsonParser::Helpers