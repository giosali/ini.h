# File::remove_section Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Removes the specified section from the [File](../file.md) instance.

## remove_section(const std::string&)

Removes the specified section from the [File](../file.md) instance.

!!! summary "remove_section(const std::string&)"

    ```cpp
    inline size_t File::remove_section(const std::string& section_name)
    ```

### Parameters

`section_name` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

The name of the section to remove.

### Returns

[size_t](https://en.cppreference.com/w/c/types/size_t)

The number of sections removed.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`section_name` is empty.

-or-

`section_name` doesn't exist.

### Examples

The following example demonstrates how to remove a section from a [File](../file.md) instance.

```cpp linenums="1" title="main.cpp"
#include <fstream>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::ifstream stream("path/to/ini/example.ini");
    ini::File file = ini::load(stream);
    stream.close();

    try {
        size_t num = file.remove_section("Foo");
    } catch (std::invalid_argument) {
        // Handle exception.
    }

}
```