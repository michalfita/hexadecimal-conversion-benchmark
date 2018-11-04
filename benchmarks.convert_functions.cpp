#include "nonius.h++"
#include "convert_functions.h"
#include "random_data_generator.h"
#include <memory>

#include <list>
#include <forward_list>

// NONIUS_BENCHMARK("list<long long>", [](nonius::chronometer meter) {
//     std::list<long long> l;
//     meter.measure([&](int i) { l.push_front(i); });
// })

NONIUS_BENCHMARK("convert_hex_string_naive_sscanf", [](nonius::chronometer meter) {
    constexpr size_t data_length = 1024; //83886080;
    auto input = random_data_generator(data_length);
    auto output = std::make_unique<char[]>(data_length);
    meter.measure([input = move(input), output = move(output), data_length](int i)
        {
            return convert_hex_string_naive_sscanf(input.get(), output.get(), data_length);
        });
})

NONIUS_BENCHMARK("convert_hex_string_naive_strtoul", [](nonius::chronometer meter) {
    constexpr size_t data_length = 1024; //83886080;
    auto input = random_data_generator(data_length);
    auto output = std::make_unique<char[]>(data_length);
    meter.measure([input = move(input), output = move(output), data_length](int i)
        {
            return convert_hex_string_naive_strtoul(input.get(), output.get(), data_length);
        });
})

NONIUS_BENCHMARK("convert_hex_string_naive_lookup", [](nonius::chronometer meter) {
    constexpr size_t data_length = 1024; //83886080;
    auto input = random_data_generator(data_length);
    auto output = std::make_unique<char[]>(data_length);
    meter.measure([input = move(input), output = move(output), data_length](int i)
        {
            return convert_hex_string_naive_lookup(input.get(), output.get(), data_length);
        });
})

NONIUS_BENCHMARK("convert_hex_string_calculated", [](nonius::chronometer meter) {
    constexpr size_t data_length = 1024; //83886080;
    auto input = random_data_generator(data_length);
    auto output = std::make_unique<char[]>(data_length);
    meter.measure([input = move(input), output = move(output), data_length](int i)
        {
            return convert_hex_string_calculated(input.get(), output.get(), data_length);
        });
})