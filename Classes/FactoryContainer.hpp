//
//  portFactoryContainer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#ifndef portFactoryContainer_hpp
#define portFactoryContainer_hpp


#include "cocos2d.h"
#include "MenuItemTouch.hpp"
#include "arsenal.hpp"

USING_NS_CC;



class FactoryContainer:public Node
{
public:
    enum FactoryState
    {
        free,
        building,
        finish
    };
    
    static FactoryContainer* create(int position);
    bool init(int position);
    void initBg();
    void initButton();
    void initArsenal();
    
    void selectButtonCallback(Ref* pSender);
    void fastBuildCallback(Ref* pSender);
    void buildCallback(Ref* pSender);
    void getCallback(Ref* pSender);
    void update();
private:
    int position;
    FactoryState state;
    MenuItemButton* fastBuild;
    MenuItemSprite* buildButton;
    MenuItemSprite* getButton;
    Sprite* shipFinish;
    Menu* mn;
    Sprite* title;
    
    Sprite* slipway;
};


#endif /* portFactoryContainer_hpp */
