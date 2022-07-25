# File::clear Function

## Definition

~Namespace:~ ~[ini](../../ini_namespace.md)~

Removes all sections from the [File](../file.md) instance.

## clear()

Removes all sections from the [File](../file.md) instance.

!!! summary "clear()"

    ```cpp
    inline void File::clear() noexcept
    ```

### Examples

The following example demonstrates how to remove all sections from a [File](../file.md) instance.

```cpp linenums="1" title="main.cpp"
#include <fstream>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::ifstream stream("path/to/ini/example.ini");
    ini::File file = ini::load(stream);
    stream.close();

    file.clear();
}
```