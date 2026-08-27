

#include "JsonC++/JsonParser/JsonParser.h"
#include "JsonC++/Core/JsonValue.Types.h"
#include "JsonC++/JsonParser/JsonParserError.h"
#include "helpers.h"
#include <charconv>
#include <cstdint>
#include <limits>
#include <system_error>
#include <utility>
#include <variant>

namespace JsonParser
{

std::expected<std::variant<Core::Json_Int64, Core::Json_UInt64, Core::Json_Double>, JsonParserError> JsonParser::
    parseNumber(Iterator iterator, End end)
{
    constexpr auto maxInt64 = std::numeric_limits<int64_t>::max();
    constexpr auto maxUInt64 = std::numeric_limits<uint64_t>::max();
    constexpr auto maxDouble = std::numeric_limits<double>::max();

    constexpr auto minInt64 = std::numeric_limits<int64_t>::min();
    constexpr auto minUInt64 = std::numeric_limits<uint64_t>::min();
    constexpr auto minDouble = std::numeric_limits<double>::min();

    constexpr uint8_t maxUnsignedDigits = std::numeric_limits<uint64_t>::digits10;
    constexpr uint8_t maxSignedDigits = std::numeric_limits<int64_t>::digits10;

    bool isInitialized{false};

    bool isNegative{false};
    bool isFloating{false};
    bool digitsOverflow{false};
    bool hasExponent{false};

    short digitsCount{};

    uint64_t value{};

    auto iteratorCopy = iterator;

    for (; iterator != end; ++iterator)
    {
        if (Helpers::isDigit(iterator))
        {
            if (*iterator == '0')
            {
                if (!isInitialized && iterator + 1 != end && !Helpers::isDot(iterator + 1))
                {
                    return std::unexpected(JsonParserError::invalid_format);
                }
            }

            if ((isNegative && (digitsCount > maxSignedDigits)) || (!isNegative && (digitsCount > maxUnsignedDigits)))
            {
                digitsOverflow = true;
                break;
            }

            digitsCount++;

            value = value * 10 + (*iterator - '0');

            if (!isInitialized)
            {
                isInitialized = true;
            }
        }
        else if (Helpers::isDot(iterator))
        {
            if (!isInitialized)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            if (isFloating)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else if (iterator + 1 == end)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }

            isFloating = true;
        }
        else if (Helpers::isWhitespace(iterator))
        {
            return std::unexpected(JsonParserError::invalid_format);
        }
        else if (Helpers::isMinusSign(iterator))
        {
            if (isNegative)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else if (iterator + 1 == end)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else if (!Helpers::isDigit(iterator + 1))
            {
                return std::unexpected(JsonParserError::invalid_format);
            }

            if (!isInitialized)
            {
                isNegative = true;
                continue;
            }

            return std::unexpected(JsonParserError::invalid_format);
        }
        else if (Helpers::isExponentSign(iterator))
        {
            if (hasExponent)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else if (iterator + 1 == end)
            {
                return std::unexpected(JsonParserError::invalid_format);
            }
            else
            {
                bool hasSign{false};
                bool hasDigit{false};
                ++iterator;

                while (iterator != end)
                {
                    if (Helpers::isDigit(iterator))
                    {
                        hasDigit = true;
                    }
                    else if (Helpers::isMinusSign(iterator) || Helpers::isPlusSign(iterator))
                    {
                        if (iterator + 1 == end)
                        {
                            return std::unexpected(JsonParserError::invalid_format);
                        }

                        if (hasDigit || hasSign)
                        {
                            return std::unexpected(JsonParserError::invalid_format);
                        }

                        hasSign = true;
                    }
                    else
                    {
                        return std::unexpected(JsonParserError::invalid_format);
                    }

                    ++iterator;
                }

                hasExponent = true;
                break;
            }
        }
        else if (Helpers::isJsonNumberInvalidCharacter(iterator))
        {
            return std::unexpected(JsonParserError::invalid_format);
        }
    }

    if (isFloating || digitsOverflow || hasExponent)
    {
        double res{};

        auto [ptr, err] = std::from_chars(iteratorCopy, end, res);

        if (err == std::errc{})
        {
            return static_cast<double>(res);
        }
        else
        {
            return std::unexpected(JsonParserError::unknown);
        }
    }

    if (isNegative)
    {
        if (std::cmp_less_equal(value, static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) + 1))
        {
            return -static_cast<int64_t>(value);
        }
    }

    if (std::cmp_greater_equal(value, minInt64) && std::cmp_less_equal(value, maxInt64))
    {
        return static_cast<int64_t>(value);
    }
    else
    {
        return static_cast<uint64_t>(value);
    }

    return value;
};

} // namespace JsonParser