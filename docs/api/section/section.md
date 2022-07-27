# Section Class

## Definition

~Namespace:~ ~[ini](../ini_namespace.md)~

Represents a section of an INI file.

!!! summary "Section class"

    ```cpp
    class Section
    ```

## Constructors

| Constructor | Description |
| :---------- | :---------- |
| [Section()](constructors.md#section) | Initializes an instance of the [Section](section.md) class. |

## Functions

| Name| Description |
| :-- | :---------- |
| [clear()](functions/clear.md) | Removes all keys from the [Section](section.md) instance. |
| [empty()](functions/empty.md) | Indicates whether the [Section](section.md) instance contains no keys. |
| [get<T>(const std::string&)](functions/get) | Gets a value from the [Section](section.md) instance that is converted to the specified type before being returned. |
| [has_key(const std::string&)](functions/has_key.md) | Indicates whether the [Section](section.md) instance contains a specified key. |
| [remove_key(const std::string&)](functions/remove_key.md) | Removes the specified key from the [Section](section.md) instance. |
| [rename_key(const std::string&, const std::string&)](functions/rename_key.md) | Renames the specified key in the [Section](section.md) instance. |
| [size()](functions/size.md) | Returns the number of keys in the [Section](section.md) instance. |
| [set<T>(const std::string&, const T&)](functions/set.md) | Sets the specified value in the [Section](section.md) instance based on the specified key and converts it to a [string](https://en.cppreference.com/w/cpp/string/basic_string). |