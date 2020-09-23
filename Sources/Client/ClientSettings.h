#pragma once

#include "SettingsManager.h"

enum ClientSetting: int
{
    GridVisible,
    GridSize,
    GUIMainFile,
};

const SettingsManager::tdProperties& GetDefaultClientSettings();