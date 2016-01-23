//
//  BattleEnemy.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 11/3/15.
//
//

#include "BattleEnemy.h"
#include "AnimationMaker.h"


BattleEnemy* BattleEnemy::create(Kantai* info, cocos2d::Node *parent, int row)
{
    BattleEnemy* hero=new BattleEnemy;
    hero->setInfo(info);
    if (hero&&hero->init(info->getKantaiNumber(), parent, row))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}


bool BattleEnemy::init(int kantaiNumber, cocos2d::Node *parent, int row)
{
    parent->addChild(this);
    this->parent=parent;
    this->kantaiNumber=kantaiNumber;
    
    card=new CharacterCard(true,kantaiNumber);
    addChild(card);
    
    
    hpBar->setPosition(635,341-41*row);
    addChild(hpBar);
    
    if (row==1)
    {
        border=Sprite::create("interface/BattleMain/BattleMain_483.png");
        flagIcon = Sprite::create("interface/BattleMain/BattleMain_88.png");
        flagIcon->setPosition(788, 367 - 41);
        this->addChild(flagIcon);
    }
    else
        border=Sprite::create("interface/BattleMain/BattleMain_481.png");
    
    border->setPosition(714, 363-41*row);
    addChild(border);
    card->setPosition(718, 360-41*row);
    
    
    
    return true;
}


void BattleEnemy::apearAnimation()
{
    Color3B col = card->getColor();
    FiniteTimeAction *tinto = TintTo::create(1.5, Color3B(242,75,75));
    FiniteTimeAction *tinback = TintTo::create(1.2, col);
    Sequence *seq = Sequence::create(tinto, tinback, NULL);
    card->runAction(seq);
    
    FiniteTimeAction *fadeIn = FadeIn::create(1);
    border->setOpacity(0);
    border->runAction(fadeIn);
    
    FiniteTimeAction *fadeIn2 = FadeIn::create(0.6);
    hpBar->setOpacity(0);
    hpBar->runAction(fadeIn2);
    
    maxHpLabel->setCascadeOpacityEnabled(true);
    currentHpLabel->setCascadeOpacityEnabled(true);
    
    FiniteTimeAction *fadeIn3 = FadeIn::create(0.3);
    maxHpLabel->setOpacity(0);
    maxHpLabel->runAction(fadeIn3);
    
    FiniteTimeAction *fadeIn4 = FadeIn::create(0.3);
    currentHpLabel->setOpacity(0);
    currentHpLabel->runAction(fadeIn4);
}


void BattleEnemy::ThreeDigitMode()
{
    currentHpLabel->runAction(MoveBy::create(0.01, ccp(-10,0)));
    maxHpLabel->runAction(MoveBy::create(0.01, ccp(-3,0)));
}

void BattleEnemy::setCurrentHp(int hp)
{
    currentHp=hp;
    currentHpLabel->setString(std::to_string(hp));
    float percentage=0;
    
    if (maxHp)
    {
        percentage=((float)hp)/((float)maxHp);
    }
    hpBar->setScaleY(percentage);
    
    if (percentage>0.75)
    {
        hpBar->setColor(Color3B::GREEN);
    }
    else if (percentage>0.50)
    {
        hpBar->setColor(Color3B::YELLOW);
        setBroken(tiny);
    }
    else if(percentage>0.25)
    {
        hpBar->setColor(Color3B::ORANGE);
        setBroken(BrokenType::mid);
    }
    else if(percentage>0)
    {
        hpBar->setColor(Color3B::RED);
        setBroken(BrokenType::large);
    }
    else
    {
        setBroken(BrokenType::drown);
    }
    
}

void BattleEnemy::setMaxHp(int hp)
{
    if (hp>99)
    {
        ThreeDigitMode();
    }
    this->maxHp=hp;
    this->maxHpLabel->setString("/"+std::to_string(hp));
    setCurrentHp(hp);
}

void BattleEnemy::stepOut(float delay)
{
    FiniteTimeAction* out=MoveBy::create(0.3, Point(-40,0));
    runAction(Sequence::create(DelayTime::create(delay),out, NULL));
}

void BattleEnemy::stepBack(float delay)
{
    FiniteTimeAction* back=MoveBy::create(0.3, Point(40,0));
    runAction(Sequence::create(DelayTime::create(delay),back, NULL));
}

float BattleEnemy::showAttackingAnime(float delay)
{
    if (closeUp==nullptr)
    {
        closeUp=Sprite::create("kantai/"+std::to_string(kantaiNumber)+"/image 3.png");
        parent->addChild(closeUp);
        closeUp->setZOrder(3);
    }
    
    closeUp->setPosition(1200,0);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay,Point(700,240), 0.5);
    updateInformationBoard();
    
    informationBoard->runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.05), DelayTime::create(0.5), FadeOut::create(0.3), NULL));
    return 0.85;
    
}

void BattleEnemy::updateInformationBoard()
{
    if (informationBoard == nullptr)
    {
        informationBoard = Sprite::create("interface/BattleMain/BattleMain_568.png");
        parent->addChild(informationBoard);
        informationBoard->setPosition(600, 70);
        informationBoard->setZOrder(4);
        
    }
    informationBoard->setOpacity(0);
}

void BattleEnemy::showCloseUp()
{
    
}









