#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "random_data_generator.h"
#include "matcher.hexadecimal_digit.h"

TEST_CASE("Generate small data", "[generator]")
{
    auto data = random_data_generator(2);

    REQUIRE_THAT(data[0], IsHexadecimalDigit());
    REQUIRE_THAT(data[1], IsHexadecimalDigit());
}

TEST_CASE("Generate massive data", "[generator]")
{
    constexpr static const size_t required_size = 80 * 1024;
    auto data = random_data_generator(required_size);

    SECTION("check data validity")
    {
        auto g = GENERATE(range(static_cast<size_t>(0), required_size));
        CAPTURE(g, data[g]);
        REQUIRE_THAT(data[g], IsHexadecimalDigit());
    }
}