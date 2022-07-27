# Section::size Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Returns the number of keys in the [Section](../section.md) instance.

## size()

Returns the number of keys in the [Section](../section.md) instance.

!!! summary "size()"

    ```cpp
    size_t Section::size() const noexcept
    ```

### Returns

[size_t](https://en.cppreference.com/w/cpp/types/size_t)

The number of keys in the [Section](../section.md) instance.

### Examples

The following example demonstrates how to determine the number of keys in a [Section](../section.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            std::cout << file["postgresql"].size() << std::endl; // 5
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