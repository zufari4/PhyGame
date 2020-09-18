#include "Utils.h"
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <direct.h>

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

    std::vector<int> strtoki(const std::string& str)
    {
        std::vector<int> res;
        const auto v = Tokinize(str, ',');
        for (const auto& t : v) {
            res.push_back(std::stoi(t));
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
        auto p = fileName.rfind('\\');
        if (p == std::string::npos) p = fileName.rfind('/');
        if (p == std::string::npos) throw std::runtime_error("Can't extract file path from file name '" + fileName + "'");
        return fileName.substr(0, p);
    }

    std::string ReadFile(const std::string& fileName)
    {
        std::ifstream f(fileName);
        std::stringstream buffer;
        buffer << f.rdbuf();
        return buffer.str();
    }

    long GetFileSize(const std::string& filename)
    {
        struct stat stat_buf;
        int rc = stat(filename.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;
    }

    bool DirectoryExists(const std::string& path)
    {
        struct stat info;

        if (stat(path.c_str(), &info) != 0)
            return 0;
        else if (info.st_mode & S_IFDIR)
            return 1;
        else
            return 0;
    }   

    bool CreateDirectory(const std::string& path)
    {
        return _mkdir(path.c_str()) == 0;
    }

    bool strncasecpm(const std::string& a, const std::string& b)
    {
        size_t sz = a.size();
        if (b.size() != sz)
            return false;
        for (size_t i = 0; i < sz; ++i)
            if (tolower(a[i]) != tolower(b[i]))
                return false;
        return true;
    }

}