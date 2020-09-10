#pragma once

#include <string>
#include <unordered_map>

class SettingsManager
{
public:
    struct Property
    {
        std::string    section;
        std::string    name;
        std::string    value;
    };

    using tdProperties = std::unordered_map<int, Property>;

    SettingsManager(const std::string& configFile, const tdProperties& defaultSettings, bool fillConfigFile);
    int64_t     GetPropertyAsInteger(int propertyID) const;
    uint64_t    GetPropertyAsUnsigned(int propertyID) const;
    float       GetPropertyAsFloat(int propertyID) const;
    std::string GetPropertyAsString(int propertyID) const;
    bool        GetPropertyAsBool(int propertyID) const;
    void SetPropertyValue(int propertyID, int64_t val) const;
    void SetPropertyValue(int propertyID, uint64_t val) const;
    void SetPropertyValue(int propertyID, float val) const;
    void SetPropertyValue(int propertyID, const std::string& val) const;
    void SetPropertyValue(int propertyID, bool val) const;
private:
    std::string configFile_;
    const tdProperties& defaultSettings_;

    void createConfigFile() const;
    const Property& GetDefaultProperty(int propertyID) const;
};