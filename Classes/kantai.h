//
//  KantaiPlayerGot.h
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//

#ifndef __kancolle_alpha__KantaiPlayerGot__
#define __kancolle_alpha__KantaiPlayerGot__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "kantaiDB.h"
#include "Equip.h"
#include "KantaiMgr.hpp"
#include "ExpMgr.hpp"
USING_NS_CC;

#define INIT_FATIGUEVALUE 50




typedef enum
{
    Free,
    Repairing,
    Expedition,
    Error,
}KantaiState;


class Kantai:public Ref
{
    friend class DBInit;
    friend class Player;
public:
    static Kantai* create();
    static Kantai* create(int kantaiKey,int kantaiNumber,LoadState state,Ref* parent=NULL);
    void init(int kantaiKey,int kantaiNumber,LoadState state,Ref* parent=NULL);

    
    
public:
    int getKantaiKey(){return kantaiKey;}
    int getKantaiNumber(){return kantaiNumber;}
    char* getKantaiName() const {return kantaiImp->kantaiName;}
    char* getKantaiFullName() const {return kantaiImp->kantaiFullName;}
    KantaiType getKantaiType() const{return kantaiImp->kantaiType;}
    int getBuildTime() const {return kantaiImp->buildTime;} //有可能进一步修改
    int getCurrLV() const{return currLV;}
    void setCurrLV(int lv);
    int getUpdateLV() const{return kantaiImp->updateLv;}
    int getMaxFuel() const{return kantaiImp->fuel;}
    int getMaxAmmo() const{return kantaiImp->ammo;}
    int getCurrFuel() const{return currFuel;}
    int getCurrAmmo() const{return currAmmo;}
    void setCurrFuel(int fuel);
    void setCurrAmmo(int ammo);
    Move_Speed getSpeed() const{return kantaiImp->speed;}
    Shooting_Range getRange() const {return kantaiImp->range;}
    int getMaxHp() const {return kantaiImp->maxHp;}
    int getCurrHp() const{return currHp;}
    void setCurrHp(int hp);
    int getTransformTimes() const{return kantaiImp->transformTimes;}
    int getMaxLuck() const{return kantaiImp->maxLuck;}
    int getMaxAntiSubmarine() const{return kantaiImp->maxAntiSubmarine;}
    int getMaxDodge() const{return kantaiImp->maxDodge;}
    int getMaxAntiAir() const{return kantaiImp->maxAntiAir;}
    int getMaxTorpedo() const{return kantaiImp->maxTorpedo;}
    int getMaxSearchEnemy() const{return kantaiImp->maxSearchEnemy;}
    int getMaxFirePower() const{return kantaiImp->maxFirePower;}
    int getMaxArmor() const{return kantaiImp->maxArmor;}
    int getInitSearchEnemy() const{return kantaiImp->initSearchEnemy;}
    int getInitArmor() const{return kantaiImp->initArmor;}
    int getInitLuck() const{return kantaiImp->initLuck;}
    int getInitAntiSubmarine() const{return kantaiImp->initAntiSubmarine;}
    int getInitDodge() const{return kantaiImp->initDodge;}
    int getInitTorpedo() const{return kantaiImp->initTorpedo;}
    int getInitFirePower() const{return kantaiImp->initFirePower;}
    int getInitAntiAir() const{return kantaiImp->initAntiAir;}
    int getKantaiEquipSize() const{return kantaiImp->kantaiEquipSize;}
    int getInitEquip(int number)
    {
        if (number<0&&number>=getKantaiEquipSize()) {
            CCASSERT(false, "getInitEquip error");
        }
        return kantaiImp->kantaiEquipInit[number];
    }
    int getInitPlaneLoad(int number)
    {
        if (number<0&&number>=getKantaiEquipSize()) {
            CCASSERT(false, "getInitPlaneLoad error");
        }
        return kantaiImp->planeLoad[number];
    }
    int getSearchEnemy() const{return searchEnemy;}
    int getArmor() const{return armor;}
    int getLuck() const{return luck;}
    int getAntiSubMarine() const{return AntiSubMarine;}
    int getDodge() const{return dodge;}
    int getTorpedo() const{return torpedo;}
    int getFirePower() const{return firePower;}
    int getAntiAir() const{return antiAir;}
    void setSearchEnemy(int searchEnemy);
    void setArmor(int armor);
    void setLuck(int luck);
    void setAntiSubmarine(int antiSubmarine);
    void setDodge(int dodge);
    void setTorpedo(int torpedo);
    void setFirePower(int firePower);
    void setAntiAir(int antiAir);
    bool addExp(int exp);
    void setUpdateExp();
    void setFatigueValue(int fatigueValue);
    void setKantaiLock(bool kantaiLock);
    void setKantaiStar(int kantaiStar);
    void setKantaiState(KantaiState kantaiState);
    int getFatigueValue() const{return fatigueValue;}
    bool getKantaiLock() const {return kantaiLock;}
    int getKantaiStar() const {return kantaiStar;}
    KantaiState getKantaiState() const {return kantaiState;}
    void setBrokenType();
    BrokenType getBrokenType() const {return brokenType;}
    Ref* getFleet()const {return parent;}
    void setFleet(Ref* fleet){parent=fleet;}
    
    
    
public://后期一定要修改的函数
    bool canAirBattle();
    Equip* getMainCannon();
    void getDamage(int damage);
    bool canAttack();
    
    

public:
    bool fillUpFuel();//在之前就需要判断可不可以加满,这里不调用player中减少钱的函数
    bool fillUpAmmo();//在之前就判断可不可以加满，这里不调用player中减少钱的函数
    ~Kantai();
protected:
    Kantai();
    
private:
    //inline void geneNewKantai(ValueVector& _kantaiData);
    int kantaiKey;
    
    int kantaiNumber;
    
    int currLV;
    
    int currFuel;
    
    int currAmmo;
    
    int currHp;
    
    int searchEnemy;
    
    int armor;
    
    int luck;
    
    int AntiSubMarine;
    
    int dodge;
    
    int torpedo;
    
    int firePower;
    
    int antiAir;
    
    int currExp;
    
    int updateExp;
    ///后期还得去改需要加上回调，每一定时间涨一次
    int fatigueValue;
    
    bool kantaiLock;
    //以后慢慢做
    int kantaiStar;
    
    KantaiState kantaiState;
    
    BrokenType brokenType;
public:
    std::vector<Equip*> equipGrid;
    
    std::vector<int> currPlaneLoad;
    
private:
    Ref* parent;//
    
    KantaiMgr::stKantaiData* kantaiImp;
};

//
//class KantaiPrint
//{
//public:
//    void PrintKantaiInfo(const Kantai &_kantai);
//};
//


#endif /* defined(__kancolle_alpha__KantaiPlayerGot__) */
