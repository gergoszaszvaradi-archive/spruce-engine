#pragma once
#include "core.h"
#include "imgui.h"
#include "selection.h"
#include "scene/entity.h"
#include "system/assets.h"
#include "math/vector3D.h"

namespace spr {

    class Widgets {
    public:
        static void NewEntityPopup(const Vector3D& newEntityPosition = { 0, 0 });
    };

}