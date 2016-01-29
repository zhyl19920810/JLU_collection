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
class Dock:public Singleton<Dock>
{
    friend class Singleton<Dock>;
public:
    struct DockData
    {
        Kantai* kantai;
        float remainTime;
    };
    
    void initDock(int playerKey);
    
    int buildNewDock();
    void update();
private:
    Scheduler ts;
    void kantaiComplete(int position);
    int maxDockSize;
    std::vector<DockData*> dock;
    
};


#define sDock Dock::getInstance() 
#endif /* dock_hpp */
