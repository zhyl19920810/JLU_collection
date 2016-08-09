//
//  buildKantaiUnit.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/3/16.
//
//

#ifndef buildKantaiUnit_hpp
#define buildKantaiUnit_hpp

#include "cocos2d.h"
#include "Player.h"

NS_KCL_BEGIN

typedef enum
{
    kantaiBuilding,
    equipBuilding
}factoryBM;


class BuildKantaiUnit:public Node
{
public:
    bool init(factoryBM mode);
    
    //build
    bool canBuildKantai() const {return canBuild;}
    void setCanBuild(bool canBuild){this->canBuild=canBuild;}
    int getResouce() const {return currRes;}
    void updateRes();
private:
    bool canBuild;
    
private:
    void initBg();
    Menu* mn;
    
    
    
    void initRes();
    virtual void initIcon()=0;
    int minRes;
    int maxRes;
    int currRes;
    factoryBM mode;
    
    virtual int getPlayerRes()=0;
    virtual void minusPlayerRes(int res)=0;
    //callback
    void arrowCallback(Ref* pSender,bool addDir);
    void decadeCallback(Ref* pSender,bool addDir);
    void hundredCallback(Ref* pSender,bool addDir);
    void maxCallback(Ref* pSender);
    void resetCallback(Ref* pSender);
    
    bool canAddDecade();
    bool canMinusDecade();
    bool canAddHundred();
    bool canMinusHundred();
    void setDecadeButtonVisible(bool addButton);
    
    //
    Label* resLabel;
    MenuItemSprite* addArrow;
    MenuItemSprite* minusArrow;
    
    MenuItemSprite* addDecade;
    MenuItemSprite* minusDecade;
    MenuItemSprite* addHundred;
    MenuItemSprite* minusHundred;
    
    MenuItemSprite* resetButton;
    MenuItemSprite* maxButton;
    

    void updateButtonAndLabel(float dt);
protected:
    Sprite* unitBg;
};



class FuelBuildUnit:public BuildKantaiUnit
{
public:
    static FuelBuildUnit* create(factoryBM mode);
    virtual int getPlayerRes();
    virtual void initIcon();
    virtual void minusPlayerRes(int res);
};

class AmmoBuildUnit:public BuildKantaiUnit
{
public:
    static AmmoBuildUnit* create(factoryBM mode);
    virtual int getPlayerRes();
    virtual void initIcon();
    virtual void minusPlayerRes(int res);
};


class SteelBuildUnit:public BuildKantaiUnit
{
public:
    static SteelBuildUnit* create(factoryBM mode);
    virtual int getPlayerRes();
    virtual void initIcon();
    virtual void minusPlayerRes(int res);
};

class AlBuildUnit:public BuildKantaiUnit
{
public:
    static AlBuildUnit* create(factoryBM mode);
    virtual int getPlayerRes();
    virtual void initIcon();
    virtual void minusPlayerRes(int res);
};



NS_KCL_END






#endif /* buildKantaiUnit_hpp */
