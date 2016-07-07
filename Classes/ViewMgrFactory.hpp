//
//  ViewMgrFactory.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/6/16.
//
//

#ifndef ViewMgrFactory_hpp
#define ViewMgrFactory_hpp

#include "cocos2d.h"
#include "ViewMgrMacro.hpp"

NS_KCL_BEGIN

class ViewMgrFactory
{
public:
    static cocos2d::Scene* getScene(SceneType type,const cocos2d::Value& data=cocos2d::Value::Null);
    
    static cocos2d::Layer* getLayer(LayerType type,const cocos2d::Value& data=cocos2d::Value::Null);
};



NS_KCL_END

#endif /* ViewMgrFactory_hpp */
