# ini.h

## Overview

`ini.h` is a header-only library for reading and writing INI files in C++ through a simple, intuitive API.

!!! settings "Prerequisites"

    `ini.h` is only compatible with **C++17** or higher.

## Usage

### Reading and Writing

!!! example "Reading an INI file"

    There are two ways to read and parse the contents of an INI file:

    1. Through a file path
    2. Through a file stream

    === "File Path"

        === "main.cpp"
            ```cpp linenums="1" hl_lines="5"
            #include "ini.h"

            int main(int argc, char* argv[])
            {
                ini::File file = ini::open("path/to/ini/example.ini");
            }
            ```

    === "File Stream"

        === "main.cpp"
            ```cpp linenums="1" hl_lines="7 10"
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

        !!! warning "Close the File Stream"
        
            Don't forget to close the file stream. You are responsible for closing it.

!!! example "Writing to an INI File"

    === "main.cpp"
        ```cpp linenums="1" hl_lines="10"
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

!!! example "Getting Values"

    === "main.cpp"
        ```cpp linenums="1" hl_lines="7-10"
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

    === "example.ini"
        ```ini linenums="1"
        [FileInfo]
        title = On the topic of C++
        author = John Appleseed
        lastDateOpened = 2022-07-24
        autoSaveEnabled = true
        wordCount = 0
        lineSpacing = 1.5
        ```

!!! example "Setting Values"

    === "main.cpp"
        ```cpp linenums="1" hl_lines="7-10"
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

    === "example.ini"
        ```ini linenums="1"
        [FileInfo]
        title = On the topic of C++
        author = John Appleseed
        lastDateOpened = 2022-07-24
        autoSaveEnabled = true
        wordCount = 0
        lineSpacing = 1.5
        ```

## Features

!!! settings "List of Features"

    - [x] **Comments**

        - `; comment text`
        - `# comment text`

        !!! note

            Comments must start at the beginning of a line.

    - [x] **Case Sensitivity**
        
        !!! note

            Section names and keys are case-sensitive.

        !!! example

            ```ini linenums="1"
            [SECTION]
            key = value
            KEY = value

            [section]
            key = value
            KEY = value
            ```
    
    - **Delimiters**:
    
        - [x] `=`
        - [x] `:`

        !!! example

            ```ini
            [Section]
            key1 = value
            key2 : value
            ```

    - **Supported Value Types**:

        - [x] [int](https://en.cppreference.com/w/cpp/language/types)
        - [x] [float](https://en.cppreference.com/w/cpp/language/types)
        - [x] [double](https://en.cppreference.com/w/cpp/language/types)
        - [x] [size_t](https://en.cppreference.com/w/c/types/size_t)
        - [x] [std::size_t](https://en.cppreference.com/w/cpp/types/size_t)
        - [x] [std::string](https://en.cppreference.com/w/cpp/string/basic_string)