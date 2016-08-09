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
#include "LayerCover.hpp"
#include "unityEntity.hpp"

USING_NS_CC;

NS_KCL_BEGIN



class OrganSelectEntity:public UnitEntity
{
public:
    OrganSelectEntity();
    static OrganSelectEntity* create(Vec2 pos);
    void updateKantai(Kantai* kantai);
    
    
private:
    void changeShipCallback(Ref* pSender);
    bool canChangeKantai(Kantai* kantai);
    
    
private:
    void setEquipContainerVisible(int equipNumber,bool bVisible);
    int equipSize;
    std::vector<EquipContainer*> equipContainer;
    std::vector<Sprite*> equipEmpty;
    
private:
    MenuItemButton* changeShipButton;
    Label* kantaiName;
    Label* kantaiLv;
    Sprite* lvIcon;
    HpBar* hpBar;
    Label* kantaiHp;
    Stars* stars;
    KantaiCard* kantaiCard;
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
    
private:
    bool init(Vec2 pos);
    void initButton();
    void initKantai();
    void initTitle();
    void initEntity();
};

NS_KCL_END


#endif /* OrganizeSelectEntity_hpp */
