//
//  portRemodeLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portRemodeLayer.h"


NS_KCL_BEGIN

bool PortRemodeLayer::init()
{
    bool bRet=false;
    do
    {
        
        if (!Layer::init())
        {
            
            break;
        }
        
        initLayer();
        bRet=true;
    }while(0);
    return bRet;
}


PortRemodeLayer::PortRemodeLayer()
{
    
}

void PortRemodeLayer::initLayer()
{
    Sprite* bgimg = Sprite::create("interface/RemodelMain/RemodelMain_183.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(400, 200);
    
    //detailPage = new CharacterDetailPage(this);
    //detailPage->setCharacter(GameModel::getInstance()->getFleet(0)->getShip(0));
    
}

void PortRemodeLayer::callBack(Ref* pSender)
{
    
}


NS_KCL_END