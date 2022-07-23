#ifndef INI_H
#define INI_H

#include <string>
#include <unordered_map>

#endif

namespace ini {

class Section {
public:
    Section();

    std::string& operator[](const std::string&);
    std::unordered_map<std::string, std::string>::const_iterator begin() const;
    std::unordered_map<std::string, std::string>::iterator begin();
    std::unordered_map<std::string, std::string>::const_iterator end() const;
    std::unordered_map<std::string, std::string>::iterator end();

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

} // namespace ini