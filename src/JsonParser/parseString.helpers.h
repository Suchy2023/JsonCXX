
#include "char.helpers.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <iterator>

namespace JsonParser::Helpers
{

bool isValidEscapeSequence(IteratorCopy iterator, EndRef end);

bool isValidEscapeCharacter(IteratorRef iterator);

// API PROPOSITION

enum class EscapedCharacters : unsigned char
{
    quotation_mark,
    back_slash,
    forward_slash,
    backspace,
    form_feed,
    line_feed,
    carriage_return,
    tab,
    hex,
    count
};

bool isEscaped(EscapedCharacters c, IteratorCopy iterator, EndRef end);


} // namespace JsonParser::Helpers
