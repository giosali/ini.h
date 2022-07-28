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
| [add_section(const std::string&)](functions/add_section.md) | Adds a section to the [File](file.md) instance. |
| [clear()](functions/clear.md) | Removes all sections from the [File](file.md) instance. |
| [empty()](functions/empty.md) | Indicates whether the [File](file.md) instance contains no sections. |
| [has_section(const std::string&)](functions/has_section.md) | Indicates whether the [File](file.md) instance contains a specified section. |
| [remove_section(const std::string&)](functions/remove_section.md) | Removes the specified section from the [File](file.md) instance. |
| [rename_section(const std::string&, const std::string&)](functions/rename_section.md) | Renames the specified section in the [File](file.md) instance. |
| [size()](functions/size.md) | Returns the number of sections in the [File](file.md) instance. |
| [write(const std::filesystem::path&)](functions/write.md) | Serializes the [File](file.md) instance and writes it to the specified file path. |

## Operators

| Name | Description |
| :--- | :---------- |
| [operator[]](operators/operator[].md) | Gets or sets a section that corresponds to the specified section name. |