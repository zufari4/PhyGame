#include "AlignHelper.h"

namespace GUI
{
    namespace AlignHelper
    {
        void UpdateControlsPosition(tdControls& controls, int parentWidth, int parentHeight)
        {
            int remainWidth = parentWidth;
            int remainHeight = parentHeight;
            int xOffsetLeft = 0;
            int yOffsetTop = 0;
            int xOffsetRight = parentWidth;
            int yOffsetBottom = parentHeight;
            int x = 0;
            int y = 0;
            int width = 0;
            int height = 0;

            for (const auto& ctrl : controls) {

                switch (ctrl->GetAlign())
                {
                case AlignType::Top: {
                    x = xOffsetLeft;
                    y = yOffsetTop;
                    width = remainWidth;
                    height = std::min(ctrl->GetHeight(), remainHeight);
                    yOffsetTop += ctrl->GetHeight();
                    remainHeight -= ctrl->GetHeight();
                } break;
                case AlignType::Bottom: {
                    x = xOffsetLeft;
                    y = yOffsetBottom - ctrl->GetHeight();
                    width = remainWidth;
                    height = std::min(ctrl->GetHeight(), remainHeight);
                    yOffsetBottom -= ctrl->GetHeight();
                    remainHeight -= ctrl->GetHeight();
                } break;
                case AlignType::Fill: {
                    x = 0;
                    y = 0;
                    width = parentWidth;
                    height = parentHeight;
                    remainWidth = 0;
                    remainHeight = 0;
                    xOffsetLeft = parentWidth;
                    xOffsetRight = 0;
                    yOffsetTop = parentHeight;
                    yOffsetBottom = 0;
                } break;
                case AlignType::Left: {
                    x = xOffsetLeft;
                    y = yOffsetTop;
                    width = std::min(ctrl->GetWidth(), remainWidth);
                    height = remainHeight;
                    remainWidth -= ctrl->GetWidth();
                    xOffsetLeft += ctrl->GetWidth();
                } break;
                case AlignType::Right: {
                    x = xOffsetLeft - ctrl->GetWidth();
                    width = std::min(ctrl->GetWidth(), remainWidth);
                    height = remainHeight;
                    remainWidth -= ctrl->GetWidth();
                    xOffsetRight -= ctrl->GetWidth();
                } break;
                case AlignType::Center: {
                    x = parentWidth / 2 - ctrl->GetWidth() / 2;
                    y = parentHeight / 2 - ctrl->GetHeight() / 2;
                    width  = ctrl->GetWidth();
                    height = ctrl->GetHeight();
                } break;
                }
                ctrl->SetPos(x, y, width, height);
                UpdateControlsPosition(*ctrl->GetControls(), ctrl->GetWidth(), ctrl->GetHeight());
            }
        }
    }
}