workspace "TestPlatform"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    startproject "TestPlatform"
outputdir = "%{cfg.buildcfg}"


include ("premake/scripts/raylib_premake5.lua");
include("premake/scripts/spdlog_premake5.lua")


project "TestPlatform"
    location "TestPlatform"
    kind "ConsoleApp"
    language "C++"
    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "ptpch.h"
    pchsource "TestPlatform/ptpch.cpp"
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }
    includedirs
    {
        "%{prj.name}",  
    }
    link_raylib();
    link_spdlog();




filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"

        

filter "configurations:Release"
        staticruntime "off"
        runtime "Release"
        defines "RELEASE"
        defines "NDEBUG"
        optimize "on"

filter "configurations:Dist"
    staticruntime "off"
    runtime "Release"
    kind "WindowedApp"
    defines "DIST"
    defines "NDEBUG"
    optimize "on"


include("premake_external_connectionLib.lua")
print("Everything is setup correctly!")
    
-- project "UnitTests"
--     location "UnitTests"
--     kind "SharedLib"
--     language "C++"
--     targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
--     objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
    
--     pchheader "pch.h"
--     pchsource "%{prj.name}/pch.cpp"
--     files
--     {
--         "%{prj.name}/**.h",
--         "%{prj.name}/**.cpp",

--     }
--     includedirs
--     {
--         "%{prj.name}",
--         "TestPlatform",
--         "%{VCInstallDir}UnitTest/include"   
--     }
--     libdirs
--     {
--         "%{VCInstallDir}UnitTest/lib",
--     }
--     links
--     {
--         "build/bin-int/" .. outputdir .. "/TestPlatform/*.obj",
        
--     }
--     link_raylib();
--     link_spdlog();
--     link_mysql();
--     link_mailio();
    

