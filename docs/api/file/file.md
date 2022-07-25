# File Class

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

Represents an INI file.

!!! summary "File class"

    ```cpp
    class File
    ```

## Constructors

| Constructor | Description |
| :---------- | :---------- |
| [File()](constructors.md#file) | Initializes an instance of the [File](file.md) class. |
| [File(std::ifstream&)](constructors.md#filestdifstream) | Initializes an instance of the [File](file.md) class and reads and deserializes an input file stream. |
| [File(const std::string&)](constructors.md#fileconst-stdstring) | Initializes an instance of the [File](file.md) class and deserializes a [string](https://en.cppreference.com/w/cpp/string/basic_string). |

## Functions

| Name | Description |
| :--- | :---------- |
| add_section(const std::string&) | Adds a section to the [File](file.md) instance. |
| clear() | Removes all sections from the [File](file.md) instance. |
| empty() | Indicates whether the [File](file.md) instance contains no sections. |
| has_section(const std::string&) | Indicates whether the [File](file.md) instance contains a specified section. |
| remove_section(const std::string&) | Removes the specified section from the [File](file.md) instance. |
| rename_section(const std::string&, const std::string&) | Renames the specified section in the [File](file.md) instance. |
| size() const noexcept | Returns the number of sections in the [File](file.md) instance. |
| write(const std::filesystem::path&) | Serializes the [File](file.md) instance and writes it to the specified file path. |