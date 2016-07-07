//
//  EquipmentContainer.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef EquipmentContainer_hpp
#define EquipmentContainer_hpp

#include "cocos2d.h"
#include "Equip.h"
using namespace cocos2d;

NS_KCL_BEGIN

class EquipContainer :public Node{
public:
    EquipContainer();
    void updateEquip(Equip* equip);
    CREATE_FUNC(EquipContainer);
    bool init();
private:
    
    void initContainer();
    Sprite* border;
    Sprite* icon;
    Sprite* cross;
    Label* label;
};

NS_KCL_END

#endif /* EquipmentContainer_hpp */
