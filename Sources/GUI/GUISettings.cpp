#include "GUISettings.h"

namespace GUI
{

    const SettingsManager::tdProperties& GetDefaultSettings()
    {
        static const SettingsManager::tdProperties defSettings =
        {
            { Setting::DescriptionFile, {"GUI",  "DescriptionFile", "gui.json"} },
        };

        return defSettings;
    }

}