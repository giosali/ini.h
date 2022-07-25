#include "ini.h"
#include "utest.h"
#include <string>

UTEST(ini_h, load_string)
{
    // Must not throw an exception.
    std::string text = "[Section]";
    ini::File file = ini::load(text);
}