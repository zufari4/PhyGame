#include "JsonCast.h"
#include "Utils.h"
#include "elements.h"
#include "reader.h"
#include <sstream>

namespace JsonCast
{
    json::Object loadFromFile(const std::string& jsonFile)
    {
        const auto jsonText = Utils::ReadFile(jsonFile);
        std::istringstream istr(jsonText);
        json::Object obj;
        json::Reader::Read(obj, istr);
        return obj;
    }

}