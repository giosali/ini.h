#include "ini.h"

#include "utest.h"
#include <fstream>
#include <stdexcept>
#include <string>

namespace load_stdIfstream {

namespace mustNotThrow {

    // Case
    // The stream is an input file stream of an INI file.
    UTEST(load_stdIfstream_mustNotThrow, inputFileStream)
    {
        std::ifstream stream("example.ini");
        ini::File file = ini::load(stream);
        stream.close();
    }

} // namespace mustNotThrow

namespace mustThrow {

    // Case
    // The file stream is closed before being processed.
    UTEST(load_stdIfstream_mustThrow, streamIsClosed)
    {
        std::ifstream stream;
        stream.close();
        ASSERT_EXCEPTION(ini::load(stream), std::invalid_argument);
    }

} // namespace mustThrow

} // namespace load_stdIfstream

namespace load_constStdString {

namespace mustNotThrow {

    // Case
    // Input consists of a single section.
    UTEST(load_constStdString_mustNotThrow, singleSection)
    {
        std::string text = "[Section]";
        ini::File file = ini::load(text);
    }

    // Case
    // Input consists of a single section and a few key-value pairs.
    UTEST(load_constStdString_mustNotThrow, single_section_and_key_value_pairs)
    {
        std::string text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
        ini::File file = ini::load(text);
    }

    // Case
    // Input consists of two different sections where both contain identical
    // key-value pairs.
    UTEST(load_constStdString_mustNotThrow, different_sections_identical_key_value_pairs)
    {
        std::string text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo\n[Section 2]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
        ini::File file = ini::load(text);
    }

    // Case
    // Input consists of multiple empty sections.
    UTEST(load_constStdString_mustNotThrow, multiple_empty_sections)
    {
        std::string text = "[Section 1]\n[Section 2]\n[Section 3]";
        ini::File file = ini::load(text);
    }

    // Case
    // Input contains whitespace on the left side of each line.
    UTEST(load_constStdString_mustNotThrow, whiteSpaceLeftSide)
    {
        std::string text = "     [Section]\n   key = value";
        ini::File file = ini::load(text);
    }

    // Case
    // Input contains whitespace on the right side of each line.
    UTEST(load_constStdString_mustNotThrow, whiteSpaceRightSide)
    {
        std::string text = "[Section]      \nkey = value        ";
        ini::File file = ini::load(text);
    }

    // Case
    // Input contains lines that are padded with whitespace on both sides.
    UTEST(load_constStdString_mustNotThrow, whiteSpaceBothSides)
    {
        std::string text = "      [Section]      \n      key = value       ";
        ini::File file = ini::load(text);
    }

} // namespace mustNotThrow

namespace mustThrow {

    // Case
    // Input contains a missing header.
    UTEST(load_constStdString_mustThrow, missingHeader)
    {
        std::string text = "key = value\nfoo = bar\n[Section]\nkey = value";
        ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
    }

    // Case
    // Input contains a section with duplicate keys.
    UTEST(load_constStdString_mustThrow, duplicate_keys)
    {
        std::string text = "[Section]\nkey = value\nkey = value";
        ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
    }

    // Case
    // Input contains an empty section.
    UTEST(load_constStdString_mustThrow, emptySection)
    {
        std::string text = "[]\nfoo = bar";
        ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);

        text = "[Section]\nfoo = bar\n\n[]\nfoo = bar";
        ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
    }

} // namespace mustThrow

namespace doesNotEndWithNewline {

    // Case
    // Section must be created if the input isn't terminated by a newline
    // character.
    UTEST(load_constStdString_doesNotEndWithNewline, section)
    {
        std::string text = "[Section]\nfoo = bar\n[Section 2]";
        ini::File file = ini::load(text);
        ASSERT_TRUE(file.has_section("Section 2"));
    }

    // Case
    // Key-value pair must be created if the input isn't terminated by
    // a newline character.
    UTEST(load_constStdString_doesNotEndWithNewline, key_value)
    {
        std::string text = "[Section]\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_TRUE(file["Section"]["foo"] == "bar");
    }

} // namespace doesNotEndWithNewline

} // namespace load_constStdString

namespace open_constStdFilesystemPath {

namespace mustNotThrow {

    // Case
    // Opening and reading an INI file.
    UTEST(open_constStdFilesystemPath_mustNotThrow, filesystemPath)
    {
        ini::File file = ini::open("example.ini");
    }

} // namespace mustNotThrow

} // namespace open_constStdFilesystemPath

namespace file {

namespace add_section_constStdString {

    // Case
    // Adds a section to the File instance.
    UTEST(add_section_constStdString, addsSection)
    {
        ini::File file = ini::open("example.ini");
        file.add_section("Bar");
        ASSERT_TRUE(file.has_section("Bar"));
    }

    // Case
    // Section name already exists.
    UTEST(add_section_constStdString_mustThrow, sectionAlreadyExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.add_section("Settings"), std::invalid_argument);
    }

} // namespace add_section_constStdString

namespace clear {

    // Case
    // There are zero sections remaining after using the clear function.
    UTEST(clear, fileIsEmpty)
    {
        ini::File file = ini::open("example.ini");
        file.clear();
        ASSERT_TRUE(file.empty());
    }

    // Case
    // Clearing an empty File instance should have no effect.
    UTEST(clear, emptyFile)
    {
        ini::File file = ini::load(std::string());
        file.clear();
        ASSERT_TRUE(file.empty());
    }

} // namespace clear

namespace empty {

    // Case
    // File instance contains sections.
    UTEST(empty, fileWithSections)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_FALSE(file.empty());
    }

    // Case
    // File instance is empty.
    UTEST(empty, emptyFile)
    {
        ini::File file = ini::load(std::string());
        ASSERT_TRUE(file.empty());
    }

} // namespace empty

namespace has_section_constStdString {

    // Case
    // The section name exists in the File instance.
    UTEST(has_section, sectionNameExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_TRUE(file.has_section("Foo"));
    }

    // Case
    // The section name doesn't exist in the File instance.
    UTEST(has_section, sectionNameDoesNotExist)
    {
        ini::File file = ini::load(std::string());
        ASSERT_FALSE(file.has_section("Foo"));
    }

    // Case
    // The section name is an empty string.
    UTEST(has_section, sectionNameIsEmpty)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_FALSE(file.has_section(std::string()));
    }

} // namespace has_section_constStdString

namespace rename_section_constStdString_constStdString {

    // Case
    // The old section name does not exist in the File instance.
    UTEST(rename_section_constStdString_constStdString, mustThrow_oldSectionNameDoesNotExist)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.rename_section("Bar", "bar"), std::invalid_argument);
    }

    // Case
    // The new section name already exists in the File instance.
    UTEST(rename_section_constStdString_constStdString, mustThrow_newSectionNameExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.rename_section("Settings", "Foo"), std::invalid_argument);
    }

} // namespace rename_section_constStdString_constStdString

} // namespace file