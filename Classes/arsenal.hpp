//
//  arsenal.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#ifndef arsenal_hpp
#define arsenal_hpp

#include "cocos2d.h"
#include "Player.h"
#include "Singleton.hpp"
#include "arsenalDB.hpp"
#include "metaphysics.hpp"

class Arsenal:public Singleton<Arsenal>
{
    friend class Singleton<Arsenal>;
public:
    struct ArsenalData
    {
        int kantaiNumber;
        float remainTime;
        bool finished;
        ArsenalData(){bzero(this, sizeof(this));}
    };
    void initArsenal(int playerKey);
    void buildNewArsenal();
    
    void finishBuildingKantai(int position);
    void cancelBuildingKantai(int position);
    void buildNewKantai(int position,int fuel,int steel,int ammo,int aluminium,int developMaterial,bool fastRepair=false);
    bool isBuildingFinished(int position);
    
    int calNewKantai(int fuel,int steel,int ammo,int aluminium,int developMaterial);
    void buildTimeCircle(float dt);
private:
    Scheduler ts;
    int maxArsenalSize;
    int playerKey;
    std::vector<ArsenalData> arsenal;
    void startCircle();
    void endCircle();
    
    MetaPhysics* metaPhysics;
};

#define sArsenal Arsenal::getInstance()

#endif /* arsenal_hpp */
