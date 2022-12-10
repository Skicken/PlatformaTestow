

SPDLOG_LIB_DIR = "vendor/spdlog"
function force_build_spdlog ()
    print("Building spdlog! \n")
    os.mkdir("cmake-build");
    os.chdir("cmake-build");
    os.execute("cmake ..");
    os.execute("make -j")
    os.chdir(_WORKING_DIR);
end
    
function build_spdlog()
    os.chdir(SPDLOG_LIB_DIR);
    if not os.isdir("cmake-build") then
        force_build_poco()
    end
    os.chdir(_WORKING_DIR);
end
-- build_spdlog();

function link_spdlog()
    includedirs{SPDLOG_LIB_DIR.."/include"}
    libdirs {SPDLOG_LIB_DIR.."/bin/"}
    links{"spdlog.lib"}

end


project "spdlog"
    kind "StaticLib"
    defines "SPDLOG_COMPILED_LIB"
    location (""..SPDLOG_LIB_DIR.."/build")
    language "C++"
    targetdir (""..SPDLOG_LIB_DIR.."/bin")
    includedirs{
        SPDLOG_LIB_DIR.."/include",
        SPDLOG_LIB_DIR.."/src"

    }
    files {
           SPDLOG_LIB_DIR .. "/include/**.h", 
           SPDLOG_LIB_DIR .. "/src/**.cpp"
    }
