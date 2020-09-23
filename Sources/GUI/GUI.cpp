#include "GUI.h"
#include "Instance.h"

namespace GUI
{
    std::unique_ptr<Instance> instance;

    LIB_API void GUI::Init(SDL_Window* window, void* glContext, const std::string& configFile, const std::string& resourceDirectory)
    {
        instance = std::make_unique<Instance>(window, glContext, configFile, resourceDirectory);
    }

    LIB_API void Free()
    {
        instance.reset();
    }

    LIB_API void ProcessFrame()
    {
        instance->ProcessFrame();
    }

    LIB_API void LoadGUI(const std::string& jsonFile)
    {
        instance->LoadGUI(jsonFile);
    }

    const std::string& GetResourceDirectory()
    {
        return instance->GetResourceDirectory();
    }

}