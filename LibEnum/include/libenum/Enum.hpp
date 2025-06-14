#pragma once

#include "Core.hpp"

#include <limits>
#include <string_view>

template <class T>
concept enum_value_concept = requires (T t) {
    t.value;
};

#define ENUM_VALUE(NAME, VALUE)                                                   \
private:                                                                          \
class __##NAME##__##VALUE {                                                       \
public:                                                                           \
    static constexpr size_t value = __COUNTER__ - BASE - 1;                       \
                                                                                  \
    constexpr operator size_t() const { return value; }                           \
    constexpr operator char const*() const { return #VALUE; }                     \
                                                                                  \
    template <enum_value_concept T>                                               \
    constexpr bool operator==(T that) const { return this->value == that.value; } \
                                                                                  \
    template <enum_value_concept T>                                               \
    constexpr bool operator<(T that) const { return this->value < that.value; }   \
                                                                                  \
    template <enum_value_concept T>                                               \
    constexpr bool operator<=(T that) const { return this->value <= that.value; } \
                                                                                  \
    template <enum_value_concept T>                                               \
    constexpr bool operator>(T that) const { return this->value > that.value; }   \
                                                                                  \
    template <enum_value_concept T>                                               \
    constexpr bool operator>=(T that) const { return this->value >= that.value; } \
};                                                                                \
public:                                                                           \
inline static __##NAME##__##VALUE VALUE;

#define ENUM_VALUES(NAME, ...) FOR_EACH(ENUM_VALUE, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_INT_VALUE_CONVERSION(NAME, VALUE) if (value == NAME::VALUE) return NAME::VALUE;
#define ENUM_INT_VALUES_CONVERSION(NAME, ...) FOR_EACH(ENUM_INT_VALUE_CONVERSION, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_INT_VALUE_CONVERTIBLE(NAME, VALUE) if (value == NAME::VALUE) return true;
#define ENUM_INT_VALUES_CONVERTIBLE(NAME, ...) FOR_EACH(ENUM_INT_VALUE_CONVERTIBLE, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_STRING_VALUE_CONVERSION(NAME, VALUE) if (value == std::string_view(VALUE)) return NAME::VALUE;
#define ENUM_STRING_VALUES_CONVERSION(NAME, ...) FOR_EACH(ENUM_STRING_VALUE_CONVERSION, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_STRING_VALUE_CONVERTIBLE(NAME, VALUE) if (value == std::string_view(VALUE)) return true;
#define ENUM_STRING_VALUES_CONVERTIBLE(NAME, ...) FOR_EACH(ENUM_STRING_VALUE_CONVERTIBLE, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_CLASS(NAME, ...)                                                               \
class NAME {                                                                                \
    static constexpr auto BASE = __COUNTER__;                                               \
public:                                                                                     \
    constexpr NAME() = default;                                                             \
    constexpr NAME(auto value)                                                              \
    {                                                                                       \
        this->value = value;                                                                \
        this->string = std::string_view(value);                                             \
    }                                                                                       \
                                                                                            \
    ENUM_VALUES(NAME __VA_OPT__(,) __VA_ARGS__)                                             \
                                                                                            \
    constexpr operator size_t() const { return value; }                                     \
    constexpr operator char const*() const { return string.data(); }                        \
                                                                                            \
    constexpr size_t to_int() const { return value; }                                       \
    constexpr char const* to_string() const { return string.data(); }                       \
                                                                                            \
    static constexpr NAME from_int(auto value)                                              \
    {                                                                                       \
        ENUM_INT_VALUES_CONVERSION(NAME __VA_OPT__(,) __VA_ARGS__)                          \
        return {};                                                                          \
    }                                                                                       \
                                                                                            \
    static constexpr NAME from_string(auto value)                                           \
    {                                                                                       \
        ENUM_STRING_VALUES_CONVERSION(NAME __VA_OPT__(,) __VA_ARGS__)                       \
        return {};                                                                          \
    }                                                                                       \
                                                                                            \
    static constexpr bool is_convertible(std::integral auto value)                          \
    {                                                                                       \
        ENUM_INT_VALUES_CONVERTIBLE(NAME __VA_OPT__(,) __VA_ARGS__)                         \
        return false;                                                                       \
    }                                                                                       \
                                                                                            \
    static constexpr bool is_convertible(auto value)                                        \
    {                                                                                       \
        ENUM_STRING_VALUES_CONVERTIBLE(NAME __VA_OPT__(,) __VA_ARGS__)                      \
        return false;                                                                       \
    }                                                                                       \
                                                                                            \
    constexpr bool operator==(NAME const& that) const { return this->value == that.value; } \
    constexpr bool operator<(NAME const& that) const { return this->value < that.value; }   \
    constexpr bool operator<=(NAME const& that) const { return this->value <= that.value; } \
    constexpr bool operator>(NAME const& that) const { return this->value > that.value; }   \
    constexpr bool operator>=(NAME const& that) const { return this->value >= that.value; } \
                                                                                            \
private:                                                                                    \
    std::string_view string = "INVALID";                                                    \
    size_t value = std::numeric_limits<size_t>::max();                                      \
};

