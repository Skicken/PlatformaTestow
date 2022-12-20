

POCO_LIB_DIR = "vendor/poco"
function build_poco ()
    print("Building Poco! \n")
    os.chdir(POCO_LIB_DIR);
    os.mkdir("cmake-build");
    os.chdir("cmake-build");
    os.execute("cmake ..");
    os.execute("cmake --build . --config Release")
    -- os.execute("cmake --build . --config Debug")
    os.chdir(_WORKING_DIR);
end
    
build_poco();
-- 
