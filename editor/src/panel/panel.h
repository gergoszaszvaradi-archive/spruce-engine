#pragma once
#include "imguiex.h"

namespace spr {

    class Panel {
    public:
        Panel(const std::string& name, ImGuiWindowFlags flags = 0);

        void Show();

        virtual void Render();

        virtual void Content() = 0;

        inline const std::string& GetName() const { return name; }

    protected:
        std::string name;
        bool visible;
        ImGuiWindowFlags flags;
    };

}