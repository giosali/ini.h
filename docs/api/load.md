# ini::load Function

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

## Overloads

| Name  | Description |
| :---- | :---------- |
| [load(std::ifstream&)](load.md#loadstdifstream) | Reads and deserializes an input stream of an INI file line by line and returns a [File](./file/file.md) object. |
| [load(const std::string&)](load.md#loadconst-stdstring) | Reads and deserializes a string and returns a [File](./file/file.md) object. |

## load(std::ifstream&)

Reads and deserializes an input stream of an INI file line by line and returns a [File](./file/file.md) object.

!!! summary "load(std::ifstream&)"

    ```cpp
    inline File load(std::ifstream& stream)
    ```

### Parameters

`stream` [std::ifstream](https://cplusplus.com/reference/fstream/ifstream/)

The input stream of an INI file.

### Returns

A [File](./file/file.md) object.

### Exceptions

[std::invalid_argument](https://cplusplus.com/reference/stdexcept/invalid_argument/)

`stream` is closed.

-or-

The INI file is missing a section header.

-or-

The INI file contains duplicate keys in a section.

### Examples

The following example demonstrates how to read an INI file using a file stream.

```cpp linenums="1" title="main.cpp"
#include <fstream>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::ifstream stream("path/to/ini/example.ini");
    ini::File file(stream);
    stream.close();
}
```

### Remarks

The caller is responsible for closing `stream`.

## load(const std::string&)

!!! summary "load(const std::string&)"

    ```cpp
    inline File load(const std::string& text)
    ```

### Parameters

`text` [std::string](https://cplusplus.com/reference/string/string/)

A string that contains an INI-like structure.

### Returns

A [File](./file/file.md) object.

### Exceptions

[std::invalid_argument](https://cplusplus.com/reference/stdexcept/invalid_argument/)

The INI file is missing a section header.

-or-

The INI file contains duplicate keys in a section.

### Examples

The following example demonstrates how to read a [string](https://cplusplus.com/reference/string/string/).

```cpp linenums="1" title="main.cpp"
#include <string>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::string text = "[Settings]\nrunAtStartup = true\nisAutoSaveEnabled = false\n[Random]\nhello = world\npi = 3.14\nsentence = This is a long sentence; unfortunately, newlines don't work in values when the input is a string instead of an input stream :(";
    ini::File file(text);
}
```

### Remarks

`text` will break the deserialization process if it contains newlines in the values. For example, a [string](https://cplusplus.com/reference/string/string/) that resembles the following will be problematic:

```ini
[Section Header]
genericKey = This is the first line\nThis is the second line\nThis is the third line
```

The newlines in the value that corresponds to "genericKey" will cause an issue for the algorithm responsible for parsing INI files. This is only the case for this overload of the [load](load.md) function.