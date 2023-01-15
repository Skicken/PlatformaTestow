outputdir = "%{cfg.buildcfg}"
include("premake/scripts/mysql_premake5.lua")
include("premake/scripts/mailio_premake5.lua")
function configuration()
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
end
project "ExternalConnection"
    location "ExternalConnection"
    kind "StaticLib"
    language "C++"
    targetdir ("vendor/%{prj.name}/%{cfg.buildcfg}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
    pchheader "ecpch.h"
    pchsource "ExternalConnection/ecpch.cpp"
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
    configuration();
    
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
        "ExternalConnection",
        "%{VCInstallDir}UnitTest/include"   
    }
    libdirs
    {
        "%{VCInstallDir}UnitTest/lib",
        "vendor/ExternalConnection",
    }
    links
    {
        "%{cfg.buildcfg}/ExternalConnection.lib",
    }
    link_mysql();
    link_mailio();

    filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"
        links
        {
            "mysqlcppconn-staticd.lib",
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





