//
//  BattleModel.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__BattleModel__
#define __kancolle_beta__BattleModel__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

NS_KCL_BEGIN

enum FormationType
{
    DanZong=1,
    FuZong=2,
    LunXing=3,
    TiXing = 4,
    DanHeng = 5
};

enum Attack_Type{
    dayBattle,
    nightBattle,
    antiSubmarine,
    
};


enum T_Word
{
    TongHang,
    FanHang,
    TYouLi,
    TBuLi
};
enum Air_Control{
    full, //÷∆ø’»®»∑±£
    advantage, //∫Ωø’”≈ ∆
    balanced, //æ˘ ∆
    lost //÷∆ø’»®…• ß
};


class BattleModel
{
public:
    BattleModel();
    BattleModel(Fleet* allies,Fleet* enemy,FormationType alliesFormation,FormationType enemyFormation);
    
    
    
    inline Air_Control getAirControl(){return airControl;}

    
    void getFireDamage(bool alliesAttack, int alliesIndex, int enemyIndex, bool &doubleHit, bool &specialAttack, bool &ci,int &damage, bool &critical,bool &miss);
    
    void resetFireBattle();

    bool getNextIndexToFire(bool &allies, int &index);

    int getTargetIndex(bool alliesAttack);
    
    
    
public:
    std::vector<Kantai*> allies;
    std::vector<Kantai*> enemy;
    
    FormationType alliesFormation;
    FormationType enemyFormation;
    T_Word tword;
    
private:

    Air_Control airControl;

    
    int getDamage(Attack_Type attackType,float basicAttack,int enemyArmour,float preCorrection,float postCorrection,float AmmoCorrection);
    
    float getDamageAfterMaxCorrection(float damage,Attack_Type type);
    
    float formationCorrection(FormationType type,bool antiSubmarine);
    
    float TWordCorrection(T_Word t);
    
    float brokenCorrection(BrokenType type);
    
    float ammoCorrection();
    
    BrokenType getBrokenType(int currentHP,int maxHp);
    
    void insertToRangeVector(Shooting_Range range,int index);
    
    
    
    std::vector<int> exlongIndex;
    std::vector<int> longIndex;
    std::vector<int> midIndex;
    std::vector<int> shortIndex;
};


NS_KCL_END




#endif /* defined(__kancolle_beta__BattleModel__) */
