#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Utils
{
    std::string GetAppDataPath();
    bool stob(const std::string& str);
    std::vector<float> stocolor(const std::string& str);
    std::vector<std::string> Tokinize(const std::string& str, char delimiter);
    std::string ExtractPath(const std::string& fileName);
    std::string ReadFile(const std::string& fileName);

    template<typename Derived, typename Base>
    std::unique_ptr<Derived> unique_ptr_cast(std::unique_ptr<Base> srcPtr)
    {
        return std::unique_ptr<Derived>(static_cast<Derived*>(srcPtr.release()));
    }
}