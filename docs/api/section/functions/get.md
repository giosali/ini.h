# Section::get Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Gets a value from the [Section](../section.md) instance that is converted to the specified type before being returned.

## get<T\>(const std::string&)

Gets a value from the [Section](../section.md) instance that is converted to the specified type before being returned.

!!! summary "get<T>(conststd::string&)"

    ```cpp
    template <typename T>
    inline T Section::get(const std::string& key) const
    ```

### Type Parameters

`T`

The type of the value to retrieve.

### Parameters

`key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The key of the value.

### Returns

`T`

A value of type `T`.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

The type `T` is unsupported.

### Examples

The following example demonstrates how to retrieve a value from a [Section](../section.md) instance of a specified type.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include <string>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            
            // bool
            bool isUp = file["Database"].get<bool>("is_up");
            if (isUp) {
                // ...
            }

            // int
            int port = file["Database"].get<int>("port");

            // double
            double pi = file["Database"].get<double>("pi");

            // size_t
            size_t timeout = file["Database"].get<size_t>("timeout");

            // std::string
            std::string name = file["Owner"]["name"]
            std::string organization = file["Owner"].get<std::string>("organization");
            std::cout << "name: " << name << std::endl // John Appleseed
                      << "organization: " << organization << std::endl; // F.B. Widgets Inc.
        }
        ```

    === "example.ini"
        ```ini linenums="1"
        [Owner]
        name = John Appleseed
        organization = F.B. Widgets Inc.

        [Database]
        server = 192.0.2.62
        port = 143
        timeout = 10000
        pi = 3.14159265359
        is_up = True
        ```

### Remarks

!!! note "Currently Supported Types"

    The following is a list of types that are supported by the [get](get.md) function.

    - [x] [bool](https://en.cppreference.com/w/cpp/language/types)
    - [x] [int](https://en.cppreference.com/w/cpp/language/types)
    - [x] [float](https://en.cppreference.com/w/cpp/language/types)
    - [x] [double](https://en.cppreference.com/w/cpp/language/types)
    - [x] [size_t](https://en.cppreference.com/w/c/types/size_t)
    - [x] [std::size_t](https://en.cppreference.com/w/cpp/types/size_t)
    - [x] [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

#### std::string

Although [get](get.md) supports [std::string](https://en.cppreference.com/w/cpp/string/basic_string), the caller should opt to use the subscript operator instead. It's much simpler (*and more efficient*) to do:

```cpp
ini::File file;
std::string str = file["Section"]["key"];
```

than:

```cpp
ini::File file;
std::string str = file["Section"].get<std::string>("key");
```