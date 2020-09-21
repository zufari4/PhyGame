#include "ErrorWindow.h"
#include <windows.h>

void ShowErroWindow(const std::string& text)
{
    auto hwnd = MessageBoxA(nullptr, text.c_str(), "Error", MB_ICONERROR | MB_OK);
}
