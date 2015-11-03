//
//  databaseBase.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "databaseBase.h"

sqlite3* DBBase::kancolleDB=0;


void DBBase::init(const std::string &pathName)
{
    if (sqlite3_open(pathName.c_str(), &kancolleDB)!=SQLITE_OK)
    {
        sqlite3_close(kancolleDB);
        CCASSERT(false, "can not open the db");
    }
}

void DBBase::end()
{
    sqlite3_close(kancolleDB);
}