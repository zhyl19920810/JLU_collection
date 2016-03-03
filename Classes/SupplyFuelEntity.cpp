//
//  SupplyFuelEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#include "SupplyFuelEntity.hpp"



FuelEntity::FuelEntity()
{
    consumeFuel=0;
}


bool FuelEntity::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        
        
        auto fuelBg =Sprite::createWithSpriteFrameName("fuelBg.png");
        this->addChild(fuelBg);
        fuelBg->setPosition(-50, 1);
        
        
        leftBottom=Sprite::create("SupplyMain/image 8.png");
        addChild(leftBottom);
        leftBottom->setPosition(-73-leftBottom->getContentSize().width/2,-73);
        leftBottom->setAnchorPoint(Vec2(0.0, 0.5));
        leftBottom->setOpacity(200);
        leftBottom->setFlippedX(true);
        
        rightBottom=Sprite::create("SupplyMain/image 8.png");
        addChild(rightBottom);
        rightBottom->setOpacity(200);
        rightBottom->setPosition(-28+rightBottom->getContentSize().width/2,-73);
        rightBottom->setAnchorPoint(Vec2(1.0, 0.5));
        
        
        auto fuelBox =Sprite::createWithSpriteFrameName("fuelBox.png");
        this->addChild(fuelBox);
        fuelBox->setPosition(-50, 105);
        
        auto supplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
        addChild(supplyLight);
        supplyLight->setPosition(fuelBg->getPosition()-Vec2(0,20));
        

        
        bRet=true;
    }while(0);
    
    return bRet;
}



void FuelEntity::addFuelTank(int number)
{
    if (number--)
    {
        int type=rand()%5;
        FuelTank* tank=FuelTank::create(type,fuelTank.size()+1);
        addChild(tank);
        tank->setPosition(Vec2(3+type*8-100,50));
        
        fuelTank.push_back(tank);
        tank->show(0);
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelEntity::addFuelTank, this,number));
        runAction(Sequence::create(DelayTime::create(0.03),call, NULL));
    }
}

void FuelEntity::addConsumeFuel(int val)
{
    int pre=ceil(consumeFuel/50.0);
    consumeFuel+=val;
    int curr=ceil(consumeFuel/50.0);
    if (pre<10&&curr>pre)
    {
        int minVal=10<curr?10:curr;
        addFuelTank(minVal-pre);
    }
}

void FuelEntity::minusFuelTank(int number)
{
    if (number--)
    {
        FuelTank* tank=fuelTank.back();
        fuelTank.pop_back();
        tank->disappear(0);
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelEntity::minusFuelTank, this,number));
        runAction(Sequence::create(DelayTime::create(0.03),call, NULL));
    }
}



void FuelEntity::minusConsumeFuel(int val)
{
    int pre=ceil(consumeFuel/50.0);
    consumeFuel-=val;
    int curr=ceil(consumeFuel/50.0);
    if (curr<pre)
    {
        int maxVal=curr>0?curr:0;
        minusFuelTank(pre-maxVal);
    }
}

void FuelEntity::supplyAll()
{
    FiniteTimeAction* left=ScaleBy::create(0.25, 0.0001, 1);
    FiniteTimeAction* right=ScaleBy::create(0.25, 0.0001,1);
    leftBottom->runAction(Sequence::create(left,left->reverse(), NULL));
    rightBottom->runAction(Sequence::create(right,right->reverse(), NULL));
    CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelEntity::_supplyAll, this,fuelTank.size()));
    runAction(Sequence::create(DelayTime::create(0.2),call, NULL));
}

void FuelEntity::_supplyAll(int number)
{
    if (number--)
    {
        auto tank=fuelTank.back();
        fuelTank.pop_back();
        tank->supply(0);
        
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelEntity::_supplyAll, this,number));
        tank->runAction(Sequence::create(DelayTime::create(0.05),call, NULL));
    }
}

void FuelTank::supply(float delay)
{
    FiniteTimeAction* move=MoveBy::create(0.2, Vec2(0, -150));
    CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelTank::removeNode, this));
    runAction(Sequence::create(move,call, NULL));
}


FuelTank::FuelTank()
{
    
}

bool FuelTank::init(int type,int number)
{
    bool bRet=false;
    this->number=number;
    do
    {
        if (!Node::init())
        {
            break;
        }
        
        char name[30];
        int i=24+type*2;
        sprintf(name, "SupplyMain/image %d.png",i);
        tank=Sprite::create(name);
        addChild(tank);
        tank->setPosition(Vec2::ZERO);
        bRet=true;
    }while(0);
    return bRet;
}



void FuelTankAction::fuelTankDropDown(Node *target,const Vec2 &pos,float delay)
{
    FiniteTimeAction* rotate=Repeat::create(Sequence::create(RotateBy::create(0.03, 5),RotateBy::create(0.03, -5), NULL),5);
    FiniteTimeAction* moveDown=MoveTo::create(0.3, pos);
    target->runAction(Sequence::create(DelayTime::create(delay),Spawn::create(rotate,moveDown,NULL), NULL));
}



void FuelTank::show(float delay)
{
    FuelTankAction::fuelTankDropDown(this, fuelTankLoc[number], 0);
    
}

void FuelTank::disappear(float delay)
{
    tank->setVisible(false);
    Sprite* smoke=Sprite::create("SupplyMain/image 35.png");
    smoke->setPosition(tank->getPosition());
    addChild(smoke);
    
    FiniteTimeAction* fade=Sequence::create(FadeIn::create(0.15),FadeOut::create(0.15), NULL);
    FiniteTimeAction* move=MoveTo::create(0.3, Vec2(5,14));
    CallFunc* call=CallFunc::create(CC_CALLBACK_0(FuelTank::removeNode, this));
    smoke->runAction(Sequence::create(DelayTime::create(delay),fade,move,call, NULL));
}

void FuelTank::removeNode()
{
    FuelEntity* parent=static_cast<FuelEntity*>(_parent);
    parent->removeChild(this);
}


