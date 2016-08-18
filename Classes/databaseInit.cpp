//
//  databaseInit.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "databaseInit.h"
#include "Player.h"


NS_KCL_BEGIN

void logAllData(std::unordered_map<int,Kantai*> _kantaiMap,
                std::unordered_map<int,Equip*> _equipMap,
                std::unordered_map<int,Fleet*> _fleetMap,
                std::unordered_map<int,std::pair<int, int>> _fleetKantaiMap,
                std::unordered_map<int,std::pair<int, int>> _kantaiEquipMap)
{
    log("-------------------------kantai in the map:-------------------------------");
    for (auto it=_kantaiMap.begin(); it!=_kantaiMap.end(); ++it)
    {
        log("kantaiKey: %d   kantaiNumber: %d",it->first,it->second->getKantaiNumber());
    }
    log("-------------------------equip in the map:-------------------------------");
    for (auto it=_equipMap.begin(); it!=_equipMap.end(); ++it)
    {
        log("equipKey: %d   equipNumber: %d",it->first,it->second->getEquipNumber());
    }
    log("-------------------------fleet in the map:-------------------------------");
    for (auto it=_fleetMap.begin(); it!=_fleetMap.end(); ++it)
    {
        log("fleetKey: %d   fleetKey: %d",it->first,it->second->getFleetKey());
    }
    log("-------------------------fleet and kantai relation in the map:-------------------------------");
    for (auto it=_fleetKantaiMap.begin(); it!=_fleetKantaiMap.end(); ++it)
    {
        log("kantaiKey: %d  fleetKey: %d  position: %d",it->first,it->second.first,it->second.second);
    }
    log("-------------------------kantai and equip relation in the map:-------------------------------");
    for (auto it=_kantaiEquipMap.begin(); it!=_kantaiEquipMap.end(); ++it)
    {
        log("equipKey: %d  kantaiKey: %d  position: %d",it->first,it->second.first,it->second.second);
    }
}


std::vector<int> DBInit::parsePlaneLoad(char* planeLoad)
{
    std::vector<int> returnVec;
    if (!planeLoad)
    {
        return returnVec;
    }
    
    std::string s=(std::string)planeLoad;
    std::string temp="";
    std::stringstream ss;
    
    int number=0;
    for (int i=0; i<strlen(planeLoad); ++i)
    {
        if (s[i]!='#') {
            temp+=s[i];
        }
        else
        {
            ss<<temp;
            ss>>number;
            returnVec.push_back(number);
            temp.clear();
            ss.clear();
        }
    }
    if (temp!="")
    {
        ss<<temp;
        ss>>number;
        returnVec.push_back(number);
        temp.clear();
    }
    return returnVec;
}

std::string DBInit::convertToStr(std::vector<int> &planeLoadVec)
{
    std::string planeLoadStr;
    if (!planeLoadVec.empty())
    {
        planeLoadStr+=std::to_string(planeLoadVec[0]);
        
        for (int i=1; i<planeLoadVec.size(); ++i)
        {
            planeLoadStr+="#";
            planeLoadStr+=std::to_string(planeLoadVec[i]);
        }
    }
    return planeLoadStr;
}


///////////init///////////////////////
void DBInit::initDB(int _playerKey)
{

    std::unordered_map<int,Kantai*> _kantaiMap=std::unordered_map<int,Kantai*>();

    std::unordered_map<int,Equip*> _equipMap=std::unordered_map<int,Equip*>();

    std::unordered_map<int,Fleet*> _fleetMap=std::unordered_map<int,Fleet*>();

    std::unordered_map<int,std::pair<int, int>> _fleetKantaiMap=std::unordered_map<int,std::pair<int, int>>();//kantai

    std::unordered_map<int,std::pair<int, int>> _kantaiEquipMap=std::unordered_map<int,std::pair<int, int>>();//equip

    initPlayer(_playerKey);
    
    initFleet(_fleetMap);
    
    initKantai(_kantaiMap);

    initEquip(_equipMap);

    initFleetKantai(_fleetKantaiMap);

    initKantaiEquip(_kantaiEquipMap);

    //logAllData(_kantaiMap, _equipMap, _fleetMap, _fleetKantaiMap, _kantaiEquipMap);
    Kantai* tempKantai;
    for (auto it=_kantaiEquipMap.begin(); it!=_kantaiEquipMap.end(); ++it)
    {
        auto equipIt=_equipMap.find(it->first);
        if (equipIt!=_equipMap.end())
        {
            auto kantaiIt=_kantaiMap.find(it->second.first);
            if (kantaiIt!=_kantaiMap.end())
            {
                tempKantai=kantaiIt->second;
                tempKantai->equipGrid[it->second.second-1]=equipIt->second;
                equipIt->second->setKantai(tempKantai);
                //tempKantai->setEquip(equipIt->second, it->second.second);
                //_equipMap.erase(equipIt);
            }
        }
        else
            continue;
    }
    
    Fleet* tempFleet;
    for (auto it=_fleetKantaiMap.begin(); it!=_fleetKantaiMap.end(); ++it)
    {
        auto kantaiIt=_kantaiMap.find(it->first);
        if (kantaiIt!=_kantaiMap.end())
        {
            auto fleetIt=_fleetMap.find(it->second.first);
            if (fleetIt!=_fleetMap.end()) {
                tempFleet=fleetIt->second;
                tempFleet->ship[it->second.second-1]=kantaiIt->second;
                kantaiIt->second->setFleet(tempFleet);
                //tempFleet->setKantai(kantaiIt->second,it->second.second);
                //_kantaiMap.erase(kantaiIt);
            }
        }
        else
            continue;
    }

    sPlayer.initDatabaseData(_fleetMap, _kantaiMap, _equipMap);
    
}




void DBInit::initPlayer(int _playerKey)
{
    std::string qsql="SELECT * FROM PLAYER WHERE PLAYERKEY=";
    qsql+=std::to_string(_playerKey);
    
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            char* _playerName=(char*)sqlite3_column_text(statement, 1);
            char* _playerSign=(char*)sqlite3_column_text(statement, 2);
            
            int _currLV=sqlite3_column_int(statement, 3);
            int _currExp=sqlite3_column_int(statement, 4);
            
            int _fuel=sqlite3_column_int(statement, 5);
            int _ammo=sqlite3_column_int(statement, 6);
            int _steel=sqlite3_column_int(statement, 7);
            int _aluminium=sqlite3_column_int(statement, 8);
            int _maxDockSize=sqlite3_column_int(statement, 9);
            int _maxFleetSize=sqlite3_column_int(statement, 10);
            
            auto& player=Player::getInstance();
            
            player.playerKey=_playerKey;
            player.playerName=_playerName;//////?
            player.playerSign=_playerSign;////////?
            player.currLV=_currLV;
            player.playerCurrExp=_currExp;
            player.playerUpdateExp=sExpMgr.getPlayerUpdateExp(player.currLV);
            
            player.fuel=_fuel;
            player.ammo=_ammo;
            player.steel=_steel;
            player.aluminium=_aluminium;
//            player.maxFuel=InitPlayerProp::getMaxFuelByLV(_currLV);
//            player.maxAmmo=InitPlayerProp::getMaxAmmoByLV(_currLV);
//            player.maxSteel=InitPlayerProp::getMaxSteelByLV(_currLV);
//            player.maxAluminium=InitPlayerProp::getMaxAluminiumByLV(_currLV);
            player.maxDockSize=_maxDockSize;
//            player.maxKantaiSize=InitPlayerProp::getMaxKantaiSize(_currLV);
//            player.maxEquipSize=InitPlayerProp::getMaxEquipSize(_currLV);
            player.maxFleetSize=_maxFleetSize;
            player.setMaxAttr();
    
        }
    }
    
    sqlite3_finalize(statement);

}


void DBInit::initFleet(std::unordered_map<int,Fleet*>& _kantaiFleet)
{
    std::string qsql="SELECT * FROM player_got_fleet";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            int fleetKey=sqlite3_column_int(statement, 0);
            std::string fleetName=std::string((const char *)sqlite3_column_text(statement, 1));
            FleetState fleetState=static_cast<FleetState>(sqlite3_column_int(statement, 2));
            auto fleet=Fleet::create(fleetKey,READ_KANTAI_DATABASE);
            fleet->fleetName=fleetName;
            fleet->fleetState=fleetState;
            _kantaiFleet.insert(std::pair<int, Fleet*>(fleetKey,fleet));
        }
    }
}

void DBInit::initKantai(std::unordered_map<int,Kantai*>& _kantaiMap)
{
    std::string qsql="SELECT * FROM player_got_kantai";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            
            int kantaiKey=sqlite3_column_int(statement, 0);
            
            int kantaiNumber=sqlite3_column_int(statement, 1);
            int currLV=sqlite3_column_int(statement, 2);
            
            int currFuel=sqlite3_column_int(statement, 3);
            int currAmmo=sqlite3_column_int(statement, 4);
            int currRange=sqlite3_column_int(statement, 5);
            
            int currHP=sqlite3_column_int(statement, 6);
            int currExp=sqlite3_column_int(statement, 7);
            int updateExp=sqlite3_column_int(statement, 8);
            int firePower=sqlite3_column_int(statement, 9);
            int armor=sqlite3_column_int(statement, 10);
            int torpedo=sqlite3_column_int(statement, 11);
            int dodge=sqlite3_column_int(statement, 12);
            int antiAir=sqlite3_column_int(statement, 13);
            int antiSubmarine=sqlite3_column_int(statement, 14);
            int searchEnemy=sqlite3_column_int(statement, 15);
            int luck=sqlite3_column_int(statement, 16);
            int fatigueValue=sqlite3_column_int(statement, 17);
            int kantaiLock=sqlite3_column_int(statement, 18);
            int kantaiStar=sqlite3_column_int(statement, 19);
            int kantaiState=sqlite3_column_int(statement, 20);
            char* planeLoadPr=(char *)sqlite3_column_text(statement, 21);
            std::vector<int> _planeLoadPr=parsePlaneLoad(planeLoadPr);
            auto kantai=Kantai::create(kantaiKey, kantaiNumber, READ_KANTAI_DATABASE);
            kantai->currLV=currLV;
            kantai->setUpdateExp();
            kantai->currFuel=currFuel;
            kantai->currAmmo=currAmmo;
            kantai->currHp=currHP;
            kantai->currExp=currExp;
            kantai->firePower=firePower;
            kantai->armor=armor;
            kantai->torpedo=torpedo;
            kantai->dodge=dodge;
            kantai->antiAir=antiAir;
            kantai->AntiSubMarine=antiSubmarine;
            kantai->searchEnemy=searchEnemy;
            kantai->luck=luck;
            kantai->fatigueValue=fatigueValue;
            kantai->kantaiLock=kantaiLock;
            kantai->kantaiStar=kantaiStar;
            kantai->kantaiState=static_cast<KantaiState>(kantaiState);
            kantai->setBrokenType();
            kantai->equipGrid.resize(kantai->getKantaiEquipSize());
            kantai->currPlaneLoad=_planeLoadPr;

            _kantaiMap.insert(std::pair<int,Kantai*>(kantaiKey,kantai));
        }
    }
    
    sqlite3_finalize(statement);
}


void DBInit::initEquip(std::unordered_map<int,Equip*>& _kantaiEquip)
{
    std::string qsql="SELECT * FROM player_got_equip";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            int _equipKey=sqlite3_column_int(statement, 0);
            int _equipNumber=sqlite3_column_int(statement, 1);
            Equip* equip=Equip::create(_equipKey,_equipNumber);
            _kantaiEquip.insert(std::pair<int, Equip*>(_equipKey,equip));
        }
    }
    sqlite3_finalize(statement);
}

void DBInit::initFleetKantai(std::unordered_map<int, std::pair<int, int> >& _fleetKantaiMap)
{
    std::string qsql="SELECT * FROM player_got_kantai_player_got_fleet";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            int _kantaiKey=sqlite3_column_int(statement, 0);
            int _fleetKey=sqlite3_column_int(statement, 1);
            int _position=sqlite3_column_int(statement, 2);
            _fleetKantaiMap.insert(std::pair<int, std::pair<int, int>>(_kantaiKey,std::pair<int, int>(_fleetKey,_position)));
        }
    }
    sqlite3_finalize(statement);
}

void DBInit::initKantaiEquip(std::unordered_map<int, std::pair<int, int> >& _kantaiEquipMap)
{
    std::string qsql="SELECT * FROM player_got_kantai_player_got_equip";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            int _kantaiKey=sqlite3_column_int(statement, 0);
            int _equipKey=sqlite3_column_int(statement, 1);
            int _position=sqlite3_column_int(statement, 2);
            _kantaiEquipMap.insert(std::pair<int, std::pair<int, int>>(_equipKey,std::pair<int, int>(_kantaiKey,_position)));
        }
    }
    sqlite3_finalize(statement);
}

NS_KCL_END
