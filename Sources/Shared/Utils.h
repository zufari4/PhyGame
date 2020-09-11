#pragma once

#include <string>
#include <memory>

namespace Utils
{
    std::string GetAppDataPath();
    bool stob(const std::string& str);
    float storcolor(const std::string& str);
    float stogcolor(const std::string& str);
    float stobcolor(const std::string& str);
    std::string ExtractPath(const std::string& fileName);
    std::string ReadFile(const std::string& fileName);

    template<typename Derived, typename Base>
    std::unique_ptr<Derived> unique_ptr_cast(std::unique_ptr<Base> srcPtr)
    {
        return std::unique_ptr<Derived>(static_cast<Derived*>(srcPtr.release()));
    }
}