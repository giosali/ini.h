# File Constructors

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

Initializes an instance of the [File](file.md) class.

## Overloads

| Constructor | Description |
| :---------- | :---------- |
| [File()](constructors.md#file) | Initializes an instance of the [File](file.md) class. |
| [File(std::ifstream&)](constructors.md#filestdifstream) | Initializes an instance of the [File](file.md) class and reads and deserializes an input file stream. |
| [File(const std::string&)](constructors.md#fileconst-stdstring) | Initializes an instance of the [File](file.md) class and deserializes a [string](https://en.cppreference.com/w/cpp/string/basic_string). |

## Remarks

These constructors are not intended to be used directly by the caller. The caller should rely on the [load](../load.md) and [open](../open.md) functions instead.

## File()

Initializes an instance of the [File](file.md) class.

!!! summary "File()"

    ```cpp
    inline File::File()
    ```

## File(std::ifstream&)

Initializes an instance of the [File](file.md) class and reads and deserializes an input file stream.

!!! summary "File(std::ifstream&)"

    ```cpp
    inline File::File(std::ifstream& stream)
    ```

### Parameters

`stream` [std::ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream)

The input file stream of an INI file.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

`stream` is closed.

-or-

The INI file is missing a section header.

-or-

The INI file contains an empty section header.

-or-

The INI file contains duplicate keys in a section.

## File(const std::string&)

Initializes an instance of the [File](file.md) class and deserializes a [string](https://en.cppreference.com/w/cpp/string/basic_string).

!!! summary "File(const std::string&)"

    ```cpp
    inline File::File(const std::string& text)
    ```

### Parameters

`text` [std::string](https://en.cppreference.com/w/cpp/string/basic_string)

A string that contains an INI-like structure.

### Exceptions

[std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument)

The INI file is missing a section header.

-or-

The INI file contains an empty section header.

-or-

The INI file contains duplicate keys in a section.