
MAILIO_DIR = "%{wks.location}/vendor/mailio"
BOOST_DIR = "C:/boost_1_81_0"
OPENSSL_DIR = "C:/Program Files/OpenSSL-Win64"
function link_mailio()
    if os.isdir(MAILIO_DIR.."/Release")==nil then
        print("mailio needs to be built")
        defines "NO_MAIL"
    end
    link_boost()
    link_openssl()
    includedirs
    {
        MAILIO_DIR,
        MAILIO_DIR.."/include"
    }
    libdirs
    {
        MAILIO_DIR.."/Release"
    }
    links
    {
        "mailio.lib"
    }
end
function link_boost()

    if os.isdir(BOOST_DIR)==nil 
    then
        print("could not find boost, mailing disabled")
        defines "NO_MAIL"
    end
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

    if os.isdir(BOOST_DIR)==nil 
    then
        print("could not find opensll, mailing disabled")
        defines "NO_MAIL"
    end
    includedirs
    {
        OPENSSL_DIR.."/include"
    }
    libdirs
    {
        OPENSSL_DIR.."/libs"
    }

end