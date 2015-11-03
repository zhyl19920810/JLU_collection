//
//  Compass.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#include "Compass.h"

Compass::Compass()
{
    body=Sprite::create("interface/SallyMain/SallyMain_830.png");
    pointer=Sprite::create("interface/SallyMain/SallyMain_833.png");
    
    addChild(body);
    addChild(pointer);
    
    pointer->runAction(RepeatForever::create((ActionInterval*)Sequence::create(
    RotateBy::create(0.15, 5),
    RotateBy::create(0.12, -8),
    RotateBy::create(0.08, 6),
    RotateBy::create(0.18, -9),
    RotateBy::create(0.21, 6),NULL)));
}

Compass_Direction Compass::parseDirection(std::string direction)
{
    if (direction=="N")
    {
        return compass_N;
    }
    else if(direction=="S")
    {
        return compass_S;
    }
    else if(direction=="W")
    {
        return compass_W;
    }
    else if(direction=="E")
    {
        return compass_E;
    }
    else if(direction=="NE")
    {
        return compass_NE;
    }
    else if(direction=="SE")
    {
        return compass_SE;
    }
    else if(direction=="NW")
    {
        return compass_NW;
    }
    else
    {
        return compass_SW;
    }
}