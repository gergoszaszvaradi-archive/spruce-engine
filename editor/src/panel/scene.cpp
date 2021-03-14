#include "sprpch.h"
#include "scene.h"

namespace spr {

    ScenePanel::ScenePanel() : Panel("Scene")
    {
        camera.SetSize(10);
        camera.SetNearClip(-100.0f);
        camera.SetFarClip(100.0f);

        shader = AssetManager<Shader>::Get("assets/shaders/default.glsl");
    }

    void ScenePanel::Content() {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        if (ImGui::IsWindowHovered() && !ImGui::IsWindowFocused() && (ImGui::IsMouseClicked(ImGuiMouseButton_Middle) || io.MouseWheel != 0)) {
            ImGui::FocusWindow(ImGui::GetCurrentContext()->CurrentWindow);
            prevMousePos = ImGui::GetMousePos();
        }

        ImGuiEx::VerticalSpace();
        ImGuiEx::HorizontalSpace();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Add))
            ImGui::OpenPopup("NewEntityPopup");

        Widgets::NewEntityPopup(camera.GetPosition());

        ImGui::SameLine(0, 5.0f);
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine(0, 5.0f);
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Hand, (gizmoType == GizmoType::None) ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) gizmoType = GizmoType::None;
        ImGui::SameLine();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Move, (gizmoType == GizmoType::Translation) ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) gizmoType = GizmoType::Translation;
        ImGui::SameLine();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Rotate, (gizmoType == GizmoType::Rotation) ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) gizmoType = GizmoType::Rotation;
        ImGui::SameLine();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Scale, (gizmoType == GizmoType::Scale) ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) gizmoType = GizmoType::Scale;
        ImGui::SameLine(0, 5.0f);
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine(0, 5.0f);
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Global, (gizmoSpace == GizmoSpace::World) ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) gizmoSpace = (GizmoSpace)(1 - (int)gizmoSpace);
        ImGui::SameLine();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::ThreeD, camera3D ? style.Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 })) {
            if (camera3D)
                camera.SetRotation(0, 0, 0);
            else
                camera.SetRotation(Math::PI * 0.25f, -Math::PI * 0.25f, 0);

            camera3D = !camera3D;
        }

        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 viewportPos = ImGui::GetCursorScreenPos();
        if (viewportPos.x != viewport.x || viewportPos.y != viewport.y) {
            viewport.x = viewportPos.x;
            viewport.y = viewportPos.y;
        }
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (viewportSize.x != viewport.width || viewportSize.y != viewport.height) {
            camera.SetAspectRatio(viewportSize.x / viewportSize.y);
            Renderer::GetFrameBuffer()->Resize(viewportSize.x, viewportSize.y);
            viewport.width = viewportSize.x;
            viewport.height = viewportSize.y;
        }
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->AddRectFilled(viewportPos, { viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y }, ImGui::GetColorU32(ImGuiCol_TitleBg));
        ImGui::Image((ImTextureID)Renderer::GetRendereredTextureID(), ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

        if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && !gizmoUsing && !gizmoHovering) {
            uint32 id = (uint32)Renderer::GetFrameBuffer()->GetPixel(1, PrimitiveType::UInt, (uint32)(mousePos.x - viewportPos.x), (uint32)(viewportSize.y - (mousePos.y - viewportPos.y)));
            if (id)
                Selection::Set({ id - 1, Scene::GetActiveScene() });
            else
                Selection::Clear();
        }

        // Editor Camera control
        hovered = ImGui::IsWindowHovered();
        active = (hovered && ImGui::IsWindowFocused());

        if (active) {
            if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) || (gizmoType == GizmoType::None && ImGui::IsMouseDown(ImGuiMouseButton_Left))) {
                float size = camera.GetSize() * 2.0f;
                float aspect = camera.GetAspectRatio();
                if (io.KeyAlt) {
                    Vector3D rot = camera.GetRotation();
                    camera.SetRotation(rot.x + Math::ToRad((prevMousePos.y - mousePos.y)), rot.y + Math::ToRad((prevMousePos.x - mousePos.x)), 0.0f);
                    if (prevMousePos.x != mousePos.x || prevMousePos.y != mousePos.y) camera3D = true;
                }
                else {
                    Vector3D pos = camera.GetPosition();
                    camera.SetPosition(pos.x + (prevMousePos.x - mousePos.x) * size * aspect / viewport.width, pos.y - (prevMousePos.y - mousePos.y) * size / viewport.height);
                }
            }

            float newSize = camera.GetSize() * (1.0f - io.MouseWheel * 0.1f);
            if (newSize < 0.1f) newSize = 0.1f;
            if (newSize > 100.0f) newSize = 100.0f;
            camera.SetSize(newSize);
        }

        // Gizmo
        if (!Selection::IsEmpty() && gizmoType != GizmoType::None) {
            Entity entity = Selection::GetEntity();
            Transform& transform = entity.GetComponent<Transform>();

            if (entity.HasComponent<SpriteRenderer>()) {
                DrawSpriteRendererGizmo(transform);
            }

            DrawTransformGizmo(transform, gizmoSpace, gizmoType);
        }

        prevMousePos = mousePos;
    }
    
    void ScenePanel::DrawTransformGizmo(Transform& transform, GizmoSpace space, GizmoType type) {
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        Vector3D relScreenPos = camera.GetViewProjection() * transform.position;
        ImVec2 screenPos = { roundf((relScreenPos.x + 1.0f) / 2.0f * viewport.width + viewport.x), roundf(viewport.height - (relScreenPos.y + 1.0f) / 2.0f * viewport.height + viewport.y) };
        ImVec2 mousePos = ImGui::GetMousePos();

        const float GIZMO_SIZE = 100.0f;
        const float GIZMO_END_SIZE = 15.0f;
        const float GIZMO_TRANSLATION_SNAP = 0.25f;
        const float GIZMO_ROTATION_SNAP = 15.0f;
        float rCos1 = 1.0f;
        float rSin1 = 0.0f;
        float rCos2 = 1.0f;
        float rSin2 = 0.0f;
        if (space == GizmoSpace::Local || type != GizmoType::Translation) {
            rCos1 = cosf(transform.rotation.z);
            rSin1 = sinf(transform.rotation.z);
            rCos2 = cosf(-transform.rotation.z);
            rSin2 = sinf(-transform.rotation.z);
        }
        auto Rotate = [&](ImVec2 pos) { return ImVec2{ roundf(screenPos.x + (pos.x - screenPos.x) * rCos1 + (pos.y - screenPos.y) * rSin1), roundf(screenPos.y - (pos.x - screenPos.x) * rSin1 + (pos.y - screenPos.y) * rCos1) }; };
        auto InverseRotate = [&](ImVec2 pos) { return ImVec2{ roundf(screenPos.x + (pos.x - screenPos.x) * rCos2 + (pos.y - screenPos.y) * rSin2), roundf(screenPos.y - (pos.x - screenPos.x) * rSin2 + (pos.y - screenPos.y) * rCos2) }; };

        mousePos = InverseRotate(mousePos);
        float cameraSize = camera.GetSize() * 2.0f;
        float cameraAspect = camera.GetAspectRatio();
        float unitSize = viewport.height / cameraSize;

        bool xAxisActive = ((gizmoUsing && gizmoCurrentAxis == GizmoActiveAxis::X) || (mousePos.x >= screenPos.x + GIZMO_END_SIZE * 0.5f && mousePos.x <= screenPos.x + GIZMO_SIZE && mousePos.y >= screenPos.y - GIZMO_END_SIZE * 0.5f && mousePos.y <= screenPos.y + GIZMO_END_SIZE * 0.5f));
        bool yAxisActive = ((gizmoUsing && gizmoCurrentAxis == GizmoActiveAxis::Y) || (mousePos.x >= screenPos.x - GIZMO_END_SIZE * 0.5f && mousePos.x <= screenPos.x + GIZMO_END_SIZE * 0.5f && mousePos.y >= screenPos.y - GIZMO_SIZE && mousePos.y <= screenPos.y - GIZMO_END_SIZE * 0.5f));
        bool zAxisActive = ((gizmoUsing && gizmoCurrentAxis == GizmoActiveAxis::XY) || (mousePos.x >= screenPos.x + 25 && mousePos.x <= screenPos.x + 50 && mousePos.y >= screenPos.y - 50 && mousePos.y <= screenPos.y - 25));

        ImU32 hoverColor = IM_COL32(232, 210, 18, 255);
        ImU32 oldColor = IM_COL32(100, 100, 100, 255);
        ImU32 xColor = IM_COL32(251, 91, 80, 255);
        ImU32 yColor = IM_COL32(108, 193, 40, 255);
        ImU32 zColor = IM_COL32(18, 104, 232, 255);
        ImU32 xAxisColor = (xAxisActive) ? hoverColor : xColor;
        ImU32 yAxisColor = (yAxisActive) ? hoverColor : yColor;
        ImU32 zAxisColor = (zAxisActive) ? hoverColor : zColor;

        drawList->PushClipRect({ viewport.x, viewport.y }, { viewport.x + viewport.width, viewport.y + viewport.height });

        if (type == GizmoType::Translation) {
            if (gizmoUsing) {
                Vector3D startRelScreenPos = camera.GetViewProjection() * gizmoStartTransform.position;
                ImVec2 startScreenPos = { roundf((startRelScreenPos.x + 1.0f) / 2.0f * viewport.width + viewport.x), roundf(viewport.height - (startRelScreenPos.y + 1.0f) / 2.0f * viewport.height + viewport.y) };
                drawList->AddLine(startScreenPos, screenPos, oldColor, 2.0f);
                drawList->AddCircleFilled(startScreenPos, 5.5f, oldColor, 12);
            }

            drawList->AddLine(screenPos, Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE * 0.5f, screenPos.y }), xAxisColor, 3.0f);
            drawList->AddLine(screenPos, Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE * 0.5f }), yAxisColor, 3.0f);

            drawList->AddTriangleFilled(Rotate({ screenPos.x + GIZMO_SIZE, screenPos.y }), Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE, screenPos.y - GIZMO_END_SIZE * 0.5f }), Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE, screenPos.y + GIZMO_END_SIZE * 0.5f }), xAxisColor);
            drawList->AddTriangleFilled(Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE }), Rotate({ screenPos.x - GIZMO_END_SIZE * 0.5f, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE }), Rotate({ screenPos.x + GIZMO_END_SIZE * 0.5f, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE }), yAxisColor);
            drawList->AddLine(Rotate({ screenPos.x + 38, screenPos.y - 26 }), Rotate({ screenPos.x + 38, screenPos.y - 51 }), zAxisColor, 25);
        }
        else if (type == GizmoType::Rotation) {
            float arcRadius = GIZMO_SIZE - 8.0f;
            float arcDist = 0.552284749831f * arcRadius;

            float mousePosDistFromOrigin = (mousePos.x - screenPos.x - 5) * (mousePos.x - screenPos.x - 5) + (mousePos.y - screenPos.y + 5) * (mousePos.y - screenPos.y + 5);
            xAxisActive = yAxisActive = false;
            xAxisColor = xColor;
            yAxisColor = yColor;
            zAxisActive = ((gizmoUsing && gizmoCurrentAxis == GizmoActiveAxis::XY) || (mousePos.x > screenPos.x + 5 && mousePos.y < screenPos.y - 5 && mousePosDistFromOrigin > (arcRadius - 10) * (arcRadius - 10) && mousePosDistFromOrigin < (arcRadius + 5) * (arcRadius + 5)));
            zAxisColor = (zAxisActive) ? hoverColor : zColor;

            drawList->AddLine(screenPos, Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE * 0.5f, screenPos.y }), xAxisColor, 3.0f);
            drawList->AddLine(screenPos, Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE * 0.5f }), yAxisColor, 3.0f);

            drawList->AddTriangleFilled(Rotate({ screenPos.x - 5, screenPos.y - GIZMO_SIZE + 10 }), Rotate({ screenPos.x + 5, screenPos.y - GIZMO_SIZE + 10 }), Rotate({ screenPos.x + 5, screenPos.y - GIZMO_SIZE }), yAxisColor);
            drawList->AddTriangleFilled(Rotate({ screenPos.x + GIZMO_SIZE - 10, screenPos.y - 5 }), Rotate({ screenPos.x + GIZMO_SIZE - 10, screenPos.y + 5 }), Rotate({ screenPos.x + GIZMO_SIZE, screenPos.y - 5 }), xAxisColor);
            drawList->AddBezierCurve(Rotate({ screenPos.x + 5, screenPos.y - GIZMO_SIZE + 6 }), Rotate({ screenPos.x + 5 + arcDist, screenPos.y - GIZMO_SIZE + 6 }), Rotate({ screenPos.x + GIZMO_SIZE - 6, screenPos.y - 5 - arcDist }), Rotate({ screenPos.x + GIZMO_SIZE - 6, screenPos.y - 5 }), zAxisColor, 3.0f, 12);
        }
        else if (type == GizmoType::Scale) {
            if (gizmoUsing) {
                drawList->AddLine(screenPos, Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE * 0.5f, screenPos.y }), oldColor, 3.0f);
                drawList->AddLine(screenPos, Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE * 0.5f }), oldColor, 3.0f);
                drawList->AddLine(Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE, screenPos.y }), Rotate({ screenPos.x + GIZMO_SIZE, screenPos.y }), oldColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE }), Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE }), oldColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x + 38, screenPos.y - 26 }), Rotate({ screenPos.x + 38, screenPos.y - 51 }), oldColor, GIZMO_SIZE * 0.25f);

                float xDist = (gizmoCurrentAxis == GizmoActiveAxis::X) ? (gizmoStartMousePos.x - mousePos.x) : 0.0f;
                float yDist = (gizmoCurrentAxis == GizmoActiveAxis::Y) ? (gizmoStartMousePos.y - mousePos.y) : 0.0f;
                float xyDist = (gizmoCurrentAxis == GizmoActiveAxis::XY) ? ((gizmoStartMousePos.x - mousePos.x) - (gizmoStartMousePos.y - mousePos.y)) * 0.5f : 0.0f;
                drawList->AddLine(Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE - xDist, screenPos.y }), Rotate({ screenPos.x + GIZMO_SIZE - xDist, screenPos.y }), xAxisColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE - yDist }), Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE - yDist }), yAxisColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x + 38 - xyDist, screenPos.y - 26 + xyDist }), Rotate({ screenPos.x + 38 - xyDist, screenPos.y - 51 + xyDist }), zAxisColor, GIZMO_SIZE * 0.25f);

                drawList->AddLine(screenPos, Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE * 0.5f - xDist, screenPos.y }), xAxisColor, 3.0f);
                drawList->AddLine(screenPos, Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE * 0.5f - yDist }), yAxisColor, 3.0f);
            }
            else {
                drawList->AddLine(screenPos, Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE * 0.5f, screenPos.y }), xAxisColor, 3.0f);
                drawList->AddLine(screenPos, Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE * 0.5f }), yAxisColor, 3.0f);

                drawList->AddLine(Rotate({ screenPos.x + GIZMO_SIZE - GIZMO_END_SIZE, screenPos.y }), Rotate({ screenPos.x + GIZMO_SIZE, screenPos.y }), xAxisColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE + GIZMO_END_SIZE }), Rotate({ screenPos.x, screenPos.y - GIZMO_SIZE }), yAxisColor, GIZMO_END_SIZE);
                drawList->AddLine(Rotate({ screenPos.x + 38, screenPos.y - 26 }), Rotate({ screenPos.x + 38, screenPos.y - 51 }), zAxisColor, GIZMO_SIZE * 0.25f);
            }
        }

        drawList->AddCircleFilled(screenPos, 5.5f, 0xFFFFFFFF, 12);

        drawList->PopClipRect();

        gizmoHovering = (xAxisActive || yAxisActive || zAxisActive);

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !gizmoUsing && gizmoHovering) {
            if (xAxisActive) gizmoCurrentAxis = GizmoActiveAxis::X;
            if (yAxisActive) gizmoCurrentAxis = GizmoActiveAxis::Y;
            if (zAxisActive) gizmoCurrentAxis = GizmoActiveAxis::XY;
            gizmoUsing = true;
            gizmoStartTransform = transform;
            gizmoStartMousePos = mousePos;
        }

        if (gizmoUsing) {
            float factor = 1.0f;
            if (io.KeyShift) factor = 5.0f;
            if (io.KeyAlt) factor = 0.25f;

            ImVec2 pMousePos = InverseRotate(prevMousePos);
            if (type == GizmoType::Translation) {
                float tx = (gizmoStartMousePos.x - mousePos.x) * cameraSize * cameraAspect / viewport.width * factor;
                float ty = (gizmoStartMousePos.y - mousePos.y) * cameraSize / viewport.height * factor;

                if (io.KeyCtrl) {
                    tx = roundf(tx / GIZMO_TRANSLATION_SNAP) * GIZMO_TRANSLATION_SNAP;
                    ty = roundf(ty / GIZMO_TRANSLATION_SNAP) * GIZMO_TRANSLATION_SNAP;
                }

                if (gizmoCurrentAxis == GizmoActiveAxis::X || gizmoCurrentAxis == GizmoActiveAxis::XY)
                    transform.position.x = gizmoStartTransform.position.x - tx;
                if (gizmoCurrentAxis == GizmoActiveAxis::Y || gizmoCurrentAxis == GizmoActiveAxis::XY)
                    transform.position.y = gizmoStartTransform.position.y + ty;
            }
            else if (type == GizmoType::Rotation) {
                float r = Math::ToRad((ImGui::GetMouseDragDelta(ImGuiMouseButton_Left)).x) * 0.5f * factor;
                if (io.KeyCtrl) {
                    float rs = Math::ToRad(GIZMO_ROTATION_SNAP);
                    r = roundf(r / rs) * rs;
                }
                transform.rotation.z = gizmoStartTransform.rotation.z - r;
            }
            else if (type == GizmoType::Scale) {
                if (gizmoCurrentAxis == GizmoActiveAxis::X)
                    transform.scale.x = gizmoStartTransform.scale.x - (gizmoStartMousePos.x - mousePos.x) / 100.0f * factor;
                if (gizmoCurrentAxis == GizmoActiveAxis::Y)
                    transform.scale.y = gizmoStartTransform.scale.y + (gizmoStartMousePos.y - mousePos.y) / 100.0f * factor;
                if (gizmoCurrentAxis == GizmoActiveAxis::XY) {
                    float r = gizmoStartTransform.scale.x / gizmoStartTransform.scale.y;
                    float dist = ((gizmoStartMousePos.x - mousePos.x) - (gizmoStartMousePos.y - mousePos.y)) * 0.5f;
                    transform.scale.x = gizmoStartTransform.scale.x - dist / 100.0f * r * factor;
                    transform.scale.y = gizmoStartTransform.scale.y - dist / 100.0f * factor;
                }
            }
        }

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) gizmoUsing = false;
    }

    void ScenePanel::DrawSpriteRendererGizmo(Transform& transform)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        Vector3D relScreenPos = camera.GetViewProjection() * transform.position;
        ImVec2 screenPos = { roundf((relScreenPos.x + 1.0f) / 2.0f * viewport.width + viewport.x), roundf(viewport.height - (relScreenPos.y + 1.0f) / 2.0f * viewport.height + viewport.y) };

        float cameraSize = camera.GetSize() * 2.0f;
        float unitSize = viewport.height / cameraSize;

        float rCos = cosf(transform.rotation.z);
        float rSin = sinf(transform.rotation.z);
        auto Rotate = [&](ImVec2 pos) { return ImVec2{ roundf(screenPos.x + (pos.x - screenPos.x) * rCos + (pos.y - screenPos.y) * rSin), roundf(screenPos.y - (pos.x - screenPos.x) * rSin + (pos.y - screenPos.y) * rCos) }; };

        ImVec2 bounds[4] = {
            Rotate({screenPos.x - unitSize * transform.scale.x * 0.5f, screenPos.y - unitSize * transform.scale.y * 0.5f}),
            Rotate({screenPos.x + unitSize * transform.scale.x * 0.5f, screenPos.y - unitSize * transform.scale.y * 0.5f}),
            Rotate({ screenPos.x + unitSize * transform.scale.x * 0.5f, screenPos.y + unitSize * transform.scale.y * 0.5f}),
            Rotate({ screenPos.x - unitSize * transform.scale.x * 0.5f, screenPos.y + unitSize * transform.scale.y * 0.5f})
        };

        ImU32 color = IM_COL32(232, 210, 18, 255);
        drawList->AddPolyline(bounds, 4, color, true, 1.0f);
    }

    void ScenePanel::DrawGrid()
    {
        float size = camera.GetSize() * 2.0f;
        float aspect = camera.GetAspectRatio();
        float lineWidth = size / viewport.height;

        float unitSize = (size >= 20.0f) ? 10.0f : (size >= 2.0f) ? 1.0f : 0.1f;

        float gridHorizontalLinesCount = ceilf(size * aspect / unitSize * 0.5f);
        float gridVerticalLinesCount = ceilf(size / unitSize * 0.5f);

        Vector3D pos = camera.GetPosition();
        Vector2D gridOrigin = { roundf(pos.x / unitSize) * unitSize, roundf(pos.y / unitSize) * unitSize };

        for (float x = -unitSize * gridHorizontalLinesCount; x <= unitSize * gridHorizontalLinesCount; x += unitSize) {
            for (float y = -unitSize * gridVerticalLinesCount; y <= unitSize * gridVerticalLinesCount; y += unitSize) {
                Matrix4 translation = Matrix4::Translation(gridOrigin.x + x, gridOrigin.y + y);
                Renderer::SubmitQuad(0, translation * Matrix4::Scaled(size * aspect, lineWidth), { 0.2f, 0.2f, 0.2f, 1.0f }, shader);
                Renderer::SubmitQuad(0, translation * Matrix4::Scaled(lineWidth, size), { 0.2f, 0.2f, 0.2f, 1.0f }, shader);
            }
        }

        Renderer::SubmitQuad(0, Matrix4::Translation(pos.x, 0) * Matrix4::Scaled(size * aspect, lineWidth * 2.0f), { 0.54117f, 0.25490f, 0.29411f, 1.0f }, shader); // red 
        Renderer::SubmitQuad(0, Matrix4::Translation(0, pos.y) * Matrix4::Scaled(lineWidth * 2.0f, size), { 0.36862f, 0.48627f, 0.2f, 1.0f }, shader); // green
    }

    void ScenePanel::OnUpdate()
    {
        Renderer::Begin(camera);
        DrawGrid();

        if (Scene::GetActiveScene())
            Scene::GetActiveScene()->OnUpdate();

        Renderer::End();
    }

    void ScenePanel::OnEvent(Event& e) {
        if (e.type == EventType::KeyPressed) {
            if (!gizmoUsing && hovered) {
                if (e.keyboard.key == KeyCode::Q) gizmoType = GizmoType::None;
                if (e.keyboard.key == KeyCode::W) gizmoType = GizmoType::Translation;
                if (e.keyboard.key == KeyCode::E) gizmoType = GizmoType::Rotation;
                if (e.keyboard.key == KeyCode::R) gizmoType = GizmoType::Scale;
            }

            if (!Selection::IsEmpty() && e.keyboard.key == KeyCode::Del) {
                Scene::GetActiveScene()->RemoveEntity(Selection::GetEntity());
                Selection::Clear();
            }
        }
    }

}