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
    static LayerSelecter* create(PortScene *parent,Point position)
    {
        LayerSelecter* tmp=new (std::nothrow)LayerSelecter;
        if (tmp&&tmp->init(parent, position))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return tmp;
    }
    
    LayerSelecter();
    
    void moveOut();
    
    void moveIn();
    
    void pauseButton(){menu->pause();}
    void resumeButton(){menu->resume();}
private:
    bool init(PortScene *parent,Point position);
    
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
