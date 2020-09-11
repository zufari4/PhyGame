#include "ClientSettings.h"

const SettingsManager::tdProperties& GetDefaultClientSettings()
{
    static const SettingsManager::tdProperties defSettings =
    {
        { ClientSetting::GridVisible, {"Grid",  "Visible", "True"} },
        { ClientSetting::GridSize,    {"Grid",  "Size", "10.0f"} },
    };

    return defSettings;
}