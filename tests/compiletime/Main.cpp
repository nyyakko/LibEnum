#include <gtest/gtest.h>

#include <fmt/format.h>
#include <libenum/Enum.hpp>

using sv = std::string_view;

ENUM_CLASS(Test,
    A,
    B,
    C
);

static_assert(!::Test::is_convertible("E"), "This shouldn't be possible");
static_assert(sv(::Test::A) == "A", "Couldn't convert enum to string representation");
static_assert(::Test::A == 0, "Couldn't convert enum to numeric representation");
static_assert(::Test::from_string("A").to_string() == sv("A"));

static_assert(::Test::from_string("A") == ::Test::A);
static_assert(::Test::from_string("C") != ::Test::A);

TEST(compile_time, switch_cases)
{
    [] (::Test value) {
        switch (value)
        {
        case ::Test::A:
        case ::Test::B:
        case ::Test::C: break;
        };
    }(::Test::A);
}

