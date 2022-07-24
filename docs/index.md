# ini.h

## Overview

`ini.h` is a single-header library for reading and writing INI files in C++. You can easily retrieve and manipulate values from INI files through a simple and intuitive API.

`ini.h` is compatible with **C++17** or higher.

## Usage

!!! example "Basic Example"

    === "main.cpp"
        ```cpp
        #include <iostream>
        #include <string>
        #include "ini.h"

        int main(int argc, char* argv[])
        {
            // Reading an INI file.
            ini::File file("/path/to/ini/example.ini");

            // Getting values from an INI file.
            std::string title = file["File1"]["title"];
            std::cout << "Title: " << title << std::endl;

            int word_count = file["File1"].get<int>("wordCount");
            double line_spacing = file["File1"].get<double>("lineSpacing");
            std::cout << "Word count: " << word_count << std::endl;
            std::cout << "Line spacing: " << line_spacing << std::endl;

            // Setting values of an INI file.
            ini::Section& section = file["Settings"];
            section["runAtStartup"] = "false";

            file["Settings"].set<bool>("saveOnExit", true);

            // Writing to an INI file.
            file.write("/path/to/ini/example.ini");
        }
        ```

    === "example.ini"
        ```ini
        [Settings]
        runAtStartup = true
        saveOnExit = false
        maxOpenFiles = 5

        [File1]
        title = On the topic of C++
        author = John Appleseed
        lastDateOpened = 2022-07-24
        autoSaveEnabled = true
        wordCount = 0
        lineSpacing = 1.5
        ```