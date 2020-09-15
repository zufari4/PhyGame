#include "AlignType.h"
#include "Utils.h"

namespace GUI
{

    AlignType strToAlign(const std::string& val)
    {
        if (Utils::strncasecpm(val, "top")) {
            return AlignType::Top;
        }
        else if (Utils::strncasecpm(val, "bottom")) {
            return AlignType::Botton;
        }
        else if (Utils::strncasecpm(val, "left")) {
            return AlignType::Left;
        }
        else if (Utils::strncasecpm(val, "right")) {
            return AlignType::Right;
        }
        else if (Utils::strncasecpm(val, "fill")) {
            return AlignType::Fill;
        }
        else {
            return AlignType::None;
        }
    }

}