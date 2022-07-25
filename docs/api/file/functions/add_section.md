# File::add_section Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Adds a section to the [File](../file.md) instance.

## add_section(const std::string&)

Adds a section to the [File](../file.md) instance.

!!! summary "add_section(const std::string&)"

    ```cpp
    inline void File::add_section(const std::string& section_name)
    ```

### Parameters

`section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the section that will be added.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

A section with the same name already exists.

### Examples

The following example demonstrates how to add a section to a [File](../file.md) instance.

```cpp linenums="1" title="main.cpp"
#include <string>
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
    file.add_section("New Section");

    // Now we can retrieve an instance of the newly created section.
    ini::Section& section = file["New Section"];
}
```