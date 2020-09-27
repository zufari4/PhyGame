#include "ControlTypes.h"
#include "StrUtils.h"

namespace GUI
{

    ControlType strToControlType(const std::string& str)
    {
        if (StrUtils::strncasecpm(str, "button")) {
            return ControlType::Button;
        }
        else if (StrUtils::strncasecpm(str, "panel")) {
            return ControlType::Panel;
        }
        else if (StrUtils::strncasecpm(str, "label")) {
            return ControlType::Label;
        }
        else {
            return ControlType::Unknown;
        }
    }

}