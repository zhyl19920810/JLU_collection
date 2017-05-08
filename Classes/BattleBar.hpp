//
//  BattleBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleBar_hpp
#define BattleBar_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN

USING_NS_CC;


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

class BattleBar:public Node
{
public:
    static BattleBar* create();
    virtual bool init() override;
    void openAndCloseAnimation(GreenBarPosition position, Sprite*label);
    void openAndCloseAnimation(GreenBarPosition position, Sprite*label,float delay);
    void openAndCloseAnimation(GreenBarPosition position, GreenBarLableType type);
    void openAndCloseAnimation(GreenBarPosition position, GreenBarLableType type,float delay);
    void runAction(Action* action, GreenBarPosition position);
private:
    void openAndCloseAnimation(Sprite * border, Sprite*label,float delay);
    Sprite* centerGreenBar;
    Sprite* topGreenBar;
    Sprite* bottomGreenBar;
    Sprite* label;
    
    
};

NS_KCL_END

#endif /* BattleBar_hpp */
