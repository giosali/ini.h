# Section Class

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

Represents a section of an INI file.

!!! summary "File class"

    ```cpp
    class Section
    ```

## Constructors

| Constructor | Description                                                 |
| :---------- | :---------------------------------------------------------- |
| Section()   | Initializes an instance of the [Section](section.md) class. |

# Functions

| Name                        | Description                                                            |
| :-------------------------- | :--------------------------------------------------------------------- |
| clear()                     | Removes all keys from the [Section](section.md) instance.              |
| empty()                     | Indicates whether the [Section](section.md) instance contains no keys. |
| has_key(const std::string&) | Indicates whether the [Section](section.md) instance contains a specified key. |
| remove_key(const std::string&) | Removes the specified key from the [Section](section.md) instance. |
| rename_key(const std::string&, const std::string&) | Renames the specified key in the [Section](section.md) instance. |
| size() | Returns the number of keys in the [Section](section.md) instance. |
| get<T>(const std::string&) | Gets a value from the [Section](section.md) instance that is converted to the specified type before being returned. |
| set<T>(const std::string&, const T&) | Sets the specified value in the [Section](section.md) instance based on the specified key and converts it to a [string](https://cplusplus.com/reference/string/string/). |