//
//  LayerCover.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/16/16.
//
//

#ifndef LayerCover_hpp
#define LayerCover_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;

NS_KCL_BEGIN

class LayerCover:public Layer
{
    typedef std::function<void(Ref*)>  FUNC;
public:
    static LayerCover* create(FUNC callback);
    
    bool init(FUNC callback);
    void setCoverEnable(bool bEnble);
    
    
private:
    LayerColor* bgCover;
    EventListenerTouchOneByOne* listener;
    FUNC callback;
};

NS_KCL_END

#endif /* LayerCover_hpp */
