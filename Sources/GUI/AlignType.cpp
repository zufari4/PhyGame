#include "AlignType.h"
#include "StrUtils.h"

namespace GUI
{

    AlignType strToAlign(const std::string& val)
    {
        if (StrUtils::strncasecpm(val, "top")) {
            return AlignType::Top;
        }
        else if (StrUtils::strncasecpm(val, "bottom")) {
            return AlignType::Bottom;
        }
        else if (StrUtils::strncasecpm(val, "left")) {
            return AlignType::Left;
        }
        else if (StrUtils::strncasecpm(val, "right")) {
            return AlignType::Right;
        }
        else if (StrUtils::strncasecpm(val, "fill")) {
            return AlignType::Fill;
        }
        else if (StrUtils::strncasecpm(val, "center")) {
            return AlignType::Center;
        }
        else {
            return AlignType::None;
        }
    }

}