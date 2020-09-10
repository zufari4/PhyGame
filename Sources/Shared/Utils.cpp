#include "Utils.h"
#include <stdlib.h>
#include <sstream>

namespace Utils
{
    std::string GetAppDataPath()
    {
        char* buff = nullptr;
        _dupenv_s(&buff, nullptr, "APPDATA");
        std::string res(buff ? buff : "");
        return res;
    }

    bool stob(const std::string& str)
    {
        bool res;
        std::istringstream(str) >> std::boolalpha >> res;
        return res;
    }

    float storcolor(const std::string& str)
    {
        const auto s = str.substr(0, str.find(','));
        return std::stof(s);
    }

    float stogcolor(const std::string& str)
    {
        auto s = str.substr(str.find(',')+1);
        s = s.substr(0, s.find(','));
        return std::stof(s);
    }

    float stobcolor(const std::string& str)
    {
        const auto s = str.substr(str.rfind(',') + 1);
        return std::stof(s);
    }
}