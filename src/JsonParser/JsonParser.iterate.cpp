
#include "JsonC++/JsonParser/JsonParser.h"

#include "JsonC++/Core/JsonValue.h"

#include "helpers.h"

namespace JsonParser
{

Core::JsonValue JsonParser::iterate(const char *&iterator, const char *const end)
{
    for (; iterator != end; ++iterator)
    {
        if (Helpers::isDigit(iterator))
        {
            return parseNumber(iterator, end);
        }
        else if (Helpers::isDoubleQuote(iterator))
        {
            return parseString(iterator, end);
        }
        else if (Helpers::isOpenCurlyBracket(iterator))
        {
            return parseObject(iterator, end);
        }
        else if (Helpers::isOpenSqBracket(iterator))
        {
            return parseArray(iterator, end);
        }
        else if (Helpers::isWhitespace(iterator))
        {
            continue;
        }
    }

    return Core::JsonValue{};
};

} // namespace JsonParser