//
//  portSupplyLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portSupplyLayer__
#define __kancolle_alpha__portSupplyLayer__

#include "cocos2d.h"

class PortScene;



USING_NS_CC;

class PortSupplyLayer:public Layer
{
public:
    PortSupplyLayer(PortScene* parent);
    
private:
    PortScene* parent;
    
private:
    void initLayer();
    
    void callBack(Ref* pSender);
};

#endif /* defined(__kancolle_alpha__portSupplyLayer__) */
