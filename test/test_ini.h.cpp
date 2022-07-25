#include "ini.h"
#include "utest.h"
#include <stdexcept>
#include <string>

// Test
// ini::load(const std::string& text)
// Must not throw.
UTEST(ini__load__const_std_string, must_not_throw)
{
    // Case
    // Input consists of a single section.
    std::string text = "[Section]";
    ini::File file = ini::load(text);

    // Case
    // Input consists of a single section and a few key-value pairs.
    text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
    file = ini::load(text);

    // Case
    // Input consists of two different sections where both contain identical
    // key-value pairs.
    text = "[Section]\nkey = value\nhello = world\nFOO=BAR\nbar : foo\n[Section 2]\nkey = value\nhello = world\nFOO=BAR\nbar : foo";
    file = ini::load(text);

    // Case
    // Input consists of multiple empty sections
    text = "[Section 1]\n[Section 2]\n[Section 3]";
    file = ini::load(text);

    // Case
    // Input contains whitespace on the left side of each line.
    text = "     [Section]\n   key = value";
    file = ini::load(text);

    // Case
    // Input contains whitespace on the right side of each line.
    text = "[Section]      \nkey = value        ";
    file = ini::load(text);

    // Case
    // Input contains lines that are padded with whitespace.
    text = "      [Section]      \n      key = value       ";
}

// Test
// ini::load(const std::string& text)
// Must throw an exception.
UTEST(ini__load__const_std_string, must_throw)
{
    // Case
    // Input contains a missing header.
    std::string text = "key = value\nfoo = bar\n[Section]\nkey = value";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);

    // Case
    // Input contains a section with duplicate keys.
    text = "[Section]\nkey = value\nkey = value";
    ASSERT_EXCEPTION(ini::load(text), std::invalid_argument);
}

UTEST(ini__load__const_std_string, string_doesnt_end_with_newline)
{
    // Case
    // Key-value pair must be created if the input isn't terminated by
    // a newline character.
    std::string text = "[Section]\nfoo = bar";
    ini::File file = ini::load(text);
    ASSERT_TRUE(file["Section"]["foo"] == "bar");

    // Case
    // Section must be created if the input isn't terminated by a newline
    // character.
    text = "[Section]\nfoo = bar\n[Section 2]";
    file = ini::load(text);
    ASSERT_TRUE(file.has_section("Section 2"));
}