# File::empty Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Indicates whether the [File](../file.md) instance contains no sections.

## empty()

Indicates whether the [File](../file.md) instance contains no sections.

!!! summary "empty()"

    ```cpp
    inline bool File::empty() const noexcept
    ```

### Returns

[bool](https://en.cppreference.com/w/cpp/language/types)

`true` if the [File](../file.md) instance doesn't contain any sections; otherwise, `false`.

### Examples

The following example demonstrates how to determine if a [File](../file.md) instance is empty.

```cpp linenums="1" title="main.cpp"
#include <iostream>
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
    bool isEmpty = file.empty();
    if (isEmpty) {
        std::cout << "example.ini doesn't have any sections" << std::endl;
    } else {
        std::cout << "example.ini isn't empty" << std::endl;
    }
}
```