#pragma once

#include "Core.hpp"

#include <string_view>

#define ENUM_VALUE(NAME, VALUE)                                        \
private:                                                               \
class __##NAME##__##VALUE {                                            \
public:                                                                \
    static constexpr auto value = __COUNTER__ - BASE - 1;              \
                                                                       \
    constexpr operator size_t() const { return value; }                \
    constexpr operator char const*() const { return #NAME"::"#VALUE; } \
};                                                                     \
public:                                                                \
static __##NAME##__##VALUE VALUE;

#define ENUM_VALUES(NAME, ...) FOR_EACH(ENUM_VALUE, NAME __VA_OPT__(,) __VA_ARGS__)

#define ENUM_CLASS(NAME, ...)                                         \
class NAME {                                                          \
    static constexpr auto BASE = __COUNTER__;                         \
public:                                                               \
    constexpr NAME(auto value)                                        \
    {                                                                 \
        this->numeric = value;                                        \
        this->stringy = std::string_view(value);                      \
    }                                                                 \
                                                                      \
    ENUM_VALUES(NAME __VA_OPT__(,) __VA_ARGS__)                       \
                                                                      \
    constexpr operator size_t() const { return numeric; }             \
    constexpr operator char const*() const { return stringy.data(); } \
private:                                                              \
    std::string_view stringy = #NAME"::INVALID";                      \
    size_t numeric = 0;                                               \
};

