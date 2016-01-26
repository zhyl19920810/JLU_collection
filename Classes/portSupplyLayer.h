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
public:
    ShipUnit(int position,Node* parent);
    bool init(Kantai* kantai);
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
    Node* select;
    int position;
    Kantai* kantai;
    Node* parent;
};




class SupplyLayerAction
{
public:
    static void action1();
};


class PortSupplyLayer:public Layer
{
    friend class ShipUnit;
public:
    PortSupplyLayer();
    
    ~PortSupplyLayer();
    bool init() override;
    
    CREATE_FUNC(PortSupplyLayer);
    
    
    
    
    
private:
    Sprite* fuelButtonUp;
    Sprite* ammoButtonUp;
    Sprite* midButtonUp;
    Label* fuelNumber;
    Label* ammoNumber;
    Label* consumeAmmoLabel;
    Label* consumeFuelLabel;
    
    
private:

private:
    void initLayer();
    void initKantaiTable();
    
    void callBack(Ref* pSender);
    
    void addConsumeAmmo(int position,int ammo);
    void addConsumeFuel(int position,int fuel);
    
    int minusConsumeAmmo(int position);
    int minusConsumeFuel(int position);
    
    bool isKantaiExist(int position);
    bool canFillUpAmmo(int position);
    bool canFillUpFuel(int position);
    
    
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
