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
    virtual void updateUnit()=0;
    
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
    MenuItemSprite* selectDocks;
};

class RepairContainer:public RepairContainerParent
{
public:
    RepairContainer();
    static RepairContainer* create(int position);
    void setFastRepairVisible(bool visible);
    void haveKantaiInReparing(bool visible);
    bool init(int position);
    void updateUnit();
private:
    void selectKantai(Ref* pSender);
    void fastRepairCallback(Ref* pSender);
    void initBg();
    void initKantai();
    bool haveKantai;
};

class NoReapirContainer:public RepairContainerParent
{
public:
    static NoReapirContainer* create(int position);
    
    bool init(int position);
    void updateUnit(){}
    
private:
};



#endif /* RepairContainer_hpp */
