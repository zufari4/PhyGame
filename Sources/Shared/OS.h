#pragma once

#include <string>

namespace OS
{
    std::string GetApplicationFileName();
    int statFile(const std::string& path, unsigned short* st_mode = nullptr, long* st_size = nullptr);
    int mkDir(const std::string& path);
    FILE* OpenFile(const std::string& fileName, const std::string& mode);
    void ShowErrorWindow(const std::string& text, const std::string& title = "Error");
}