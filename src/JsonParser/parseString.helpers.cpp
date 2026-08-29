
#include "parseString.helpers.h"
#include "parseNumber.helpers.h"
#include <algorithm>
#include <cctype>
#include <iterator>

namespace JsonParser::Helpers
{

constexpr int JSON_DEFAULT_ESCAPE_LENGTH = 2;
constexpr int JSON_HEX_ESCAPE_LENGTH = 6;

constexpr bool basicEscapeSequenceValidator(EscapedCharacters escaped, IteratorCopy iterator, EndRef end);

constexpr bool hexEscapeSequenceValidator(EscapedCharacters escaped, IteratorCopy iterator, EndRef end);

constexpr bool isMatchingEscapeChar(EscapedCharacters escaped, IteratorCopy iterator);

struct EscapedCharacterEntry
{
    EscapedCharacters id;
    char escaped;
    bool (*validate)(EscapedCharacters c, IteratorCopy iterator, EndRef end){basicEscapeSequenceValidator};
};

constexpr std::array<EscapedCharacterEntry, static_cast<std::size_t>(EscapedCharacters::count)> kEscapeTable{
    {
        {EscapedCharacters::quotation_mark, '\"'},
        {EscapedCharacters::back_slash, '\\'},
        {EscapedCharacters::forward_slash, '/'},
        {EscapedCharacters::backspace, 'b'},
        {EscapedCharacters::form_feed, 'f'},
        {EscapedCharacters::line_feed, 'n'},
        {EscapedCharacters::carriage_return, 'r'},
        {EscapedCharacters::tab, 't'},
        {EscapedCharacters::hex, 'u', hexEscapeSequenceValidator},
    },
};

constexpr bool isMatchingEscapeChar(EscapedCharacters escaped, IteratorCopy iterator)
{
    const auto entry = std::ranges::find_if(
        kEscapeTable, [&](const EscapedCharacterEntry& other) -> bool { return other.id == escaped; });

    return entry->escaped == *iterator;
}

constexpr bool basicEscapeSequenceValidator(EscapedCharacters escaped, IteratorCopy iterator, EndRef end)
{
    if (std::distance(iterator, end) != JSON_DEFAULT_ESCAPE_LENGTH)
    {
        return false;
    }

    if (!isBackSlash(iterator))
    {
        return false;
    }

    ++iterator;

    if (!isMatchingEscapeChar(escaped, iterator))
    {
        return false;
    }

    return true;
};

constexpr bool hexEscapeSequenceValidator(EscapedCharacters escaped, IteratorCopy iterator, EndRef end)
{
    if (std::distance(iterator, end) != JSON_HEX_ESCAPE_LENGTH)
    {
        return false;
    }

    if (!isBackSlash(iterator))
    {
        return false;
    }

    iterator++;

    if (!isMatchingEscapeChar(escaped, iterator))
    {
        return false;
    }

    iterator++;

    while (iterator != end)
    {
        if (!std::isxdigit(static_cast<unsigned char>(*iterator)))
        {
            return false;
        }

        ++iterator;
    }

    return true;
}

bool isEscaped(EscapedCharacters c, IteratorCopy iterator, EndRef end)
{
    const auto entry =
        std::ranges::find_if(kEscapeTable, [&c](const EscapedCharacterEntry& other) -> bool { return other.id == c; });

    return (*entry).validate(c, iterator, end);
}

} // namespace JsonParser::Helpers