//
//  kantaiCard.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "kantaiCard.hpp"

NS_KCL_BEGIN


KantaiCard::KantaiCard()
{
    
}

bool KantaiCard::init()
{
    bool bRet=false;
    do
    {
        m_bIsEnemy = false;
        mainImage = Sprite::create();
        shader = Sprite::create();
        brokenMark = Sprite::create();
        this->addChild(mainImage);
        this->addChild(shader);
        this->addChild(brokenMark);
        bRet=true;
    }while(0);
    
    return bRet;
}


void KantaiCard::updateCard(Kantai* kantai,bool isEnemy)
{
    m_bIsEnemy=isEnemy;
    char name[30];
    bzero(name, sizeof(name));
    BrokenType type=kantai->getBrokenType();
    if (isEnemy)
    {
        sprintf(name, "enemy/%d/image 1.png",kantai->getKantaiNumber());
        mainImage->setTexture(name);
    }
    else if (type == BrokenType::normal || type == BrokenType::tiny)
    {
        sprintf(name, "kantai/%d/image 1.png",kantai->getKantaiNumber());
        mainImage->setTexture(name);
    }
    else
    {
        sprintf(name, "kantai/%d/image 3.png",kantai->getKantaiNumber());
        mainImage->setTexture(name);
    }
    setBrokenMark(type);
    if (kantai->getKantaiState()==KantaiState::Repairing)
    {
        brokenMark->setTexture("CommonAssets/xiufuState.png");
    }
}

void KantaiCard::setBrokenMark(BrokenType brokenType)
{

    switch (brokenType)
    {
        case BrokenType::normal:
            brokenMark->setTexture("");
            shader->setTexture("");
            break;
        case BrokenType::tiny:
            brokenMark->setTexture("CommonAssets/xiaopoState.png");
            shader->setTexture("CommonAssets/xiaopoShader.png");
            break;
        case BrokenType::mid:
            brokenMark->setTexture("CommonAssets/zhongpoState.png");
            shader->setTexture("CommonAssets/zhongpoShader.png");
            break;
        case BrokenType::large:
            brokenMark->setTexture("CommonAssets/dapoState.png");
            shader->setTexture("CommonAssets/dapoShader.png");
            break;
        case BrokenType::drown:
            brokenMark->setTexture("CommonAssets/dapoState.png");
            mainImage->setColor(Color3B(192, 192, 192));//GRAY
            shader->setTexture("CommonAssets/dapoShader.png");
            break;
        default:
            break;
    }

}

NS_KCL_END
