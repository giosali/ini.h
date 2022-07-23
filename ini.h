#ifndef INI_H
#define INI_H

#include <algorithm>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
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

    inline std::string trim(const std::string& str)
    {
        if (str.empty()) {
            return str;
        }

        size_t length = str.length();

        // Trim head
        size_t start = 0;
        for (; start < length; start++) {
            if (str[start] != ' ') {
                break;
            }
        }

        // Trim tail
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

    std::string& operator[](const std::string&);
    std::unordered_map<std::string, std::string>::const_iterator begin() const;
    std::unordered_map<std::string, std::string>::iterator begin();
    std::unordered_map<std::string, std::string>::const_iterator end() const;
    std::unordered_map<std::string, std::string>::iterator end();
    template <typename T>
    T get(const std::string&);
    template <typename T>
    void set(const std::string&, const T&);

private:
    std::unordered_map<std::string, std::string> m_items;
};

inline Section::Section()
{
}

inline std::string& Section::operator[](const std::string& key)
{
    return m_items[key];
}

inline std::unordered_map<std::string, std::string>::const_iterator Section::begin() const
{
    return m_items.begin();
}

inline std::unordered_map<std::string, std::string>::iterator Section::begin()
{
    return m_items.begin();
}

inline std::unordered_map<std::string, std::string>::const_iterator Section::end() const
{
    return m_items.end();
}

inline std::unordered_map<std::string, std::string>::iterator Section::end()
{
    return m_items.end();
}

template <typename T>
inline T Section::get(const std::string&)
{
    if constexpr (std::is_same<T, bool>::value) {
        return stob(m_items[key]);
    } else if constexpr (std::is_same<T, int>::value) {
        return std::stoi(m_items[key]);
    } else if constexpr (std::is_same<T, float>::value) {
        return std::stof(m_items[key]);
    } else if constexpr (std::is_same<T, double>::value) {
        return std::stod(m_items[key]);
    } else if constexpr (std::is_same<T, std::string>::value) {
        return m_items[key];
    } else {
        throw std::invalid_argument("type is not supported");
    }
}

template <typename T>
inline void Section::set(const std::string& key, const T& value)
{
    if constexpr (std::is_same<T, bool>::value) {
        m_items[key] = value ? "true" : "false";
    } else if constexpr (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value) {
        std::ostringstream stream;
        stream << value;
        m_items[key] = stream.str();
    } else if constexpr (std::is_same<T, std::string>::value) {
        m_items[key] = value;
    } else {
        throw std::invalid_argument("type is not supported");
    }
}

class File {
public:
    File(std::ifstream&);

private:
    void read(std::istream&);

    std::unordered_map<std::string, Section> m_sections;
};

inline File::File(std::ifstream& stream)
{
    if (!stream.is_open()) {
        throw std::invalid_argument("stream is closed");
    }

    read(stream);
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

        // Adds the key and value to the section.
        std::string key = line.substr(0, delimiter_pos);
        if (m_sections.find(key) != m_sections.end()) {
            throw std::invalid_argument("key already exists");
        }

        std::string value = line.substr(delimiter_pos + 1);
        (*section)[trim(key)] = trim(value);
    }
}

} // namespace ini