#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Utils
{
    std::string GetAppDataPath();
    std::string GetCurrentDirectory();
    bool stob(const std::string& str);
    std::vector<float> strtokf(const std::string& str);
    std::vector<int> strtoki(const std::string& str);
    std::vector<std::string> Tokinize(const std::string& str, char delimiter);
    std::string ExtractPath(const std::string& fileName);
    std::string ReadFile(const std::string& fileName);
    long GetFileSize(const std::string& filename);
    bool DirectoryExists(const std::string& path);
    bool FileIsExists(const std::string& filename);
    bool CreateDirectory(const std::string& path);
    bool strncasecpm(const std::string& a, const std::string& b);

    template<typename Derived, typename Base>
    std::unique_ptr<Derived> unique_ptr_cast(std::unique_ptr<Base> srcPtr)
    {
        return std::unique_ptr<Derived>(static_cast<Derived*>(srcPtr.release()));
    }
}