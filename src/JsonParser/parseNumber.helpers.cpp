

#include "parseNumber.helpers.h"
#include <cctype>
namespace JsonParser::Helpers
{

bool isJsonNumberValidCharacter(ConstIteratorRef iterator)
{
    return (isDigit(iterator) || isDot(iterator) || isMinusSign(iterator) || isExponentSign(iterator));
}

bool isJsonNumberInvalidCharacter(ConstIteratorRef iterator)
{
    return !isJsonNumberValidCharacter(iterator);
}
} // namespace JsonParser::Helpers
