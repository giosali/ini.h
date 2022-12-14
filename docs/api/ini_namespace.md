# ini Namespace

Contains fundamental classes that represent the structure of an INI file and functions for reading INI files or [strings](https://en.cppreference.com/w/cpp/string/basic_string) containing valid INI input and for writing INI files.

## Classes

| Name                            | Description                            |
| :------------------------------ | :------------------------------------- |
| [File](./file/file.md)          | Represents an INI file.                |
| [Section](./section/section.md) | Represents the section of an INI file. |

## Functions

| Name | Description |
| :--- | :---------- |
| [load(std::ifstream&)](load.md#loadstdifstream) | Reads and deserializes an input stream of an INI file line by line and returns a [File](./file/file.md) object. |
| [load(const std::string&)](load.md#loadconst-stdstring) | Reads and deserializes a string and returns a [File](./file/file.md) object. |
| [open(const std::filesystem::path&)](open.md#openconst-stdfilesystempath) | Opens, reads, and deserializes an INI file and returns a [File](./file/file.md) object. |