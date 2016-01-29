//
//  RepairContainer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#ifndef RepairContainer_hpp
#define RepairContainer_hpp

#include "cocos2d.h"
#include "RepairTimer.hpp"
#include "HpBar.hpp"
#include "Star.hpp"
#include "kantaiCard.hpp"

USING_NS_CC;

class RepairContainerParent:public Node
{
public:
    virtual bool init(int position)=0;
    virtual void update(Kantai* kantai)=0;
    
protected:
    Sprite* kantaiBg;
    Label* kantaiName;
    Label* kantaiHp;
    Label* kantaiLv;
    MenuItemSprite* fastRepair;
    Sprite* fastRepairUp;
    int position;
    HpBar* hpBar;
    Stars* stars;
    KantaiCard * kantaiCard;
    Sprite* selectDocks;
};

class RepairContainer:public RepairContainerParent
{
public:
    RepairContainer();
    static RepairContainer* create(int position);
    void setFastRepairVisible(bool visible);
    
    bool init(int position);
    void update(Kantai* kantai);
private:
    void fastRepairCallback(Ref* pSender);
    
};

//class NoReapirContainer:public RepairContainerParent
//{
//public:
//    static NoReapirContainer* create(int position);
//    
//    bool init(int position);
//    void update();
//    
//private:
//    
//};



#endif /* RepairContainer_hpp */
