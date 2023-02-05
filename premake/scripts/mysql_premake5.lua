MY_SQL = "C:/Program Files/MySQL/Connector C++ 8.0"
MY_SQL_DEBUG = "C:/Program Files/MySQL/Connector C++ 8.0-debug"

function haveMysqlDependencies()
    
    if os.getenv("MYSQL_ROOT") ~= nil
    then
        MY_SQL = os.getenv("MYSQL_ROOT")
    end

    if os.getenv("MYSQL_DEBUG_ROOT") ~= nil
    then
        MY_SQL_DEBUG = os.getenv("MYSQL_DEBUG_ROOT")
    end
    if not os.isdir(MY_SQL)
    then
        error("my sql connector not found!")
        return false
    end
    if not os.isdir(MY_SQL_DEBUG)
    then
        print("You should build sql only in release mode!")
    end
    print("Mysql is Available!")
    return true
end



function link_mysql()
    includedirs{
        MY_SQL.."/include/",
        MY_SQL_DEBUG.."/include"
    }
    libdirs
    {
        MY_SQL.."/lib64/vs14",
        MY_SQL_DEBUG.."/lib64/vs14/debug",
        MY_SQL_DEBUG.."/lib64/debug"
    }
    defines "STATIC_CONCPP"
end

