# enum library.

# installation

you may copy the files under LibEnum/include into your project, install it with [CPM](https://github.com/cpm-cmake/CPM.cmake) or install directly into your system with the following: 

* ``py install.py``

and then include it with cmake into your project

```cmake
cmake_minimum_required_version(VERSION 3.25)

project(CoolProject LANGUAGES CXX)

find_package(LibEnum CONFIG REQUIRED)
add_executable(CoolProject source.cpp)
target_link_libraries(CoolProject PRIVATE LibEnum::LibEnum)
```

# examples

```c++
#include <libenum/Enum.hpp>

#include <string_view>

ENUM_CLASS(HttpError,
    BAD_REQUEST,
    NOT_FOUND,
    OK
)

int main()
{
    static auto constexpr code = HttpError::from_string("OK");

    static_assert(code.to_string() == std::string_view("OK"));

    switch (code)
    {
    case HttpError::BAD_REQUEST:
    case HttpError::NOT_FOUND:
    case HttpError::OK: {
        std::println("{}", code.to_string());
        break;
    }
    }
}
```

i recommend you to simply explore the code and see what you can do with it. seriously. do it.
