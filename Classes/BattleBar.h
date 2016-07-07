//
//  BattleBar.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__BattleBar__
#define __kancolle_beta__BattleBar__

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

enum GreenBarPosition
{
    top,
    topleft,
    center,
    bottom
};

enum GreenBarLableType
{
    scout_start,
    scouter_doesnt_back,
    enemy_scouted,
    enemy_scouted_scouter_doesnt_back,
    enemy_not_scouted,
    enemy_seen
};


USING_NS_CC;


class BattleBar
{
public:
    BattleBar(Node *parent);
    
    void openAndCloseAnimation(GreenBarPosition position,Sprite* label);
    
    void openAndCloseAnimation(GreenBarPosition position,Sprite* label,float delay);
    
    void openAndCloseAnimation(GreenBarPosition position,GreenBarLableType type);
    
    void openAndCloseAnimation(GreenBarPosition position,GreenBarLableType type,float delay);
    
    void runAction(Action* action,GreenBarPosition position);
    
private:
    void init();
    
    void openAndCloseAnimation(Sprite * border, Sprite*label,float delay);
    
    Node* parent;
    
    Sprite* centerGreenBar;
    
    Sprite* topGreenBar;
    
    Sprite* bottomGreenBar;
};

NS_KCL_END

#endif /* defined(__kancolle_beta__BattleBar__) */
