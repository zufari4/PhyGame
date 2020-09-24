#include "ControlTypes.h"
#include "Utils.h"

namespace GUI
{

    ControlType strToControlType(const std::string& str)
    {
        if (Utils::strncasecpm(str, "button")) {
            return ControlType::Button;
        }
        else if (Utils::strncasecpm(str, "panel")) {
            return ControlType::Panel;
        }
        else if (Utils::strncasecpm(str, "header")) {
            return ControlType::Header;
        }
        else {
            return ControlType::Unknown;
        }
    }

}