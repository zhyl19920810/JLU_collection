//
//  OrganizeSelectEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#ifndef OrganizeSelectEntity_hpp
#define OrganizeSelectEntity_hpp


#include "cocos2d.h"
#include "kantai.h"
#include "kantaiCard.hpp"
#include "HpBar.hpp"
#include "MenuItemTouch.hpp"
#include "EquipmentContainer.hpp"
#include "ValueBar.hpp"
#include "Star.hpp"

USING_NS_CC;

class OrganSelectEntity:public Layer
{
public:
    OrganSelectEntity();
    
    static OrganSelectEntity* create();
    
    bool init();
    
    void moveOut();
    void moveIn();
    void updateKantai(Kantai* kantai);
private:
    Sprite* bgImg;
    void initBg();
    void initKantai();
    bool hidden;
    
    void setEquipContainerVisible(int equipNumber,bool bVisible);
    void changeShipCallback(Ref* pSender);
    bool canChangeKantai(Kantai* kantai);
    MenuItemButton* changeShipButton;
    
    Label* kantaiName;
    Label* kantaiLv;
    Sprite* lvIcon;
    HpBar* hpBar;
    Label* kantaiHp;
    Stars* stars;
    KantaiCard* kantaiCard;
    
    
    std::vector<EquipContainer*> equipContainer;
    std::vector<Sprite*> equipEmpty;
    int equipSize;
    
    Label* firePower;
    Label* torpedo;
    Label* antiAir;
    Label* armour;
    Sprite* firePowerIcon;
    Sprite* torpedoIcon;
    Sprite* antiAirIcon;
    Sprite* armourIcon;
    
    ValueBar* ammoBar;
    ValueBar* fuelBar;
    
    //kantai
    Kantai* kantai;
};


#endif /* OrganizeSelectEntity_hpp */
