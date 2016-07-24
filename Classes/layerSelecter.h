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

NS_KCL_BEGIN

class LayerSelecter:public Node
{
public:
    static LayerSelecter* create()
    {
        LayerSelecter* pRet=new (std::nothrow)LayerSelecter;
        if (pRet&&pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
        pRet=NULL;
        return pRet;
    }
    
    LayerSelecter();
    
    void moveOut();
    
    void moveIn();
    
    void pauseButton(){menu->pause();}
    void resumeButton(){menu->resume();}
private:
    bool init();
    
    Sprite *mainbody;
    Sprite *backgroud;
    
    Menu *menu;
    MenuItemSprite *portItem;
    MenuItemSprite *organizeItem;
    MenuItemSprite *supplyItem;
    MenuItemSprite *remodeItem;
    MenuItemSprite *repairItem;
    MenuItemSprite *factoryItem;
    
    void layerSelectCallback(Ref * pSender, PanelType type);
    
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__LayerSelecter__) */
