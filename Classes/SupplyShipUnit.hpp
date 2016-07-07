//
//  SupplyShipUnit.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/29/16.
//
//

#ifndef SupplyShipUnit_hpp
#define SupplyShipUnit_hpp


#include "cocos2d.h"
#include "Player.h"
#include "Star.hpp"
#include "HpBar.hpp"
#include "ValueBar.hpp"

USING_NS_CC;


NS_KCL_BEGIN

class ShipUnit:public Node
{
    typedef enum
    {
        SupplyFree,
        SupplyToggle,
        SupplySprite,
    }UnitCondition;
    friend class PortSupplyLayer;
public:
    static ShipUnit* create(int position)
    {
        ShipUnit* tmp=new(std::nothrow) ShipUnit;
        if (tmp&&tmp->init(position))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    void update(Kantai* kantai);
    bool init(int position);
    
    ShipUnit();
    
    void freshShipCondition();
    void freshShipAttr();
    void addAmmo(int ammo);
    void addFuel(int fuel);
    void setNoKantai();
    void setKantai(Kantai* kantai);
    void callback(Ref* pSender);
private:
    Sprite* kantaiBg;
    Sprite* star;
    Label* kantaiName;
    Sprite* kantaiState;
    Sprite* supplyBg2;
    Sprite* supplyBg1;
    ValueBar* ammoBar;
    ValueBar* fuelBar;
    Label* kantaiLV;
    HpBar* hpBar;
    Stars* stars;
    
    
    MenuItemToggle* select;
    int position;
    Kantai* kantai;
    UnitCondition condition;
    bool haveAddFuel;
    bool haveAddAmmo;
};


NS_KCL_END

#endif /* SupplyShipUnit_hpp */
