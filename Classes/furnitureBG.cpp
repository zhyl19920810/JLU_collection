//
//  furnitureBG.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "furnitureBG.hpp"


NS_KCL_BEGIN

USING_NS_CC;

bool FurnitureBG::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        floor = Sprite::create("furniture/floor/022.png");
        floor->setPosition(400, 100);
        this->addChild(floor);
        wall = Sprite::create("furniture/wall/012.png");
        wall->setPosition(400, 285);
        this->addChild(wall);
        object = Sprite::create("furniture/object/015.png");
        object->setPosition(80, 380);
        this->addChild(object);
        desk = Sprite::create("furniture/desk/021.png");
        desk->setPosition(170, 200);
        this->addChild(desk);
        window = Sprite::create("furniture/window/017.png");
        window->setPosition(450, 300);
        this->addChild(window);
        
        chest = Sprite::create("furniture/chest/003.png");
        chest->setPosition(700, 250);
        this->addChild(chest);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}




NS_KCL_END