project "editor"
    kind "ConsoleApp"
    systemversion "latest"
    staticruntime "on"
    language "C++"
    cppdialect "C++17"
    targetdir "bin"
    objdir "bin-int"
    debugdir "bin"
    files {
        "src/**.h",
        "src/**.cpp"
    }
    includedirs {
        "src",
        "../spruce/src",
        "../spruce/dep/glfw/include",
        "../spruce/dep/glew/include",
        "../spruce/dep/freetype/include",
        "../spruce/dep/imgui",
        "../spruce/dep/entt/src",
        "../spruce/dep/stb",
        "../spruce/dep/lua"
    }

    links {
        "spruce"
    }
    
    filter "system:windows"
        defines "SPR_WINDOWS"
    filter "system:linux"
        defines "SPR_LINUX"

        links {
            "glew",
            "glfw",
            "freetype",
            "imgui",
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
        defines "SPR_DEBUG"
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        optimize "on"
