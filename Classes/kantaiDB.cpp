//
//  kantaiDB.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "kantaiDB.h"
#include "equipDB.h"
#include "KantaiMgr.hpp"
#include "DataBaseMgr.hpp"


NS_KCL_BEGIN


KantaiDB::KantaiDB(){}


int KantaiDB::getNewKantaiByNumber(int kantaiNumber)
{
    auto tmp=sKantaiMgr.GetKantaiMap(kantaiNumber);

    
    int _fuel=tmp->fuel;
    int _ammo=tmp->ammo;
    int _range=tmp->range;
    int _maxHp=tmp->maxHp;
    int _lv=tmp->lv;
    int _firePower=tmp->initFirePower;
    int _armor=tmp->initArmor;
    int _torpedo=tmp->initTorpedo;
    int _dodge=tmp->initDodge;
    int _antiAir=tmp->initAntiAir;
    int _antiSubmarine=tmp->initAntiSubmarine;
    int _searchEnemy=tmp->initSearchEnemy;
    int _luck=tmp->initLuck;
    std::string _planeLoadPr;
    
    _planeLoadPr+=to_string(tmp->planeLoad[0]);
    for (int i=1; i<tmp->kantaiEquipSize; ++i)
    {
        _planeLoadPr+="#";
        _planeLoadPr+=to_string(tmp->planeLoad[i]);
    }
    
    std::string sqlStr="INSERT OR REPLACE INTO player_got_kantai(kantaiKey,kantaiNumber,currLV,currFuel,currAmmo,currRange,currHP,currExp,updateExp,firePower,armor,torpedo,dodge,antiAir,antiSubmarine,searchEnemy,luck,fatigueValue,kantaiLock,kantaiStar,kantaiState,planeLoadPr) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        //sqlite3_bind_int(statement ,1, 20);
        sqlite3_bind_int(statement ,2, kantaiNumber);
        sqlite3_bind_int(statement ,3, _lv);
        sqlite3_bind_int(statement ,4, _fuel);
        sqlite3_bind_int(statement ,5, _ammo);
        sqlite3_bind_int(statement ,6, _range);
        sqlite3_bind_int(statement ,7, _maxHp);//currHP
        sqlite3_bind_int(statement ,8, 0);//currExp
        sqlite3_bind_int(statement ,9, 100);//updateExp?????????
        sqlite3_bind_int(statement ,10, _firePower);//firePower
        sqlite3_bind_int(statement ,11, _armor); //armor
        sqlite3_bind_int(statement ,12, _torpedo); //torpedo
        sqlite3_bind_int(statement ,13, _dodge); //dodge
        sqlite3_bind_int(statement ,14, _antiAir); //antiAir
        sqlite3_bind_int(statement ,15, _antiSubmarine); //antiSubmarine
        sqlite3_bind_int(statement ,16, _searchEnemy); //searchEnemy
        sqlite3_bind_int(statement ,17, _luck); //luck
        sqlite3_bind_int(statement ,18, 50); //fatigueValue
        sqlite3_bind_int(statement ,19, 0); //kantaiLock
        sqlite3_bind_int(statement ,20, 0); //kantaiStar?????
        sqlite3_bind_int(statement ,21, 1); //kantaiState?????
        sqlite3_bind_text(statement, 22,_planeLoadPr.c_str(), -1, NULL);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            log("%s",sqlite3_errmsg(kancolleDB));
            CCASSERT(false, "Insert Data failure.");
        }
    }
    sqlite3_finalize(statement);
    int _kantaiKey=static_cast<int>(sqlite3_last_insert_rowid(kancolleDB));
    
    return _kantaiKey;
}

std::vector<std::pair<int,int>> KantaiDB::getNewKantaiEquip(int _kantaiKey, std::vector<int> equipVec)
{
    std::vector<int> returnVal(equipVec);
    int size=static_cast<int>(equipVec.size());
    
    std::vector<std::pair<int,int>>  returnKey;
    for (int i=0;i<size; ++i)
    {
        int _equipNumber=returnVal[i];
        int _position=i+1;
        
        int _equipKey=DB_MGR->getEquipDB()->getNewEquipByNumber(_equipNumber,_kantaiKey,_position);
        returnKey.push_back(std::pair<int, int>(_equipKey,_equipNumber));
    }
    return returnKey;
}








int KantaiDB::getNewKantaiByNumber(ValueVector& _kantaiData)
{
    int _kantaiKey;
    ValueMap _name=_kantaiData[0].asValueMap();
    std::string _kantaiName=_name.at("kantaiName").asString();
    std::string _kantaiFullName=_name.at("kantaiFullName").asString();
    
    
    ValueMap _kantaiBaseAtrr=_kantaiData[1].asValueMap();
    int _kantaiNumber=_kantaiBaseAtrr.at("kantaiNumber").asInt();
    int _fuel=_kantaiBaseAtrr.at("fuel").asInt();
    int _ammo=_kantaiBaseAtrr.at("ammo").asInt();
    int _range=_kantaiBaseAtrr.at("range").asInt();
    int _maxHp=_kantaiBaseAtrr.at("maxHp").asInt();
    
    
    ValueMapIntKey _kantaiEquipInit=_kantaiData[5].asIntKeyMap();
    
    
    ValueMap _kantaiInitAtrr=_kantaiData[3].asValueMap();
    int _firePower=_kantaiInitAtrr.at("initFirePower").asInt();
    int _armor=_kantaiInitAtrr.at("initFirePower").asInt();
    int _torpedo=_kantaiInitAtrr.at("initFirePower").asInt();
    int _dodge=_kantaiInitAtrr.at("initFirePower").asInt();
    int _antiAir=_kantaiInitAtrr.at("initFirePower").asInt();
    int _antiSubmarine=_kantaiInitAtrr.at("initFirePower").asInt();
    int _searchEnemy=_kantaiInitAtrr.at("initFirePower").asInt();
    int _luck=_kantaiInitAtrr.at("initFirePower").asInt();
    
    
    
    
    std::string sqlStr="INSERT OR REPLACE INTO player_got_kantai(kantaiKey,kantaiNumber,currLV,currFuel,currAmmo,currRange,currHP,currExp,updateExp,firePower,armor,torpedo,dodge,antiAir,antiSubmarine,searchEnemy,luck,fatigueValue,kantaiLock,kantaiStar,kantaiState) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, sqlStr.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        //sqlite3_bind_int(statement ,1, 1);
        sqlite3_bind_int(statement ,2, _kantaiNumber);
        sqlite3_bind_int(statement ,3, 1);//LV
        sqlite3_bind_int(statement ,4, _fuel);
        sqlite3_bind_int(statement ,5, _ammo);
        sqlite3_bind_int(statement ,6, _range);
        sqlite3_bind_int(statement ,7, _maxHp);//currHP
        sqlite3_bind_int(statement ,8, 0);//currExp
        sqlite3_bind_int(statement ,9, 100);//updateExp?????????
        sqlite3_bind_int(statement ,10, _firePower);//firePower
        sqlite3_bind_int(statement ,11, _armor); //armor
        sqlite3_bind_int(statement ,12, _torpedo); //torpedo
        sqlite3_bind_int(statement ,13, _dodge); //dodge
        sqlite3_bind_int(statement ,14, _antiAir); //antiAir
        sqlite3_bind_int(statement ,15, _antiSubmarine); //antiSubmarine
        sqlite3_bind_int(statement ,16, _searchEnemy); //searchEnemy
        sqlite3_bind_int(statement ,17, _luck); //luck
        sqlite3_bind_int(statement ,18, 50); //fatigueValue
        sqlite3_bind_int(statement ,19, 0); //kantaiLock
        sqlite3_bind_int(statement ,20, 1); //kantaiStar?????
        sqlite3_bind_int(statement ,21, 1); //kantaiState?????
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "Insert Data failure.");
        }
    }
    sqlite3_finalize(statement);
    _kantaiKey=static_cast<int>(sqlite3_last_insert_rowid(kancolleDB));
    
    return _kantaiKey;
}


std::vector<std::pair<int,int>> KantaiDB::getNewKantaiEquip(int _kantaiKey, ValueVector &_kantaiData)
{
    std::vector<int> returnVal;
    ValueMapIntKey _kantaiEquip=_kantaiData[5].asIntKeyMap();
    int size=static_cast<int>(_kantaiEquip.size());
    
    for (int i=0; i<size; ++i)
    {
        auto it=_kantaiEquip.find(i);
        returnVal.push_back(it->second.asInt());
    }
    
    std::vector<std::pair<int,int>>  returnKey;
    for (int i=0;i<size; ++i)
    {
        int _equipNumber=returnVal[i];
        int _position=i+1;
        
        int _equipKey=DB_MGR->getEquipDB()->getNewEquipByNumber(_equipNumber,_kantaiKey,_position);
        returnKey.push_back(std::pair<int, int>(_equipKey,_equipNumber));
    }
    return returnKey;
}


void KantaiDB::deleteKantaiKey(int kantaiKey,bool InFleet)
{
    sqlite3_stmt* statement;
    
    if (InFleet)
    {
        std::string qsql1="delete from player_got_kantai_player_got_fleet where kantaiKey=?";
        
        if (sqlite3_prepare_v2(kancolleDB, qsql1.c_str(), -1, &statement, NULL)==SQLITE_OK)
        {
            sqlite3_bind_int(statement, 1, kantaiKey);
            if (sqlite3_step(statement)!=SQLITE_DONE)
            {
                CCASSERT(false, "can not delete in the relation");
            }
            sqlite3_finalize(statement);
        }
    }
    
    
    std::string qsql2="delete from player_got_kantai where kantaiKey=?";
    
    
    if (sqlite3_prepare_v2(kancolleDB, qsql2.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete");
        }
    }
    sqlite3_finalize(statement);
}


void KantaiDB::deleteKantaiFleet(int _kantaiKey)
{
    sqlite3_stmt* statement;
    
    std::string qsql="delete from player_got_kantai_player_got_fleet where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, _kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not delete deleteKantaiFleet");
        }
    }
    sqlite3_finalize(statement);
}

void KantaiDB::changeKantaiPosition(int _kantaiKey, int _fleetNumber, int _position)
{
    
    std::string qsql="Insert or replace into player_got_kantai_player_got_fleet(kantaiKey,fleetKey,position) Values(?,?,?)";
    
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, _kantaiKey);
        sqlite3_bind_int(statement, 2, _fleetNumber);
        sqlite3_bind_int(statement, 3, _position);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not change the kantai position");
        }
    }
    sqlite3_finalize(statement);
}




    //kantai attribute update
void KantaiDB::setCurrLV(int kantaiKey, int currLV)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currLV=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currLV);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrLV");
        }
    }
}

void KantaiDB::setCurrFuel(int kantaiKey, int currFuel)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currFuel=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currFuel);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrFuel");
        }
    }
}

void KantaiDB::setCurrAmmo(int kantaiKey, int currAmmo)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currAmmo=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currAmmo);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrAmmo");
        }
    }
}

void KantaiDB::setCurrRange(int kantaiKey, int currRange)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currRange=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currRange);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrRange");
        }
    }
}

void KantaiDB::setCurrHp(int kantaiKey, int currHp)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currHp=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currHp);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrHp");
        }
    }
}

void KantaiDB::setCurrExp(int kantaiKey, int currExp)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set currExp=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, currExp);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setCurrExp");
        }
    }
}

void KantaiDB::setUpdateExp(int kantaiKey, int updateExp)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set updateExp=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, updateExp);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setUpdateExp");
        }
    }
}

void KantaiDB::setFirePower(int kantaiKey, int firePower)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set firePower=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, firePower);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setFirePower");
        }
    }
}

void KantaiDB::setArmor(int kantaiKey, int armor)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set armor=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, armor);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setArmor");
        }
    }
}

void KantaiDB::setTorpedo(int kantaiKey, int torpedo)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set torpedo=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, torpedo);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setTorpedo");
        }
    }
}


void KantaiDB::setDodge(int kantaiKey, int dodge)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set dodge=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, dodge);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setDodge");
        }
    }
}



void KantaiDB::setAntiAir(int kantaiKey, int antiAir)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set antiAir=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, antiAir);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setAntiAir");
        }
    }
}



void KantaiDB::setAntiSubmarine(int kantaiKey, int antiSubmarine)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set antiSubmarine=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, antiSubmarine);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setAntiSubmarine");
        }
    }
}



void KantaiDB::setSearchEnemy(int kantaiKey, int searchEnemy)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set searchEnemy=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, searchEnemy);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setSearchEnemy");
        }
    }
}



void KantaiDB::setLuck(int kantaiKey, int luck)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set luck=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, luck);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setLuck");
        }
    }
}



void KantaiDB::setFatigueValue(int kantaiKey, int fatigueValue)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set fatigueValue=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, fatigueValue);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setFatigueValue");
        }
    }
}



void KantaiDB::setKantaiLock(int kantaiKey, int kantaiLock)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set kantaiLock=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, kantaiLock);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setKantaiLock");
        }
    }
}



void KantaiDB::setKantaiStar(int kantaiKey, int kantaiStar)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set kantaiStar=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, kantaiStar);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setKantaiStar");
        }
    }
}


void KantaiDB::setKantaiState(int kantaiKey, int kantaiState)
{
    sqlite3_stmt* statement;
    
    std::string qsql="update player_got_kantai set kantaiState=? where kantaiKey=?";
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, kantaiState);
        sqlite3_bind_int(statement, 2, kantaiKey);
        
        if (sqlite3_step(statement)!=SQLITE_DONE)
        {
            CCASSERT(false, "can not function setKantaiState");
        }
    }
}

NS_KCL_END
