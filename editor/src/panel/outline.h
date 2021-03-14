#pragma once
#include "panel.h"
#include "imguiex.h"
#include "scene/scene.h"
#include "scene/entity.h"
#include "selection.h"
#include "widgets.h"

namespace spr {

    class OutlinePanel : public Panel {
    public:
        OutlinePanel();

        void Content() override;

    private:
        std::string searchQuery;
        bool useSearchQuery;
    };

}