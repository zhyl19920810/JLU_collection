//
//  LayerSelecter.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__LayerSelecter__
#define __kancolle_alpha__LayerSelecter__

#include "cocos2d.h"
#include "portScene.h"

USING_NS_CC;

class LayerSelecter:public Node
{
public:
    LayerSelecter(PortScene *parent,Point position);
    
    void moveOut();
    
    void moveIn();
    
    
private:
    PortScene *parent;
    
    Point initialPosition;
    Sprite *mainbody;
    Sprite *backgroud;
    
    Menu *menu;
    MenuItemImage *portItem;
    MenuItemImage *organizeItem;
    MenuItemImage *supplyItem;
    MenuItemImage *remodeItem;
    MenuItemImage *repairItem;
    MenuItemImage *factoryItem;
    
    void layerSelectCallback(Ref * pSender, LayerType type);
};


#endif /* defined(__kancolle_alpha__LayerSelecter__) */
