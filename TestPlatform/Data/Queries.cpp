#include <ptpch.h>
#include "SQLite.h"


const std::string SQLite::Queries::createUsersTable = 
"CREATE TABLE IF NOT EXISTS USERS (ID primary key auto_increment int not null";