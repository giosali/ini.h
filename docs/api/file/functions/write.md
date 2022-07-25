# File::write Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Serializes the [File](../file.md) instance and writes it to the specified file path.

## write(const std::filesystem::path&)

Serializes the [File](../file.md) instance and writes it to the specified file path.

!!! summary "write(const std::filesystem::path&)"

    ```cpp
    inline void File::write(const std::filesystem::path& path) const
    ```

### Parameters

`path` [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path)

The destination path.

### Examples

The following example demonstrates how to serialize a [File](../file.md) instance and write it to a file.

```cpp linenums="1" title="main.cpp"
#include <fstream>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::ifstream stream("path/to/ini/example.ini");
    ini::File file = ini::load(stream);
    stream.close()

    ini::Section& section = file["Foo"];
    section["key1"] = "value1";
    section["key2"] = "value2";

    file.write("path/to/ini/example.ini");
}
```

### Remarks

The caller is responsible for ensuring that the parent directories of `path` exist.