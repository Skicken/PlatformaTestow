RAY_LIB_DIR = "%{wks.location}/vendor/raylib"

function platform_defines()
    defines{"PLATFORM_DESKTOP"}

    filter {"options:graphics=opengl43"}
        defines{"GRAPHICS_API_OPENGL_43"}

    filter {"options:graphics=opengl33"}
        defines{"GRAPHICS_API_OPENGL_33"}

    filter {"options:graphics=opengl21"}
        defines{"GRAPHICS_API_OPENGL_21"}

    filter {"options:graphics=opengl11"}
        defines{"GRAPHICS_API_OPENGL_11"}

    filter {"system:macosx"}
        disablewarnings {"deprecated-declarations"}

    filter {"system:linux"}
        defines {"_GNU_SOURCE"}
    filter{}
end

function link_raylib()
    links {"raylib"}

    includedirs {"" .. RAY_LIB_DIR .. "/src" }
    includedirs {"" .. RAY_LIB_DIR .."/src/external" }
    includedirs {"" .. RAY_LIB_DIR .."/src/external/glfw/include" }
    platform_defines()

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        dependson {"raylib"}
        links {"raylib.lib"}
        characterset ("MBCS")

    filter "system:windows"
        defines{"_WIN32"}
        links {"winmm", "kernel32", "opengl32", "gdi32"}
        libdirs {""..RAY_LIB_DIR.."/bin/"}
        
    filter{}
end

project "raylib"
    kind "StaticLib"

    platform_defines()

    location (""..RAY_LIB_DIR.."/build")
    language "C"
    targetdir (""..RAY_LIB_DIR.."/bin")

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        characterset ("MBCS")

    filter{}

    includedirs {RAY_LIB_DIR .. "/src", RAY_LIB_DIR .. "/src/external/glfw/include" }
    vpaths
    {
        ["Header Files"] = { RAY_LIB_DIR .. "/src/**.h"},
        ["Source Files/*"] = { RAY_LIB_DIR .. "/src/**.c"},
    }
    files {RAY_LIB_DIR .. "/src/*.h", RAY_LIB_DIR .. "/src/*.c"}
    filter { "system:macosx", "files:" .. RAY_LIB_DIR .. "/src/rglfw.c" }
        compileas "Objective-C"

    filter{}
    print ("Raylib is Available!");
