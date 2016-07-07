//
//  CharacterCard.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/25/15.
//
//

#include "CharacterCard.h"


NS_KCL_BEGIN

void CharacterCard::initCard()
{
    
    this->isEnemy=false;
    
    mainImage=Sprite::create();
    
    shader=Sprite::create();
    
    brokenMark=Sprite::create();
    
    addChild(mainImage);
    
    addChild(shader);
    
    addChild(brokenMark);
}


CharacterCard::CharacterCard()
{
    initCard();
}

CharacterCard::CharacterCard(bool isEnemy,int kantaiNumber)
{
    initCard();
    this->isEnemy=isEnemy;
    updateCharacter(kantaiNumber,BrokenType::normal);
}

CharacterCard::CharacterCard(Kantai* kantai)
{
    initCard();
    this->isEnemy=false;
    updateCharacter(kantai->getKantaiNumber(), BrokenType::normal);
}

CharacterCard::CharacterCard(int kantaiNumber)
{
    initCard();
    this->isEnemy=false;
    updateCharacter(kantaiNumber, BrokenType::normal);
}


void CharacterCard::updateCharacter(int kantaiNumber, BrokenType type)
{
    std::string _kantaiNumber=std::to_string(kantaiNumber);
    if (isEnemy)
    {
        mainImage->setTexture("kantai/" + _kantaiNumber + "/image 1.png");
        if (Sprite::create("kantai/" + _kantaiNumber + "/image 1.png")==nullptr)
        {
            mainImage->setTexture("kantai/" + _kantaiNumber + "/image 1.png");
        }
    }
    else if(type==BrokenType::normal||type==BrokenType::tiny)
    {
        mainImage->setTexture("kantai/" + _kantaiNumber + "/image 1.png");
        if (Sprite::create("kantai/" + _kantaiNumber + "/image 1.png")==nullptr)
        {
            mainImage->setTexture("kantai/" + _kantaiNumber + "/image 1.png");
        }
    }
    else
    {
        mainImage->setTexture("kantai/" + _kantaiNumber + "/image 3.png");
        if (Sprite::create("kantai/" + _kantaiNumber + "/image 3.png")==nullptr)
        {
            mainImage->setTexture("kantai/" + _kantaiNumber + "/image 3.png");
        }
    }
    setBrokenMark(type);
}







void CharacterCard::setBrokenMark(BrokenType brokenType)
{
    switch (brokenType)
    {
        case BrokenType::normal:
        {
            brokenMark->setTexture("");
            shader->setTexture("");
            break;
        }
        case BrokenType::tiny:
        {
            brokenMark->setTexture("CommonAssets/image 344.png");
            shader->setTexture("CommonAssets/image 367.png");
            break;
        }
        case BrokenType::mid:
            brokenMark->setTexture("CommonAssets/image 346.png");
            shader->setTexture("CommonAssets/image 369.png");
            break;
        case BrokenType::large:
            brokenMark->setTexture("CommonAssets/image 348.png");
            shader->setTexture("CommonAssets/image 371.png");
            break;
        case BrokenType::drown:
            brokenMark->setTexture("CommonAssets/image 350.png");
            mainImage->setColor(Color3B(192, 192, 192));//GRAY
            shader->setTexture("CommonAssets/image 371.png");
            break;
        default:
            break;
    }
    
    
}


NS_KCL_END
