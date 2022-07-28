# File::operator[]

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Gets or sets a section that corresponds to the specified section name.

!!! summary "operator[]"

    ```cpp
    inline Section& File::operator[](const std::string& section_name)
    ```

## Parameters

`section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The section name that may exist in the [File](../file.md) instance.

## Returns

[Section](../../section/section.md)

A reference to a section that corresponds to `section_name`.

## Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`section_name` is empty.

## Examples

The following example demonstrates how to retrieve a [Section](../../section/section.md) object from a [File](../file.md) instance.

!!! example "Example 1"

    === "main.cpp"
        ```cpp linenums="1"
        #include <iostream>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            ini::File file = ini::open("example.ini");
            ini::Section& database = file["Database"]
            std::cout << database["server"] << std::endl; // 192.0.2.62
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

If `section_name` does not exist in the [File](../file.md) instance, it will be automatically created. For example, if you attempt to get a value that doesn't exist, that key will be added to the [File](../file.md).