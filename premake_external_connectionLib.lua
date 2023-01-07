outputdir = "%{cfg.buildcfg}"
include("premake/scripts/mysql_premake5.lua")
include("premake/scripts/mailio_premake5.lua")

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
        "mysqlcppconn-static.lib",

    }
    link_mysql();
    link_mailio();



    



