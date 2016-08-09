//
//  ValueBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/3/16.
//
//

#include "ValueBar.hpp"

NS_KCL_BEGIN

void  ValueBar::setVisible(bool visible)
{
    barPic->setVisible(visible);
}


ValueBar::ValueBar()
{
    
}

bool ValueBar::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        barPic=Sprite::create();
        addChild(barPic);
        barPic->setPosition(Vec2::ZERO);
        value=0;
        
        bRet=true;
    }while(0);
    return bRet;
}

void ValueBar::update(int value)
{
    char name[30];
    bzero(name, sizeof(name));
    sprintf(name, "value%d.png",value);
    barPic->setSpriteFrame(name);
}

NS_KCL_END