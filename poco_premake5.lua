

POCO_LIB_DIR = "vendor/poco"
function force_build_poco ()
    print("Building Poco! \n")
    os.mkdir("cmake-build");
    os.chdir("cmake-build");
    os.execute("cmake ..");
    os.execute("cmake --build . --config Release")
    os.execute("cmake --build . --config Debug")
    os.chdir(_WORKING_DIR);
end
    

function build_poco()
    os.chdir(POCO_LIB_DIR);
    if not os.isdir("cmake-build") then
        force_build_poco()
    end
    os.chdir(_WORKING_DIR);
end
build_poco();
-- 
