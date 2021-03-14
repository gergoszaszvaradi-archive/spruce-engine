#pragma once
#include "panel.h"
#include "engine/event.h"
#include "graphics/renderer.h"
#include "scene/entity.h"
#include "scene/scene.h"
#include "selection.h"
#include "util/rect.h"
#include "widgets.h"

#include "system/time.h"

namespace spr {

    enum class GizmoType {
        None,
        Translation,
        Rotation,
        Scale,
        Rect
    };

    enum class GizmoSpace {
        World,
        Local
    };

    enum class GizmoActiveAxis {
        None,
        X,
        Y,
        XY
    };

    class ScenePanel : public Panel {
    public:
        ScenePanel();

        void Content() override;

        void DrawTransformGizmo(Transform& transform, GizmoSpace space, GizmoType type);
        void DrawSpriteRendererGizmo(Transform& transform);

        //void DrawGizmo(GizmoType type, const Rectf& viewport, Vector3D& position, Vector3D& rotation, Vector3D& scale);

        void OnUpdate();
        void OnEvent(Event& e);

    private:
        void DrawGrid();

        bool active = false;
        bool hovered = false;
        spr::Camera camera;
        bool camera3D = false;
        Ref<Shader> shader;

        Rectf viewport;
        ImVec2 prevMousePos;

        GizmoType gizmoType = GizmoType::Translation;
        GizmoSpace gizmoSpace = GizmoSpace::World;
        bool gizmoUsing = false;
        bool gizmoHovering = false;
        GizmoActiveAxis gizmoCurrentAxis = GizmoActiveAxis::None;
        Transform gizmoStartTransform;
        ImVec2 gizmoStartMousePos;
    };

}