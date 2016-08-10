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


const static float StopTime=0.03;
const static float DropTime=0.14;
const static float LiftTime=0.34;
const static float OrbitMoveTime=0.6;



class SelecterUnit;

class LayerSelecter:public Node
{
    friend class PortPanelState;
    friend class SelecterUnit;
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
    void setBattleState();
private:
    std::map<std::string,float> xLoc;
    std::map<std::string,float> yLoc;
    std::map<std::string,Vec2>  lsPos;
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__LayerSelecter__) */
