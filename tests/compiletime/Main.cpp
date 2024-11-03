#include <gtest/gtest.h>

#include <libenum/Enum.hpp>

using sv = std::string_view;

ENUM_CLASS(Test,
    A,
    B,
    C
);

static_assert(sv(::Test::A) == "Test::A", "Couldn't convert enum to string representation");
static_assert(::Test::A == 0, "Couldn't convert enum to numeric representation");

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
