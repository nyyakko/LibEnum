#pragma once

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(MACRO, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(MACRO, __VA_ARGS__)))

#define FOR_EACH_HELPER(MACRO, a1, a2, ...)                         \
  MACRO(a1, a2)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (MACRO, a1, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER

