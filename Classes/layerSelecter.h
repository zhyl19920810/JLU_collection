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
#include "ViewMgrMacro.hpp"


USING_NS_CC;

NS_KCL_BEGIN

class SelecterUnit;

class LayerSelecter:public Node
{
    friend class PortPanelState;
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
    void changeHookPos(PanelType type);
    void setLayerType(PanelType type);
private:
    bool init();
    void loadLocData();
    void initButton();
    void initBg();
    void initHook();
    
    Sprite *mainbody;
    Sprite *backgroud;
    Sprite* hook;
    
    PanelType currType;
    SelecterUnit *mainButton;
    SelecterUnit *organizeButton;
    SelecterUnit *supplyButton;
    SelecterUnit *remodeButton;
    SelecterUnit *repairButton;
    SelecterUnit *factoryButton;
    
private:
    SelecterUnit* getSelecterUnit(PanelType type) const;
    std::string getPanelName(PanelType type) const;
    bool isPortPanel(PanelType type) const;
    
    
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__LayerSelecter__) */
