//
//  RepairSelectEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#ifndef RepairSelectEntity_hpp
#define RepairSelectEntity_hpp

#include "cocos2d.h"
#include "kantai.h"
#include "kantaiCard.hpp"
#include "RepairHpBar.hpp"
#include "unitEntity.hpp"

USING_NS_CC;

NS_KCL_BEGIN


class RepairSelectEntity:public UnitEntity
{
public:
    static RepairSelectEntity* create(Vec2 vec);
    void setStartRepairVisible(bool bVisible);
    void updateKantai(Kantai* kantai);
    void fastRepairCallback(Ref* pSender);
    void startRepairCallback(Ref* pSender);
    
private:
    MenuItemSprite* startRepair;
    Menu* mn;
    Label* kantaiName;
    Label* kantaiLv;
    Sprite* lvIcon;
    KantaiCard* kancaiCard;
    Label* kantaiHp;
    RepairHpBar* hpBar;
    Label* repairTimeLabel;
    MenuItemToggle* fastRepairToggle;
    Label* repairSteelLabel;
    Label* repairFuelLabel;
    
    
private:
    Kantai* kantai;
    void convertTimeToChar(int time,char *name);
    int repairSteel;
    int repairFuel;
    int repairTime;
    
private:
    bool init(Vec2 pos);
    void initTitle();
    void initEntity();
    void initKantai();
};


//
//class RepairSelectEntity:public Layer
//{
//public:
//    RepairSelectEntity():kantai(NULL){hidden=true;}
//    
//    static RepairSelectEntity* create();
//    
//    bool init();
//    
//    void moveOut();
//    void moveIn();
//    
//    void setStartRepairVisible(bool bVisible);
//    void updateKantai(Kantai* kantai);
//private:
//    Sprite* bgImg;
//    void initBg();
//    void initKantai();
//    bool hidden;
//    
//    
//    void startRepairCallback(Ref* pSender);
//    MenuItemSprite* startRepair;
//    Sprite* startRepairUp;
//    Menu* mn;
//    
//    Label* kantaiName;
//    Label* kantaiLv;
//    Sprite* lvIcon;
//    KantaiCard* kancaiCard;
//    Label* kantaiHp;
//    RepairHpBar* hpBar;
//    Label* repairTimeLabel;
//    MenuItemToggle* fastRepairToggle;
//    Label* repairSteelLabel;
//    Label* repairFuelLabel;
//    void fastRepairCallback(Ref* pSender);
//    
//    //kantai
//    Kantai* kantai;
//    void convertTimeToChar(int time,char *name);
//    int repairSteel;
//    int repairFuel;
//    int repairTime;
//};

NS_KCL_END
#endif /* RepairSelectEntity_hpp */
