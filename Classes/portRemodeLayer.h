//
//  portRemodeLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portRemodeLayer__
#define __kancolle_alpha__portRemodeLayer__

#include "cocos2d.h"
#include "SystemHeader.h"

using namespace cocos2d;

NS_KCL_BEGIN


class PortRemodeLayer : public Layer
{
public:
    PortRemodeLayer();
    CREATE_FUNC(PortRemodeLayer);
    bool init();
    void callBack(Ref* pSender);
    
    
private:
    
    
private:
    void initLayer();
    
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portRemodeLayer__) */
