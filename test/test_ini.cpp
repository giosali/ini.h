#include "ini.h"

#include "utest.h"
#include <stdexcept>
#include <string>

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
// Section must be created if the input isn't terminated by a newline
// character.
UTEST(load__constStdString_doesNotEndWithNewline, section)
{
    std::string text = "[Section]\nfoo = bar\n[Section 2]";
    ini::File file = ini::load(text);
    ASSERT_TRUE(file.has_section("Section 2"));
}

// Case
// Key-value pair must be created if the input isn't terminated by
// a newline character.
UTEST(load__constStdString_doesNotEndWithNewline, key_value)
{
    std::string text = "[Section]\nfoo = bar";
    ini::File file = ini::load(text);
    ASSERT_TRUE(file["Section"]["foo"] == "bar");
}