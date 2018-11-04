#include <cstdlib>
#include <cinttypes>
#include <cstdio>

int convert_hex_string_naive_sscanf(const char* input, char* output, const size_t in_length);
int convert_hex_string_naive_strtoul(const char* input, char* output, const size_t in_length);
int convert_hex_string_naive_lookup(const char* input, char* output, const size_t in_length);
int convert_hex_string_calculated(const char* input, char* output, const size_t in_length);
