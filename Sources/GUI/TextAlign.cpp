#include "TextAlign.h"
#include "Utils.h"

namespace GUI
{

    TextAlign strToTextAlign(const std::string& str)
    {
            
        if (Utils::strncasecpm(str, "TopLeft")) {
            return TextAlign::TopLeft;
        }
        else if (Utils::strncasecpm(str, "TopCenter")) {
            return TextAlign::TopCenter;
        }
        else if (Utils::strncasecpm(str, "TopRight")) {
            return TextAlign::TopRight;
        }
        else if (Utils::strncasecpm(str, "MiddleLeft")) {
            return TextAlign::MiddleLeft;
        }
        else if (Utils::strncasecpm(str, "MiddleCenter")) {
            return TextAlign::MiddleCenter;
        }
        else if (Utils::strncasecpm(str, "MiddleRight")) {
            return TextAlign::MiddleRight;
        }
        else if (Utils::strncasecpm(str, "BottomLeft")) {
            return TextAlign::BottomLeft;
        }
        else if (Utils::strncasecpm(str, "BottomCenter")) {
            return TextAlign::BottomCenter;
        }
        else if (Utils::strncasecpm(str, "BottomRight")) {
            return TextAlign::BottomRight;
        }
        else {
            return TextAlign::Undefined;
        }
    }

}