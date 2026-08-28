
#include "char.helpers.h"

namespace JsonParser::Helpers
{

bool isValidEscapeSequence(IteratorCopy iterator, EndRef end);

bool isValidEscapeCharacter(IteratorRef iterator);

bool isEscapedQuotationMark(IteratorCopy iterator, EndRef end);

bool isEscapedBackSlash(IteratorCopy iterator, EndRef end);

bool isValidJsonHex(IteratorCopy iterator, EndRef end);

} // namespace JsonParser::Helpers