//
//  MissionContainer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__MissionContainer__
#define __kancolle_alpha__MissionContainer__

#include "cocos2d.h"

USING_NS_CC;

class MissionContainer:public Node
{
public:
    MissionContainer(int areaId,int index);
    
    void updateContainer(int areaId,int index);
private:
    Sprite* image;
    Sprite* passedIcon;
    bool locked;
};


#endif /* defined(__kancolle_alpha__MissionContainer__) */
