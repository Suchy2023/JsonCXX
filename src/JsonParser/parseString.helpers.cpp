
#include "parseString.helpers.h"
#include "parseNumber.helpers.h"
#include <cctype>
#include <iterator>

namespace JsonParser::Helpers
{

bool isValidJsonHex(IteratorCopy iterator, EndRef end)
{
    if (std::distance(iterator, end) != 4)
    {
        return false;
    }

    while (iterator != end)
    {
        if (!std::isxdigit(*iterator))
        {
            return false;
        }
    }
}

bool isValidEscapeSequence(IteratorCopy iterator, EndRef end)
{
    if (iterator == end || iterator + 1 == end || !isBackSlash(iterator))
    {
        return false;
    }

    iterator++;

    if (isValidEscapeCharacter(iterator))
    {
        if (isHexEscapeChar(iterator))
        {
            if (isValidJsonHex(iterator + 1, end))
            {
                return true;
            }
            else {
                return false;
            }
        }

        return true;
    }
};

bool isValidEscapeCharacter(IteratorRef iterator)
{
    return (
        isDoubleQuote(iterator) ||
        isBackSlash(iterator) ||
        isForwardSlash(iterator) ||
        isBackspaceEscapeChar(iterator) ||
        isFormFeedEscapeChar(iterator) ||
        isLineFeedEscapeChar(iterator) ||
        isCarriageReturnEscapeChar(iterator) ||
        isHorizontalTabEscapeChar(iterator) ||
        isHexEscapeChar(iterator)
    );
}

bool isEscapedQuotationMark(IteratorCopy iterator, EndRef end)
{
    if (isBackSlash(iterator) && (iterator + 1) != end && Helpers::isDoubleQuote(iterator + 1))
    {
        return true;
    }

    return false;
};

bool isEscapedBackSlash(IteratorCopy iterator, EndRef end)
{
    if (iterator == end || (iterator + 1) == end)
    {
        return false;
    }

    auto nextIterator = iterator + 1;

    return isBackSlash(iterator) && isBackSlash(nextIterator);
}

} // namespace JsonParser::Helpers