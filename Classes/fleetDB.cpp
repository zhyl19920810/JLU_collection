//
//  fleetDB.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "fleetDB.h"

NS_KCL_BEGIN

FleetDB* FleetDB::fleetDB=new FleetDB;


FleetDB* FleetDB::getInstance()
{
    return fleetDB;
}

FleetDB::FleetDB(){}

void FleetDB::getNewFleetByNumber(int fleetKey,const std::string& name,int fleetState)
{
    
    std::string qsql="INSERT OR REPLACE INTO player_got_fleet(fleetKey,fleetName,fleetState) Values(?,?,?)";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, fleetKey);
        sqlite3_bind_text(statement, 2,name.c_str(), -1, NULL);
        sqlite3_bind_int(statement, 3, fleetState);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "Insert Data failure.");
        }
    }
    
    sqlite3_finalize(statement);
}

void FleetDB::deleteFleetByKey(int _fleetKey)
{
    std::string qsql="delete from player_got_fleet where fleetKey=?";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, _fleetKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete the fleet by key");
        }
    }
    sqlite3_finalize(statement);
}


void FleetDB::setFleetName(int _fleetKey,const std::string &_fleetName)
{
    std::string qsql="UPDATE player_got_fleet set fleetName=? where fleetKey=?";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_text(statement, 1, _fleetName.c_str(), -1, NULL);
        sqlite3_bind_int(statement, 2, _fleetKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not set the fleet name");
        }
        sqlite3_finalize(statement);
    }
}

void FleetDB::setFleetState(int _fleetKey,int _fleetState)
{
    std::string qsql="UPDATE player_got_fleet set fleetState=? where fleetKey=?";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, _fleetState);
        sqlite3_bind_int(statement, 2, _fleetKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not set the fleet state");
        }
        sqlite3_finalize(statement);
    }
}

NS_KCL_END