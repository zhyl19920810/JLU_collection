//
//  dock.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#ifndef dock_hpp
#define dock_hpp

#include "cocos2d.h"
#include "Player.h"
#include "Singleton.hpp"

NS_KCL_BEGIN
#define sDock Dock::getInstance() 

class Dock:public Singleton<Dock>
{
    friend class Singleton<Dock>;
public:
    struct DockData
    {
        Kantai* kantai;
        float remainTime;
        DockData(){bzero(this, sizeof(this));}
    };
    
    void initDock(int playerKey);
    void buildNewDock();
    
    
    void finishRepairKantai(Kantai* kantai,int position);
    void cancelRepairKantai(Kantai* kantai,int position);
    bool canRepairKantai(Kantai* kantai,int& repairSteel,int& repairAmmo,int& repairTime);
    void repairKantai(Kantai* kantai,int position,int repairSteel,int repairFuel,int repairTime);
    int calRepairTime(Kantai* kantai,int lostHp);
    int calRepairFuel(Kantai* kantai,int lostHp);
    int calRepairSteel(Kantai* kantai,int lostHp);
    
    int calAugValue(int currLV);
    void repairTimeCircle(float dt);
    const DockData& getDockData(int position);
    bool haveDock(int position);
private:
    Scheduler ts;
    void kantaiComplete(int position);
    int maxDockSize;
    int playerKey;
    std::vector<DockData> dock;
//    void startCircle();
//    void endCircle();
};

NS_KCL_END


#endif /* dock_hpp */
