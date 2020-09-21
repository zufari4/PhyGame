#include "FontManager.h"
#include "imgui_freetype.h"
#include <stdexcept>
#include <vector>

namespace GUI
{
    namespace FontManager
    {
        struct FontDescription {
            std::string fileName;
            float size;
            unsigned hintType;
            ImFont* font;
        };
        std::vector<FontDescription> fonts_;

        ImFont* CreateFont(const std::string& fileName, float size, unsigned hintType)
        {
            if (fileName.empty()) return nullptr;
            for (const auto& it : fonts_) {
                if (it.fileName == fileName && it.size == size && it.hintType == hintType) {
                    return it.font;
                }
            }
            ImGuiIO& io = ImGui::GetIO();
            ImFont* font = io.Fonts->AddFontFromFileTTF(fileName.c_str(), size, NULL, io.Fonts->GetGlyphRangesCyrillic());
            if (font == NULL) {
                throw std::runtime_error("Can't load font file '" + fileName + "'");
            }
            else {
                ImGuiFreeType::BuildFontAtlas(io.Fonts, hintType);
            }
            if (!font->IsLoaded()) {
                throw std::runtime_error("Can't load font file '" + fileName + "'");
            }
            fonts_.push_back({fileName, size, hintType, font});
            return font;
        }
    }
}