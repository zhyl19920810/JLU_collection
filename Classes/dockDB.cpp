//
//  dockDB.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "dockDB.hpp"

NS_KCL_BEGIN

DockDB* DockDB::dockDB=new DockDB;


DockDB::DockDB()
{
    
}

DockDB* DockDB::getInstance()
{
    return dockDB;
}

void DockDB::initDockDB(int playerKey, std::vector<DockDBData>& data)
{
    std::string qsql="SELECT * FROM kantai_in_repair WHERE playerKey=";
    qsql+=std::to_string(playerKey);
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            DockDBData tmp;
            tmp.kantaiKey=sqlite3_column_int(statement, 1);
            tmp.position=sqlite3_column_int(statement, 2);
            tmp.completeTime=sqlite3_column_int(statement, 3);
            data.push_back(tmp);
        }
    }
    sqlite3_finalize(statement);
    
    int nowTime;
    std::string qsql1="SELECT strftime('%s','now')";
    if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        if (sqlite3_step(statement)==SQLITE_ROW)
        {
            nowTime=sqlite3_column_int(statement, 0);
        }
    }
    for (auto it=data.begin(); it!=data.end(); ++it)
    {
        it->completeTime=it->completeTime-nowTime;
    }
    
    for (auto it=data.begin(); it!=data.end(); ++it)
    {
        printf("%d  %d  %d\n",it->kantaiKey,it->position,it->completeTime);
    }
    
    sqlite3_finalize(statement);
}




void DockDB::insertKantai(int playerKey,int kantaiKey, int position, int repairTime)
{
    char name[100];
    bzero(name, sizeof(name));
    std::string sqlStr="INSERT OR REPLACE INTO kantai_in_repair(playerKey,kantaiKey,position,completeTime) Values(?,?,?,strftime('%s','now','+"+std::to_string(repairTime);
    sqlStr+=" second'))";
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, playerKey);
        sqlite3_bind_int(statement, 2, kantaiKey);
        sqlite3_bind_int(statement, 3, position);
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not insert");
        }
        sqlite3_finalize(statement);
    }
    return;
}

void DockDB::deleteKantai(int playerKey,int kantaiKey)
{
    std::string qsql2="delete from kantai_in_repair where playerKey=? and kantaiKey=?";
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql2.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, playerKey);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete");
        }
    }
    sqlite3_finalize(statement);
}

//    sprintf(name, "insert into kantai_in_repair(playerKey,kantaiKey,position,completeTime) Values(?,?,?, strftime('%%s','now','+%d second'))",buildingTime);


NS_KCL_END



