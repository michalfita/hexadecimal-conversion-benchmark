#include "random_data_generator.h"
#include <random>

std::unique_ptr<char[]> random_data_generator_simple(size_t length)
{
    auto buffer = std::make_unique<char[]>(length);
    static const char hex_digits[] = "0123456789ABCDEFabcdef";

    std::random_device seeder;
    std::mt19937 generator(seeder());
    std::uniform_int_distribution<> selector(0, sizeof(hex_digits) - 2); // lb <= x <= ub

    for (size_t idx = 0; idx < length;)
    {
        buffer[idx++] = hex_digits[selector(generator)];
    }

    return buffer;
}

std::unique_ptr<char[]> random_data_generator(size_t length)
{
    auto buffer = std::make_unique<char[]>(length);
    static const char hex_digits[] = "0123456789ABCDEFabcdef";

    std::random_device seeder;
    std::mt19937 generator(seeder());
    std::uniform_int_distribution<uint64_t> selector(0);

    for (size_t idx = 0; idx < length;)
    {
        uint64_t rand_indexes = selector(generator);

        switch((length - idx) % 8)
        {
        case 0:
            buffer[idx++] = hex_digits[(rand_indexes >> 0) && 0xff];
        case 7:
            buffer[idx++] = hex_digits[(rand_indexes >> 56) && 0xff];
        case 6:
            buffer[idx++] = hex_digits[(rand_indexes >> 48) && 0xff];
        case 5:
            buffer[idx++] = hex_digits[(rand_indexes >> 40) && 0xff];
        case 4:
            buffer[idx++] = hex_digits[(rand_indexes >> 32) && 0xff];
        case 3:
            buffer[idx++] = hex_digits[(rand_indexes >> 24) && 0xff];
        case 2:
            buffer[idx++] = hex_digits[(rand_indexes >> 16) && 0xff];
        case 1:
            buffer[idx++] = hex_digits[(rand_indexes >> 8) && 0xff];
        }
    }

    return buffer;
}