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


NS_KCL_BEGIN

#define sArsenal Arsenal::getInstance()
#define ArsenalBuildTime "ArsenalBuildTime"


class Arsenal:public Singleton<Arsenal>
{
    friend class Singleton<Arsenal>;
public:
    struct ArsenalData
    {
        int kantaiNumber;
        int64_t completeTime;
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
    ArsenalData getArsenal(int position) const {return arsenal[position-1];}
    bool haveShip(int position);
private:
    Scheduler ts;
    int maxArsenalSize;
    int playerKey;
    std::vector<ArsenalData> arsenal;
    
    MetaPhysics* metaPhysics;
};



NS_KCL_END


#endif /* arsenal_hpp */
