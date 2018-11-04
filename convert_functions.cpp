#include <cstdlib>
#include <cinttypes>
#include <cstdio>

int convert_hex_string_naive_sscanf(const char* input, char* output, const size_t in_length)
{
    char buffer[] = "\0\0";
    uint8_t byte;
    size_t length = in_length / 2;
    for (size_t idx = 0; idx < length; ++idx)
    {
        buffer[0] = *(input++);
        buffer[1] = *(input++);
        sscanf(buffer, "%02" SCNx8, &byte);
        output[idx] = byte;
    }
    return length;
}

int convert_hex_string_naive_strtoul(const char* input, char* output, const size_t in_length)
{
    char buffer[] = "\0\0";
    size_t length = in_length / 2;
    for (size_t idx = 0; idx < length; ++idx)
    {
        buffer[0] = *(input++);
        buffer[1] = *(input++);
        output[idx] = static_cast<uint8_t>(strtoul(buffer, nullptr, 16));
    }
    return length;
}

int convert_hex_string_naive_lookup(const char* input, char* output, const size_t length)
{
    static const int8_t lookup[256] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    };

    for (size_t idx = 0; idx < (length / 2); ++idx)
    {
        //output[idx] = 16 * lookup[*(input++)];
        //output[idx] +=     lookup[*(input++)];
        output[idx]  = lookup[*(input++)] << 4;
        output[idx] += lookup[*(input++)];
    }
    return length;
}

int convert_hex_string_calculated(const char* input, char* output, const size_t length)
{
    auto hexd_nibble_to_value = [](const char c) -> uint8_t
    {
        return c <= '9' ? c - '0' : 0xA + (
                c <= 'F' ? c - 'A' :
                    c - 'a');
    };

    auto hexd_byte_to_value = [&](const char hexd_byte[2]) -> uint8_t
    {
        return ( hexd_nibble_to_value(hexd_byte[0]) << 4 )
                + hexd_nibble_to_value(hexd_byte[1]);
    };

    for (size_t idx = 0; idx < (length / 2); ++idx)
    {
        output[idx] = hexd_byte_to_value(input);
        input += 2;
    }

    return length;
}