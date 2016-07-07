//
//  KantaiDetailEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef KantaiDetailEntity_hpp
#define KantaiDetailEntity_hpp



#include "cocos2d.h"
#include "kantai.h"
#include "EquipmentContainer.hpp"
#include "HpBar.hpp"
#include "Star.hpp"

USING_NS_CC;

NS_KCL_BEGIN

class KantaiDetailEntity:public Node
{
public:
    KantaiDetailEntity();
    CREATE_FUNC(KantaiDetailEntity);
    bool init();
    void setKantai(Kantai* kantai);
    void moveOut();
    void moveIn();
    void setEquipContainerVisible(int equipNumber,bool bVisible);
    bool isHidden() {return Hidden;}
private:
    int equipSize;
    std::vector<EquipContainer*> equipContainer;
    std::vector<Sprite*> equipEmpty;
    bool Hidden;
    Sprite* kantaiDetailBg;
    Sprite* kantaiImage;
    Label * kantaiName;
    Label * kantaiLV;
    Label * kantaiHp;
    Label * maxHP;
    Label* firePower;
    Label * armour;
    Label * torpedo;
    Label * dodge;
    Label * antiAircraft;
    Label * capacity;
    Label * antiSubmarine;
    Label * searchEnemy;
    Label * luck;
    Sprite * speed;
    Sprite * range;
    
    HpBar * hpBar;
    Stars* stars;
private:
    void initPage();
};

NS_KCL_END


#endif /* KantaiDetailEntity_hpp */