//
//  Star.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "Star.hpp"

bool Stars::init()
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        for (int i = 0; i < MAX_STARS_NUMBER; i++)
        {
            stars.push_back(Sprite::create("CommonAssets/starUnit.png"));
            stars[i]->setVisible(false);
            stars[i]->setPosition(i * 15, 0);
            this->addChild(stars[i]);
        }
        bRet=true;
    }while(0);
    
    
    return bRet;
}



Stars::Stars()
{
}

void Stars::setNumber(int number)
{
    if (number>5 || number < 0)
        return;
    for (int i = 0; i < number; i++)
        stars[i]->setVisible(true);
}
