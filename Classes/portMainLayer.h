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


typedef enum
{
    organizeBu,
    supplyBu,
    remodeBu,
    repairBu,
    factoryBu,
    battleBu
}ButtonType;



class PortMainLayer:public cocos2d::Layer
{
public:
    PortMainLayer();
    
    ~PortMainLayer();
    
    void updateGirl();
    
    CREATE_FUNC(PortMainLayer);
    virtual bool init();
    
    void resumeDispatcher();
private:
    int girlflag;
    Sprite * floor;
    Sprite * desk;
    Sprite * wall;
    Sprite *window;
    Sprite*object;
    Sprite* chest;
    Sprite *girl;
    
    Sprite* organizeButton;
    Sprite* supplyButton;
    Sprite* remodeButton;
    Sprite* repairButton;
    Sprite* factoryButton;
    
    
    Sprite* battleButtonShip;
    Sprite* battleButtonGo;
    Sprite* battleButton;
    Sprite* battleLeft;
    Sprite* battleRight;
    Action* battleShipRotate;
    Action* battleLeftMove;
    Action* battleRightMove;
private:
    void stopButtonAction();
    void startButtonAction(const Vec2& point);
    Action* wave;
    Action* rotate;
    Sprite* rotateButton;
    Sprite* waveButton;
    

    bool stopEvent;
private:
    void initLayer();
    
    void initMenu();
    
    void menuCallback(Ref* pSender);
    
    void battleCallback(Ref* pSender);
    
    void layerSelectCallback(Ref * pSender, LayerType type);
    
    bool organizeBegin(Touch* touch,Event* event);
    void organizeMove(Touch* touch,Event* event);
    void organizeEnd(Touch* touch,Event* event);
    
    bool battleBegin(Touch* touch,Event* event);
    void battleMove(Touch* touch,Event* event);
    void battleEnd(Touch* touch,Event* event);
};

#endif /* defined(__kancolle_alpha__portMainLayer__) */
