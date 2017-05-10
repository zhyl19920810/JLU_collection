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
        BattleCharacter::init();
        
        m_pBattleCharacterInfo=info;
        m_pBattleAvatarCard=BattleAvatarCard::create(m_pBattleCharacterInfo->getKantaiNumber(), m_pBattleCharacterInfo->isEnemy());
        m_pBattleAvatarCard->setPosition(718, 360 - 41 * row);
        addChild(m_pBattleAvatarCard);
        
        hpBar->setPosition(635, 341 - 41 * row);
        addChild(hpBar);
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
        
        
        currentHpLabel->setPosition(602, 360 - 41 * row);
        currentHpLabel->setAlignment(TextHAlignment::RIGHT);
        maxHpLabel->setPosition(618, 360 - 41 * row);
        this->addChild(currentHpLabel);
        this->addChild(maxHpLabel);
        
        battleBar=BattleBar::create();
        addChild(battleBar);
        
        string tempStr="Resources/kantai/" + std::to_string(m_pBattleCharacterInfo->getKantaiNumber()) + "/image 13.png";
        closeUp = Sprite::create(tempStr);
        //TODO
        //closeUp = Sprite::create("Enemy/" + std::to_string(m_pBattleCharacterInfo->getKantaiNumber()) + "/image 3.png");
        addChild(closeUp);
        closeUp->setZOrder(3);
        
        informationBoard = Sprite::create("BattleMain/image 530.png");
        addChild(informationBoard);
        informationBoard->setPosition(600, 70);
        informationBoard->setZOrder(4);
        
        
        bRet=true;
    }while(0);
    return bRet;
}

float BattleEnemy::ShowAttackingAnime(float delay)
{
    closeUp->setPosition(1200, 0);
    AnimationMaker::FlyToPositionAndFadeOut(closeUp, delay,ccp(700,240),0.5);
    UpdateInformationBoard();
    informationBoard->runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.05), DelayTime::create(0.5), FadeOut::create(0.3), NULL));
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

void BattleEnemy::UpdateInfo()
{
    informationBoard->setOpacity(0);
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

NS_KCL_END

