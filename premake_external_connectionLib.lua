outputdir = "%{cfg.buildcfg}"
include("premake/scripts/mysql_premake5.lua")
include("premake/scripts/mailio_premake5.lua")
project "ExternalConnection"
    location "ExternalConnection"
    kind "StaticLib"
    language "C++"
    targetdir ("%{prj.name}")
    objdir ("%{prj.name}/obj")
    
    pchheader "ecpch.h"
    pchsource "TestPlatform/ecpch.cpp"
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }
    includedirs
    {
        "%{prj.name}",        
    }
    link_mysql();
    link_mailio();

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"
        links
        {
            "mysqlcppconn-staticd.lib"
        }

filter "configurations:Release"

        staticruntime "off"
        runtime "Release"
        defines "RELEASE"
        defines "NDEBUG"
        optimize "on"
        links
        {
            "mysqlcppconn-static.lib"
        }

filter "configurations:Dist"
    staticruntime "off"
    runtime "Release"
    kind "WindowedApp"
    defines "DIST"
    defines "NDEBUG"
    optimize "on"
    links
    {
        "mysqlcppconn-static.lib"
    }





project "ExternalConnectionUnitTests"
    location "ExternalConnectionUnitTests"
    kind "SharedLib"
    language "C++"
    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pch.h"
    pchsource "%{prj.name}/pch.cpp"
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",

    }
    includedirs
    {
        "%{prj.name}",
        "TestPlatform",
        "%{VCInstallDir}UnitTest/include"   
    }
    libdirs
    {
        "%{VCInstallDir}UnitTest/lib",
    }
    links
    {
        "build/bin-int/" .. outputdir .. "/TestPlatform/*.obj",
        
    }
    link_mysql();
    link_mailio();
    

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"
        links
        {
            "mysqlcppconn-staticd.lib"
        }

filter "configurations:Release"

        staticruntime "off"
        runtime "Release"
        defines "RELEASE"
        defines "NDEBUG"
        optimize "on"
        links
        {
            "mysqlcppconn-static.lib"
        }

