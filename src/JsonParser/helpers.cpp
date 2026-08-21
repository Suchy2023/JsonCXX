

#include <cctype>
#include "helpers.h"
namespace JsonParser::Helpers {
using T = const char *const &;

bool isDigit(T iterator) { return std::isdigit(*iterator); };

bool isColon(T iterator) { return *iterator == 58; };

bool isDoubleQuote(T iterator) { return *iterator == 34; }

bool isOpenCurlyBracket(T iterator) { return *iterator == 123; }

bool isClosedCurlyBracket(T iterator) { return *iterator == 125; }

bool isOpenSqBracket(T iterator) { return *iterator == 91; }

bool isClosedSqBracket(T iterator) { return *iterator == 93; }

bool isDot(T iterator) { return *iterator == 46; }

bool isWhitespace(T iterator) {return *iterator == 32;}
} // namespace JsonParser
