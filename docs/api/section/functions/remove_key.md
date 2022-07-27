# Section::remove_key Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Removes the specified key from the [Section](../section.md) instance.

## remove_key(const std::string&)

Removes the specified key from the [Section](../section.md) instance.

!!! summary "has_key(const std::string&)"

    ```cpp
    inline size_t Section::remove_key(const std::string& key)
    ```

### Parameters

`key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the key to remove.

### Returns

[size_t](https://en.cppreference.com/w/c/types/size_t)

The number of keys removed.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`key` does not exist.

### Examples

The following example demonstrates how to remove a key from a [Section](../section.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");

            // `section` must be a reference to a Section in order for
            // changes to be reflected in `file`.
            Section& section = file["postgresql"];
            std::cout << section.size() << std::endl; // 5

            size_t count = section.remove_key("password");
            std::cout << section.size() << std::endl; // 4
            std::cout << "count: " << count << std::endl; // 1
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