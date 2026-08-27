

namespace JsonParser::Helpers
{
    using T = const char *const &;

bool isDigit(T iterator);

bool isColon(T iterator);

bool isDoubleQuote(T iterator);

bool isOpenCurlyBracket(T iterator);

bool isClosedCurlyBracket(T iterator);

bool isOpenSqBracket(T iterator);

bool isClosedSqBracket(T iterator);

bool isDot(T iterator);

bool isWhitespace(T iterator);

bool isMinusSign(T iterator);

bool isPlusSign(T iterator);

bool isExponentSign(T iterator);

bool isJsonNumberValidCharacter(T iterator);

bool isJsonNumberInvalidCharacter(T iterator);
}