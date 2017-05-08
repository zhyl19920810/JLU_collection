//
//  Compass.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef Compass_hpp
#define Compass_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

USING_NS_CC;


class Compass :public Node
{
public:
    Compass();
    CREATE_FUNC(Compass);
    virtual bool Init();
    static CompassDirection parseDirection(std::string direction);
    
private:
    CompassDirection currentDirection;
    Sprite * pointer;
    Sprite * body;
};


NS_KCL_END

#endif /* Compass_hpp */
