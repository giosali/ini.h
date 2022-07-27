# Section::clear Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Removes all keys from the [Section](../section.md) instance.

## clear()

Removes all keys from the [Section](../section.md) instance.

!!! summary "clear()"

    ```cpp
    inline void Section::clear() noexcept
    ```

### Examples

The following example demonstrates how to remove all keys from a [Section](../section.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            std::cout << file["user info"].size() << std::endl; // 3
            file["user info"].clear();
            std::cout << file["user info"].size() << std::endl; // 0
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
        admin = John Appleseed
        login = finxter_freelancer
        password = freelancer_freedom
        ```