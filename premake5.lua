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
include ("raylib_premake5.lua");
include("poco_premake5.lua")
include("spdlog_premake5.lua")

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
        POCO_LIB_DIR.."/Foundation/include",
        POCO_LIB_DIR.."/Net/include",
        POCO_LIB_DIR.."/Data/include",
        POCO_LIB_DIR.."/Data/SQLite/include",
        POCO_LIB_DIR.."/Data/MySQL/include",


    }
    link_raylib();
    link_spdlog();

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"
        libdirs
        {
            POCO_LIB_DIR.."/cmake-build/lib/Debug",
        }
        links
        {
            "PocoFoundationd.lib",
            "PocoNetd.lib",
            "PocoDatad.lib",
            "PocoDataSQLited.lib",

            
        }
        prebuildcommands
        { 
            ("{COPY} ../"..POCO_LIB_DIR.."/cmake-build/bin/Debug/**.dll       %{cfg.targetdir}"), 
        }

filter "configurations:Release"

        staticruntime "off"
        runtime "Release"
        defines "RELEASE"
        defines "NDEBUG"
        optimize "on"
        libdirs
        {
            POCO_LIB_DIR.."/cmake-build/lib/Release",
        }
        links
        {
            "PocoFoundation.lib",
            "PocoNet.lib",
            "PocoData.lib",
            "PocoDataSQLite.lib",


        }
        prebuildcommands
        { 
            ("{COPY} ../"..POCO_LIB_DIR.."/cmake-build/bin/Release/**.dll       %{cfg.targetdir}"), 
        }
filter "configurations:Dist"
    staticruntime "off"
    runtime "Release"
    kind "WindowedApp"
    defines "DIST"
    defines "NDEBUG"
    optimize "on"
    libdirs
    {
        POCO_LIB_DIR.."/cmake-build/lib/Release",
    }
    links
    {
        "PocoFoundation.lib",
        "PocoNet.lib",
        "PocoData.lib",
        "PocoDataSQLite.lib",


    }
    prebuildcommands
    { 
        ("{COPY} ../"..POCO_LIB_DIR.."/cmake-build/bin/Release/**.dll       %{cfg.targetdir}"), 
    }

