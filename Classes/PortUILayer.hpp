//
//  PortUILayer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef PortUILayer_hpp
#define PortUILayer_hpp

#include "cocos2d.h"
#include "ViewMgrMacro.hpp"

NS_KCL_BEGIN

USING_NS_CC;

class PortUILayer:public Layer
{
public:
    PortUILayer();
    
    
    CREATE_FUNC(PortUILayer);
    
    void changeLabelFuel(int fuel)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",fuel);
        labelFuel->setString(name);
    }
    void changeLabelSteel(int steel)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",steel);
        labelSteel->setString(name);
    }
    void changeLabelAmmo(int ammo)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",ammo);
        labelAmmo->setString(name);
    }
    void changeLabelAluminium(int aluminium)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",aluminium);
        labelAluminium->setString(name);
    }
    
    void menuHandlingCallback(Ref* pSender);
    void changeFurnitureCallback(Ref* psSender);
    void startCircle();
    void endCircle();
    void update(float dt) override;
    
    
    void changeTitlePic(kancolle::LayerType type);
private:
    bool init() override;
    
    
private:
    Sprite *black;
    Layer* currentLayer;
    Label *labelFuel;
    Label *labelSteel;
    Label *labelAmmo;
    Label *labelAluminium;
    Sprite *title;
    Label *playerName;
    Label  *playerLevel;
    Label  *playerTitle;
    Label *fleetCount;
    Label *shipCount;
    Label *quickRepairCount;
    Label *devToolCount;
    
private:
    void initPortSceneBar();
    void initSelectButton();
    void initPlayerAttr();
    void initTopLeftCircle();
    void initClock();
    
    void updatePlayerAttr(float dt);
    
};

NS_KCL_END

#endif /* PortUILayer_hpp */
