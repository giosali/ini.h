# Section::rename_key Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Renames the specified key in the [Section](../section.md) instance.

## rename_key(const std::string&, const std::string&)

Renames the specified key in the [Section](../section.md) instance.

!!! summary "rename_key(const std::string&, const std::string&"

    ```cpp
    inline void Section::rename_key(const std::string& old_key, const std::string& new_key)
    ```

### Parameters

`old_key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The key whose name will be replaced.

`new_key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The new name for the key.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`old_key` or `new_key` is empty.

-or-

`old_key` doesn't exist.

-or-

`new_key` already exists.

### Examples

The following example demonstrates how to change the name of a key in a [Section](../section.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            ini::Section& section = file["postgresql"];
            section.rename_key("password", "nothing to see here");

            std::cout << file["postgresql"].has_key("password") << std::endl; // 0
            std::cout << file["postgresql"].has_key("nothing to see here") << std::endl; // 1
            std::cout << file["postgresql"]["nothing to see here"] << std::endl; // myfinxterpw
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