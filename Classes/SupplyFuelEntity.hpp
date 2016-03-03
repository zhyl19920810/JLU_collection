//
//  SupplyFuelEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#ifndef SupplyFuelEntity_hpp
#define SupplyFuelEntity_hpp


#include "cocos2d.h"

USING_NS_CC;

static std::map<int,Vec2> fuelTankLoc=
{   {1,Vec2(-25,-75)},
    {2,Vec2(-40,-75)},
    {3,Vec2(-55,-75)},
    {4,Vec2(-70,-75)},
    {5,Vec2(-32,-58)},
    {6,Vec2(-47,-58)},
    {7,Vec2(-62,-58)},
    {8,Vec2(-40,-41)},
    {9,Vec2(-55,-41)},
    {10,Vec2(-48,-24)}};


class FuelTankAction
{
public:
    static void fuelTankDropDown(Node *target,const Vec2 &pos,float delay);
};



class FuelTank:public Node
{
public:
    FuelTank();
    
    bool init(int type,int number);
    static FuelTank* create(int type,int number)
    {
        FuelTank* tmp=new(std::nothrow) FuelTank;
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



class FuelEntity:public Node
{
public:
    FuelEntity();
    
    static FuelEntity* create()
    {
        FuelEntity* tmp=new(std::nothrow) FuelEntity;
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
    
    void addConsumeFuel(int val);
    void minusConsumeFuel(int val);
    void supplyAll();
    void _supplyAll(int number);
    
    void addFuelTank(int number);
    void minusFuelTank(int number);
    
    
private:
    std::vector<FuelTank*> fuelTank;
    Sprite* leftBottom;
    Sprite* rightBottom;
    int consumeFuel;
};



#endif /* SupplyFuelEntity_hpp */
