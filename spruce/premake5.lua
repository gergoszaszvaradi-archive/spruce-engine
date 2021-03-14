project "spruce"
    systemversion "latest"
    kind "SharedLib"
    staticruntime "on"
    language "C++"
    cppdialect "C++17"
    targetdir "../bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "../bin-int/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    flags {
        "FatalCompileWarnings"
	}
    files {
        "src/**.h",
        "src/**.cpp"
    }
    includedirs {
        "src",
        "dep/glfw/include",
        "dep/glew/include",
        "dep/freetype/include",
        "dep/imgui/",
        "dep/entt/src",
        "dep/stb",
        "dep/lua"
    }
    
    links {
        "glew",
        "glfw",
        "freetype",
        "imgui",
        "lua"
    }

    defines "GLEW_STATIC"
    
    filter "system:windows"
        defines "SPR_WINDOWS"
        pchheader "sprpch.h"
        pchsource "src/sprpch.cpp"

        -- filter { "files:dep/imgui/backends/imgui_impl_glfw.cpp" }
        --     flags { "NoPCH" }
        -- filter "files:dep/imgui/backends/imgui_impl_opengl3.cpp"
        --     flags { "NoPCH" }

        links {
            "opengl32.lib"
        }

    filter "system:linux"
        defines "SPR_LINUX"

        links {
            "pthread",
            "dl",
            "GLU",
            "GL",
            "rt",
            "Xrandr",
            "Xxf86vm",
            "Xi",
            "Xinerama",
            "X11"
        }
        
    filter "configurations:Debug"
        kind "StaticLib"
        defines "SPR_DEBUG"
        runtime "Debug"
        symbols "on"
        postbuildcommands { "copy ..\\bin\\%{prj.name}\\%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}\\%{prj.name}.lib ..\\example\\bin\\%{prj.name}.lib" }

    filter "configurations:Release"
        kind "StaticLib"
        defines "SPR_RELEASE"
        runtime "Release"
        optimize "on"
        postbuildcommands { "copy ..\\bin\\%{prj.name}\\%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}\\%{prj.name}.lib ..\\example\\bin\\%{prj.name}.lib" }

    filter "configurations:DebugDLL"
        defines {
            "SPR_DEBUG",
            "SPR_BUILD_DLL",
            "SPR_DLL"
        }
        runtime "Debug"
        staticruntime "off"
        symbols "on"
        postbuildcommands { "copy ..\\bin\\%{prj.name}\\%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}\\%{prj.name}.dll ..\\example\\bin\\%{prj.name}.dll" }

    filter "configurations:ReleaseDLL"
        defines {
            "SPR_RELEASE",
            "SPR_BUILD_DLL",
            "SPR_DLL"
        }
        runtime "Release"
        staticruntime "off"
        optimize "on"
        postbuildcommands { "copy ..\\bin\\%{prj.name}\\%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}\\%{prj.name}.dll ..\\example\\bin\\%{prj.name}.dll" }