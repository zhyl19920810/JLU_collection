//
//  portMainLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portMainLayer__
#define __kancolle_alpha__portMainLayer__

#include "cocos2d.h"
#include "portScene.h"
USING_NS_CC;

class PortMainLayer:public cocos2d::Layer
{
public:
    PortMainLayer(PortScene* parent);
    
    ~PortMainLayer();
    
    void updateGirl();
    
private:
    int girlflag;
    PortScene * parent;
    Sprite * floor;
    Sprite * desk;
    Sprite * wall;
    Sprite *window;
    Sprite*object;
    Sprite* chest;
    Sprite *girl;
    
    
private:
    void initLayer();
    
    void initMenu();
    
    void menuCallback(Ref* pSender);
    
    void battleCallback(Ref* pSender);
    
    void layerSelectCallback(Ref * pSender, LayerType type);
    
    
    
};

#endif /* defined(__kancolle_alpha__portMainLayer__) */
