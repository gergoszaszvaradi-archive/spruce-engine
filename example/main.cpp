#include "spruce.h"

#include "graphics/texture.h"


#include "lua/luaex.h"

#define GRIDSIZE 50
#define TESTSIZE 1000000
#define TESTCOUNT 1

//struct Point {
//    float x, y;
//    Point(float x, float y) : x(x), y(y) {};
//    ~Point() {
//        spr::Console::LogWarning("Point DTOR!");
//    }
//
//    float Length() {
//        return x * x + y * y;
//    }
//};
//
//struct MultiPoint {
//    Point *a, *b;
//
//    MultiPoint() : a(new Point(1, 2)), b(new Point(3, 4)) {};
//    ~MultiPoint() {
//        spr::Console::LogWarning("DTOR!");
//        delete a;
//        delete b;
//    }
//
//    Point* WithMaxLength() {
//        return (a->Length() > b->Length()) ? a : b;
//    }
//
//    void NoRet() {
//        spr::Console::LogWarning("NO RET");
//    }
//};

class Example : public spr::Application {
public:
    spr::Ref<spr::Shader> shader;

    spr::Ref<spr::Texture> texture1;
    spr::Ref<spr::Texture> texture2;

    spr::Ref<spr::Scene> scene;
    spr::Entity entity;

    spr::Camera camera;

    void OnStart() {
        spr::Console::Log("STARTED");

        camera.SetSize(10);
        camera.SetAspectRatio(1280.0f / 720.0f);

        shader = spr::AssetManager<spr::Shader>::Get("assets/shaders/default.glsl");

        texture1 = spr::AssetManager<spr::Texture>::Get("assets/textures/test.png");

        //scene = spr::Scene::Create();
        //entity = scene->CreateEntity();
        //auto& spr = entity.AddComponent<spr::SpriteRenderer>(shader);
        //spr.texture = texture1;

        //spr::LuaClass<Point>("Point")
        //    .AddConstructor<float, float>()
        //    .AddProperty<float>("x", &Point::x)
        //    .AddProperty<float>("y", &Point::y)
        //    .AddFunction<float>("Length", &Point::Length);

        //spr::LuaClass<MultiPoint>("MultiPoint")
        //    .AddConstructor<>()
        //    .AddDestructor()
        //    .AddProperty<Point*>("a", &MultiPoint::a)
        //    .AddProperty<Point*>("b", &MultiPoint::b)
        //    .AddFunction<Point*>("WithMaxLength", &MultiPoint::WithMaxLength)
        //    .AddFunction<void>("NoRet", &MultiPoint::NoRet);

        spr::Lua::Run(R"(
            scene = Scene();
            e = scene:CreateEntity("FromLua")
        )");

        spr::Scene* scene = (spr::Scene*)spr::Lua::GetUserData("scene");
        spr::Entity e = spr::Lua::Get<spr::Entity>("e");

        //spr::Vector2D* p = (spr::Vector2D*)spr::Lua::GetUserData("p");
        //spr::Console::Log(p->x, p->y);
        //
        //float t = spr::Lua::Get<float>("t");
        //spr::Console::Log(t);
    }

    void OnClose() {
        spr::Console::Log("CLOSED");
    }

    void OnEvent(spr::Event& e) {
        //spr::Console::Log("Event", e, "from", w->GetID());

        if (e.type == spr::EventType::WindowResized) {
            camera.SetAspectRatio((float)e.size.width / e.size.height);
        }
    }

    void OnUpdate() {
        // entity.GetComponent<spr::Transform>().rotation.z += 0.001f;

        spr::Renderer::Begin(camera);
        // scene->OnUpdate();
        spr::Renderer::End();
    }

    void OnUI() {
    }
};

int main() {
    spr::WindowProps props;
    props.vSync = false;
    spr::CreateApplication<Example>(props);
}

#ifndef SPR_DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    main();
    return 0;
}
#endif