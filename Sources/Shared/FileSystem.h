#pragma once

#include <string>

namespace FileSystem
{
    std::string GetAppDataPath();
    std::string GetCurrentDirectory();
    std::string ExtractPath(const std::string& fileName);
    std::string ReadTextFile(const std::string& fileName);
    void WriteTextFile(const std::string& fileName, const std::string& content);
    long GetFileSize(const std::string& filename);
    bool DirectoryExists(const std::string& path);
    bool FileIsExists(const std::string& filename);
    bool CreateDirectory(const std::string& path);
}