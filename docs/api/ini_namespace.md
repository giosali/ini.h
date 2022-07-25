# ini Namespace

Contains fundamental classes that represent the structure of an INI file and functions for reading INI files or [strings](https://cplusplus.com/reference/string/string/) containing valid INI input and for writing INI files.

## Classes

| Name                            | Description                            |
| :------------------------------ | :------------------------------------- |
| [File](./file/file.md)          | Represents an INI file.                |
| [Section](./section/section.md) | Represents the section of an INI file. |

## Functions

| Name | Description |
| :--- | :---------- |
| load(std::ifstream&) | Reads and deserializes an input stream of an INI file line by line and returns a [File](./file/file.md) object. |
| load(const std::string&) | Reads and deserializes a string and returns a [File](./file/file.md) object. |
| open(const std::filesystem::path&) | Opens, reads, and deserializes an INI file and returns a [File](./file/file.md) object. |