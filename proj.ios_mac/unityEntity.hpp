//
//  unityEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/9/16.
//
//

#ifndef unityEntity_hpp
#define unityEntity_hpp

#include "cocos2d.h"
#include "SystemHeader.h"
#include "kantai.h"

USING_NS_CC;


NS_KCL_BEGIN
class LayerCover;

class UnitEntity:public Node
{
public:
    
    void moveIn();
    void moveOut();
private:
    void initEntityBg(Vec2 pos);
    void setHide(bool hide);
private:
    bool hidden;
    LayerCover* layerCover;
    
protected:
    virtual void initTitle()=0;
    virtual void initEntity()=0;
    bool init(Vec2 pos);
    Kantai* kantai;
    Node* entity;
    Sprite* bgImg;
};

NS_KCL_END

#endif /* unityEntity_hpp */
