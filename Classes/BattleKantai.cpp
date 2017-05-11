//
//  BattleKantai.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#include "BattleKantai.hpp"
#include "AnimationMaker.hpp"


NS_KCL_BEGIN

std::string int2str(int &i) {
    std::string s;
    std::stringstream ss(s);
    ss << i;
    
    return ss.str();
}


BattleKantai* BattleKantai::create(kancolle::BattleCharacterInfo *info,int row)
{
    BattleKantai* pRet=new BattleKantai;
    if (pRet&&pRet->init(info,row))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool BattleKantai::init(kancolle::BattleCharacterInfo *info,int row)
{
    bool bRet=false;
    
    do
    {
        if (!BattleCharacter::init()) break;
        
        m_pBattleCharacterInfo=info;
        
        hpBar = Sprite::create("BattleMain/image 430.png");
        hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        hpBar->setPosition(163, 391 - 41 * row);
        addChild(hpBar);
        
        //TODO
        maxHp=m_pBattleCharacterInfo->getMaxHp();
        maxHpLabel = Label::create();
        maxHpLabel->setColor(Color3B::WHITE);
        maxHpLabel->setPosition(197, 410 - 41 * row);
        maxHpLabel->setString(std::to_string(maxHp));
        addChild(maxHpLabel);
        
        
        currentHp=m_pBattleCharacterInfo->getCurrHp();
        currentHpLabel = Label::create();
        currentHpLabel->setColor(Color3B::WHITE);
        currentHpLabel->setPosition(180, 410 - 41 *row);
        currentHpLabel->setString(std::to_string(currentHp));
        addChild(currentHpLabel);
        
        InitInfo();
        
        
        m_pBattleAvatarCard=BattleAvatarCard::create(info->getKantaiNumber(), info->isEnemy());
        m_pBattleAvatarCard->setPosition(80, 410 - 41 * row);
        this->addChild(m_pBattleAvatarCard);
        SetBroken(info->getBrokenType());

        if (row == 1)
        {
            border = Sprite::create("BattleMain/image 442.png");
            flagIcon = Sprite::create("BattleMain/image 88.png");
            flagIcon->setPosition(148, 417 - 41);
            addChild(flagIcon);
        }
        else
            border = Sprite::create("BattleMain/image 437.png");
        border->setPosition(84, 413 - 41 * row);
        addChild(border);
        
        

        battleBar=BattleBar::create();
        addChild(battleBar);
        
        //default

        
        closeUp = Sprite::create("kantai/" + std::to_string(m_pBattleCharacterInfo->getKantaiNumber()) + "/image 9.png");
        addChild(closeUp);
        closeUp->setZOrder(3);
        closeUp->setScale(0.8);
        
        
        
        m_pMainCannon=NULL;
        m_pMainCannon=m_pBattleCharacterInfo->GetMainCannon();
        if (m_pMainCannon)
        {
            string tempStr=m_pMainCannon->getLabel();
            equipmentLabel = Sprite::create("btxt_flat/001.png");
            equipmentLabel->setPosition(650, 100);
            equipmentLabel->setOpacity(0);
        }
        else
        {
            equipmentLabel=NULL;
        }


        
        bRet=true;
    }while(0);
    return bRet;
}






float BattleKantai::ShowCloseUp(float delay)
{

    closeUp->setPosition(1200, -240);
    return AnimationMaker::FlyToCenterLeftAndFadeOut(closeUp,delay);
}


float BattleKantai::ShowAttackingAnime(float delay)
{
    closeUp->setPosition(-400, -0);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay,ccp(100,240),0.5);
    UpdateInformationBoard();
    informationBoard->runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.05), DelayTime::create(0.5), FadeOut::create(0.3), NULL));
    
    if (m_pBattleCharacterInfo->CanAirBattle())
    {
        return AnimationMaker::playAirBattleAnimation(delay + 0.9);
    }
    
    if (m_pMainCannon)
    {
        battleBar->openAndCloseAnimation(bottom, equipmentLabel, delay);
    }
    
    return 0.05+0.5+0.3;
}


void BattleKantai::StepOut(float delay){
    FiniteTimeAction *out = MoveBy::create(0.2, Point(40, 0));
    this->runAction(Sequence::create(DelayTime::create(delay), out, NULL));
}


void BattleKantai::StepBack(float delay){
    FiniteTimeAction *back = MoveBy::create(0.2, Point(-40, 0));
    this->runAction(Sequence::create(DelayTime::create(delay),back,NULL));
}

void BattleKantai::InitInfo()
{

    informationBoard = Sprite::create("BattleMain/image 530.png");
    addChild(informationBoard);
    informationBoard->setPosition(200, 70);
    informationBoard->setZOrder(4);
    informationBoard->setCascadeOpacityEnabled(true);
    
    firePowerLabel =Label::create();
    firePowerLabel->setPosition(80, 17);
    informationBoard->addChild(firePowerLabel);
    
    torpedoLabel =Label::create();
    torpedoLabel->setPosition(160, 17);
    informationBoard->addChild(torpedoLabel);
    
    antiaircraftLabel =Label::create();
    antiaircraftLabel->setPosition(240, 17);
    informationBoard->addChild(antiaircraftLabel);
    
    armourLabel = Label::create();
    armourLabel->setPosition(320, 17);
    informationBoard->addChild(armourLabel);
    
    nameLabel =Label::create();
    nameLabel->setPosition(45, 80);
    informationBoard->addChild(nameLabel);
    
    levelLabel = Label::create();
    levelLabel->setPosition(60, 40);
    informationBoard->addChild(levelLabel);
    
//    firePowerLabel = Label::createWithTTF("","fonts/STXINWEI.TTF",20);
//    torpedoLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
//    antiaircraftLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
//    armourLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 20);
//    nameLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 35);
//    levelLabel = Label::createWithTTF("", "fonts/STXINWEI.TTF", 25);
    
    
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
}

void BattleKantai::UpdateInfo()
{
    firePowerLabel->setString(std::to_string(m_pBattleCharacterInfo->getFirePower()));
    torpedoLabel->setString(std::to_string(m_pBattleCharacterInfo->getTorpedo()));
    antiaircraftLabel->setString(std::to_string(m_pBattleCharacterInfo->getAntiAir()));
    armourLabel->setString(std::to_string(m_pBattleCharacterInfo->getArmor()));
    nameLabel->setString(m_pBattleCharacterInfo->getKantaiName());
    levelLabel->setString(std::to_string(m_pBattleCharacterInfo->getCurrLV()));
    
    
    
    if (m_pBattleCharacterInfo->GetEquipInfo(1)!= NULL)
        equipment1->setTexture(m_pBattleCharacterInfo->GetEquipInfo(1)->getIcon());
    if (m_pBattleCharacterInfo->GetEquipInfo(2)!= NULL)
        equipment2->setTexture(m_pBattleCharacterInfo->GetEquipInfo(2)->getIcon());
    if (m_pBattleCharacterInfo->GetEquipInfo(3)!= NULL)
        equipment3->setTexture(m_pBattleCharacterInfo->GetEquipInfo(3)->getIcon());
    if (m_pBattleCharacterInfo->GetEquipInfo(4)!= NULL)
        equipment4->setTexture(m_pBattleCharacterInfo->GetEquipInfo(4)->getIcon());
    
    
    informationBoard->setOpacity(0);
}

NS_KCL_END

