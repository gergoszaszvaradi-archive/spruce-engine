workspace "spruce-engine"
    platforms {
        "x86",
        "x86_64"
    }

    configurations {
        "Debug",
        "Release",
        "DebugDLL",
        "ReleaseDLL"
    }

group "dependencies"
    include "spruce/dep"
    
group ""
    include "spruce"
    include "example"
    include "editor"