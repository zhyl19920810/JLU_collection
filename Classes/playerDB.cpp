//
//  playerDB.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "playerDB.h"

NS_KCL_BEGIN


void PlayerDB::modifyPlayerName(int playerKey,const std::string &playerName)
{
    std::string sqlStr="UPDATE player set playerName=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_text(statement, 1, playerName.c_str(), -1, NULL);
        sqlite3_bind_int(statement, 2,playerKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}


void PlayerDB::modifyPlayerSign(int playerKey,const std::string &playerSign)
{
    std::string sqlStr="UPDATE player set playerSign=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_text(statement, 1, playerSign.c_str(), -1, NULL);
        sqlite3_bind_int(statement, 2,playerKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}

void PlayerDB::modifyCurrLV(int playerKey,int currLV)
{
    std::string sqlStr="UPDATE player set currLV=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,currLV);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}

void PlayerDB::modifyPlayerCurrExp(int playerKey,int currExp)
{
    std::string sqlStr="UPDATE player set currExp=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,currExp);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}



void PlayerDB::modifyFuel(int playerKey,int fuel)
{
    std::string sqlStr="UPDATE player set fuel=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,fuel);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}



void PlayerDB::modifyAmmo(int playerKey,int ammo)
{
    std::string sqlStr="UPDATE player set ammo=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,ammo);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}


void PlayerDB::modifySteel(int playerKey,int steel)
{
    std::string sqlStr="UPDATE player set steel=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,steel);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}


void PlayerDB::modifyAluminium(int playerKey,int aluminium)
{
    std::string sqlStr="UPDATE player set aluminium=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,aluminium);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}

void PlayerDB::modifyMaxDockSize(int playerKey,int dockSize)
{
    std::string sqlStr="UPDATE player set maxDockSize=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,dockSize);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}


void PlayerDB::modifyMaxMissionSize(int playerKey,int missionSize)
{
    std::string sqlStr="UPDATE player set maxMissionSize=? where playerKey=?";
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2,playerKey);
        sqlite3_bind_int(statement, 1,missionSize);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not update database poi!!!!");
        }
    }
    sqlite3_finalize(statement);
}


PlayerDB::PlayerDB(){}


NS_KCL_END
