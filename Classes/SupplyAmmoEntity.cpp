//
//  SupplyAmmoEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#include "SupplyAmmoEntity.hpp"

AmmoEntity::AmmoEntity()
{
    consumeAmmo=0;
}


bool AmmoEntity::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        
        
        auto ammoBg =Sprite::createWithSpriteFrameName("ammoBg.png");
        this->addChild(ammoBg);
        ammoBg->setPosition(50, 0);
        
        auto ammoBox =Sprite::createWithSpriteFrameName("ammoBox.png");
        this->addChild(ammoBox,2);
        ammoBox->setPosition(50, 105);
        
        auto rSupplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
        addChild(rSupplyLight,3);
        rSupplyLight->setPosition(ammoBg->getPosition()-Vec2(0,15));
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}



void AmmoEntity::addAmmoTank(int number)
{
    if (number--)
    {
        int type=rand()%5;
        AmmoTank* tank=AmmoTank::create(type,ammoTank.size()+1);
        addChild(tank);
        tank->setPosition(Vec2(3+type*8,50));
        
        ammoTank.push_back(tank);
        tank->show(0);
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(AmmoEntity::addAmmoTank, this,number));
        runAction(Sequence::create(DelayTime::create(0.03),call, NULL));
    }
}

void AmmoEntity::addConsumeAmmo(int val)
{
    int pre=consumeAmmo/50;
    consumeAmmo+=val;
    int curr=consumeAmmo/50;
    if (curr>pre)
    {
        int minVal=10<curr?10:curr;
        addAmmoTank(minVal-pre);
    }
}

void AmmoEntity::minusAmmoTank(int number)
{
    if (number--)
    {
        AmmoTank* tank=ammoTank.back();
        ammoTank.pop_back();
        tank->disappear(0);
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(AmmoEntity::minusAmmoTank, this,number));
        runAction(Sequence::create(DelayTime::create(0.03),call, NULL));
    }
}



void AmmoEntity::minusConsumeAmmo(int val)
{
    int pre=consumeAmmo/50;
    consumeAmmo-=val;
    int curr=consumeAmmo/50;
    if (curr<pre)
    {
        int maxVal=curr>0?curr:0;
        minusAmmoTank(pre-maxVal);
    }
}

void AmmoEntity::supplyAll()
{
    _supplyAll(ammoTank.size());
}

void AmmoEntity::_supplyAll(int number)
{
    if (number--)
    {
        auto tank=ammoTank.back();
        ammoTank.pop_back();
        tank->supply(0);
        
        CallFunc* call=CallFunc::create(CC_CALLBACK_0(AmmoEntity::_supplyAll, this,number));
        tank->runAction(Sequence::create(DelayTime::create(0.05),call, NULL));
    }
}

void AmmoTank::supply(float delay)
{
    FiniteTimeAction* move=MoveBy::create(0.2, Vec2(0, -150));
    CallFunc* call=CallFunc::create(CC_CALLBACK_0(AmmoTank::removeNode, this));
    runAction(Sequence::create(move,call, NULL));
}


AmmoTank::AmmoTank()
{
    
}

bool AmmoTank::init(int type,int number)
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
        int i=41+type*2;
        sprintf(name, "SupplyMain/image %d.png",i);
        tank=Sprite::create(name);
        addChild(tank);
        tank->setPosition(Vec2::ZERO);
        bRet=true;
    }while(0);
    return bRet;
}



void SupplyLayerAction::ammoTankDropDown(Node *target,const Vec2 &pos,float delay)
{
    FiniteTimeAction* rotate=Repeat::create(Sequence::create(RotateBy::create(0.03, 5),RotateBy::create(0.03, -5), NULL),5);
    FiniteTimeAction* moveDown=MoveTo::create(0.3, pos);
    target->runAction(Sequence::create(DelayTime::create(delay),Spawn::create(rotate,moveDown,NULL), NULL));
}



void AmmoTank::show(float delay)
{
    SupplyLayerAction::ammoTankDropDown(this, ammoTankLoc[number], 0);
    
}

void AmmoTank::disappear(float delay)
{
    tank->setVisible(false);
    Sprite* smoke=Sprite::create("SupplyMain/image 35.png");
    smoke->setPosition(tank->getPosition());
    addChild(smoke);
    
    FiniteTimeAction* fade=Sequence::create(FadeIn::create(0.15),FadeOut::create(0.15), NULL);
    FiniteTimeAction* move=MoveTo::create(0.3, Vec2(5,14));
    CallFunc* call=CallFunc::create(CC_CALLBACK_0(AmmoTank::removeNode, this));
    smoke->runAction(Sequence::create(DelayTime::create(delay),fade,move,call, NULL));
}

void AmmoTank::removeNode()
{
    AmmoEntity* parent=static_cast<AmmoEntity*>(_parent);
    parent->removeChild(this);
}


