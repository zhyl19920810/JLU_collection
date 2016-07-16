//
//  IndicatorBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef IndicatorBar_hpp
#define IndicatorBar_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

class IndicatorBar:public cocos2d::Node
{
public:
    CREATE_FUNC(IndicatorBar);
    
private:
    virtual bool init() override;
};

NS_KCL_END

#endif /* IndicatorBar_hpp */
