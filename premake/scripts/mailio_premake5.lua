MAILIO_DIR = "vendor/mailio"
BOOST_DIR = "C:/boost_1_81_0"
OPENSSL_DIR = "C:/Program Files/OpenSSL-Win64"


function haveMailoDependencies()

    if os.getenv("BOOST_ROOT") ~= nil
    then
        BOOST_DIR = os.getenv("BOOST_ROOT")
    end

    if os.getenv("OPENSSL_ROOT") ~= nil
    then
        OPENSSL_DIR = os.getenv("OPENSSL_ROOT")
    end

    
    if not os.isdir(BOOST_DIR)
    then
        error("could not find Boost library")
        return false
    end
    if not os.isdir(OPENSSL_DIR)
    then
        error("could not find OpenSSL library")
        return false
    end
    if not os.isdir(MAILIO_DIR.."/Release")
    then

        os.chdir(MAILIO_DIR)    
        os.execute("cmake .")
        error("Open mailo.sln and build it!")
        return false;
    end
    print("mailio is Available!")
    return true
end

function link_mailio()

    link_boost()
    link_openssl()
    includedirs
    {
        MAILIO_DIR,
        MAILIO_DIR.."/include"
    }
    libdirs
    {
        MAILIO_DIR.."/%{cfg.buildcfg}"
    }
    links
    {
        "mailio.lib"
    }
end
function link_boost()
    includedirs
    {
        BOOST_DIR
    }
    libdirs
    {
        BOOST_DIR.."/libs"
    }
end
function link_openssl()

    includedirs
    {
        OPENSSL_DIR.."/include"
    }
    libdirs
    {
        OPENSSL_DIR.."/libs"
    }

end