#pragma once

#include "SettingsManager.h"

namespace GUI
{
    enum Setting : int
    {
        Test
    };

    const SettingsManager::tdProperties& GetDefaultSettings();
}