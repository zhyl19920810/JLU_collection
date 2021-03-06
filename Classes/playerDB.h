//
//  playerDB.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__playerDB__
#define __kancolle_alpha__playerDB__

#include "cocos2d.h"
#include "databaseBase.h"

using namespace cocos2d;


#define sPlayerDB PlayerDB::getInstance()

class PlayerDB:public DBBase
{
public:
    void modifyPlayerName(int playerKey,const std::string &playerName);
    
    void modifyPlayerSign(int playerKey,const std::string &playerSign);
    
    void modifyCurrLV(int playerKey,int currLV);
    
    void modifyPlayerCurrExp(int playerKey,int currExp);
    
    void modifyFuel(int playerKey,int fuel);
    
    void modifyAmmo(int playerKey,int ammo);
    
    void modifySteel(int playerKey,int steel);
    
    void modifyAluminium(int playerKey,int aluminium);
    
    void modifyMaxDockSize(int playerKey,int dockSize);
    
    void modifyMaxMissionSize(int playerKey,int missionSize);
    
    
    
    static PlayerDB* getInstance();
    
protected:
    PlayerDB();
private:
    static PlayerDB* playerDB;
};

#endif /* defined(__kancolle_alpha__playerDB__) */
