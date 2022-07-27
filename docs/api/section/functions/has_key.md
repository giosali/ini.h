# Section::has_key Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Indicates whether the [Section](../section.md) instance contains a specified key.

## has_key(const std::string&)

Indicates whether the [Section](../section.md) instance contains a specified key.

!!! summary "has_key(const std::string&)"

    ```cpp
    inline bool Section::has_key(const std::string& key) const
    ```

### Parameters

`key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the key.

### Returns

[bool](https://en.cppreference.com/w/cpp/language/types)

`true` if `key` was found; otherwise, `false`.

### Examples

The following example demonstrates how to check if a [Section](../section.md) instance contains a specific key.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            bool foundKey = file["postgresql"].has_key("container");
            std::cout << foundKey << std::endl; // 0

            foundKey = file["postgresql"].has_key("host");
            std::cout << foundKey << std::endl; // 1
        }
        ```

    === "example.ini"
        ```ini linenums="1"
        [postgresql]
        host = localhost
        user = finxter1
        port = 5543
        password = myfinxterpw
        db = postgres
        ```