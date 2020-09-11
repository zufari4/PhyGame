#pragma once

#include "SettingsManager.h"

namespace GUI
{
    enum Setting : int
    {
        DescriptionFile,
        FontFile,
        FontSize
    };

    const SettingsManager::tdProperties& GetDefaultSettings();
}