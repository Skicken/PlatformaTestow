
MY_SQL_DIR = "C:/Program Files/MySQL/Connector C++ 8.0"
if os.isdir(MY_SQL_DIR)==nil
then
    defines "NO_MYSQL"
end

function link_mysql()
    includedirs{
        MY_SQL_DIR.."/include/",
    }
    libdirs
    {
        MY_SQL_DIR.."/lib64/vs14"
    }
    defines "STATIC_CONCPP"
end

