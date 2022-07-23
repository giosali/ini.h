#ifndef INI_H
#define INI_H

#include <algorithm>
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

} // namespace ini