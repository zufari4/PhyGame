#include "OS.h"
#include <windows.h>
#include <codecvt>
#include <vector>

namespace OS
{
	std::vector<wchar_t> utf8ToUCS2(const std::string& path)
	{
		const int path_wsize = ::MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, NULL, 0);
		std::vector<wchar_t> buf;
		buf.resize(path_wsize);
		::MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, (wchar_t*)&buf[0], path_wsize);
		return buf;
	}

    std::string GetApplicationFileName()
    {
        wchar_t buffer[MAX_PATH] = { 0 };
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
        return utf8_conv.to_bytes(buffer);
    }

	int statFile(const std::string& path, unsigned short* st_mode /*= nullptr*/, long* st_size /*= nullptr*/)
	{
		const auto unicode = utf8ToUCS2(path);
		struct _stat64i32 info;
		auto res = _wstat(unicode.data(), &info);
		if (st_mode) *st_mode = info.st_mode;
		if (st_size) *st_size = info.st_size;
		return res;
	}

	int mkDir(const std::string& path)
	{
		const auto unicode = utf8ToUCS2(path);
		return _wmkdir(unicode.data());
	}

	FILE* OpenFile(const std::string& fileName, const std::string& mode)
	{
		const auto unicodeFile = utf8ToUCS2(fileName);
		const auto unicodeMode = utf8ToUCS2(mode);
		FILE* f = nullptr;
		_wfopen_s(&f, unicodeFile.data(), unicodeMode.data());
		return f;
	}

	void ShowErrorWindow(const std::string& text, const std::string& title /*= "Error"*/)
	{
		MessageBoxW(nullptr, utf8ToUCS2(text).data(), utf8ToUCS2(title).data(), MB_ICONERROR | MB_OK);
	}
}