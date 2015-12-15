//
//  databaseInit.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#include "databaseInit.h"
void logAllData(std::unordered_map<int,Kantai*> _kantaiMap,
                std::unordered_map<int,Equip*> _equipMap,
                std::unordered_map<int,Fleet*> _fleetMap,
                std::unordered_map<int,std::pair<int, int>> _fleetKantaiMap,
                std::unordered_map<int,std::pair<int, int>> _kantaiEquipMap)
{
    for (auto it=_kantaiMap.begin(); it!=_kantaiMap.end(); ++it)
    {
        log("kantaiKey: %d   kantaiNumber: %d",it->first,it->second->getkantaiNumber());
    }
    
    for (auto it=_equipMap.begin(); it!=_equipMap.end(); ++it)
    {
        log("equipKey: %d   equipNumber: %d",it->first,it->second->getequipNumber());
    }
    
    for (auto it=_fleetMap.begin(); it!=_fleetMap.end(); ++it)
    {
        log("fleetKey: %d   fleetKey: %d",it->first,it->second->getfleetKey());
    }
    
    for (auto it=_fleetKantaiMap.begin(); it!=_fleetKantaiMap.end(); ++it)
    {
        log("kantaiKey: %d  fleetKey: %d  position: %d",it->first,it->second.first,it->second.second);
    }
    
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
Player* DBInit::initDB(int _playerKey)
{

    std::unordered_map<int,Kantai*> _kantaiMap=std::unordered_map<int,Kantai*>();

    std::unordered_map<int,Equip*> _equipMap=std::unordered_map<int,Equip*>();

    std::unordered_map<int,Fleet*> _fleetMap=std::unordered_map<int,Fleet*>();

    std::unordered_map<int,std::pair<int, int>> _fleetKantaiMap=std::unordered_map<int,std::pair<int, int>>();//kantai

    std::unordered_map<int,std::pair<int, int>> _kantaiEquipMap=std::unordered_map<int,std::pair<int, int>>();//equip

    auto _player=initPlayer(_playerKey);

    initFleet(_player,_fleetMap);

    initKantai(_player, _kantaiMap);

    initEquip(_player, _equipMap);

    initFleetKantai(_player, _fleetKantaiMap);

    initKantaiEquip(_player, _kantaiEquipMap);

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
                //tempFleet->setKantai(kantaiIt->second,it->second.second);
                //_kantaiMap.erase(kantaiIt);
            }
        }
        else
            continue;
    }

    _player->initDatabaseData(_fleetMap, _kantaiMap, _equipMap);
    return _player;
}




Player* DBInit::initPlayer(int _playerKey)
{
    Player* returnPlayer;
    
    
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
            
            InitPlayerProp initPlayerProp;
            
            returnPlayer=Player::getInstance();
            
            returnPlayer->setplayerKey(_playerKey);
            returnPlayer->setplayerName(_playerName);
            returnPlayer->setplayerSign(_playerSign);
            returnPlayer->setcurrLV(_currLV);
            returnPlayer->setplayerCurrExp(_currExp);
            returnPlayer->setplayerUpdateExp(initPlayerProp.initPlayerUpdateExpByLV(_currLV));
            
            returnPlayer->setfuel(_fuel);
            returnPlayer->setammo(_ammo);
            returnPlayer->setsteel(_steel);
            returnPlayer->setaluminium(_aluminium);
            
            returnPlayer->setmaxFuel(initPlayerProp.initMaxFuelByLV(_currLV));
            returnPlayer->setmaxAmmo(initPlayerProp.initMaxAmmoByLV(_currLV));
            returnPlayer->setmaxSteel(initPlayerProp.initMaxSteelByLV(_currLV));
            returnPlayer->setmaxAluminium(initPlayerProp.initMaxAluminiumByLV(_currLV));
            
            returnPlayer->setmaxDockSize(_maxDockSize);
            returnPlayer->setmaxKantaiSize(initPlayerProp.initMaxKantaiSize(_currLV));
            returnPlayer->setmaxEquipSize(initPlayerProp.initMaxEquipSize(_currLV));
            returnPlayer->setmaxFleetSize(_maxFleetSize);
            
        }
    }
    
    sqlite3_finalize(statement);
    
    
    return returnPlayer;
    
}


void DBInit::initFleet(const Player *player,std::unordered_map<int,Fleet*>& _kantaiFleet)
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
            auto fleet=new Fleet(fleetKey,fleetName,fleetState);
            _kantaiFleet.insert(std::pair<int, Fleet*>(fleetKey,fleet));
        }
    }
}

void DBInit::initKantai(const Player* player,std::unordered_map<int,Kantai*>& _kantaiMap)
{
    XMLControl* xmlControl=new XMLBaseControl;
    std::string qsql="SELECT * FROM player_got_kantai";
    
    sqlite3_stmt* statement;
    
    if (sqlite3_prepare_v2(kancolleDB, qsql.c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            
            int keytaiKey=sqlite3_column_int(statement, 0);
            
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
            
            
            auto kantai=new Kantai(keytaiKey,READ_KANTAI_DATABASE);
            kantai->setkantaiNumber(kantaiNumber);
            kantai->setcurrLV(currLV);
            kantai->setcurrFuel(currFuel);
            kantai->setcurrAmmo(currAmmo);
            kantai->setrange(currRange);
            kantai->setcurrHp(currHP);
            kantai->setcurrExp(currExp);
            kantai->setupdateExp(updateExp);
            
            kantai->setfirePower(firePower);
            kantai->setarmor(armor);
            kantai->settorpedo(torpedo);
            kantai->setdodge(dodge);
            kantai->setantiAir(antiAir);
            kantai->setAntiSubMarine(antiSubmarine);
            kantai->setsearchEnemy(searchEnemy);
            kantai->setluck(luck);
            kantai->setfatigueValue(fatigueValue);
            kantai->setkantaiLock(kantaiLock);
            kantai->setkantaiStar(kantaiStar);
            kantai->setkantaiState(static_cast<KantaiState>(kantaiState));
            
            
            //插入kantai具体数据通过xml方式
            
            ValueVector _kantaiData=xmlControl->ReadKantaiXML(kantaiNumber);
            
            ValueMap _name=_kantaiData[0].asValueMap();
            kantai->setkantaiName(_name["kantaiName"].asString());
            kantai->setkantaiFullName(_name["kantaiFullName"].asString());
            
            ValueMap _kantaiBaseAtrr=_kantaiData[1].asValueMap();
            kantai->setmaxAmmo(_kantaiBaseAtrr["ammo"].asInt());
            kantai->setmaxFuel(_kantaiBaseAtrr["fuel"].asInt());
            kantai->setkantaiType(static_cast<KantaiType>(_kantaiBaseAtrr["kantaiType"].asInt()));
            kantai->setspeed(_kantaiBaseAtrr["speed"].asInt());
            kantai->setrange(_kantaiBaseAtrr["range"].asInt());
            kantai->setmaxHp(_kantaiBaseAtrr["maxHp"].asInt());
            kantai->setbuildTime(_kantaiBaseAtrr["buildTime"].asInt());
            kantai->settransformTimes(_kantaiBaseAtrr["transformTimes"].asInt());
            
            
            ValueMap _kantaiMaxAttr=_kantaiData[2].asValueMap();
            kantai->setmaxLuck(_kantaiMaxAttr["maxLuck"].asInt());
            kantai->setmaxAntiSubmarine(_kantaiMaxAttr["maxAntiSubmarine"].asInt());
            kantai->setmaxDodge(_kantaiMaxAttr["maxDodge"].asInt());
            kantai->setmaxAntiAir(_kantaiMaxAttr["maxAntiAir"].asInt());
            kantai->setmaxTorpedo(_kantaiMaxAttr["maxArmor"].asInt());
            kantai->setmaxSearchEnemy(_kantaiMaxAttr["maxSearchEnemy"].asInt());
            kantai->setmaxFirePower(_kantaiMaxAttr["maxFirePower"].asInt());
            kantai->setmaxArmor(_kantaiMaxAttr["maxArmor"].asInt());
            
            int equipSize=_kantaiData[4].asInt();
            kantai->equipGrid.resize(equipSize);
            //kantai->planeLoadPr.resize(equipSize);
            kantai->maxPlaneLoad.resize(equipSize);
            

            
            kantai->planeLoadPr=_planeLoadPr;
            ValueVector _maxPlaneLoad=_kantaiData[6].asValueVector();
            for (int i=0;i<equipSize;++i)
            {
                kantai->maxPlaneLoad[i]=_maxPlaneLoad[i].asInt();
            }
            kantai->setBrokenType();
            
            _kantaiMap.insert(std::pair<int,Kantai*>(keytaiKey,kantai));
        }
    }
    delete xmlControl;
    
    sqlite3_finalize(statement);
}


void DBInit::initEquip(const Player* player,std::unordered_map<int,Equip*>& _kantaiEquip)
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

void DBInit::initFleetKantai(const Player *player, std::unordered_map<int, std::pair<int, int> >& _fleetKantaiMap)
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

void DBInit::initKantaiEquip(const Player *player, std::unordered_map<int, std::pair<int, int> >& _kantaiEquipMap)
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

