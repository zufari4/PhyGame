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
            return AlignType::Bottom;
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
        else if (Utils::strncasecpm(val, "center")) {
            return AlignType::Center;
        }
        else {
            return AlignType::None;
        }
    }

}