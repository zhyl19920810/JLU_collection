//
//  BattleCharacter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#include "BattleCharacter.h"

NS_KCL_BEGIN

BattleCharacter::BattleCharacter()
{
    border=nullptr;
    flagIcon=nullptr;
    closeUp=nullptr;
    informationBoard=nullptr;
    equipmentLabel=nullptr;
    card=nullptr;
    
    
    hpBar=Sprite::create("interface/BattleMain/BattleMain_467.png");
    hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    
    maxHpLabel=Label::create();
    currentHpLabel=Label::create();
    
    maxHpLabel->setColor(Color3B::WHITE);
    currentHpLabel->setColor(Color3B::WHITE);
}




Point BattleCharacter::getRealPosition()
{
    return this->card->getPosition();
}




void BattleCharacter::setCurrentHp(int hp)
{
    this->currentHp=hp;
    currentHpLabel->setString(std::to_string(hp)+"/");
    float persentage=0;
    if (maxHp!=0)
    {
        persentage=(float)currentHp/(float)maxHp;
    }
    
    hpBar->setScaleY(persentage);
    if (persentage>0.75)
    {
        hpBar->setColor(Color3B::GREEN);
    }
    else if(persentage>0.5)
    {
        hpBar->setColor(Color3B::YELLOW);
        setBroken(BrokenType::tiny);
    }
    else if(persentage>0.25)
    {
        hpBar->setColor(Color3B::ORANGE);
        setBroken(BrokenType::mid);
    }
    else if(persentage>0)
    {
        hpBar->setColor(Color3B::RED);
        setBroken(BrokenType::large);
    }
    else
    {
        setBroken(BrokenType::drown);
    }
}




void BattleCharacter::setMaxHp(int hp)
{
    if (hp>99)
    {
        ThreeDigitMode();
    }
    this->maxHp=hp;
    this->maxHpLabel->setString(std::to_string(hp));
}



void BattleCharacter::getDamage(int damage)
{
    int newHp;
    if (damage>0)
    {
        newHp=this->currentHp-damage;
        if (newHp<=0)
        {
            newHp=0;
        }
    }
    setCurrentHp(newHp);
}

void BattleCharacter::showAttackAnime(float delay)
{
    AnimationMaker::playShakingAnimation(this, delay);
}

void BattleCharacter::showDamgeAnime(float delay, bool miss, bool critical, int damage)
{
    int reciveDamage=damage;
    auto callFunc=CallFunc::create(CC_CALLBACK_0(BattleCharacter::getDamage, this,reciveDamage));
    AnimationMaker::playDamageNumberAnimation(this->getPosition(), this->parent, delay, miss, critical, damage, callFunc);
}


bool BattleCharacter::canAttack()
{
    if (info->getKantaiType()==KantaiType::Carrier||info->getKantaiType()==KantaiType::Light_Carrier)
    {
        float persentage=currentHp/maxHp;
        if (persentage<=0.5)
        {
            return false;
        }
    }
    
    if (currentHp==0)
    {
        return false;
    }
    
    return true;
}

float BattleCharacter::receiveDamage(float delay, bool miss, bool critical, int damage, int explodeTimes)
{
    float time=AnimationMaker::playExplodeAnimation(this->parent, delay, this->getRealPosition(),explodeTimes);
    showAttackingAnime(delay);
    showDamgeAnime(delay+0.1, miss, critical, damage);
    return time;
}



void BattleCharacter::setBroken(BrokenType type)
{
    this->type=type;
    card->updateCharacter(this->kantaiNumber, type);
}

NS_KCL_END