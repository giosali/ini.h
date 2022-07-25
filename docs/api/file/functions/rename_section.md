# File::rename_section Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Renames the specified section in the [File](file.md) instance.

## rename_section(const std::string&, const std::string&)

Renames the specified section in the [File](file.md) instance.

!!! summary "rename_section(const std::string&, const std::string&)"

    ```cpp
    inline void File::rename_section(const std::string& old_section_name, const std::string& new_section_name)
    ```

### Parameters

`old_section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the section whose name will be changed.

`new_section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The new name for the section.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`old_section_name` doesn't exist.

-or-

`new_section_name` already exists.

### Examples

The following example demonstrates how to change the name of a section of a [File](../file.md) instance.

```cpp linenums="1" title="main.cpp"
#include <iostream>
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
    file.add_section("Foo");
    ini::Section& section = file["Foo"];
    section["key"] = "value";

    // ...

    file.rename_section("Foo", "Bar");
    std::cout << file.has_section("Foo") << std::endl; // 0
    std::cout << file.has_section("Bar") << std::endl; // 1
    std::cout << file["Bar"]["key"] << std::endl; // value
}
```