#pragma once

#include "SettingsManager.h"

enum ClientSetting: int
{
    GridVisible,
    GridSize,
};

const SettingsManager::tdProperties& GetDefaultClientSettings();