//
//  BattleInfoBoard.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/11/17.
//
//

#include "BattleInfoBoard.hpp"
#include "BattleCharacterInfo.hpp"

NS_KCL_BEGIN


bool BattleInfoBorard::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init()) break;
        
        InitInfo();
        
        
        bRet=true;
    }while (0);
    return bRet;
}


void BattleInfoBorard::InitInfo()
{
    
    informationBoard = Sprite::create("BattleMain/image 530.png");
    addChild(informationBoard);
    
    
    firePowerLabel = Label::createWithTTF("","fonts/STXINWEI.TTF",20);
    torpedoLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
    antiaircraftLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
    armourLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
    nameLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 35);
    levelLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 25);
    
    //firePowerLabel =Label::create();
    firePowerLabel->setPosition(80, 17);
    informationBoard->addChild(firePowerLabel);
    
    //torpedoLabel =Label::create();
    torpedoLabel->setPosition(160, 17);
    informationBoard->addChild(torpedoLabel);
    
    //antiaircraftLabel =Label::create();
    antiaircraftLabel->setPosition(240, 17);
    informationBoard->addChild(antiaircraftLabel);
    
    //armourLabel = Label::create();
    armourLabel->setPosition(320, 17);
    informationBoard->addChild(armourLabel);
    
    //nameLabel =Label::create();
    nameLabel->setPosition(45, 80);
    informationBoard->addChild(nameLabel);
    
    //levelLabel = Label::create();
    levelLabel->setPosition(60, 40);
    informationBoard->addChild(levelLabel);
    

    informationBoard->setCascadeOpacityEnabled(true);
    
    equipment1 = Sprite::create();
    equipment2 = Sprite::create();
    equipment3 = Sprite::create();
    equipment4 = Sprite::create();
    equipment1->setPosition(190, 72);
    equipment2->setPosition(230, 72);
    equipment3->setPosition(270, 72);
    equipment4->setPosition(310, 72);
    informationBoard->addChild(equipment1);
    informationBoard->addChild(equipment2);
    informationBoard->addChild(equipment3);
    informationBoard->addChild(equipment4);
    
    setOpacity(0);
}


void BattleInfoBorard::UpdateInfo(BattleCharacterInfo* characterInfo)
{
    firePowerLabel->setString(std::to_string(characterInfo->getFirePower()));
    torpedoLabel->setString(std::to_string(characterInfo->getTorpedo()));
    antiaircraftLabel->setString(std::to_string(characterInfo->getAntiAir()));
    armourLabel->setString(std::to_string(characterInfo->getArmor()));
    nameLabel->setString(characterInfo->getKantaiName());
    levelLabel->setString(std::to_string(characterInfo->getCurrLV()));
    
    
    
    if (characterInfo->GetEquipInfo(1)!= NULL)
        equipment1->setTexture(characterInfo->GetEquipInfo(1)->getIcon());
    if (characterInfo->GetEquipInfo(2)!= NULL)
        equipment2->setTexture(characterInfo->GetEquipInfo(2)->getIcon());
    if (characterInfo->GetEquipInfo(3)!= NULL)
        equipment3->setTexture(characterInfo->GetEquipInfo(3)->getIcon());
    if (characterInfo->GetEquipInfo(4)!= NULL)
        equipment4->setTexture(characterInfo->GetEquipInfo(4)->getIcon());
    
    
    setOpacity(0);
}


void BattleInfoBorard::MoveOut(int delay)
{
    setOpacity(0);
}

void BattleInfoBorard::FadeIn(int delay)
{
     runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.05), DelayTime::create(0.5), FadeOut::create(0.3), NULL));
}


NS_KCL_END

