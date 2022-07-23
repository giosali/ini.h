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

} // namespace ini