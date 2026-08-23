
#pragma once

namespace JsonParser
{

    enum class JsonParserError : unsigned char
    {
        parse_error,
        out_of_range,
        not_integral,
        invalid_format
    };

}