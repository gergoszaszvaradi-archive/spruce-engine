#pragma once
#include "core.h"
#include "engine/window.h"
#include "graphics/renderer.h"
#include "util/size.h"
#include "iconset.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace spr {

    enum class UITextAlignment {
        Left = 0,
        Top = 0,
        Center = 1,
        Middle = 1,
        Right = 2,
        Bottom = 2
    };

    struct UIContext {
        Vector4D color = {1, 1, 1, 1}; // ? Maybe use the Color class?
        Ref<Font> font;
        Ref<Texture> texture;
        Ref<Shader> shader;
        float depth = 0.0f;
        Matrix4 projection;
    };

    struct UIStyle {
        Vector4D textColor = { 1, 1, 1, 1 };
        Vector4D buttonColor = {97 / 255.0f, 130 / 255.0f, 160 / 255.0f};
        Vector4D buttonHoverColor = { 97 / 255.0f, 130 / 255.0f, 160 / 255.0f };
        Vector4D buttonActiveColor = { 97 / 255.0f, 130 / 255.0f, 160 / 255.0f };
    };

    class UI {
    public:
        SPR_API static void Init(uint32 width, uint32 height);
        SPR_API static void Resize(uint32 width, uint32 height);
        SPR_API static void Dispose();

        SPR_API static void BeginFrame();
        SPR_API static void EndFrame();

        SPR_API static const UIContext& GetContext() { return context; }
        SPR_API static void SetContext(const UIContext& context) { UI::context = context; }
        SPR_API static void SetColor(const Vector4D& color) { context.color = color; }
        SPR_API static void SetFont(const Ref<Font>& font) { context.font = font; }
        SPR_API static void SetTexture(const Ref<Texture>& texture) { context.texture = texture; }
        SPR_API static void SetShader(const Ref<Shader>& shader) { context.shader = shader; }
        SPR_API static void Higher() { context.depth += 1.0f; }
        SPR_API static void Lower() { context.depth -= 1.0f; }

        SPR_API static void Rect(const Rectf& rect);
        SPR_API static void Text(const Rectf& rect, const std::wstring& text);
        SPR_API static void TextAligned(const Rectf& rect, const std::wstring& text, UITextAlignment hAlign, UITextAlignment vAlign);
        SPR_API static bool Button(const Rectf& rect, const std::wstring& text);
        SPR_API static void Icon(const Rectf& rect, const Ref<UIIconSet>& iconSet, uint32 idx);

        SPR_API static Sizef GetTextDimensions(const std::wstring& text);

    private:
        static SPR_API UIContext context;
        static SPR_API UIStyle style;
    };

}