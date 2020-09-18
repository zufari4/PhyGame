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
                const auto& margin = ctrl->GetMargin();
                switch (ctrl->GetAlign())
                {
                case AlignType::Top: {
                    x = xOffsetLeft + margin[0];
                    y = yOffsetTop + margin[1];
                    width = remainWidth - (margin[0] + margin[2]);
                    height = ctrl->GetHeight();
                    yOffsetTop += (margin[1] + ctrl->GetHeight() + margin[3]);
                    remainHeight -= (margin[1] + ctrl->GetHeight() + margin[3]);
                } break;
                case AlignType::Bottom: {
                    x = xOffsetLeft + margin[0];
                    y = yOffsetBottom - ctrl->GetHeight() - margin[3];
                    width = remainWidth - (margin[0] + margin[2]);
                    height = ctrl->GetHeight();
                    yOffsetBottom -= (margin[1] + ctrl->GetHeight() + margin[3]);
                    remainHeight -= (margin[1] + ctrl->GetHeight() + margin[3]);
                } break;
                case AlignType::Fill: {
                    x = xOffsetLeft + margin[0];
                    y = yOffsetTop + margin[1];
                    width = remainWidth - (margin[0] + margin[2]);
                    height = remainHeight - (margin[1] + margin[3]);
                    remainWidth = 0;
                    remainHeight = 0;
                    xOffsetLeft = parentWidth;
                    xOffsetRight = 0;
                    yOffsetTop = parentHeight;
                    yOffsetBottom = 0;
                } break;
                case AlignType::Left: {
                    x = xOffsetLeft + margin[0];
                    y = yOffsetTop + margin[1];
                    width = ctrl->GetWidth();
                    height = remainHeight - (margin[1] + margin[3]);
                    remainWidth -= (margin[0] + ctrl->GetWidth() + margin[2]);
                    xOffsetLeft += (margin[0] + ctrl->GetWidth() + margin[2]);
                } break;
                case AlignType::Right: {
                    x = xOffsetRight - ctrl->GetWidth() - margin[2];
                    width = ctrl->GetWidth();
                    height = remainHeight - (margin[1] + margin[3]);
                    remainWidth -= (margin[0] + ctrl->GetWidth()+ margin[2]);
                    xOffsetRight -= (margin[0] + ctrl->GetWidth() + margin[2]);
                } break;
                case AlignType::Center: {
                    x = parentWidth / 2 - ctrl->GetWidth() / 2;
                    y = parentHeight / 2 - ctrl->GetHeight() / 2;
                    width  = ctrl->GetWidth();
                    height = ctrl->GetHeight();
                } break;
                default:
                    x = ctrl->GetPosX();
                    y = ctrl->GetPosY();
                    width = ctrl->GetWidth();
                    height = ctrl->GetHeight();
                    break;
                }
                
                ctrl->SetPos(x, y, width, height);
                UpdateControlsPosition(*ctrl->GetControls(), ctrl->GetWidth(), ctrl->GetHeight());
            }
        }
    }
}