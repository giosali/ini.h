#ifndef INI_H
#define INI_H

#include <string>
#include <unordered_map>

#endif

namespace ini {

class Section {
public:
    Section();

private:
    std::unordered_map<std::string, std::string> m_items;
};

inline Section::Section()
{
}

} // namespace ini