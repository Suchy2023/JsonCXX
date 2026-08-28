

namespace JsonParser::Helpers
{

using IteratorCopy = const char*;

using IteratorRef = const char*&;

using ConstIteratorRef = const char* const &;

using EndRef = const char* const;

bool isBackSlash(ConstIteratorRef iterator);

bool isForwardSlash(ConstIteratorRef iterator);

bool isBackspaceEscapeChar(ConstIteratorRef iterator);

bool isFormFeedEscapeChar(ConstIteratorRef iterator);

bool isLineFeedEscapeChar(ConstIteratorRef iterator);

bool isCarriageReturnEscapeChar(ConstIteratorRef iterator);

bool isHorizontalTabEscapeChar(ConstIteratorRef iterator);

bool isHexEscapeChar(ConstIteratorRef iterator);

bool isDigit(ConstIteratorRef iterator);

bool isColon(ConstIteratorRef iterator);

bool isDoubleQuote(ConstIteratorRef iterator);

bool isOpenCurlyBracket(ConstIteratorRef iterator);

bool isClosedCurlyBracket(ConstIteratorRef iterator);

bool isOpenSqBracket(ConstIteratorRef iterator);

bool isClosedSqBracket(ConstIteratorRef iterator);

bool isDot(ConstIteratorRef iterator);

bool isWhitespace(ConstIteratorRef iterator);

bool isMinusSign(ConstIteratorRef iterator);

bool isPlusSign(ConstIteratorRef iterator);

bool isExponentSign(ConstIteratorRef iterator);

} // namespace JsonParser::Helpers