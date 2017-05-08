//
//  BattleAvatarCard.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattleAvatarCard.hpp"


NS_KCL_BEGIN

BattleAvatarCard* BattleAvatarCard::create(int kantaiNumber,bool isEnemy)
{
    BattleAvatarCard* pRet=new BattleAvatarCard;
    if (pRet&&pRet->init(kantaiNumber,isEnemy))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

bool BattleAvatarCard::init(int kantaiNumber,bool isEnemy)
{
    bool bRet=false;
    do
    {
        m_bIsEnemy=isEnemy;
        m_iKantaiNumber=kantaiNumber;
        m_pMainImage = Sprite::create();
        m_pShader = Sprite::create();
        m_pBrokenMark = Sprite::create();
        this->addChild(m_pMainImage);
        this->addChild(m_pShader);
        this->addChild(m_pBrokenMark);
        
        bRet=true;
    }while(0);
    return bRet;
}


void BattleAvatarCard::UpdateCard(BrokenType type)
{
    if (m_bIsEnemy)
    {
        m_pMainImage->setTexture("Enemy/" + std::to_string(m_iKantaiNumber) + "/image 1.png");
    }
    else if (type == BrokenType::normal || type == BrokenType::tiny)
    {
        m_pMainImage->setTexture("Character/" + std::to_string(m_iKantaiNumber) + "/image 1.png");
    }
    else
    {
        m_pMainImage->setTexture("Character/" + std::to_string(m_iKantaiNumber) + "/image 3.png");
    }
    SetBrokenMark(type);
}


void BattleAvatarCard::UpdateCard(int kantaiNumber, BrokenType type)
{
    m_iKantaiNumber=kantaiNumber;
    UpdateCard(type);
}

void BattleAvatarCard::SetBrokenMark(BrokenType brokenType)
{
    switch (brokenType)
    {
        case BrokenType::normal:
            m_pBrokenMark->setTexture("");
            m_pShader->setTexture("");
            break;
        case BrokenType::tiny:
            m_pBrokenMark->setTexture("commonAssets/image 344.png");
            m_pShader->setTexture("commonAssets/image 367.png");
            break;
        case BrokenType::mid:
            m_pBrokenMark->setTexture("commonAssets/image 346.png");
            m_pShader->setTexture("commonAssets/image 369.png");
            break;
        case BrokenType::large:
            m_pBrokenMark->setTexture("commonAssets/image 348.png");
            m_pShader->setTexture("commonAssets/image 371.png");
            break;
        case BrokenType::drown:
            m_pBrokenMark->setTexture("commonAssets/image 350.png");
            m_pMainImage->setColor(Color3B(192, 192, 192));//GRAY
            m_pShader->setTexture("commonAssets/image 371.png");
            break;
        default:
            break;
    }
}




//
//CharacterCard::CharacterCard()
//{
//    initCard();
//    
//}
//CharacterCard::CharacterCard(bool isEnemy, std::string resourcefolder)
//{
//    initCard();
//    this->isEnemy = isEnemy;
//    updateCharacter(resourcefolder, BrokenType::normal);
//}
//CharacterCard::CharacterCard(CharacterInfo* info)
//{
//    initCard();
//    updateCharacter(info->resourceFolder, info->brokenType);
//}
//CharacterCard::CharacterCard(std::string resourcefolder)
//{
//    initCard();
//    updateCharacter(resourcefolder, BrokenType::normal);
//}
//
//void CharacterCard::initCard()
//{
//    this->isEnemy = false;
//    mainImage = Sprite::create();
//    shader = Sprite::create();
//    brokenMark = Sprite::create();
//    this->addChild(mainImage);
//    
//    this->addChild(shader);
//    this->addChild(brokenMark);
//}
//void CharacterCard::updateCharacter(std::string resourceFolder, BrokenType type)
//{
//    
//    if (isEnemy)
//    {
//        mainImage->setTexture("Enemy/" + resourceFolder + "/image 1.png");
//        if (Sprite::create("Enemy/" + resourceFolder + "/image 1.png") == nullptr)
//            mainImage->setTexture("Enemy/" + resourceFolder + "/image 1.jpg");
//    }
//    
//    else if (type == BrokenType::normal || type == BrokenType::tiny)
//    {
//        mainImage->setTexture("Character/" + resourceFolder + "/image 1.png");
//        if (Sprite::create("Character/" + resourceFolder + "/image 1.png") == nullptr)
//            mainImage->setTexture("Character/" + resourceFolder + "/image 1.jpg");
//    }
//    
//    else
//    {
//        mainImage->setTexture("Character/" + resourceFolder + "/image 3.png");
//        if (Sprite::create("Character/" + resourceFolder + "/image 3.png") == nullptr)
//            mainImage->setTexture("Character/" + resourceFolder + "/image 3.jpg");
//    }
//    setBrokenMark(type);
//}
//


//
//void CharacterCard::setBrokenMark(BrokenType brokenType)
//{
//    switch (brokenType)
//    {
//        case BrokenType::normal:
//            brokenMark->setTexture("");
//            shader->setTexture("");
//            break;
//        case BrokenType::tiny:
//            brokenMark->setTexture("commonAssets/image 344.png");
//            shader->setTexture("commonAssets/image 367.png");
//            break;
//        case BrokenType::mid:
//            brokenMark->setTexture("commonAssets/image 346.png");
//            shader->setTexture("commonAssets/image 369.png");
//            break;
//        case BrokenType::large:
//            brokenMark->setTexture("commonAssets/image 348.png");
//            shader->setTexture("commonAssets/image 371.png");
//            break;
//        case BrokenType::drown:
//            brokenMark->setTexture("commonAssets/image 350.png");
//            mainImage->setColor(Color3B(192, 192, 192));//GRAY
//            shader->setTexture("commonAssets/image 371.png");
//            break;
//        default:
//            break;
//    }
//}

NS_KCL_END

