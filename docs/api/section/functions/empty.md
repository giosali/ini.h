# Section::empty Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Indicates whether the [Section](../section.md) instance contains no keys.

## empty()

Indicates whether the [Section](../section.md) instance contains no keys.

!!! summary "empty()"

    ```cpp
    inline bool Section::empty() const noexcept
    ```

### Returns

[bool](https://en.cppreference.com/w/cpp/language/types)

`true` if the [Section](../section.md) instance doesn't contain any keys; otherwise, `false`.

### Examples

The following example demonstrates how to determine if a [Section](../section.md) instance contains zero keys.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            std::cout << file["postgresql"].empty() << std::endl; // false
            std::cout << file["user info"].empty() << std::endl; // true
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

        [user info]
        ```