//
//  BattleHero.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/25/15.
//
//

#include "BattleHero.h"


NS_KCL_BEGIN

#define LabelFont "fonts/STXINWEI.ttf"
BattleHero* BattleHero::create(int kantaiNumber, cocos2d::Node *parent, int row)
{
    BattleHero* hero=new BattleHero;
    
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////

}

BattleHero* BattleHero::create(Kantai *info, cocos2d::Node *parent, int row)
{
    BattleHero* hero=new BattleHero;
    hero->setInfo(info);
    
    if (hero&&hero->init(info->getKantaiNumber(),parent,row))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}

bool BattleHero::init(int kantaiNumber, cocos2d::Node *parent, int row)
{
    this->parent=parent;
    
    parent->addChild(this);
    
    
    this->kantaiNumber=kantaiNumber;
    
    card=new CharacterCard(kantaiNumber);
    this->addChild(card);
    
    hpBar->setPosition(163,391-41*row);
    this->addChild(hpBar);
    
    if (row==1)
    {
        border=Sprite::create("interface/BattleMain/BattleMain_479.png");
        flagIcon=Sprite::create("interface/BattleMain/BattleMain_88.png");
        flagIcon->setPosition(148,417-41);
    }
    else
    {
        border=Sprite::create("interface/BattleMain/BattleMain_474.png");
    }
    border->setPosition(84,413-41*row);
    addChild(border);
    card->setPosition(80,410-41*row);
    
    currentHpLabel->setPosition(180,410-41*row);
    maxHpLabel->setPosition(197,410-41*row);
    
    addChild(currentHpLabel);
    addChild(maxHpLabel);
    
    battleBar=new BattleBar(parent);
    
    setMaxHp(info->getMaxHp());
    setCurrentHp(info->getCurrHp());
    
    return true;
}

float BattleHero::showCloseUp(float delay)
{
    if (closeUp==nullptr)
    {
        closeUp=Sprite::create("kantai/"+std::to_string(kantaiNumber)+"/image 9.png");
        parent->addChild(closeUp);
        closeUp->setZOrder(3);
        closeUp->setScale(0.8);
    }
    
    closeUp->setPosition(1200,-240);
    return AnimationMaker::FlyToCenterLeftAndFadeOut(closeUp, delay);
}



void BattleHero::stepOut(float delay)
{
    FiniteTimeAction* out=MoveBy::create(0.2, Point(40,0));
    this->runAction(Sequence::create(DelayTime::create(delay),out, NULL));
}

void BattleHero::stepBack(float delay)
{
    FiniteTimeAction* back=MoveBy::create(0.2, Point(-40,0));
    this->runAction(Sequence::create(DelayTime::create(delay),back, NULL));
}

float BattleHero::showAttackingAnime(float delay)
{
    if (closeUp==nullptr)
    {
        closeUp=Sprite::create("kantai/"+std::to_string(kantaiNumber)+"/image 9.png");
        parent->addChild(closeUp);
        closeUp->setZOrder(3);
    }
    closeUp->setPosition(-400,0);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay, ccp(100,240), 0.5);
    updateInformationBoard();
    
    informationBoard->runAction(Sequence::create(DelayTime::create(delay),FadeIn::create(0.05),DelayTime::create(0.5),FadeOut::create(0.3), NULL));
    
    if (info->canAirBattle())
    {
        return AnimationMaker::playAirBattleAnimation(parent, delay+0.9);
    }
    Equip* mainCannon=info->getMainCannon();
    if (mainCannon!=nullptr)
    {
        if (equipmentLabel!=nullptr)
        {
            removeChild(equipmentLabel);
        }
        equipmentLabel=Sprite::create("interface/BattleMain/BattleMain_53.png");
        equipmentLabel->setPosition(650,100);
        equipmentLabel->setOpacity(0);
        
        battleBar->openAndCloseAnimation(bottom, equipmentLabel, delay);
    }
    
    return 0.05+0.5+0.3;
}



void BattleHero::updateInformationBoard()
{
    if (informationBoard==nullptr)
    {
        informationBoard=Sprite::create("interface/BattleMain/BattleMain_568.png");
        parent->addChild(informationBoard);
        informationBoard->setPosition(200,70);
        informationBoard->setZOrder(4);
        
        
        firePowerLabel=Label::create("", LabelFont, 20);
        torpedoLabel=Label::create("", LabelFont, 20);
        antiaircraftLabel = Label::create("", "fonts/STXINWEI.ttf", 20);
        armourLabel = Label::create("", "fonts/STXINWEI.ttf", 20);
        nameLabel = Label::create("", "fonts/STXINWEI.ttf", 35);
        levelLabel = Label::create("", "fonts/STXINWEI.ttf", 25);
        
        
        equipment1 = Sprite::create();
        equipment2 = Sprite::create();
        equipment3 = Sprite::create();
        equipment4 = Sprite::create();
        equipment1->setPosition(190, 72);
        equipment2->setPosition(230, 72);
        equipment3->setPosition(270, 72);
        equipment4->setPosition(310, 72);
        
        informationBoard->setCascadeOpacityEnabled(true);
        
        informationBoard->addChild(firePowerLabel);
        informationBoard->addChild(torpedoLabel);
        informationBoard->addChild(antiaircraftLabel);
        informationBoard->addChild(armourLabel);
        informationBoard->addChild(nameLabel);
        informationBoard->addChild(levelLabel);
        informationBoard->addChild(equipment1);
        informationBoard->addChild(equipment2);
        informationBoard->addChild(equipment3);
        informationBoard->addChild(equipment4);
    }
    
    firePowerLabel->setString(std::to_string(info->getFirePower()));
    
    torpedoLabel->setString(std::to_string(info->getTorpedo()));
    
    antiaircraftLabel->setString(std::to_string(info->getAntiAir()));
    
    armourLabel->setString(std::to_string(info->getArmor()));
    
    nameLabel->setString(info->getKantaiName());
    
    levelLabel->setString(std::to_string(info->getCurrLV()));
    
    if (info->equipGrid[0]!=nullptr)
    {
        equipment1->setTexture("");
    }
    if (info->equipGrid[1]!=nullptr)
    {
        equipment2->setTexture("");
    }
    if (info->equipGrid[2]!=nullptr)
    {
        equipment3->setTexture("");
    }
    if (info->equipGrid[3]!=nullptr)
    {
        equipment4->setTexture("");
    }
    
    informationBoard->setOpacity(0);
}


NS_KCL_END






