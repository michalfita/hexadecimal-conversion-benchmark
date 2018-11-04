#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "convert_functions.h"
#include <memory>

TEST_CASE("Simple hexadecimal conversion", "[converter]")
{
  #if __cpp_structured_bindings < 201606 
    const char* input;
    const char* expected;
    std::tie(input, expected) = 
  #else
    auto [input, expected] = 
  #endif
                             GENERATE(table<const char*, const char*>({
        {"01", "\x01"},
        {"55", "\x55"},
        {"AB", "\xAB"},
        {"FF", "\xFF"},
    }));

    char buffer[] = "\0\0";

    SECTION("convert_hex_string_naive_sscanf")
    {
        convert_hex_string_naive_sscanf(input, buffer, 2);
    }

    SECTION("convert_hex_string_naive_strtoul")
    {
        convert_hex_string_naive_strtoul(input, buffer, 2);
    }

    SECTION("convert_hex_string_naive_lookup")
    {
        convert_hex_string_naive_lookup(input, buffer, 2);
        CAPTURE(expected, buffer);
    }

    REQUIRE(memcmp(expected, buffer, 1) == 0);
}

TEST_CASE("Complex hexadecimal conversion", "[converter]")
{
  #if __cpp_structured_bindings < 201606 
    const char* input;
    const char* expected;
    std::tie(input, expected) = 
  #else
    auto [input, expected] = 
  #endif
                             GENERATE(table<const char*, const char*>({
        {"0123456789ABCDEF", "\x01\x23\x45\x67\x89\xAB\xCD\xEF"},
        {"FEDCBA9876543210", "\xFE\xDC\xBA\x98\x76\x54\x32\x10"},
        {"2f525ba8b492468ca7a672c1a1e715e73130ce5358c2659ed457b48ca27042e52346ca427d736d86e69090306863f15aa880d189b44f9b7efe2ed85d6a45b48a",
         "/R[\xa8\xb4\x92\x46\x8c\xa7\xa6\x72\xc1\xa1\xe7\x15\xe7\x31\x30\xce\x53\x58\xc2\x65\x9e\xd4\x57\xb4\x8c\xa2\x70\x42\xe5\x23\x46\xca"
             "\x42\x7d\x73\x6d\x86\xe6\x90\x90\x30\x68\x63\xf1\x5a\xa8\x80\xd1\x89\xb4\x4f\x9b\x7e\xfe\x2e\xd8\x5d\x6a\x45\xb4\x8a"}
    }));

    const size_t input_length = strlen(input);
    const size_t output_length = input_length / 2;

    // Make space for null, to prevent crashes if something goes wrong
    std::unique_ptr<char []> buffer = std::make_unique<char []>(output_length + 1);
    buffer[output_length] = '\0';

    SECTION("convert_hex_string_naive_sscanf")
    {
        convert_hex_string_naive_sscanf(input, buffer.get(), input_length);
    }

    SECTION("convert_hex_string_naive_strtoul")
    {
        convert_hex_string_naive_strtoul(input, buffer.get(), input_length);
    }

    SECTION("convert_hex_string_naive_lookup")
    {
        convert_hex_string_naive_lookup(input, buffer.get(), input_length);
    }

    SECTION("convert_hex_string_calculated")
    {
        convert_hex_string_calculated(input, buffer.get(), input_length);
    }

    CAPTURE(expected, buffer.get());
    REQUIRE(memcmp(expected, buffer.get(), output_length) == 0);
}