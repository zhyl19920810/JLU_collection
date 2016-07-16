//
//  furnitureBG.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef furnitureBG_hpp
#define furnitureBG_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN


class FurnitureBG:public cocos2d::Layer
{
public:
    CREATE_FUNC(FurnitureBG);
    
    
private:
    virtual bool init();
    cocos2d::Sprite * floor;
    cocos2d::Sprite * desk;
    cocos2d::Sprite * wall;
    cocos2d::Sprite *window;
    cocos2d::Sprite*object;
    cocos2d::Sprite* chest;
};











NS_KCL_END

#endif /* furnitureBG_hpp */
