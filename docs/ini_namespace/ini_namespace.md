# ini Namespace

Contains fundamental classes that represent the structure of an INI file and functions for reading INI files or [strings](https://cplusplus.com/reference/string/string/) containing valid INI input and for writing INI files.

## Functions

| Name                               | Description                          |
| :--------------------------------- | :----------------------------------- |
| load(std::ifstream&)               | Reads and deserializes an input stream to an INI file line by line and returns a File object. |
| load(const std::string&)           | Reads and deserializes a string and returns a File object. |
| open(const std::filesystem::path&) | Opens, reads, and deserializes an INI file and returns a File object. |

## Classes

| Name    | Description                            |
| :------ | :------------------------------------- |
| File    | Represents an INI file.                |
| Section | Represents the section of an INI file. |