#include "Utils.h"
#include <stdlib.h>
#include <sstream>
#include <filesystem>
#include <fstream>

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

    std::string ExtractPath(const std::string& fileName)
    {
        const std::filesystem::path p = fileName;
        return p.parent_path().string();
    }

    std::string ReadFile(const std::string& fileName)
    {
        std::ifstream f(fileName, std::ios::in | std::ios::binary);
        const auto sz = std::filesystem::file_size(fileName);
        std::string result(sz, '\0');
        f.read(result.data(), sz);

        return result;
    }

}