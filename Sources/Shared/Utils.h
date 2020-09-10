#pragma once

#include <string>

namespace Utils
{
    std::string GetAppDataPath();
    bool stob(const std::string& str);
    float storcolor(const std::string& str);
    float stogcolor(const std::string& str);
    float stobcolor(const std::string& str);
}