#include "GUI.h"
#include "Instance.h"

namespace GUI
{
    std::unique_ptr<Instance> instance;

    LIB_API void GUI::Init(SDL_Window* window, void* glContext, const std::string& configFile)
    {
        instance = std::make_unique<Instance>(window, glContext, configFile);
    }

    LIB_API void Free()
    {
        instance.reset();
    }

    LIB_API void ProcessFrame()
    {
        instance->ProcessFrame();
    }
}