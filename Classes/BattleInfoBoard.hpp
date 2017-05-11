//
//  BattleInfoBoard.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/11/17.
//
//

#ifndef BattleInfoBoard_hpp
#define BattleInfoBoard_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN


USING_NS_CC;

class BattleCharacterInfo;

class BattleInfoBorard:public Node
{
public:
    CREATE_FUNC(BattleInfoBorard);
    
    virtual bool init() override;
    void InitInfo();
    void UpdateInfo(BattleCharacterInfo* characterInfo);
    void MoveOut(int delay);
    void FadeIn(int delay);
    
private:
    Sprite * informationBoard;
    Label *firePowerLabel;
    Label *torpedoLabel;
    Label *antiaircraftLabel;
    Label *nameLabel;
    Label *levelLabel;
    Label *armourLabel;
    Sprite *equipment1;
    Sprite *equipment2;
    Sprite* equipment3;
    Sprite* equipment4;
};








NS_KCL_END


#endif /* BattleInfoBoard_hpp */
