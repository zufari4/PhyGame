#pragma once

#include "SettingsManager.h"

namespace GUI
{
    enum Setting : int
    {
        DescriptionFile,
    };

    const SettingsManager::tdProperties& GetDefaultSettings();
}