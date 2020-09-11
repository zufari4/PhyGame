#include "GUISettings.h"

namespace GUI
{

    const SettingsManager::tdProperties& GetDefaultSettings()
    {
        static const SettingsManager::tdProperties defSettings =
        {
            { Setting::DescriptionFile, {"GUI",  "DescriptionFile", "gui.json"} },
            { Setting::FontFile, {"GUI",  "FontFile", ""} },
            { Setting::FontSize, {"GUI",  "FontSize", "16.0"} },
        };

        return defSettings;
    }

}