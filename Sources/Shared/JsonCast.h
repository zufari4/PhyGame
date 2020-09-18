#pragma once

#include <string>

namespace json
{
    class Object;
}

namespace JsonCast
{
    json::Object loadFromFile(const std::string& jsonFile);
}