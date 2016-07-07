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
#include "SystemHeader.h"

USING_NS_CC;

NS_KCL_BEGIN

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

NS_KCL_END

#endif /* defined(__kancolle_alpha__MissionContainer__) */
