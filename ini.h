/*
Copyright 2022 Giovanni Salinas

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef INI_H
#define INI_H

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>

#endif

namespace ini {

namespace {

    inline bool stob(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), tolower);
        if (str == "true") {
            return true;
        } else if (str == "false") {
            return false;
        } else {
            throw std::invalid_argument("could not convert string to boolean");
        }
    }

    inline size_t stoszt(const std::string& str)
    {
        std::istringstream stream(str);
        size_t n;
        stream >> n;
        return n;
    }

    inline std::string trim(const std::string& str)
    {
        if (str.empty()) {
            return str;
        }

        size_t length = str.length();

        // Trims head.
        size_t start = 0;
        for (; start < length; start++) {
            if (str[start] != ' ') {
                break;
            }
        }

        // Trims tail.
        size_t end = length - 1;
        for (; end >= start; end--) {
            if (str[end] != ' ') {
                break;
            }
        }

        return str.substr(start, end - start + 1);
    }

} // namespace

class Section {
public:
    Section();

    void clear() noexcept;
    bool empty() const noexcept;
    bool has_key(const std::string&) const;
    size_t remove_key(const std::string&);
    void rename_key(const std::string&, const std::string&);
    size_t size() const noexcept;
    template <typename T>
    T get(const std::string&) const;
    template <typename T>
    void set(const std::string&, const T&);
    std::unordered_map<std::string, std::string>::const_iterator begin() const noexcept;
    std::unordered_map<std::string, std::string>::iterator begin() noexcept;
    std::unordered_map<std::string, std::string>::const_iterator end() const noexcept;
    std::unordered_map<std::string, std::string>::iterator end() noexcept;
    std::string& operator[](const std::string&);

private:
    std::unordered_map<std::string, std::string> m_items;
};

inline Section::Section()
{
}

inline void Section::clear() noexcept
{
    m_items.clear();
}

inline bool Section::empty() const noexcept
{
    return m_items.empty();
}

inline bool Section::has_key(const std::string& key) const
{
    return m_items.find(key) != m_items.end();
}

inline size_t Section::remove_key(const std::string& key)
{
    if (m_items.find(key) == m_items.end()) {
        throw std::invalid_argument("key does not exist");
    }

    return m_items.erase(key);
}

inline void Section::rename_key(const std::string& old_key, const std::string& new_key)
{
    if (old_key.empty() || new_key.empty()) {
        throw std::invalid_argument("keys cannot be empty");
    }

    if (m_items.find(old_key) == m_items.end()) {
        throw std::invalid_argument("old key does not exist");
    }

    if (m_items.find(new_key) != m_items.end()) {
        throw std::invalid_argument("new key already exists");
    }

    auto item = m_items.extract(old_key);
    item.key() = new_key;
    m_items.insert(std::move(item));
}

size_t Section::size() const noexcept
{
    return m_items.size();
}

template <typename T>
inline T Section::get(const std::string& key) const
{
    if (m_items.find(key) == m_items.end()) {
        throw std::invalid_argument("key does not exist");
    }

    if constexpr (std::is_same<T, bool>::value) {
        return stob(m_items.at(key));
    } else if constexpr (std::is_same<T, int>::value) {
        return std::stoi(m_items.at(key));
    } else if constexpr (std::is_same<T, float>::value) {
        return std::stof(m_items.at(key));
    } else if constexpr (std::is_same<T, double>::value) {
        return std::stod(m_items.at(key));
    } else if constexpr (std::is_same<T, size_t>::value) {
        return stoszt(m_items.at(key));
    } else if constexpr (std::is_same<T, std::string>::value) {
        return m_items.at(key);
    } else {
        throw std::invalid_argument("type is not supported");
    }
}

template <typename T>
inline void Section::set(const std::string& key, const T& value)
{
    if constexpr (std::is_same<T, bool>::value) {
        m_items[key] = value ? "true" : "false";
    } else if constexpr (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, size_t>::value) {
        std::ostringstream stream;
        stream << value;
        m_items[key] = stream.str();
    } else if constexpr (std::is_same<T, std::string>::value) {
        m_items[key] = value;
    } else {
        throw std::invalid_argument("type is not supported");
    }
}

inline std::unordered_map<std::string, std::string>::const_iterator Section::begin() const noexcept
{
    return m_items.begin();
}

inline std::unordered_map<std::string, std::string>::iterator Section::begin() noexcept
{
    return m_items.begin();
}

inline std::unordered_map<std::string, std::string>::const_iterator Section::end() const noexcept
{
    return m_items.end();
}

inline std::unordered_map<std::string, std::string>::iterator Section::end() noexcept
{
    return m_items.end();
}

inline std::string& Section::operator[](const std::string& key)
{
    if (key.empty()) {
        throw std::invalid_argument("keys cannot be empty");
    }

    return m_items[key];
}

class File {
public:
    File();
    File(std::ifstream&);
    File(const std::string&);

    void add_section(const std::string&);
    void clear() noexcept;
    bool empty() const noexcept;
    bool has_section(const std::string&) const;
    size_t remove_section(const std::string&);
    void rename_section(const std::string&, const std::string&);
    size_t size() const noexcept;
    void write(const std::filesystem::path&) const;
    std::unordered_map<std::string, Section>::const_iterator begin() const noexcept;
    std::unordered_map<std::string, Section>::iterator begin() noexcept;
    std::unordered_map<std::string, Section>::const_iterator end() const noexcept;
    std::unordered_map<std::string, Section>::iterator end() noexcept;
    Section& operator[](const std::string&);

private:
    void read(std::istream&);

    std::unordered_map<std::string, Section> m_sections;
};

inline File::File()
{
}

inline File::File(std::ifstream& stream)
{
    if (!stream.is_open()) {
        throw std::invalid_argument("stream is closed");
    }

    read(stream);
}

inline File::File(const std::string& text)
{
    std::istringstream stream(text);
    read(stream);
}

inline void File::add_section(const std::string& section_name)
{
    if (m_sections.find(section_name) != m_sections.end()) {
        throw std::invalid_argument("section already exists");
    }

    m_sections[section_name];
}

inline void File::clear() noexcept
{
    m_sections.clear();
}

inline bool File::empty() const noexcept
{
    return m_sections.empty();
}

inline bool File::has_section(const std::string& section_name) const
{
    return m_sections.find(section_name) != m_sections.end();
}

inline size_t File::remove_section(const std::string& section_name)
{
    if (section_name.empty()) {
        throw std::invalid_argument("section names cannot be empty");
    }

    if (m_sections.find(section_name) == m_sections.end()) {
        throw std::invalid_argument("section does not exist");
    }

    return m_sections.erase(section_name);
}

inline void File::rename_section(const std::string& old_section_name, const std::string& new_section_name)
{
    if (old_section_name.empty() || new_section_name.empty()) {
        throw std::invalid_argument("section names cannot be empty");
    }

    if (m_sections.find(old_section_name) == m_sections.end()) {
        throw std::invalid_argument("old section name does not exist");
    }

    if (m_sections.find(new_section_name) != m_sections.end()) {
        throw std::invalid_argument("new section name already exists");
    }

    auto section = m_sections.extract(old_section_name);
    section.key() = new_section_name;
    m_sections.insert(std::move(section));
}

inline size_t File::size() const noexcept
{
    return m_sections.size();
}

inline void File::write(const std::filesystem::path& path) const
{
    std::ofstream stream(path);
    if (!stream.is_open()) {
        throw std::invalid_argument("stream is closed");
    }

    for (auto const& [section_name, section] : m_sections) {
        stream << "[" << section_name << "]" << std::endl;
        for (auto const& [key, value] : section) {
            stream << key << " = " << value << std::endl;
        }

        stream << std::endl;
    }

    stream.close();
}

inline std::unordered_map<std::string, Section>::const_iterator File::begin() const noexcept
{
    return m_sections.begin();
}

inline std::unordered_map<std::string, Section>::iterator File::begin() noexcept
{
    return m_sections.begin();
}

inline std::unordered_map<std::string, Section>::const_iterator File::end() const noexcept
{
    return m_sections.end();
}

inline std::unordered_map<std::string, Section>::iterator File::end() noexcept
{
    return m_sections.end();
}

inline Section& File::operator[](const std::string& section_name)
{
    if (section_name.empty()) {
        throw std::invalid_argument("section headers cannot be empty");
    }

    return m_sections[section_name];
}

inline void File::read(std::istream& stream)
{
    Section* section = nullptr;
    std::string line;
    while (std::getline(stream, line)) {
        // Removes whitespace on both ends.
        line = trim(line);

        // Checks if the current line is a section declaration.
        size_t r_bracket_pos = line.rfind(']');
        if (line.find('[') == 0 && r_bracket_pos != std::string::npos) {
            if (r_bracket_pos == 1) {
                throw std::invalid_argument("section headers cannot be empty");
            }

            section = &m_sections[line.substr(1, r_bracket_pos - 1)];
            continue;
        }

        // Skips the current line if it doesn't contain a delimiter ('=', ':')
        // or if the line is a comment.
        size_t delimiter_pos = std::min<size_t>(line.find('='), line.find(':'));
        if (line.find(';') == 0 || line.find('#') == 0 || delimiter_pos == std::string::npos) {
            continue;
        }

        // Throws an exception because if the section is null
        // then a section header is missing from the configuration file.
        if (section == nullptr) {
            throw std::invalid_argument("file is missing a section header");
        }

        std::string key = trim(line.substr(0, delimiter_pos));

        // Checks if the key is an empty string.
        if (key.empty()) {
            throw std::invalid_argument("keys cannot be empty");
        }

        // Checks if the key already exists.
        if ((*section).has_key(key)) {
            throw std::invalid_argument("key already exists");
        }

        std::string value = trim(line.substr(delimiter_pos + 1));

        // Adds the key and value to the section.
        (*section)[key] = value;
    }
}

inline File load(std::ifstream& stream)
{
    return File(stream);
}

inline File load(const std::string& text)
{
    return File(text);
}

inline File open(const std::filesystem::path& path)
{
    std::ifstream stream(path);
    File file(stream);
    stream.close();
    return file;
}

} // namespace ini