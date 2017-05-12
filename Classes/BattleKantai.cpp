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
        maxHpLabel = Label::create();
        maxHpLabel->setColor(Color3B::WHITE);
        maxHpLabel->setPosition(197, 410 - 41 * row);
        maxHpLabel->setString(std::to_string(maxHp));
        addChild(maxHpLabel);
        
        currentHpLabel = Label::create();
        currentHpLabel->setColor(Color3B::WHITE);
        currentHpLabel->setPosition(180, 410 - 41 *row);
        currentHpLabel->setString(std::to_string(currentHp));
        addChild(currentHpLabel);
        
        
        m_pBattleInfoBorard=BattleInfoBorard::create();
        addChild(m_pBattleInfoBorard);
        m_pBattleInfoBorard->setPosition(200, 70);
        m_pBattleInfoBorard->setGlobalZOrder(10);
        m_pBattleInfoBorard->setCascadeOpacityEnabled(true);
        
        
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
        closeUp->setScale(0.8);
        closeUp->setPosition(-400, -0);
        closeUp->setGlobalZOrder(10);
        
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
        
        SetMaxHp(m_pBattleCharacterInfo->getMaxHp());
        SetCurrentHp(m_pBattleCharacterInfo->getCurrHp());
        SetBroken(m_pBattleCharacterInfo->getBrokenType());
        
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
    closeUp->setVisible(true);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay,Vec2(100,240),0.5);
    m_pBattleInfoBorard->UpdateInfo(m_pBattleCharacterInfo);
    m_pBattleInfoBorard->FadeIn(delay);

    
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


NS_KCL_END

