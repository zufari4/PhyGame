#include "TextAlign.h"
#include "StrUtils.h"

namespace GUI
{

    TextAlign strToTextAlign(const std::string& str)
    {
            
        if (StrUtils::strncasecpm(str, "TopLeft")) {
            return TextAlign::TopLeft;
        }
        else if (StrUtils::strncasecpm(str, "TopCenter")) {
            return TextAlign::TopCenter;
        }
        else if (StrUtils::strncasecpm(str, "TopRight")) {
            return TextAlign::TopRight;
        }
        else if (StrUtils::strncasecpm(str, "MiddleLeft")) {
            return TextAlign::MiddleLeft;
        }
        else if (StrUtils::strncasecpm(str, "MiddleCenter")) {
            return TextAlign::MiddleCenter;
        }
        else if (StrUtils::strncasecpm(str, "MiddleRight")) {
            return TextAlign::MiddleRight;
        }
        else if (StrUtils::strncasecpm(str, "BottomLeft")) {
            return TextAlign::BottomLeft;
        }
        else if (StrUtils::strncasecpm(str, "BottomCenter")) {
            return TextAlign::BottomCenter;
        }
        else if (StrUtils::strncasecpm(str, "BottomRight")) {
            return TextAlign::BottomRight;
        }
        else {
            return TextAlign::Undefined;
        }
    }

}