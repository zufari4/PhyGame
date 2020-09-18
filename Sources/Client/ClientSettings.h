#pragma once

#include "SettingsManager.h"

enum ClientSetting: int
{
    GridVisible,
    GridSize,
    GUIMainMenuFile
};

const SettingsManager::tdProperties& GetDefaultClientSettings();