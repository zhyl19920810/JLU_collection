//
//  BattleCharacter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattleCharacter.hpp"
#include "AnimationMaker.hpp"


NS_KCL_BEGIN


BattleCharacter* BattleCharacter::create()
{
    BattleCharacter* pRet=new BattleCharacter;
    if (pRet&&pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

BattleCharacter::BattleCharacter()
{
    maxHp=1;
    currentHp=0;
}


bool BattleCharacter::init()
{
    bool bRet=false;
    do
    {
        
        if (!Node::init()) break;
        
//        hpBar = Sprite::create("BattleMain/image 430.png");
//        hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
//        maxHpLabel = Label::create();
//        maxHpLabel->setColor(Color3B::WHITE);
//        addChild(maxHpLabel);
//        
//        currentHpLabel = Label::create();
//        currentHpLabel->setColor(Color3B::WHITE);
//        addChild(currentHpLabel);
        
        bRet=true;
    }while(0);
    return bRet;
}




void BattleCharacter::SetCurrentHp(int hp)
{
    currentHp = hp;
    currentHpLabel->setString(CCString::createWithFormat("%d", currentHp)->_string+"/");
    m_pBattleCharacterInfo->setBrokenType();
    
    
    BrokenType type=m_pBattleCharacterInfo->getBrokenType();
    
    float persentage = 0;
    if (maxHp!=0)
        persentage = (float)currentHp / (float)maxHp;
    hpBar->setScaleY(persentage);
    
    switch (type)
    {
        case BrokenType::normal:
            hpBar->setColor(Color3B::GREEN);
            break;
        case BrokenType::tiny:
            hpBar->setColor(Color3B::YELLOW);
            break;
        case BrokenType::mid:
            hpBar->setColor(Color3B::ORANGE);
            break;
        case BrokenType::large:
            hpBar->setColor(Color3B::RED);
            break;
        case BrokenType::drown:
            break;
        default:
            break;
    }
     m_pBattleAvatarCard->UpdateCard(m_pBattleCharacterInfo->getBrokenType());
    
}
void BattleCharacter::SetMaxHp(int hp)
{
    if (hp > 99)
        ThreeDigitMode();
    this->maxHp = hp;
    this->maxHpLabel->setString(CCString::createWithFormat("%d", maxHp)->_string);
}



void BattleCharacter::GetDamage(int damage)
{
    //int newHp = info->currentHP;
    int newHp;
    if (damage > 0)
    {
        newHp = this->currentHp - damage;
        if (newHp <= 0)
            newHp = 0;
    }
    SetCurrentHp(newHp);
}
void BattleCharacter::ShowAttackedAnime(float delay){
    AnimationMaker::playShakingAnimation(this, delay);
}

bool BattleCharacter::CanAttack()
{
    if (m_pBattleCharacterInfo->getKantaiType()==KantaiType::Light_Carrier|| m_pBattleCharacterInfo->getKantaiType()==KantaiType::Battle_Carrier||m_pBattleCharacterInfo->getKantaiType()==KantaiType::Armor_Carrier)
    {
        float persentage = m_pBattleCharacterInfo->getCurrHp() / m_pBattleCharacterInfo->getMaxHp();
        if (persentage <= 0.5)
            return false;
    }
    
    
    if (m_pBattleCharacterInfo->getCurrHp() == 0)
        return false;
    
    return true;
}

Point BattleCharacter::GetRealPosition()
{
    return m_pBattleAvatarCard->getPosition();
}
void BattleCharacter::ShowDamageAnime(float delay, bool miss, bool critical, int damage)
{
    int receivedDamage = damage;
    auto callFunc = CallFunc::create(CC_CALLBACK_0(BattleCharacter::GetDamage, this, receivedDamage));
    AnimationMaker::playDamageNumberAnimation(this->GetRealPosition(),delay, miss, critical, receivedDamage, callFunc);
}
void BattleCharacter::SetBroken(BrokenType type)
{
    m_pBattleCharacterInfo->setBrokenType();
    m_pBattleAvatarCard->UpdateCard(type);
    
}
float BattleCharacter::ReceiveDamage(float delay, bool miss, bool critical, int damage,int explodeTimes)
{
    float time = AnimationMaker::playExplodeAnimation(delay, this->GetRealPosition(), explodeTimes);
    this->ShowAttackedAnime(delay);
    this->ShowDamageAnime(delay + 0.1, miss, critical, damage);
    return time;
}

std::string BattleCharacter::int2str(int &i) {
    std::string s;
    std::stringstream ss(s);
    ss << i;
    
    return ss.str();
}

void BattleCharacter::UpdateCard()
{
    m_pBattleAvatarCard->UpdateCard(m_pBattleCharacterInfo->getBrokenType());
}


NS_KCL_END
