//
//  SupplyAmmoEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#ifndef SupplyAmmoEntity_hpp
#define SupplyAmmoEntity_hpp

#include "cocos2d.h"

USING_NS_CC;

static std::map<int,Vec2> ammoTankLoc=
   {{1,Vec2(40,-75)},
    {2,Vec2(50,-75)},
    {3,Vec2(60,-75)},
    {4,Vec2(70,-75)},
    {5,Vec2(45,-65)},
    {6,Vec2(55,-65)},
    {7,Vec2(65,-65)},
    {8,Vec2(50,-55)},
    {9,Vec2(60,-55)},
    {10,Vec2(55,-50)}};


class SupplyLayerAction
{
public:
    static void ammoTankDropDown(Node *target,const Vec2 &pos,float delay);
};



class AmmoTank:public Node
{
public:
    AmmoTank();
    
    bool init(int type,int number);
    static AmmoTank* create(int type,int number)
    {
        AmmoTank* tmp=new(std::nothrow) AmmoTank;
        if (tmp&&tmp->init(type,number))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    
    void show(float delay);
    void disappear(float delay);
    void supply(float delay);
    void removeNode();
    
private:
    Sprite* tank;
    int number;
};



class AmmoEntity:public Node
{
public:
    AmmoEntity();
    
    static AmmoEntity* create()
    {
        AmmoEntity* tmp=new(std::nothrow) AmmoEntity;
        if (tmp&&tmp->init())
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    
    bool init();
    
    void addConsumeAmmo(int val);
    void minusConsumeAmmo(int val);
    void supplyAll();
    void _supplyAll(int number);
    
    void addAmmoTank(int number);
    void minusAmmoTank(int number);
    
    //void addFuelTank(int number);
    //void minusFuelTank(int number);
    //void removeAllAmmoTank();
    //void removeAllFuelTank();
    
private:
    std::vector<AmmoTank*> ammoTank;
    Sprite* leftBottom;
    Sprite* rightBottom;
    int consumeAmmo;
};




#endif /* SupplyAmmoEntity_hpp */
