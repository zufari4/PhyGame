#include "OS.h"
#include <windows.h>

namespace OS
{
    std::string GetApplicationFileName()
    {
        char buffer[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return buffer;
    }
}