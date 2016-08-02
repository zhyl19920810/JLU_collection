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
class SupplyImp;

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
    

    void updatehipAllState();
    void updateAllBar();
    
    
    void update(float dt) override;
    void setUnitReset(int position);
private:

    MenuItemSprite* ammoButton;
    MenuItemSprite* fuelButton;
    MenuItemSprite* midButton;
    
    
    Label* fuelNumber;
    Label* ammoNumber;
    Label* consumeAmmoLabel;
    Label* consumeFuelLabel;
    Sprite* bgimg;

private:
    void callFuelButton(Ref* pSender);
    void callAmmoButton(Ref* pSender);
    void callMidButton(Ref* pSender);
    void startCircle();
    void endCircle();
    
private:
    std::vector<ShipUnit*> shipUnit;
private:
    int fleetNumber;
    Fleet* fleet;
    FleetButton* fleetButton;
    AmmoEntity* ammoEntity;
    FuelEntity* fuelEntity;
    
private:
    void initLayer();
    void initKantai();
    void initFleet();
    void initButton();
    void initAttrDisplay();
    void initEntity();
    
private:
    void fleetButtonCallback(int fleetNumber);
    void updateButton();
    void resetAmmoFuel();
    void updateKantai();

public:
    SupplyImp* supplyImp;
    
};


NS_KCL_END
#endif /* defined(__kancolle_alpha__portSupplyLayer__) */
