#include "SettingsManager.h"
#include "IniFile.h"
#include "Utils.h"
#include <filesystem>
#include <stdexcept>

SettingsManager::SettingsManager(const std::string& configFile, const tdProperties& defaultSettings, bool fillConfigFile)
    : configFile_(configFile)
    , defaultSettings_(defaultSettings)
{
    if (fillConfigFile) createConfigFile();
}

int64_t SettingsManager::GetPropertyAsInteger(int propertyID) const
{
    const auto& defaultProperty = GetDefaultProperty(propertyID);
    const int64_t defValue = std::stoll(defaultProperty.value);

    Ini_file f;
    if (!f.Open(configFile_)) {
        return defValue;
    }

    return f.Get_value(defaultProperty.section, defaultProperty.name, defValue);
}

uint64_t SettingsManager::GetPropertyAsUnsigned(int propertyID) const
{
    const auto& defaultProperty = GetDefaultProperty(propertyID);
    const uint64_t defValue = std::stoull(defaultProperty.value);

    Ini_file f;
    if (!f.Open(configFile_)) {
        return defValue;
    }

    return f.Get_value(defaultProperty.section, defaultProperty.name, defValue);
}

float SettingsManager::GetPropertyAsFloat(int propertyID) const
{
    const auto& defaultProperty = GetDefaultProperty(propertyID);
    const float defValue = std::stof(defaultProperty.value);

    Ini_file f;
    if (!f.Open(configFile_)) {
        return defValue;
    }

    return f.Get_value(defaultProperty.section, defaultProperty.name, defValue);
}

std::string SettingsManager::GetPropertyAsString(int propertyID) const
{
    const auto& defaultProperty = GetDefaultProperty(propertyID);

    Ini_file f;
    if (!f.Open(configFile_)) {
        return defaultProperty.value;
    }

    return f.Get_value(defaultProperty.section, defaultProperty.name, defaultProperty.value.c_str());
}

bool SettingsManager::GetPropertyAsBool(int propertyID) const
{
    const auto& defaultProperty = GetDefaultProperty(propertyID);
    const bool defValue = Utils::stob(defaultProperty.value);

    Ini_file f;
    if (!f.Open(configFile_)) {
        return defValue;
    }

    return f.Get_value(defaultProperty.section, defaultProperty.name, defValue);
}

void SettingsManager::SetPropertyValue(int propertyID, const std::string& val) const
{
    const auto defaultProperty = GetDefaultProperty(propertyID);

    Ini_file f;
    if (!f.Open(configFile_)) {
        throw std::runtime_error("Can't open file '" + configFile_ + "'");
    }

    f.Set_value(defaultProperty.section, defaultProperty.name, val.c_str());
}

void SettingsManager::SetPropertyValue(int propertyID, int64_t val) const
{
    SetPropertyValue(propertyID, std::to_string(val));
}

void SettingsManager::SetPropertyValue(int propertyID, float val) const
{
    SetPropertyValue(propertyID, std::to_string(val));
}

void SettingsManager::SetPropertyValue(int propertyID, bool val) const
{
    SetPropertyValue(propertyID, std::to_string(val));
}

void SettingsManager::SetPropertyValue(int propertyID, uint64_t val) const
{
    SetPropertyValue(propertyID, std::to_string(val));
}

const SettingsManager::Property& SettingsManager::GetDefaultProperty(int propertyID) const
{
    const auto& it = defaultSettings_.find(propertyID);
    if (it == defaultSettings_.end()) {
        throw std::runtime_error("Property " + std::to_string(propertyID) + " not found");
    }
    return it->second;
}

void SettingsManager::createConfigFile() const
{
    const std::filesystem::path p = configFile_;
    auto configDir = p.parent_path().string();
    if (!std::filesystem::exists(configDir)) {
        if (!std::filesystem::create_directories(configDir)) {
            throw std::runtime_error("Can't create directory '" + configDir + "'");
        }
    }

    Ini_file f;
    if (!f.Open(configFile_)) {
        throw std::runtime_error("Can't open config file '" + configFile_ + "'");
    }

    for (const auto& prop : defaultSettings_)
    {
        if (!f.ParameterExists(prop.second.section, prop.second.name))
            f.Set_value(prop.second.section, prop.second.name, prop.second.value.c_str());
    }

    f.Save();
}
