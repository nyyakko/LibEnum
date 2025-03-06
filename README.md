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

    switch ()
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

using [LibError](https://github.com/nyyakko/liberror):

```c++
#include <libenum/Enum.hpp>
#include <liberror/Try.hpp>
#include <liberror/Result.hpp>

ENUM_CLASS(HttpStatus,
    BAD_REQUEST,
    NOT_FOUND,
    OK
)

using namespace liberror;

class [[nodiscard]] HttpError
{
public:
    using message_t = HttpStatus;

    constexpr explicit HttpError(HttpStatus message) : message_m { message } {}

    constexpr  HttpError() noexcept = default;
    constexpr ~HttpError() noexcept = default;

    constexpr HttpError(HttpError const& error) : message_m { error.message_m } {}
    constexpr HttpError(HttpError&& error) noexcept : message_m { std::move(error.message_m) } {}

    constexpr HttpError& operator=(HttpError&& error) noexcept
    {
        message_m = std::move(error.message_m);
        return *this;
    }

    constexpr HttpError& operator=(HttpError const& error)
    {
        message_m = error.message_m;
        return *this;
    }

    [[nodiscard]] constexpr auto const& message() const noexcept { return message_m; }

private:
    HttpStatus message_m;
};

Result<int, HttpError> http_work()
{
    return make_error<HttpError>(HttpStatus::BAD_REQUEST);
}

int main()
{
    auto result = http_work();

    if (!result.has_value())
    {
        fmt::println("{}", result.error().message().to_string());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

i recommend you to simply explore the code and see what you can do with it. seriously. do it.
