//
//  Player.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/6/15.
//
//

#ifndef __kancolle_alpha__Player__
#define __kancolle_alpha__Player__

#include "cocos2d.h"
#include "Equip.h"
#include "FleetPlayerGot.h"
#include "KantaiPlayerGot.h"
#include "playerDB.h"
#include "XMLControl.h"
#include "fleetDB.h"


using namespace cocos2d;


#define CC_GETVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\

#define CC_RWVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\
public: void set##varName(varType var) {varName=var;}\

class Player;

class KantaiDock
{
public:
    
    
private:
    
};


class Player
{
    CC_RWVALUE(int, playerKey);
    
    CC_RWVALUE(std::string, playerName);
    CC_RWVALUE(std::string, playerSign);
    CC_RWVALUE(int, currLV);
    CC_RWVALUE(int, playerCurrExp);
    CC_RWVALUE(int, playerUpdateExp);
    CC_RWVALUE(int, fuel);
    CC_RWVALUE(int, ammo);
    CC_RWVALUE(int, steel);
    CC_RWVALUE(int, aluminium);
    
    CC_RWVALUE(int, maxFuel);
    CC_RWVALUE(int, maxAmmo);
    CC_RWVALUE(int, maxSteel);
    CC_RWVALUE(int, maxAluminium);
    
    CC_RWVALUE(int, maxDockSize);
    CC_RWVALUE(int, maxKantaiSize);
    CC_RWVALUE(int, maxEquipSize);
    CC_RWVALUE(int, maxFleetSize);
    
    
    
    
    
public:
    static Player* getInstance();
    
    std::vector<Fleet*> getfleetData()
    {return fleetData;}
    
    std::vector<Equip*> getequipData()
    {return equipData;}
    
    std::vector<Kantai*> getkantaiData()
    {return kantaiData;}
    
    void initDatabaseData(std::unordered_map<int,Fleet*>& _fleetData,std::unordered_map<int,Kantai*>& _kantaiData,std::unordered_map<int,Equip*>& _equipData);
    
    
    //no database operation
    void setMaxFuel(int maxFuel);
    
    void setMaxAmmo(int maxAmmo);
    
    void setMaxSteel(int maxSteel);
    
    void setMaxAluminium(int maxAluminium);
    
    void setMaxKantaiSize(int maxKantaiSize);
    
    void setMaxEquipSize(int maxEquipSize);
    
    void setMaxFleetSize(int maxFleetSize);
    

    
    ////database operation
    //player attr
    void setPlayerName(const std::string& name);
    
    void setPlayerSign(const std::string& name);
    
    void setCurrLV(int currLV);
    
    void setPlayerCurrExp(int currExp);
    
    void setPlayerUpdateExp(int updateExp);
    
    void setFuel(int fuel);
    
    void setAmmo(int ammo);
    
    void setSteel(int steel);
    
    void setAluminium(int aluminium);
    
    void setMaxDockSize(int dockSize);
    
    void setMaxMissionSize(int missionSize);
    
    
    //equip
    void buildNewEquip(int _equipNumber,int _kantaiKey=-1,int _position=0);
    
    void deleteEquip(Kantai& _kantai,int _position);
    
    void deleteEquip(int _equipKey);
    
    void removeEquip(Kantai& _kantai,int _position);
    
    void changeEquipPosition(int _equipKey,int _kantaiKey,int _position);
    
    
    //kantai
    void buildNewKantai(int _kantaiNumber);
    
    void deleteKantai(int _kantaiKey); //装备也删除
    
    void deleteKantai(Fleet& _fleet,int _position);
    
    void removeKantai(Fleet& _fleet,int _position);
    
    void changeKantaiPosition(int _kantaiKey,int _fleetNumber,int _position);
    
    //fleet
    void buildNewFleet(int _fleetKey);
    
    void deleteFleet(int _fleetNumber); //只删除fleet，舰娘放回表中
    
public:
    std::vector<KantaiDock*> kantaiDock;
    std::vector<Kantai*> kantaiData;
    std::vector<Fleet*> fleetData;
    std::vector<Equip*> equipData;
    std::vector<int> planeLoad;
    
    
    
    //equip
    inline Equip* findEquipByEquipKey(int _equipKey);
    //kantai
    inline Kantai* findKantaiByKantaiKey(int _kantaiKey);
    //fleet
    Fleet* findFleetByFleetKey(int _fleetKey);
protected:
    Player();
    
private:
    //equip
    inline void deleteEquipByEquipKey(int _equipKey);
    

    
    
    
    int playerKey;
    
    std::string playerName;
    
    std::string playerSign;//??
    
    int currLV;
    
    int playerCurrExp;
    
    int playerUpdateExp;
    
    int fuel;
    
    int ammo;
    
    int steel;
    
    int aluminium;
    
    int maxFuel;
    
    int maxAmmo;
    
    int maxSteel;
    
    int maxAluminium;
    
    int maxDockSize;
    
    int maxKantaiSize;
    
    int maxEquipSize;
    
    int maxFleetSize;
    
    int equipSize;//加上这个
    

    
    static Player* player;
    
};


class LogPlayer
{
public:
    static void logPlayerData(const Player* player)
    {
        log("=>fleet");
        for (auto it=player->fleetData.begin(); it!=player->fleetData.end(); ++it)
        {
            if (*it)
            {
                log("==>fleet %d",(*it)->getfleetKey());
                for (int i=0; i<6; ++i)
                {
                    if ((*it)->ship[i])
                    {
                        log("===>kantaiKey: %d position: %d",(*it)->ship[i]->getkantaiKey(),i+1);
                        for (int j=0; j<4; ++j)
                        {
                            auto equipTemp=(*it)->ship[i]->equipGrid[j];
                            if (equipTemp)
                            {
                                log("====>equipKey: %d position: %d",equipTemp->getequipKey(),j+1);
                            }
                        }
                    }
                }
            }

        }
        
        log("=>kantai");
        for (auto it=player->kantaiData.begin(); it!=player->kantaiData.end(); ++it)
        {
            log("==>kantaiKey: %d",(*it)->getkantaiKey());
            for (int j=0; j<4; ++j)
            {
                auto equipTemp=(*it)->equipGrid[j];
                if (equipTemp)
                {
                    log("====>equipKey: %d position: %d",equipTemp->getequipKey(),j+1);
                }
            }
        }
        
            log("=>equip");
            for (auto it=player->equipData.begin(); it!=player->equipData.end(); ++it)
            {
                log("==>equipKey: %d",(*it)->getequipKey());
            }
    }
    
};







#endif /* defined(__kancolle_alpha__Player__) */
