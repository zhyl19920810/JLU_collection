//
//  BattleEnemy.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattleEnemy.hpp"
#include "AnimationMaker.hpp"

NS_KCL_BEGIN

BattleEnemy* BattleEnemy::create(BattleCharacterInfo *info,int row)
{
    BattleEnemy* pRet=new BattleEnemy;
    if (pRet&&pRet->init(info, row))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

bool BattleEnemy::init(BattleCharacterInfo *info,int row)
{
    bool bRet=false;
    do
    {
        if (!BattleCharacter::init()) break;
        
        m_pBattleCharacterInfo=info;
        
        hpBar = Sprite::create("BattleMain/image 430.png");
        hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        hpBar->setPosition(635, 341 - 41 * row);
        addChild(hpBar);
        
        maxHpLabel = Label::create();
        maxHpLabel->setColor(Color3B::WHITE);
        maxHpLabel->setPosition(618, 360 - 41 * row);
        maxHpLabel->setString(std::to_string(maxHp));
        addChild(maxHpLabel);
        
        currentHpLabel = Label::create();
        currentHpLabel->setColor(Color3B::WHITE);
        currentHpLabel->setPosition(602, 360 - 41 * row);
        currentHpLabel->setAlignment(TextHAlignment::RIGHT);
        currentHpLabel->setString(std::to_string(currentHp));
        addChild(currentHpLabel);
        
        m_pBattleInfoBorard=BattleInfoBorard::create();
        addChild(m_pBattleInfoBorard);
        m_pBattleInfoBorard->setPosition(600, 70);
        m_pBattleInfoBorard->setGlobalZOrder(10);
        m_pBattleInfoBorard->setCascadeOpacityEnabled(true);
        
        m_pBattleAvatarCard=BattleAvatarCard::create(m_pBattleCharacterInfo->getKantaiNumber(), m_pBattleCharacterInfo->isEnemy());
        m_pBattleAvatarCard->setPosition(718, 360 - 41 * row);
        addChild(m_pBattleAvatarCard);
        SetBroken(m_pBattleCharacterInfo->getBrokenType());

        if (row == 1)
        {
            border = Sprite::create("BattleMain/image 446.png");
            flagIcon = Sprite::create("BattleMain/image 88.png");
            flagIcon->setPosition(788, 367 - 41);
            this->addChild(flagIcon);
        }
        else
            border = Sprite::create("BattleMain/image 444.png");
        border->setPosition(714, 363 - 41 * row);
        this->addChild(border);
        
        battleBar=BattleBar::create();
        addChild(battleBar);
        
        
        //TODO
        //closeUp = Sprite::create("Enemy/" + std::to_string(m_pBattleCharacterInfo->getKantaiNumber()) + "/image 3.png");
        closeUp = Sprite::create("kantai/" + std::to_string(m_pBattleCharacterInfo->getKantaiNumber()) + "/image 9.png");
        closeUp->setZOrder(3);
        closeUp->setPosition(1200, -0);
        addChild(closeUp);
        closeUp->setVisible(false);
        closeUp->setGlobalZOrder(10);
        

        
        SetMaxHp(m_pBattleCharacterInfo->getMaxHp());
        
        
        bRet=true;
    }while(0);
    return bRet;
}

float BattleEnemy::ShowAttackingAnime(float delay)
{
    closeUp->setPosition(1200, 0);
    closeUp->setVisible(true);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay,Vec2(700,240),0.5);
    m_pBattleInfoBorard->UpdateInfo(m_pBattleCharacterInfo);
    m_pBattleInfoBorard->FadeIn(delay);
    
    return 0.85;
}
void BattleEnemy::ApearAnimation()
{
    Color3B col = m_pBattleAvatarCard->getColor();
    FiniteTimeAction *tinto = TintTo::create(1.5, Color3B(242,75,75));
    FiniteTimeAction *tinback = TintTo::create(1.2, col);
    Sequence *seq = Sequence::create(tinto, tinback, NULL);
    m_pBattleAvatarCard->runAction(seq);
    
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
void BattleEnemy::ShowCloseUp()
{
    
}

void BattleEnemy::StepOut(float delay){
    FiniteTimeAction *out = MoveBy::create(0.3, Point(-40, 0));
    this->runAction(Sequence::create(DelayTime::create(delay), out, NULL));
}
void BattleEnemy::StepBack(float delay){
    FiniteTimeAction *back = MoveBy::create(0.3, Point(40, 0));
    this->runAction(Sequence::create(DelayTime::create(delay), back, NULL));
}


void BattleEnemy::ThreeDigitMode(){
    currentHpLabel->runAction(MoveBy::create(0.01, ccp(-10, 0)));
    maxHpLabel->runAction(MoveBy::create(0.01, ccp(-3, 0)));
}

void BattleEnemy::SetCurrentHp(int hp)
{
    currentHp = hp;
    currentHpLabel->setString(CCString::createWithFormat("%d", currentHp)->_string );
    float persentage = 0;
    if (maxHp != 0)
        persentage = (float)hp / (float)maxHp;
    
    hpBar->setScaleY(persentage);
    
    //setBroken(info->brokenType);
    
    if (persentage>0.75)
    {
        hpBar->setColor(Color3B::GREEN);
    }
    else if (persentage>0.50) //–°∆∆
    {
        hpBar->setColor(Color3B::YELLOW);
        SetBroken(tiny);
    }
    else if (persentage>0.25)//÷–∆∆
    {
        hpBar->setColor(Color3B::ORANGE);
        SetBroken(BrokenType::mid);
    }
    else if (persentage>0)//¥Û∆∆
    {
        hpBar->setColor(Color3B::RED);
        SetBroken(large);
    }
    else
    {
        SetBroken(drown);
    }
    
}
void BattleEnemy::SetMaxHp(int hp)
{
    if (hp > 99)
        ThreeDigitMode();
    this->maxHp = hp;
    this->maxHpLabel->setString("/"+CCString::createWithFormat("%d", maxHp)->_string);
    SetCurrentHp(hp);
}


BattleEnemy::~BattleEnemy()
{
    
}


NS_KCL_END

