//
//  equipDB.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "equipDB.h"


NS_KCL_BEGIN

EquipDB* EquipDB::equipDB=new EquipDB;

int EquipDB::getNewEquipByNumber(int equipNumber,int kantaiKey,int position)
{
    std::string qsql="INSERT OR REPLACE INTO player_got_equip(equipKey,equipNumber) VALUES (?,?)";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 2, equipNumber);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not insert");
        }
        int equipKey=static_cast<int>(sqlite3_last_insert_rowid(kancolleDB));
        
        sqlite3_finalize(statement);
        
        if (kantaiKey!=-1)
        {
            std::string qsql1="INSERT OR REPLACE INTO player_got_kantai_player_got_equip(kantaiKey,equipKey,position) VALUES(?,?,?)";
            
            if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(),-1, &statement, NULL)==SQLITE_OK)
            {
                sqlite3_bind_int(statement, 1, kantaiKey);
                sqlite3_bind_int(statement, 2, equipKey);
                sqlite3_bind_int(statement, 3, position);
                
                if (sqlite3_step(statement)!=SQLITE_DONE)
                {
                    CCASSERT(false, "can not insert");
                }
            }
            sqlite3_finalize(statement);
        }
        return equipKey;
    }
    else
    {
        sqlite3_finalize(statement);
    }
    
    return -1;
}

EquipDB::EquipDB()
{
    
}

void EquipDB::deleteEquipKey(int equipKey,bool InKantai)
{
    sqlite3_stmt* statement;
    
    if (InKantai)
    {
        std::string qsql1="delete from player_got_kantai_player_got_equip where equipKey=?";
        
        if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(), -1, &statement, NULL)==SQLITE_OK)
        {
            sqlite3_bind_int(statement, 1, equipKey);
            if (sqlite3_step(statement)!=SQLITE_DONE)
            {
                CCASSERT(false, "can not delete in the relation");
            }
            sqlite3_finalize(statement);
        }
    }
    
    
    std::string qsql2="delete from player_got_equip where equipKey=?";

    
    if (sqlite3_prepare_v2(kancolleDB, qsql2.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, equipKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete");
        }
    }
    sqlite3_finalize(statement);
}

void EquipDB::deleteEquipRelation(int equipKey)
{
     sqlite3_stmt* statement;
    std::string qsql1="delete from player_got_kantai_player_got_equip where equipKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, equipKey);
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete in the relation");
        }
        sqlite3_finalize(statement);
    }
}


void EquipDB::changeEquipPosition(int _equipKey, int _kantaiKey, int _position)
{
    
    std::string qsql1="INSERT OR REPLACE INTO player_got_kantai_player_got_equip(kantaiKey,equipKey,position) VALUES(?,?,?)";
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(),-1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, _kantaiKey);
        sqlite3_bind_int(statement, 2, _equipKey);
        sqlite3_bind_int(statement, 3, _position);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not insert");
        }
    }
    sqlite3_finalize(statement);
}






EquipDB* EquipDB::getInstance()
{
    return equipDB;
}

NS_KCL_END
