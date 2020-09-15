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
        const auto s = Tokinize(str, ',');
        return std::stof(s[0]);
    }

    float stogcolor(const std::string& str)
    {
        const auto s = Tokinize(str, ',');
        return std::stof(s[1]);
    }

    float stobcolor(const std::string& str)
    {
        const auto s = Tokinize(str, ',');
        return std::stof(s[2]);
    }

    float stoacolor(const std::string& str)
    {
        const auto s = Tokinize(str, ',');
        return std::stof(s[3]);
    }

    std::vector<float> strtokf(const std::string& str)
    {
        std::vector<float> res;
        const auto v = Tokinize(str, ',');
        for (const auto& t : v) {
            res.push_back(std::stof(t));
        }
        return res;
    }

    std::vector<std::string> Tokinize(const std::string& str, char delimiter)
    {
        std::vector<std::string> result;
        size_t offset = 0;
        while (true)
        {
            auto pos = str.find(delimiter, offset);
            if (pos == std::string::npos) break;
            std::string tok = str.substr(offset, pos - offset);
            result.push_back(tok);
            offset = pos + 1;
        }
        auto pos = str.rfind(delimiter);
        if (pos != std::string::npos) {
            result.push_back(str.substr(pos+1));
        }
        return result;
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