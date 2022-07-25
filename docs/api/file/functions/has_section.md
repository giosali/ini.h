# File::has_section Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Indicates whether the [File](../file.md) instance contains a specified section.

## has_section(const std::string&)

Indicates whether the [File](../file.md) instance contains a specified section.

!!! summary "has_section(const std::string&)"

    ```cpp
    inline bool File::has_section(const std::string& section_name) const
    ```

### Parameters

`section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of a section.

### Returns

`true` if `section_name` was found; otherwise, `false`.

### Examples

The following example demonstrates how to determine if a [File](../file.md) contains a section name.

```cpp linenums="1" title="main.cpp"
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
    bool contains_section_name = file.has_section("Settings");
    std::cout << "Section name exists: " << contains_section_name << std::endl;
}
```