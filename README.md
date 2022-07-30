<h1 align="center">ini.h</h1>

<div align="center">
    <picture>
        <source media="(prefers-color-scheme: dark)"
                srcset="https://raw.githubusercontent.com/giosali/ini.h/main/ext/logo-dark.png">
        <source media="(prefers-color-scheme: light)"
                srcset="https://raw.githubusercontent.com/giosali/ini.h/main/ext/logo-light.png">
        <img src="https://raw.githubusercontent.com/giosali/ini.h/main/ext/logo-dark.png"
             alt="Logo"
             width="175">
    </picture>
</div>

<p align="center">
    <a href="https://github.com/giosali/ini.h/releases">
        <img src="https://img.shields.io/github/v/release/giosali/ini.h"
             alt="Release Version">
    </a>
    <a href="https://github.com/giosali/ini.h/blob/main/LICENSE">
        <img src="https://img.shields.io/github/license/giosali/ini.h"
             alt="MIT License">
    </a>
</p>

<p align="center">
    <a href="https://github.com/giosali/ini.h/actions/workflows/windows.yml">
        <img src="https://github.com/giosali/ini.h/actions/workflows/windows.yml/badge.svg"
             alt="Windows Build">
    </a>
    <a href="https://github.com/giosali/ini.h/actions/workflows/macos.yml">
        <img src="https://github.com/giosali/ini.h/actions/workflows/macos.yml/badge.svg"
             alt="macOS Build">
    </a>
    <a href="https://github.com/giosali/ini.h/actions/workflows/ubuntu.yml">
        <img src="https://github.com/giosali/ini.h/actions/workflows/ubuntu.yml/badge.svg"
             alt="Ubuntu Build">
    </a>
</p>

<p align="center">
    <b>ini.h</b> is a header-only library for reading and writing INI files in C++ through a simple, intuitive API.
</p>

## Intro

To start using **ini.h**, copy the single header file and drop it into your project. Now you can use the library by adding the following directive: 

```cpp
#include "ini.h"
```

### Prerequisites

* C++17 or higher

## Usage

### Reading and Writing INI Files

There are two ways to read and parse INI files with **ini.h**:

1. Through a file path
2. Through a file stream

<p align="center">
    <b>File Path</b>
</p>

```cpp
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");
}
```

<p align="center">
    <b>File Stream</b>
</p>

```cpp
#include <fstream>
#include "ini.h"

int main(int argc, char* argv[])
{
    std::ifstream stream("path/to/ini/example.ini");
    ini::File file = ini::load(stream);

    // You are responsible for closing the file stream.
    stream.close();
}
```

As for writing, simply pass the destination path to the `write` function.

<p align="center">
    <b>Writing to an INI File</b>
</p>

```cpp
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");

    file.add_section("New Section");
    file["New Section"]["is_generic_key"] = "true";

    file.write("path/to/ini/example.ini");
}
```

### Getting and Setting Values

You can retrieve values by using the operator[] but this will only return a string value. If you need a value in the form of a bool, for example, you can do so by using the `get` function.

<p align="center">
    <b>Getting Values</b>
</p>

```cpp
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");

    std::string title = file["FileInfo"]["title"];
    bool auto_save_enabled = file["FileInfo"].get<bool>("autoSaveEnabled"):
    size_t word_count = file["FileInfo"].get<size_t>("wordCount");
    double line_spacing = file["FileInfo"].get<double>("lineSpacing");
}
```

<p align="center">
    <b>example.ini</b>
</p>

```ini
[FileInfo]
title = On the topic of C++
author = John Appleseed
lastDateOpened = 2022-07-24
autoSaveEnabled = true
wordCount = 0
lineSpacing = 1.5
```

Setting values with can also be done with the subscript operator but this requires a string representation of the value you're trying to set.

If you already have a `bool`, a `double`, etc., you can simply use the `set` function. Those values will automatically be converted into a string representation for you.

<p align="center">
    <b>Setting Values</b>
</p>

```cpp
#include "ini.h"

int main(int argc, char* argv[])
{
    ini::File file = ini::open("path/to/ini/example.ini");

    file["FileInfo"]["title"] = "On the topic of C#";
    file["FileInfo"].set<bool>("autoSaveEnabled", false);
    file["FileInfo"].set<size_t>("wordCount", 1);
    file["FileInfo"].set<double>("lineSpacing", 2.0);
}
```

<p align="center">
    <b>example.ini</b>
</p>

```ini
[FileInfo]
title = On the topic of C++
author = John Appleseed
lastDateOpened = 2022-07-24
autoSaveEnabled = true
wordCount = 0
lineSpacing = 1.5
```

## Features

### Comments

- `; comment text`
- `# comment text`

> ℹ️ Comments must start at the beginning of a line.

### Case Sensitivity

Section names and keys are case-sensitive.

<p align="center">
    <b>example.ini</b>
</p>

```ini
[SECTION]
key = value
KEY = value

[section]
key = value
KEY = value
```

### Delimiters

- `=`
- `:`

<p align="center">
    <b>example.ini</b>
</p>

 ```ini
[Section]
key1 = value
key2 : value
```

### Supported Value Types

- [x] [int](https://en.cppreference.com/w/cpp/language/types)
- [x] [float](https://en.cppreference.com/w/cpp/language/types)
- [x] [double](https://en.cppreference.com/w/cpp/language/types)
- [x] [size_t](https://en.cppreference.com/w/c/types/size_t)
- [x] [std::size_t](https://en.cppreference.com/w/cpp/types/size_t)
- [x] [std::string](https://en.cppreference.com/w/cpp/string/basic_string)