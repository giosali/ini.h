#include "ini.h"

#include "utest.h"
#include <fstream>
#include <stdexcept>
#include <string>

namespace load_stdIfstream {

// Case
// The stream is an input file stream of an INI file.
UTEST(load_stdIfstream, mustNotThrow_inputFileStream)
{
    std::ifstream stream("example.ini");
    ini::File file = ini::load(stream);
    stream.close();
}

// Case
// The file stream is closed before being processed.
UTEST(load_stdIfstream, mustThrow_streamIsClosed)
{
    std::ifstream stream;
    stream.close();
    ASSERT_EXCEPTION(ini::load(stream), std::invalid_argument);
}

} // namespace load_stdIfstream

namespace load_constStdString {

// Case
// Input consists of a single section.
UTEST(load_constStdString, mustNotThrow_singleSection)
{
    std::string text = "[Section]";
    ini::File file = ini::load(text);
}

// Case
// Input consists of a single section and a few key-value pairs.
UTEST(load_constStdString, mustNotThrow_singleSectionAndKeyValuePairs)
{
    std::string text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
    ini::File file = ini::load(text);
}

// Case
// Input consists of two different sections where both contain identical
// key-value pairs.
UTEST(load_constStdString, mustNotThrow_differentSectionsIdenticalKeyValuePairs)
{
    std::string text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo\n[Section 2]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
    ini::File file = ini::load(text);
}

// Case
// Input consists of multiple empty sections.
UTEST(load_constStdString, mustNotThrow_multipleEmptySections)
{
    std::string text = "[Section 1]\n[Section 2]\n[Section 3]";
    ini::File file = ini::load(text);
}

// Case
// Input contains whitespace on the left side of each line.
UTEST(load_constStdString, mustNotThrow_whiteSpaceLeftSide)
{
    std::string text = "     [Section]\n   key = value";
    ini::File file = ini::load(text);
}

// Case
// Input contains whitespace on the right side of each line.
UTEST(load_constStdString, mustNotThrow_whiteSpaceRightSide)
{
    std::string text = "[Section]      \nkey = value        ";
    ini::File file = ini::load(text);
}

// Case
// Input contains lines that are padded with whitespace on both sides.
UTEST(load_constStdString, mustNotThrow_whiteSpaceBothSides)
{
    std::string text = "      [Section]      \n      key = value       ";
    ini::File file = ini::load(text);
}

// Case
// Input contains a missing header.
UTEST(load_constStdString, mustThrow_missingHeader)
{
    std::string text = "key = value\nfoo = bar\n[Section]\nkey = value";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
}

// Case
// Input contains a section with duplicate keys.
UTEST(load_constStdString, mustThrow_duplicateKeys)
{
    std::string text = "[Section]\nkey = value\nkey = value";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
}

// Case
// Input contains an empty section.
UTEST(load_constStdString, mustThrow_emptySection)
{
    std::string text = "[]\nfoo = bar";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);

    text = "[Section]\nfoo = bar\n\n[]\nfoo = bar";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
}

// Case
// Input contains an empty key in a section.
UTEST(load_constStdString, mustThrow_emptyKey)
{
    std::string text = "[Section]\n= bar\nhello = world";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
}

// Case
// Section must be created if the input isn't terminated by a newline
// character.
UTEST(load_constStdString, sectionDoesNotEndWithNewline)
{
    std::string text = "[Section]\nfoo = bar\n[Section 2]";
    ini::File file = ini::load(text);
    ASSERT_TRUE(file.has_section("Section 2"));
}

// Case
// Key-value pair must be created if the input isn't terminated by
// a newline character.
UTEST(load_constStdString, keyValueDoesNotEndWithNewline)
{
    std::string text = "[Section]\nfoo = bar";
    ini::File file = ini::load(text);
    ASSERT_TRUE(file["Section"]["foo"] == "bar");
}

} // namespace load_constStdString

namespace open_constStdFilesystemPath {

// Case
// Opening and reading an INI file.
UTEST(open_constStdFilesystemPath, mustNotThrow_filesystemPath)
{
    ini::File file = ini::open("example.ini");
}

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
    // A File instance with sections.
    UTEST(clear, file)
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

namespace remove_section_constStdString {

    // Case
    // The section name is an empty string.
    UTEST(remove_section_constStdString, mustThrow_sectionNameIsEmpty)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.remove_section(std::string()), std::invalid_argument);
    }

    // Case
    // The name of the section to remove does not exist.
    UTEST(remove_section_constStdString, mustThrow_sectionNameDoesNotExist)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.remove_section("Bar"), std::invalid_argument);
    }

    // Case
    // Section name exists in the File instance.
    UTEST(remove_section_constStdString, sectionExists)
    {
        ini::File file = ini::open("example.ini");
        size_t count = file.remove_section("Foo");
        ASSERT_EQ(count, 1);
        ASSERT_FALSE(file.has_section("Foo"));
    }

} // namespace remove_section_constStdString

namespace rename_section_constStdString_constStdString {

    // Case
    // Either the old section name or the new section name is an empty string.
    UTEST(rename_section_constStdString_constStdString, mustThrow_emptySectionName)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file.rename_section(std::string(), "Bar"), std::invalid_argument);
        ASSERT_EXCEPTION(file.rename_section("Bar", std::string()), std::invalid_argument);
        ASSERT_EXCEPTION(file.rename_section(std::string(), std::string()), std::invalid_argument);
    }

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

    // Case
    // The new section name replaces the old section name.
    UTEST(rename_section_constStdString_constStdString, newSectionName)
    {
        ini::File file = ini::open("example.ini");
        file.rename_section("Foo", "Bar");
        ASSERT_FALSE(file.has_section("Foo"));
        ASSERT_TRUE(file.has_section("Bar"));
    }

} // namespace rename_section_constStdString_constStdString

namespace size {

    // Case
    // File instance contains no sections.
    UTEST(size, fileIsEmpty)
    {
        ini::File file = ini::load(std::string());
        ASSERT_EQ(file.size(), 0);
    }

    // Case
    // File instance is not empty.
    UTEST(size, fileIsNotEmpty)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_GT(file.size(), 0);
    }

} // namespace size

} // namespace file

namespace section {

namespace clear {

    // Case
    // A Section with key-value pairs.
    UTEST(clear, section)
    {
        ini::File file = ini::open("example.ini");
        file["Settings"].clear();
        ASSERT_TRUE(file["Settings"].empty());
    }

    // Case
    // A Section with no key-value pairs.
    UTEST(clear, emptySection)
    {
        ini::File file = ini::open("example.ini");
        file["Foo"].clear();
        ASSERT_TRUE(file["Foo"].empty());
    }

} // namespace clear

namespace empty {

    // Case
    // Section has key-value pairs.
    UTEST(empty, sectionWithKeys)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_FALSE(file["Settings"].empty());
    }

    // Case
    // Section has no key-value pairs.
    UTEST(empty, emptySection)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_TRUE(file["Foo"].empty());
    }

} // namespace empty

namespace has_key {

    // Case
    // Key exists in the Section.
    UTEST(has_key, keyExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_TRUE(file["Settings"].has_key("foo"));
    }

    // Case
    // Key does not exist in the Section.
    UTEST(has_key, keyDoesNotExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_FALSE(file["Foo"].has_key("bar"));
    }

    // Case
    // Key is an empty string.
    UTEST(has_key, emptyString)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_FALSE(file["Settings"].has_key(std::string()));
    }

} // namespace has_key

namespace remove_key {

    // Case
    // Key does not exist in Section.
    UTEST(remove_key, mustThrow_keyDoesNotExist)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_EXCEPTION(file["Foo"].remove_key("bar"), std::invalid_argument);
    }

    // Case
    // Key exists in the Section.
    UTEST(remove_key, keyExists)
    {
        ini::File file = ini::open("example.ini");
        ASSERT_TRUE(file["Settings"].has_key("foo"));
        size_t count = file["Settings"].remove_key("foo");
        ASSERT_TRUE(count == 1);
        ASSERT_FALSE(file["Settings"].has_key("foo"));
    }

} // namespace remove_key

namespace rename_key {

    // Case
    // The old key is an empty string.
    UTEST(rename_key, mustThrow_oldKeyEmpty)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_EXCEPTION(file["Section"].rename_key(std::string(), "bar"), std::invalid_argument);
    }

    // Case
    // The new key is an empty string.
    UTEST(rename_key, mustThrow_newKeyEmpty)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_EXCEPTION(file["Section"].rename_key("foo", std::string()), std::invalid_argument);
    }

    // Case
    // Both the old key and the new key are empty strings.
    UTEST(rename_key, mustThrow_bothKeysEmpty)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_EXCEPTION(file["Section"].rename_key(std::string(), std::string()), std::invalid_argument);
    }

    // Case
    // THe old key to replace does not exist in the Section.
    UTEST(rename_key, mustThrow_oldKeyDoesNotExist)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_EXCEPTION(file["Section"].rename_key("bar", "car"), std::invalid_argument);
    }

    // Case
    // The new key already exists in the Section.
    UTEST(rename_key, mustThrow_newKeyAlreadyExists)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        ASSERT_EXCEPTION(file["Section"].rename_key("foo", "key"), std::invalid_argument);
    }

    // Case
    // The old key is replaced by the new key
    UTEST(rename_key, keyChanges)
    {
        std::string text = "[Section]\nkey = value\nfoo = bar";
        ini::File file = ini::load(text);
        file["Section"].rename_key("foo", "bar");
        ASSERT_FALSE(file["Section"].has_key("foo"));
        ASSERT_TRUE(file["Section"].has_key("bar"));
    }

} // namespace rename_key

} // namespace section