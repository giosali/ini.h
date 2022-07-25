# ini::open Function

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

Opens, reads, and deserializes an INI file and returns a [File](./file/file.md) object.

## open(const std::filesystem::path&)

Opens, reads, and deserializes an INI file and returns a [File](./file/file.md) object.

!!! summary "open(const std::filesystem::path&)"

    ```cpp
    inline File open(const std::filesystem::path& path)
    ```

### Parameters

`path` [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path)

The path to an INI file.

### Returns

A [File](./file/file.md) object.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

The INI file is missing a section header.

-or-

The INI file contains duplicate keys in a section.

### Examples

The following example demonstrates how to read an INI file through a file path.

```cpp linenums="1" title="main.cpp"
#include <filesystem>
#include <string>
#include "ini.h"

int main(int argc, char* argv[])
{
    // Explicitly through a std::filesystem::path
    std::filesystem::path path("path/to/ini/example1.ini");
    ini::File file1 = ini::open(path);

    // Implicitly through a std::string
    ini::File file2 = ini::open("path/to/ini/example2.ini");
}
```