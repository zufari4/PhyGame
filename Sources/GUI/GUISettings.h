#pragma once

#include "SettingsManager.h"

namespace GUI
{
    enum Setting : int
    {
        DescriptionFile,
        FontFile,
        FontSize,
        FontHinting
    };

    const SettingsManager::tdProperties& GetDefaultSettings();
}