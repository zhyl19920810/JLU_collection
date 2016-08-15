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
#include "ViewMgrMacro.hpp"
#include "Panel.hpp"


USING_NS_CC;


NS_KCL_BEGIN

class SignBoardGirl;
class MainLayerButton;
class FurnitureBG;
class SoundPanelButton;


class PortMainLayer:public Panel
{
public:
    PortMainLayer();
    ~PortMainLayer();
     CREATE_FUNC(PortMainLayer);
    
    
    void updateGirl();
    void buttonFlyIn();
    void setButtonEnable();
    void setButtonDisable();
private:

private:
    void initLayer();
    void initMenu();
    void initSignBoardGirl();
    virtual bool init();
    
    void changePanel(PanelType);
    
    
private:
    
    SignBoardGirl* signBoardGirl;
    FurnitureBG* furnitureBG;
    MainLayerButton* organizeButton;
    MainLayerButton* supplyButton;
    MainLayerButton* remodeButton;
    MainLayerButton* repairButton;
    MainLayerButton* factoryButton;
    MainLayerButton* battleButton;
    cocos2d::Node* buttonParent;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portMainLayer__) */
