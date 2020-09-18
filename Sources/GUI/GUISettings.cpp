#include "GUISettings.h"

namespace GUI
{

    const SettingsManager::tdProperties& GetDefaultSettings()
    {
        static const SettingsManager::tdProperties defSettings =
        {
        };

        return defSettings;
    }

}