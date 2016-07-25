//
//  SelecterUnit.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/24/16.
//
//

#ifndef SelecterUnit_hpp
#define SelecterUnit_hpp




#include "cocos2d.h"
#include "SystemHeader.h"
#include "MenuItemTouch.hpp"
#include "ViewMgrMacro.hpp"

NS_KCL_BEGIN

enum LayerSelecterState
{
    FREE,
    SELECTED
};



class SelecterUnit:public cocos2d::Node
{
public:
    static SelecterUnit* create(PanelType);
    void setSelected(bool enable);
    
    std::string getFreeStatePath();
    std::string getSelectedStatePath();
    
private:
    bool init(PanelType);
    void layerSelectCallback(cocos2d::Ref *pSender, PanelType type);
    
    
    bool _enable;
    MenuItemSprite* _button;
    LayerSelecterState _selecterState;
    PanelType _panelType;
};





NS_KCL_END

#endif /* SelecterUnit_hpp */
