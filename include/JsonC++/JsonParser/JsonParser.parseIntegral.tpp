#pragma once

#include "JsonC++/JsonParser/JsonParser.Concepts.h"
#include "JsonC++/JsonParser/JsonParser.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "helpers.h"
#include <cstdlib>
#include <expected>
#include <limits>
#include <type_traits>
#include <utility>

namespace JsonParser
{

template <Integral T>
constexpr bool wouldOverflow(const T& number, const int& next, const bool isNegative)
{
    constexpr auto isUnsgigned = std::is_unsigned_v<T>;

    constexpr auto max = std::numeric_limits<T>::max();
    constexpr auto maxValueDiv10 = max / 10;
    constexpr auto maxDigit = max % 10;

    constexpr auto min = std::numeric_limits<T>::min();
    constexpr auto minValueDiv10 = min / 10;
    constexpr auto minDigit = min % 10;

    if (isUnsgigned && isNegative)
    {
        return true;
    }

    if (isNegative)
    {
        if (std::cmp_less(number, minValueDiv10) || (std::cmp_equal(number, minValueDiv10) && std::cmp_greater(next, -minDigit))){
            return true;
        }

        return false;
    }
    else {
        if (std::cmp_greater(number, maxValueDiv10) || (std::cmp_equal(number,maxValueDiv10) && std::cmp_greater(next,maxDigit)))
        {
            return true;
        }

        return false;
    }
};

template <Integral T>
std::expected<T, JsonParserError> JsonParser::parseIntegral(const char *&iterator, const char *const &end)
{
    constexpr auto isUnsigned = std::is_unsigned_v<T>;

    bool isInitialized = false;

    auto number = T{};

    bool isNegative = false;

    for (; iterator != end; ++iterator)
    {
        if (Helpers::isWhitespace(iterator))
        {
            if (isInitialized)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else
            {
                continue;
            }
        }
        else if (Helpers::isDigit(iterator))
        {
            if (!isInitialized)
            {
                if (*iterator - '0' == 0 && iterator + 1 != end && *(iterator + 1) - '0' == 0)
                {
                    return std::unexpected(JsonParserError::invalid_format);
                }

                number = number * 10 + (*iterator - 48);

                if (isNegative)
                {
                    number *= -1;
                }

                isInitialized = true;
            }
            else if (wouldOverflow<T>(number, (*iterator - 48), isNegative))
            {
                return std::unexpected(JsonParserError::out_of_range);
            }
            else
            {
                number = number * 10;

                if (isNegative)
                {
                    number -= *iterator - 48;
                }
                else
                {
                    number += *iterator - 48;
                }

                isInitialized = true;
            }
        }
        else if (Helpers::isDot(iterator))
        {
            return std::unexpected(JsonParserError::not_integral);
        }
        else if (Helpers::isMinusSign(iterator))
        {
            if (isUnsigned)
            {
                return std::unexpected(JsonParserError::out_of_range);
            }

            isNegative = true;
        }
    };

    return number;
}

} // namespace JsonParser