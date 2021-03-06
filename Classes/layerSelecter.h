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
    
    void pauseButton(){menu->pause();}
    void resumeButton(){menu->resume();}
private:
    PortScene *parent;
    
    Point initialPosition;
    Sprite *mainbody;
    Sprite *backgroud;
    
    Menu *menu;
    MenuItemSprite *portItem;
    MenuItemSprite *organizeItem;
    MenuItemSprite *supplyItem;
    MenuItemSprite *remodeItem;
    MenuItemSprite *repairItem;
    MenuItemSprite *factoryItem;
    
    void layerSelectCallback(Ref * pSender, LayerType type);
};


#endif /* defined(__kancolle_alpha__LayerSelecter__) */
