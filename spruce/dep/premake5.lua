project "glew"
    kind "StaticLib"
    location "%{prj.name}"
    language "C"
    systemversion "latest"
    staticruntime "on"

    targetdir "./%{prj.name}/bin"
    objdir "./%{prj.name}/bin-int"

    includedirs {
        "./%{prj.name}/include"
    }

    files {
        "./%{prj.name}/include/GL/glew.h",
        "./%{prj.name}/src/glew.c"
    }

    defines {
        "GLEW_STATIC",
        "_LIB"
    }

    filter "system:windows"
        files {
            "./%{prj.name}/include/GL/wglew.h"
        }

        defines {
            "WIN32",
            "WIN32_LEAN_AND_MEAN"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines "_DEBUG"
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines "NDEBUG"

project "glfw"
    kind "StaticLib"
    location "%{prj.name}"
    language "C"
    systemversion "latest"
    staticruntime "on"

    targetdir "./%{prj.name}/bin"
    objdir "./%{prj.name}/bin-int"

    files {
        "./%{prj.name}/include/GLFW/glfw3.h",
        "./%{prj.name}/include/GLFW/glfw3native.h",
        "./%{prj.name}/src/glfw_config.h",
        "./%{prj.name}/src/context.c",
        "./%{prj.name}/src/init.c",
        "./%{prj.name}/src/input.c",
        "./%{prj.name}/src/monitor.c",
        "./%{prj.name}/src/vulkan.c",
        "./%{prj.name}/src/window.c"
    }

    filter "system:windows"
        files {
            "./%{prj.name}/src/win32_init.c",
            "./%{prj.name}/src/win32_joystick.c",
            "./%{prj.name}/src/win32_monitor.c",
            "./%{prj.name}/src/win32_time.c",
            "./%{prj.name}/src/win32_thread.c",
            "./%{prj.name}/src/win32_window.c",
            "./%{prj.name}/src/wgl_context.c",
            "./%{prj.name}/src/egl_context.c",
            "./%{prj.name}/src/osmesa_context.c"
        }
        
        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "system:linux"
        pic "on"

        files {
            "./%{prj.name}/src/x11_init.c",
            "./%{prj.name}/src/x11_monitor.c",
            "./%{prj.name}/src/x11_window.c",
            "./%{prj.name}/src/xkb_unicode.c",
            "./%{prj.name}/src/posix_time.c",
            "./%{prj.name}/src/posix_thread.c",
            "./%{prj.name}/src/glx_context.c",
            "./%{prj.name}/src/egl_context.c",
            "./%{prj.name}/src/osmesa_context.c",
            "./%{prj.name}/src/linux_joystick.c"
        }

        defines "_GLFW_X11"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "freetype"
    kind "StaticLib"
    location "%{prj.name}"
    language "C"
    systemversion "latest"
    staticruntime "on"

    targetdir "./%{prj.name}/bin"
    objdir "./%{prj.name}/bin-int"

    includedirs {
        "./%{prj.name}/include"
    }

    files {
        "./%{prj.name}/src/autofit/autofit.c",
        "./%{prj.name}/src/base/ftbase.c",
        "./%{prj.name}/src/base/ftbbox.c",
        "./%{prj.name}/src/base/ftbdf.c",
        "./%{prj.name}/src/base/ftbitmap.c",
        "./%{prj.name}/src/base/ftcid.c",
        "./%{prj.name}/src/base/ftfstype.c",
        "./%{prj.name}/src/base/ftgasp.c",
        "./%{prj.name}/src/base/ftglyph.c",
        "./%{prj.name}/src/base/ftgxval.c",
        "./%{prj.name}/src/base/ftinit.c",
        "./%{prj.name}/src/base/ftmm.c",
        "./%{prj.name}/src/base/ftotval.c",
        "./%{prj.name}/src/base/ftpatent.c",
        "./%{prj.name}/src/base/ftpfr.c",
        "./%{prj.name}/src/base/ftstroke.c",
        "./%{prj.name}/src/base/ftsynth.c",
        "./%{prj.name}/src/base/ftsystem.c",
        "./%{prj.name}/src/base/fttype1.c",
        "./%{prj.name}/src/base/ftwinfnt.c",
        "./%{prj.name}/src/bdf/bdf.c",
        "./%{prj.name}/src/cache/ftcache.c",
        "./%{prj.name}/src/cff/cff.c",
        "./%{prj.name}/src/cid/type1cid.c",
        "./%{prj.name}/src/gzip/ftgzip.c",
        "./%{prj.name}/src/lzw/ftlzw.c",
        "./%{prj.name}/src/pcf/pcf.c",
        "./%{prj.name}/src/pfr/pfr.c",
        "./%{prj.name}/src/psaux/psaux.c",
        "./%{prj.name}/src/pshinter/pshinter.c",
        "./%{prj.name}/src/psnames/psmodule.c",
        "./%{prj.name}/src/raster/raster.c",
        "./%{prj.name}/src/sfnt/sfnt.c",
        "./%{prj.name}/src/smooth/smooth.c",
        "./%{prj.name}/src/truetype/truetype.c",
        "./%{prj.name}/src/type1/type1.c",
        "./%{prj.name}/src/type42/type42.c",
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "FT_DEBUG_LEVEL_ERROR",
        "FT_DEBUG_LEVEL_TRACE",
        "FT2_BUILD_LIBRARY",
        "_LIB"
    }

    filter "system:windows"
        files {
            "./%{prj.name}/src/winfonts/winfnt.c",
            "./%{prj.name}/builds/windows/ftdebug.c"
        }

        defines {
            "WIN32",
            "WIN32_LEAN_AND_MEAN"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines "_DEBUG"
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines "NDEBUG"

project "imgui"
    kind "StaticLib"
    location "%{prj.name}"
    language "C"
    systemversion "latest"
    staticruntime "on"

    targetdir "./%{prj.name}/bin"
    objdir "./%{prj.name}/bin-int"

    includedirs {
        "./%{prj.name}/"
    }

    files {
        "./%{prj.name}/imconfig.h",
		"./%{prj.name}/imgui.h",
		"./%{prj.name}/imgui.cpp",
		"./%{prj.name}/imgui_draw.cpp",
		"./%{prj.name}/imgui_internal.h",
		"./%{prj.name}/imgui_widgets.cpp",
		"./%{prj.name}/imgui_tables.cpp",
		"./%{prj.name}/imstb_rectpack.h",
		"./%{prj.name}/imstb_textedit.h",
		"./%{prj.name}/imstb_truetype.h",
        "./%{prj.name}/imgui_demo.cpp"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "lua"
    kind "StaticLib"
    location "%{prj.name}"
    language "C"
    systemversion "latest"
    staticruntime "on"

    targetdir "./%{prj.name}/bin"
    objdir "./%{prj.name}/bin-int"

    includedirs {
        "./%{prj.name}/"
    }

    files {
        "./%{prj.name}/lapi.c",
        "./%{prj.name}/lapi.h",
        "./%{prj.name}/lauxlib.c",
        "./%{prj.name}/lauxlib.h",
        "./%{prj.name}/lbaselib.c",
        "./%{prj.name}/lcode.c",
        "./%{prj.name}/lcode.h",
        "./%{prj.name}/lcorolib.c",
        "./%{prj.name}/lctype.c",
        "./%{prj.name}/lctype.h",
        "./%{prj.name}/ldblib.c",
        "./%{prj.name}/ldebug.c",
        "./%{prj.name}/ldebug.h",
        "./%{prj.name}/ldo.c",
        "./%{prj.name}/ldo.h",
        "./%{prj.name}/ldump.c",
        "./%{prj.name}/lfunc.c",
        "./%{prj.name}/lfunc.h",
        "./%{prj.name}/lgc.c",
        "./%{prj.name}/lgc.h",
        "./%{prj.name}/linit.c",
        "./%{prj.name}/liolib.c",
        "./%{prj.name}/llex.c",
        "./%{prj.name}/llex.h",
        "./%{prj.name}/llimits.h",
        "./%{prj.name}/lmathlib.c",
        "./%{prj.name}/lmem.c",
        "./%{prj.name}/lmem.h",
        "./%{prj.name}/loadlib.c",
        "./%{prj.name}/lobject.c",
        "./%{prj.name}/lobject.h",
        "./%{prj.name}/lopcodes.c",
        "./%{prj.name}/lopcodes.h",
        "./%{prj.name}/loslib.c",
        "./%{prj.name}/lparser.c",
        "./%{prj.name}/lparser.h",
        "./%{prj.name}/lprefix.h",
        "./%{prj.name}/lstate.c",
        "./%{prj.name}/lstate.h",
        "./%{prj.name}/lstring.c",
        "./%{prj.name}/lstring.h",
        "./%{prj.name}/lstrlib.c",
        "./%{prj.name}/ltable.c",
        "./%{prj.name}/ltable.h",
        "./%{prj.name}/ltablib.c",
        "./%{prj.name}/ltm.c",
        "./%{prj.name}/ltm.h",
        "./%{prj.name}/lua.hpp",
        "./%{prj.name}/luaconf.h",
        "./%{prj.name}/lualib.h",
        "./%{prj.name}/lundump.c",
        "./%{prj.name}/lundump.h",
        "./%{prj.name}/lutf8lib.c",
        "./%{prj.name}/lvm.c",
        "./%{prj.name}/lvm.h",
        "./%{prj.name}/lzio.c",
        "./%{prj.name}/lzio.h"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        runtime "Release"
        optimize "on"