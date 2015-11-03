//
//  Compass.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__Compass__
#define __kancolle_alpha__Compass__

#include "cocos2d.h"

USING_NS_CC;

enum Compass_Direction
{
    compass_N,
    compass_NE,
    compass_E,
    compass_SE,
    compass_S,
    compass_SW,
    compass_W,
    compass_NW
};

class Compass:public Node
{
public:
    Compass();
    
    static Compass_Direction parseDirection(std::string direction);
    
private:
    Compass_Direction currentDirection;
    
    Sprite* pointer;
    
    Sprite* body;
};

#endif /* defined(__kancolle_alpha__Compass__) */
