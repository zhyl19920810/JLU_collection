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
//#include "equipGrid.h"
#include "kantaiDB.h"
#include "Equip.h"

USING_NS_CC;


////存储kantai本体的xml构造方法



//valueVector kantaiData
//===>valueMap name
//舰娘的各项名字(每项名字必须存在）
//=====>std::pair<std::string,Value(std::string)> kantaiName       //舰娘名字
//=====>std::pair<std::string,Value(std::string)> kantaiFullName   //舰娘全称


//===>valueMap kantaiBaseAtrr
//舰娘的基本属性(每项基本属性必须存在）
//=====>std::pair<std::string,Value(int)> kantaiNumber
//=====>std::pair<std::string,Value(int)> kantaiType
//=====>std::pair<std::string,Value(int)> buildTime
//=====>std::pair<std::string,Value(int)> updateLv
//=====>std::pair<std::string,Value(int)> fuel
//=====>std::pair<std::string,Value(int)> ammo
//=====>std::pair<std::string,Value(int)> speed
//=====>std::pair<std::string,Value(int)> range
//=====>std::pair<std::string,Value(int)> MaxHp       //耐久值
//=====>std::pair<std::string,Value(int)> transformTimes       //改造次数


//===>valueMap kantaiMaxAtrr
//舰娘相关属性初始时候的最大值（可以有最大属性不存在，不存在的话，最大属性设为0）
//=====>std::pair<std::string,Value(int)> maxFirePower
//=====>std::pair<std::string,Value(int)> maxArmor
//=====>std::pair<std::string,Value(int)> maxTorpedo
//=====>std::pair<std::string,Value(int)> maxDodge
//=====>std::pair<std::string,Value(int)> maxAntiAir
//=====>std::pair<std::string,Value(int)> maxAntiSubmarine
//=====>std::pair<std::string,Value(int)> maxSearchEnemy
//=====>std::pair<std::string,Value(int)> maxLuck


//===>valueMap kantaiInitAtrr
//舰娘相关有最大属性的值的初始值（可以没有初始值，不存在的话，初始值设为0）
//=====>std::pair<std::string,Value(int)> initFirePower
//=====>std::pair<std::string,Value(int)> initArmor
//=====>std::pair<std::string,Value(int)> initTorpedo
//=====>std::pair<std::string,Value(int)> initDodge
//=====>std::pair<std::string,Value(int)> initAntiAir
//=====>std::pair<std::string,Value(int)> initAntiSubmarine
//=====>std::pair<std::string,Value(int)> initSearchEnemy
//=====>std::pair<std::string,Value(int)> initLuck


//<equipData>
//舰娘所初始化时候所装装载的装备
//=====>Value(int kantaiEquipSize )单个舰娘所装备格子数量最大值
//=====>Value(ValueMapIntKey kantaiEquipInit) 初始的装备 map(int,value(int)) 保存的是装备的主键值

#define CC_GETVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\

#define CC_RWVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\
public: void set##varName(varType var) {varName=var;}\

enum LoadState
{
    INIT_KANTAI,
    READ_KANTAI_DATABASE
};

enum KantaiState
{
    Free,
    Repairing,
    Expedition,
    Error,
};


class Kantai:public Ref
{

    friend class XMLParser;
    
    CC_RWVALUE(std::string, kantaiName);
    CC_RWVALUE(std::string, kantaiFullName);
    CC_GETVALUE(int, kantaiKey);
    CC_RWVALUE(int, kantaiNumber);
    CC_RWVALUE(KantaiType, kantaiType);

    CC_RWVALUE(int, maxFuel);
    CC_RWVALUE(int, maxAmmo);
    CC_RWVALUE(int, speed);
    CC_RWVALUE(int, maxHp);
    CC_RWVALUE(int, buildTime);
    CC_RWVALUE(int, transformTimes);
    
    CC_RWVALUE(int,currLV);
    CC_RWVALUE(int,currFuel);
    CC_RWVALUE(int,currAmmo);
    CC_RWVALUE(int,range);
    CC_RWVALUE(int,currExp);
    CC_RWVALUE(int,updateExp);
    CC_RWVALUE(int,firePower);
    CC_RWVALUE(int,armor);
    CC_RWVALUE(int,torpedo);
    CC_RWVALUE(int,dodge);
    CC_RWVALUE(int,antiAir);
    CC_RWVALUE(int,AntiSubMarine);
    CC_RWVALUE(int,searchEnemy);
    CC_RWVALUE(int,luck);
    CC_RWVALUE(int,fatigueValue);
    CC_RWVALUE(int,kantaiLock);
    CC_RWVALUE(int,kantaiStar);
    CC_RWVALUE(KantaiState, kantaiState);
    
    CC_RWVALUE(int, maxLuck);
    CC_RWVALUE(int, maxAntiSubmarine);
    CC_RWVALUE(int, maxDodge);
    CC_RWVALUE(int, maxAntiAir);
    CC_RWVALUE(int, maxTorpedo);
    CC_RWVALUE(int, maxSearchEnemy);
    CC_RWVALUE(int, maxFirePower);
    CC_RWVALUE(int, maxArmor);
    
public:
    Kantai(int _id,LoadState loadState);
    
    Kantai(ValueVector& _kantaiData);
    
    Kantai(int _id,ValueVector& _kantaiData);
    
    //void setEquip(Equip* equip,int postion){equipGrid[--postion]=equip;}

    void setCurrLV(int currLV);
    
    void setCurrFuel(int currFuel);
    
    void setCurrAmmo(int currAmmo);
    
    void setCurrRange(int currRange);
    
    void setCurrHp(int currHp);
    
    void setCurrExp(int currExp);
    
    void setUpdateExp(int updateExp);
    
    void setFirePower(int firePower);
    
    void setArmor(int armor);
    
    void setTorpedo(int torpedo);
    
    void setDodge(int dodge);
    
    void setAntiAir(int antiAir);
    
    void _setAntiSubmarine(int antiSubmarine);
    
    void setSearchEnemy(int searchEnemy);
    
    void setLuck(int luck);
    
    void setFatigueValue(int fatigueValue);
    
    void setKantaiLock(int kantaiLock);
    
    void setKantaiStar(int kantaiStar);
    
    void setKantaiState(KantaiState kantaiState);
    
    bool canAirBattle();
    
    Equip* getMainCannon();
    
    void setBrokenType();
    
    BrokenType getBrokenType() const {return brokenType;}
    
    int getcurrHp() const {return currHp;}
    
    void setcurrHp(int val)
    {
        currHp=val;
        setBrokenType();
    }
    
    void getDamage(int damage);
    
    bool canAttack();

protected:
    Kantai(){}
    
private:
    
    inline void geneNewKantai(ValueVector& _kantaiData);
    

    //kantai's name poi(english name + transform condition(using vol)poi）
    //for example 金刚(kongo) 金刚改(kongoVol1) 金刚二改(kongoVol2)
    //name
    std::string kantaiName;
    
    std::string kantaiFullName;
    
    //kantaiBaseAttr
    int kantaiNumber;
    
    KantaiType kantaiType;
    
    int buildTime;
    
    int updateLv;
    
    int currLV;
    
    int currFuel;//不再xml中
    
    int maxFuel;
    
    int currAmmo;///不在xml中
    
    int maxAmmo;
    
    int speed;
    
    int range;
    
    int currHp;//不再xml中
    
    int maxHp;
    
    int transformTimes;
    
    //kantaiInitAtrr
    int searchEnemy=0;
    
    int armor=0;
    
    int luck=0;
    
    int AntiSubMarine=0;
    
    int dodge=0;
    
    int torpedo=0;
    
    int firePower=0;
    
    int antiAir=0;
    
    //kantaiMaxAtrr
    int maxLuck;
    
    int maxAntiSubmarine;
    
    int maxDodge;
    
    int maxAntiAir;
    
    int maxTorpedo;
    
    int maxSearchEnemy;
    
    int maxFirePower;
    
    int maxArmor;

    ///exp由固定函数生成
    int currExp;
    
    int updateExp;
    
    //剩余其他
    int kantaiKey;
    //fatigue value influences the attack capability of the kantai poi
    int fatigueValue;
    
    bool kantaiLock;
    
    int kantaiStar;
    
    KantaiState kantaiState;
    
    BrokenType brokenType;
    
public:
    std::vector<Equip*> equipGrid;
    
    std::vector<int> planeLoadPr;
    
    std::vector<int> maxPlaneLoad;
    
    
};
//
//class KantaiPrint
//{
//public:
//    void PrintKantaiInfo(const Kantai &_kantai);
//};
//


#endif /* defined(__kancolle_alpha__KantaiPlayerGot__) */
