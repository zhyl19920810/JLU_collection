//
//  portSupplyLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portSupplyLayer__
#define __kancolle_alpha__portSupplyLayer__

#include "cocos2d.h"
#include "Player.h"
#include "SupplyShipUnit.hpp"
#include "FleetButton.hpp"
#include "SupplyAmmoEntity.hpp"
#include "SupplyFuelEntity.hpp"
#include "Panel.hpp"


USING_NS_CC;


NS_KCL_BEGIN

class PortScene;
class PortSupplyLayer;


class PortSupplyLayer:public Panel
{
public:
    PortSupplyLayer();
    
    ~PortSupplyLayer();
    bool init() override;
    
    CREATE_FUNC(PortSupplyLayer);
    
    
    void addConsumeAmmo(int position,int ammo);
    void addConsumeFuel(int position,int fuel);
    
    int minusConsumeAmmo(int position);
    int minusConsumeFuel(int position);
    
    bool canFillUpAmmo(int position,Kantai* kantai);
    bool canFillUpFuel(int position,Kantai* kantai);
    void freshShipAllCondition();
    void freshShipAllAttr();
    
    void setAmmoButtonVisible(bool bVisible);
    void setFuelButtonVisible(bool bVisible);
    void setMidButtonVisible(bool bVisible);
    
    void update(float dt) override;
private:
    Sprite* ammoButtonUp;
    Sprite* fuelButtonUp;
    Sprite* midButtonUp;
    
    MenuItemSprite* ammoButton;
    MenuItemSprite* fuelButton;
    MenuItemSprite* midButton;
    
    
    Label* fuelNumber;
    Label* ammoNumber;
    Label* consumeAmmoLabel;
    Label* consumeFuelLabel;
    
    Sprite* bgimg;

    
private:
    void initLayer();
    void initKantaiTable();
    
    void callFuelButton(Ref* pSender);
    void callAmmoButton(Ref* pSender);
    void callMidButton(Ref* pSender);

    
    
    void refreshLayer();
    void refreshKantaiTable();
    void refreshFleet(int fleetNumber);
    
    void startCircle();
    void endCircle();
    
private:
    std::vector<ShipUnit*> shipUnit;
private:
    //SEL_SCHEDULE updateLabel;
    int fleetNumber;
    Fleet* fleet;
    int consumeAmmo;
    int consumeFuel;
    std::map<int,int> ammoST;
    std::map<int,int> fuelST;
    
    FleetButton* fleetButton;
    AmmoEntity* ammoEntity;
    FuelEntity* fuelEntity;
};


NS_KCL_END
#endif /* defined(__kancolle_alpha__portSupplyLayer__) */
