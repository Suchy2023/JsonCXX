

#include "JsonC++/JsonParser/JsonParser.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "helpers.h"
#include <climits>
#include <expected>

namespace JsonParser
{

/**
 * 
 */
std::expected<int, JsonParserError> JsonParser::parseInt(const char *&iterator, const char *const &end)
{
    bool isInitialized = false;
    int result{};

    for (; iterator != end; ++iterator)
    {
        if (Helpers::isDigit(iterator))
        {
            isInitialized = true;
            result = result * 10 + (*iterator - 48);
        }
        else if (Helpers::isWhitespace(iterator))
        {
            // ignoring trailing spaces
            if (!isInitialized)
                continue;

            return result;
        }
        else if (Helpers::isDot(iterator))
        {
            return std::unexpected(JsonParserError::parse_error);
        }
    };

    return result;
}
} // namespace JsonParser