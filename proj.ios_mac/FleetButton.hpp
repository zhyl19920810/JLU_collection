//
//  FleetButton.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/1/16.
//
//

#ifndef FleetButton_hpp
#define FleetButton_hpp

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class FleetButton:public Node
{
    typedef function<void(int)> ButtonUpdate;
public:
    FleetButton();
    
    static FleetButton* create(ButtonUpdate buttonUpdate)
    {
        FleetButton* tmp=new(std::nothrow) FleetButton;
        if (tmp&&tmp->init(buttonUpdate))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    bool init(ButtonUpdate buttonUpdate);
    void SetFleetButtonVisible(int fleetNumber,bool bVisible);
    void fleetCallback(Ref* pSender,int layNumber);
    void changeFleet(int fleetNumber);
    void update(int fleetNumber);
private:
    std::vector<Sprite*> fleetSprite;
    std::vector<MenuItemToggle*> fleetToggle;
    
    function<void(int)> buttonUpdate;
    int fleetNumber;
    Fleet* fleet;
};

#endif /* FleetButton_hpp */
