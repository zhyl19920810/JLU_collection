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

USING_NS_CC;


class PortScene;
class PortSupplyLayer;


class ValueBar
{
public:
    ValueBar(const Vec2& location,Node* parent);
    void setValue(int value);
    void setVisible(bool visible);
private:
    Node* parent;
    Sprite* barPic;
    int value;
};




class HpBar
{
public:
    
private:
    int maxHp;
    int currHp;
};

class ShipUnit
{
    typedef enum
    {
        SupplyFree,
        SupplyToggle,
        SupplySprite,
    }UnitCondition;
    friend class PortSupplyLayer;
public:
    ShipUnit(int position,Node* parent);
    bool init(Kantai* kantai);
    void freshShipCondition();
    void freshShipAttr();
    void addAmmo(int ammo);
    void addFuel(int fuel);
    void setNoKantai();
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
    Sprite* lvIcon;//
    Label* kantaiLV;//
    HpBar* hpBar;//
    
    
    MenuItemToggle* select;
    int position;
    Kantai* kantai;
    Node* parent;
    UnitCondition condition;
    bool haveAddFuel;
    bool haveAddAmmo;
};




class SupplyLayerAction
{
public:
    static void action1();
};


class PortSupplyLayer:public Layer
{
   // friend class ShipUnit;
public:
    PortSupplyLayer();
    
    ~PortSupplyLayer();
    bool init() override;
    
    CREATE_FUNC(PortSupplyLayer);
    
    
    void addConsumeAmmo(int position,int ammo);
    void addConsumeFuel(int position,int fuel);
    
    int minusConsumeAmmo(int position);
    int minusConsumeFuel(int position);
    
    bool isKantaiExist(int position);
    bool canFillUpAmmo(int position,Kantai* kantai);
    bool canFillUpFuel(int position,Kantai* kantai);
    void freshShipAllCondition();
    void freshShipAllAttr();
    
    void setAmmoButtonVisible(bool bVisible);
    void setFuelButtonVisible(bool bVisible);
    void setMidButtonVisible(bool bVisible);
    
    void SetFleetButtonVisible(int fleetNumber,bool bVisible);
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
    std::vector<Sprite*> fleetSprite;
    std::vector<MenuItemToggle*> fleetToggle;

private:
    void initLayer();
    void initKantaiTable();
    void initFleetButton();
    
    void callFuelButton(Ref* pSender);
    void callAmmoButton(Ref* pSender);
    void callMidButton(Ref* pSender);
    void fleetCallback(Ref* pSender,int layNumber);
    void changeFleet(int fleetNumber);
    
    
    void refreshLayer();
    void refreshKantaiTable();
private:
    std::vector<ShipUnit*> shipUnit;
private:
    int fleetNumber;
    Fleet* fleet;
    int consumeAmmo;
    int consumeFuel;
    std::map<int,int> ammoST;
    std::map<int,int> fuelST;
};

#endif /* defined(__kancolle_alpha__portSupplyLayer__) */
