//
//  arsenalDB.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#include "arsenalDB.hpp"


NS_KCL_BEGIN

ArsenalDB::ArsenalDB()
{
    
}

void ArsenalDB::initArsenalDB(int playerKey, std::vector<ArsenalDBData> &data)
{
    std::string qsql="SELECT * FROM kantai_in_building WHERE playerKey=";
    qsql+=std::to_string(playerKey);
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            ArsenalDBData tmp;
            tmp.kantaiNumber=sqlite3_column_int(statement, 1);
            tmp.position=sqlite3_column_int(statement, 2);
            tmp.completeTime=sqlite3_column_int64(statement, 3);
            data.push_back(tmp);
        }
    }
    sqlite3_finalize(statement);
    
//    int nowTime;
//    std::string qsql1="SELECT strftime('%s','now')";
//    if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(), -1, &statement, NULL)==SQLITE_OK)
//    {
//        if (sqlite3_step(statement)==SQLITE_ROW)
//        {
//            nowTime=sqlite3_column_int(statement, 0);
//        }
//    }
//    for (auto it=data.begin(); it!=data.end(); ++it)
//    {
//        it->completeTime=it->completeTime-nowTime;
//    }
//    
//    for (auto it=data.begin(); it!=data.end(); ++it)
//    {
//        printf("%d  %d  %d\n",it->kantaiNumber,it->position,it->completeTime);
//    }
    
//    sqlite3_finalize(statement);
}



void ArsenalDB::insertKantai(int playerKey,int kantaiNumber, int position, int64_t complateTime)
{
    char name[100];
    bzero(name, sizeof(name));
    std::string sqlStr="INSERT OR REPLACE INTO kantai_in_building(playerKey,kantaiNumber,position,completeTime) Values(?,?,?,?)";
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, playerKey);
        sqlite3_bind_int(statement, 2, kantaiNumber);
        sqlite3_bind_int(statement, 3, position);
        sqlite3_bind_int64(statement, 4, complateTime);
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not insert");
        }
        sqlite3_finalize(statement);
    }
    return;
//    char name[100];
//    bzero(name, sizeof(name));
//    std::string sqlStr="INSERT OR REPLACE INTO kantai_in_building(playerKey,kantaiNumber,position,completeTime) Values(?,?,?,strftime('%s','now','+"+std::to_string(buildTime);
//    sqlStr+=" second'))";
//    sqlite3_stmt* statement;
//    
//    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
//    {
//        sqlite3_bind_int(statement, 1, playerKey);
//        sqlite3_bind_int(statement, 2, kantaiNumber);
//        sqlite3_bind_int(statement, 3, position);
//        if (sqlite3_step(statement)!=SQLITE_DONE)
//        {
//            CCASSERT(false, "can not insert");
//        }
//        sqlite3_finalize(statement);
//    }
//    return;
}

void ArsenalDB::deleteKantai(int playerKey,int position)
{
    std::string qsql2="delete from kantai_in_building where playerKey=? and position=?";
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql2.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, playerKey);
        sqlite3_bind_int(statement, 3, position);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete");
        }
    }
    sqlite3_finalize(statement);
}

NS_KCL_END



