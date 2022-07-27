# File::set Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Sets the specified value in the [Section](../section.md) instance based on the specified key and converts it to a [string](https://en.cppreference.com/w/cpp/string/basic_string).

## set<T\>(const std::string&, const T&)

Sets the specified value in the [Section](../section.md) instance based on the specified key and converts it to a [string](https://en.cppreference.com/w/cpp/string/basic_string).

!!! summary "set<T\>(const std::string&, const T&)"

    ```cpp
    template <typename T>
    inline void Section::set(const std::string& key, const T& value)
    ```

### Type Parameters

`T`

The type of the value that will be converted to a [string](https://en.cppreference.com/w/cpp/string/basic_string) and then inserted into the [Section](../section.md) instance.

### Parameters

`key` [string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the key whose value will be set.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

The type `T` is unsupported.

### Examples

The following example demonstrates how to set the value of an existing key of a [Section](../section.md) instance.

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
            file["Database"].set<bool>("is_up", false);

            // int
            int port = 144;
            file["Database"].set<int>("port", port);

            // std::string
            std::string new_name = "Johnny Appleseed";
            file["Owner"].set<std::string>("name", new_name);
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

The [set](set.md) function can also be used to create a key-value pair in a [Section](../section.md) instance.

!!! example "Example 2"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include <string>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            file["Owner"].set<std::string>("dob", "Jan. 24, 1984");
            std::cout << file["Owner"]["dob"] << std::endl; // Jan. 24, 1984
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