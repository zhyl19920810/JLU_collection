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
#include "Fleet.h"
#include "kantai.h"
#include "playerDB.h"
#include "XMLControl.h"
#include "fleetDB.h"
#include "Singleton.hpp"

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



class Player:public Singleton<Player>
{
    friend class Singleton<Player>;
    friend class DBInit;
public:

    //exp
    int getCurrLV() const {return currLV;}
    int getPlayerCurrExp() const {return playerCurrExp;}
    int getPlayerUpdateExp() const{return playerUpdateExp;}
    void LVup();
    void setUpdateExp();
    void addPlayerCurrExp(int addExp);
    
    
private:
    int currLV;
    int playerCurrExp;
    int playerUpdateExp;
    
public:
    //和lv有关
    void setMaxAttr();
    int getMaxFuel() const{return maxFuel;}
    void setMaxFuel();
    int getMaxAmmo() const{return maxAmmo;}
    void setMaxAmmo();
    int getMaxSteel() const{return maxSteel;}
    void setMaxSteel();
    int getMaxAluminium() const{return maxAluminium;}
    void setMaxAluminium();
    int getMaxKantaiSize() const{return maxKantaiSize;}
    void setMaxKantaiSize();
    int getMaxEquipSize() const{return maxEquipSize;}
    void setMaxEquipSize();

private:
    int maxFuel;
    int maxAmmo;
    int maxSteel;
    int maxAluminium;
    
    int maxKantaiSize;
    int maxEquipSize;
    
public:
    //attr
    int getPlayerKey() const {return playerKey;}
    std::string getPlayerName() const{return playerName;}
    void setPlayerName(const std::string& name);
    std::string getPlayerSign() const{return playerSign;}
    void setPlayerSign(const std::string& name);
    
    int getFuel() const{return fuel;}
    int getAmmo() const{return ammo;}
    int getSteel() const {return steel;}
    int getAluminium() const{return aluminium;}
    
    void addFuel(int addFuel);
    void addAmmo(int addAmmo);
    void addAluminium(int addAluminium);
    void addSteel(int addSteel);
    
    bool canMinusFuel(int miFuel);
    bool canMinusAmmo(int miAmmo);
    bool canMinusSteel(int miSteel);
    bool canMinusAluminium(int miAluminium);
    
    void minusFuel(int miFuel);
    void minusAmmo(int miAmmo);
    void minusAluminium(int miAluminium);
    void minusSteel(int miSteel);
private:
    int playerKey;
    std::string playerName;
    std::string playerSign;
    
    int fuel;
    int ammo;
    int steel;
    int aluminium;
    
    
public:
    //db size
    int getMaxDockSize() const{return maxDockSize;}
    int getMaxFleetSize() const{return maxFleetSize;}
    void setMaxDockSize(int maxDockSize);
    void setMaxMissionSize(int missionSize);
    int getMaxFlletSize() const {return maxFleetSize;}
private:
    int maxDockSize;
    int maxFleetSize;
    int maxMissionSize;
    
public:
    
    void initDatabaseData(std::unordered_map<int,Fleet*>& _fleetData,std::unordered_map<int,Kantai*>& _kantaiData,std::unordered_map<int,Equip*>& _equipData);
    
    //equip
    void buildNewEquip(int _equipNumber,int _kantaiKey=-1,int _position=0);
    
    void deleteEquip(Equip* _equip);
    
    void deleteEquip(int _equipKey);
    
    void removeEquip(Kantai* _kantai,int _position);
    
    int _deleteEquipNodb(Equip* _equip);//No db
    
    inline int deleteEquipByEquipKey(int _equipKey);//No db
    
    

    
    void changeEquipPosition(int _equipKey,int _kantaiKey,int _position);
    
    
    inline Equip* findEquipByEquipKey(int _equipKey);
    
    
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
    
    std::vector<Kantai*> kantaiData;
    std::vector<Fleet*> fleetData;
    std::vector<Equip*> equipData;
    std::vector<int> planeLoad;
    

    //kantai
    inline Kantai* findKantaiByKantaiKey(int _kantaiKey);

    //fleet
    Fleet* findFleetByFleetKey(int _fleetKey);
protected:
    Player();
    
//dock
private:
    std::vector<KantaiDock*> kantaiDock;
   
    
};


#define sPlayer Player::getInstance()

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
                        log("===>kantaiKey: %d position: %d",(*it)->ship[i]->getKantaiKey(),i+1);
                        for (int j=0; j<4; ++j)
                        {
                            auto equipTemp=(*it)->ship[i]->equipGrid[j];
                            if (equipTemp)
                            {
                                log("====>equipKey: %d position: %d",equipTemp->getEquipKey(),j+1);
                            }
                        }
                    }
                }
            }

        }
        
        log("=>kantai");
        for (auto it=player->kantaiData.begin(); it!=player->kantaiData.end(); ++it)
        {
            log("==>kantaiKey: %d",(*it)->getKantaiKey());
            for (int j=0; j<4; ++j)
            {
                auto equipTemp=(*it)->equipGrid[j];
                if (equipTemp)
                {
                    log("====>equipKey: %d position: %d",equipTemp->getEquipKey(),j+1);
                }
            }
        }
        
            log("=>equip");
            for (auto it=player->equipData.begin(); it!=player->equipData.end(); ++it)
            {
                log("==>equipKey: %d",(*it)->getEquipKey());
            }
    }
    
};







#endif /* defined(__kancolle_alpha__Player__) */
