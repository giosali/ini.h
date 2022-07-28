# Section::operator[]

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Gets or sets a value that corresponds to the specified key.

!!! summary "operator[]"

    ```cpp
    inline std::string& Section::operator[](const std::string& key)
    ```

## Parameters

`key` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The key that may exist in the [Section](../section.md) instance.

## Returns

[std::string](https://en.cppreference.com/w/cpp/string/basic_string)

A reference to a string that corresponds to `key`.

## Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`key` is empty.

## Examples

The following example demonstrates how to retrieve a value from a [Section](../section.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include <string>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            ini::Section& database = file["Database"]
            std::cout << database["server"] << std::endl; // 192.0.2.62
            std::cout << database["port"] << std::endl; // 143
            std::cout << database["timeout"] << std::endl; // 10000
            std::cout << database["pi"] << std::endl; // 3.14159265359
            std::cout << database["is_up"] << std::endl; // True

            // Assigns the value to a string.
            std::string server = file["Section"]["server"];
            std::cout << server << std::endl; // 192.0.2.62
        }
        ```

    === "example.ini"
        ```ini linenums="1"
        [Database]
        server = 192.0.2.62
        port = 143
        timeout = 10000
        pi = 3.14159265359
        is_up = True
        ```

Additionally, [operator[]](operator[].md) can be used to set values.

!!! example "Example 2"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include <string>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            ini::Section& database = file["Section"];

            // Changes value.
            database["port"] = "144";

            // Creates new key-value pair.
            database["is_down"] = "False";

            std::cout << file["Section"]["is_down"] << std::endl; // False
        }
        ```

    === "example.ini"
        ```ini linenums="1"
        [Database]
        server = 192.0.2.62
        port = 143
        timeout = 10000
        pi = 3.14159265359
        is_up = True
        ```

## Remarks

If `key` does not exist in the [Section](../section.md) instance, it will be automatically created. For example, if you attempt to get a value that doesn't exist, that key will be added to the [Section](../section.md).