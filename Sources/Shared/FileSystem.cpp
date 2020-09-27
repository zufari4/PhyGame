#include "FileSystem.h"
#include "OS.h"
#include  <stdexcept>

namespace FileSystem
{
    std::string GetAppDataPath()
    {
        char* buff = nullptr;
        _dupenv_s(&buff, nullptr, "APPDATA");
        std::string res(buff ? buff : "");
        return res;
    }

    std::string GetCurrentDirectory()
    {
        auto appFile = OS::GetApplicationFileName();
        return ExtractPath(appFile);
    }

    std::string ExtractPath(const std::string& fileName)
    {
        auto l = fileName.rfind('/');
        auto p = fileName.rfind('\\');
        if (l != std::string::npos && l > p) p = l;
        if (p == std::string::npos) throw std::runtime_error("Can't extract file path from file name '" + fileName + "'");
        return fileName.substr(0, p);
    }

    std::string ReadTextFile(const std::string& fileName)
    {
        if (!FileIsExists(fileName)) {
            throw std::runtime_error("File '" + fileName + "' is not exists");
        }
        FILE* file = OS::OpenFile(fileName, "r");
		if (file == nullptr) {
			throw std::runtime_error("Can't open file '" + fileName + "'");
		}
        const size_t buffSize = 1024;
        char buff[buffSize];
        size_t readSize;
        std::string res;

        do {
            readSize = fread_s(buff, buffSize - 1, 1, buffSize - 1, file);
            if (readSize > 0) {
                buff[readSize] = '\0';
                res.append(buff);
            }
        } while (readSize > 0);

        fclose(file);
        return res;
    }

	void WriteTextFile(const std::string& fileName, const std::string& content)
	{
        FILE* file = OS::OpenFile(fileName, "w");
		if (file == nullptr) {
			throw std::runtime_error("Can't open file '" + fileName + "' for write");
		}
        size_t writeSize = fwrite(content.c_str(), 1, content.size(), file);
        if (writeSize != content.size()) {
            fclose(file);
            throw std::runtime_error("Can't write data to file '" + fileName + "'");
        }
        fclose(file);
	}

	long GetFileSize(const std::string& filename)
    {
        long size;
        int rc = OS::statFile(filename, nullptr, &size);
        return rc == 0 ? size : -1;
    }

    bool DirectoryExists(const std::string& path)
    {
        unsigned short st_mode;
        if (OS::statFile(path.c_str(), &st_mode) != 0)
            return false;
        else if (st_mode & S_IFDIR)
            return true;
        else
            return false;
    }   

    bool FileIsExists(const std::string& filename)
    {
        FILE* file = OS::OpenFile(filename, "r");
        if (file) {
            fclose(file);
            return true;
        }
        return false;
    }

    bool CreateDirectory(const std::string& path)
    {
        return OS::mkDir(path) == 0;
    }
}