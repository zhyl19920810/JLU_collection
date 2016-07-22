//
//  PortBgLayer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef PortBgLayer_hpp
#define PortBgLayer_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

class PortBgLayer:public cocos2d::Layer
{
public:
    CREATE_FUNC(PortBgLayer);
    
    
private:
    bool init() override;
    cocos2d::Sprite *bgImage;
    
    cocos2d::GLProgramState* m_blurGLProgramState;
    void initBlurGLprogram();
};

NS_KCL_END


#endif /* PortBgLayer_hpp */
