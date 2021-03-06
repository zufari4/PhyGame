#include "FontManager.h"
#include "FileSystem.h"
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
            if (!FileSystem::FileIsExists(fileName)) {
                throw std::runtime_error("Font file '" + fileName + "' is not found");
            }
            for (const auto& it : fonts_) {
                if (it.fileName == fileName && it.size == size && it.hintType == hintType) {
                    return it.font;
                }
            }
            ImGuiIO& io = ImGui::GetIO();
            ImVector<ImWchar> ranges;
            ImFontAtlas::GlyphRangesBuilder builder;
            builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
            builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());
            builder.AddChar(0x2190);
            builder.BuildRanges(&ranges);
            ImFont* font = io.Fonts->AddFontFromFileTTF(fileName.c_str(), size, nullptr, ranges.Data);
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