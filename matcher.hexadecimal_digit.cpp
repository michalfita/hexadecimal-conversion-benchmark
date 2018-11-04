#include "matcher.hexadecimal_digit.h"

bool HexadecimalDigit::match(char const& c) const
{
    return (c >= '0' && c <= '9')
        || (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z');
}

std::string HexadecimalDigit::describe() const
{
    return "is hexadecimal digit";
}

