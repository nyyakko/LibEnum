#include <gtest/gtest.h>

#include <fmt/format.h>
#include <libenum/Enum.hpp>

using sv = std::string_view;

ENUM_CLASS(TestEnum,
    A,
    B,
    C,
);

static_assert(!TestEnum::is_convertible("E"));
static_assert(!TestEnum::is_convertible(-1));

static_assert(sv(TestEnum::A) == "A");
static_assert("A" == sv(TestEnum::A));

static_assert(TestEnum::from_string("A").to_string() == sv("A"));
static_assert(sv("A") == TestEnum::from_string("A").to_string());

static_assert(TestEnum::A == 0);
static_assert(0 == TestEnum::A);
static_assert(TestEnum::from_int(0) == TestEnum::A);
static_assert(TestEnum::A == TestEnum::from_int(0));
static_assert(TestEnum::from_string("A") == TestEnum::from_string("A"));
static_assert(TestEnum::from_string("A") == TestEnum::A);
static_assert(TestEnum::A == TestEnum::from_string("A"));
static_assert(TestEnum::A == TestEnum::A);

static_assert(TestEnum::A != 1);
static_assert(1 != TestEnum::A);
static_assert(TestEnum::from_int(1) != TestEnum::A);
static_assert(TestEnum::A != TestEnum::from_int(1));
static_assert(TestEnum::from_string("A") != TestEnum::from_string("B"));
static_assert(TestEnum::from_string("A") != TestEnum::B);
static_assert(TestEnum::A != TestEnum::from_string("B"));
static_assert(TestEnum::A != TestEnum::B);

static_assert(TestEnum::B > 0);
static_assert(1 > TestEnum::A);
static_assert(TestEnum::from_string("B") > TestEnum::from_string("A"));
static_assert(TestEnum::from_string("B") > TestEnum::A);
static_assert(TestEnum::B > TestEnum::from_string("A"));
static_assert(TestEnum::B > TestEnum::A);

static_assert(TestEnum::A < 1);
static_assert(0 < TestEnum::B);
static_assert(TestEnum::from_string("A") < TestEnum::from_string("B"));
static_assert(TestEnum::from_string("A") < TestEnum::B);
static_assert(TestEnum::A < TestEnum::from_string("B"));
static_assert(TestEnum::A < TestEnum::B);

static_assert(TestEnum::A >= 0);
static_assert(0 >= TestEnum::A);
static_assert(TestEnum::from_string("A") >= TestEnum::from_string("A"));
static_assert(TestEnum::from_string("A") >= TestEnum::A);
static_assert(TestEnum::A >= TestEnum::from_string("A"));
static_assert(TestEnum::A >= TestEnum::A);

static_assert(TestEnum::B >= 0);
static_assert(1 >= TestEnum::A);
static_assert(TestEnum::from_string("B") >= TestEnum::from_string("A"));
static_assert(TestEnum::from_string("B") >= TestEnum::A);
static_assert(TestEnum::B >= TestEnum::from_string("A"));
static_assert(TestEnum::B >= TestEnum::A);

static_assert(TestEnum::A <= 0);
static_assert(0 <= TestEnum::A);
static_assert(TestEnum::from_string("A") <= TestEnum::from_string("A"));
static_assert(TestEnum::from_string("A") <= TestEnum::A);
static_assert(TestEnum::A <= TestEnum::from_string("A"));
static_assert(TestEnum::A <= TestEnum::A);

static_assert(TestEnum::A <= 1);
static_assert(0 <= TestEnum::B);
static_assert(TestEnum::from_string("A") <= TestEnum::from_string("B"));
static_assert(TestEnum::from_string("A") <= TestEnum::B);
static_assert(TestEnum::A <= TestEnum::from_string("B"));
static_assert(TestEnum::A <= TestEnum::B);

static_assert(
    [] (TestEnum value) consteval -> TestEnum {
        switch (value) {
            case TestEnum::A: return TestEnum::A;
            case TestEnum::B: return TestEnum::B;
            case TestEnum::C: return TestEnum::C;
        };
        return TestEnum{};
    }
(TestEnum::A) == TestEnum::A);

static_assert(
    [] (TestEnum value) consteval -> TestEnum {
        switch (value) {
            case TestEnum::A: return TestEnum::A;
            case TestEnum::B: return TestEnum::B;
            case TestEnum::C: return TestEnum::C;
        };
        return TestEnum{};
    }
(TestEnum::from_string("A")) == TestEnum::A);

static_assert(
    [] (TestEnum value) consteval -> TestEnum {
        switch (value) {
            case TestEnum::A: return TestEnum::A;
            case TestEnum::B: return TestEnum::B;
            case TestEnum::C: return TestEnum::C;
        };
        return TestEnum{};
    }
(TestEnum::from_int(0)) == TestEnum::A);
