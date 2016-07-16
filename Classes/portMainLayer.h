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


NS_KCL_BEGIN

class SignBoardGirl;
class MainLayerButton;
class FurnitureBG;


class PortMainLayer:public cocos2d::Layer
{
public:
    PortMainLayer();
    ~PortMainLayer();
     CREATE_FUNC(PortMainLayer);
    
    
    void updateGirl();
    void resumeDispatcher();
private:

private:
    void initLayer();
    void initMenu();
    void initSignBoardGirl();
    virtual bool init();
private:
    SignBoardGirl* signBoardGirl;
    FurnitureBG* furnitureBG;
    MainLayerButton* organizeButton;
    MainLayerButton* supplyButton;
    MainLayerButton* remodeButton;
    MainLayerButton* repairButton;
    MainLayerButton* factoryButton;
    MainLayerButton* battleButton;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portMainLayer__) */
