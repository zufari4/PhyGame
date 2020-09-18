#pragma once

#include "SettingsManager.h"

enum ClientSetting: int
{
    GridVisible,
    GridSize,
    GUIMainMenuFile,
    GUICreateMechanizmFile
};

const SettingsManager::tdProperties& GetDefaultClientSettings();