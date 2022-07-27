## File::size Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Returns the number of sections in the [File](../file.md) instance.

## size()

Returns the number of sections in the [File](../file.md) instance.

!!! summary "size()"

    ```cpp
    inline size_t File::size() const noexcept
    ```

### Returns

[size_t](https://en.cppreference.com/w/cpp/types/size_t)

The number of sections in the [File](../file.md) instance.

### Examples

The following example demonstrates how to retrieve the number of sections in a [File](../file.md) instance.

```cpp linenums="1" title="main.cpp"
#include <iostream>
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
    size_t count = file.size();
    std::cout << "Count: " << count << std::endl;
}
```