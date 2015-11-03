//
//  Equip.h
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//

#ifndef __kancolle_alpha__Equip__
#define __kancolle_alpha__Equip__

#include "cocos2d.h"
#include "XMLControl.h"
#include "equipDB.h"
USING_NS_CC;


//class Equip:public Ref
//{
//
//public:
//    Equip(int _equipNumber);
//
//    int GetEquipKey() const;
//
//    int GetEquipNumber() const;
//
//    std::string GetEquipName() const;
//
//    int GetEquipScope() const;
//
//    int GetEquipType() const;
//
//    bool GetIsPlane() const;
//
//    ValueMap GetEquipAdvanceAtrr() const;
//
//    ValueVector GetSupKantaiType() const;
//
//
//
//private:
//    //数据库中主键名字poi
//    int equipKey;
//
//    int equipNumber;
//
//    std::string equipName;
//
//    int equipScope;
//
//    int equipType;
//
//    bool isPlane;
//
//    ValueMap equipAdvanceAtrr;
//
//    ValueVector supKantaiType;
//
//};

#define CC_GETVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\

#define CC_RWVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\
public: void set##varName(varType var) {varName=var;}\




class EquipImp;


#define CC_GETVALUEIMP(varType,varName)\
public: varType get##varName(void) const {return equipImp->get##varName();}\

#define CC_RWVALUEIMP(varType,varName)\
public: varType get##varName(void) const {return equipImp->get##varName();}\
public: void set##varName(varType var) {equipImp->set##varName(var);}\


class EquipImp
{
    CC_RWVALUE(int, equipNumber);
    
    CC_RWVALUE(std::string, equipName);
    CC_RWVALUE(int, equipScope);
    CC_RWVALUE(int, equipType);
    CC_RWVALUE(bool, isPlane);
    
    CC_RWVALUE(int, firePower);
    CC_RWVALUE(int, AviTorpedo);
    CC_RWVALUE(int, AviBomb);
    CC_RWVALUE(int, antiAir);
    CC_RWVALUE(int, antiSubmarine);
    CC_RWVALUE(int, searchEnemy);
    CC_RWVALUE(int, hitRate);
    CC_RWVALUE(int, dodge);
    CC_RWVALUE(int, range);
    CC_RWVALUE(int, armor);
    
public:
    EquipImp(int _equipNumber);
    
    EquipImp(ValueVector& _equipData);
    
    ValueVector getSupKantaiType();
    
private:
    inline void _equipImp(ValueVector& _equipData);
    
    int equipNumber;
    
    std::string equipName;
    
    int equipScope;
    
    int equipType;
    
    bool isPlane;
    
    int firePower;
    
    int AviTorpedo;
    
    int AviBomb;
    
    int antiAir;
    
    int antiSubmarine;
    
    int searchEnemy;
    
    int hitRate;
    
    int dodge;
    
    int range;
    
    int armor;
    
    ValueVector supKantaiType;
    
    
    
};





class Equip
{
    CC_RWVALUE(int,equipKey);
    CC_RWVALUE(int, equipNumber);
    
    CC_RWVALUEIMP(std::string, equipName);
    CC_RWVALUEIMP(int, equipScope);
    CC_RWVALUEIMP(int, equipType);
    CC_RWVALUEIMP(bool, isPlane);
    
    CC_RWVALUEIMP(int, firePower);
    CC_RWVALUEIMP(int, AviTorpedo);
    CC_RWVALUEIMP(int, AviBomb);
    CC_RWVALUEIMP(int, antiAir);
    CC_RWVALUEIMP(int, antiSubmarine);
    CC_RWVALUEIMP(int, searchEnemy);
    CC_RWVALUEIMP(int, hitRate);
    CC_RWVALUEIMP(int, dodge);
    CC_RWVALUEIMP(int, range);
    CC_RWVALUEIMP(int, armor);
public:
    Equip(int equipKey,int equipNumber);
    
    
private:
    int equipKey;
    
    int equipNumber;
    
    EquipImp* equipImp;
    
    //db
    
};




class EquipDec
{
    CC_RWVALUEIMP(int, equipNumber);
    
    CC_RWVALUEIMP(std::string, equipName);
    CC_RWVALUEIMP(int, equipScope);
    CC_RWVALUEIMP(int, equipType);
    CC_RWVALUEIMP(bool, isPlane);
    
    CC_RWVALUEIMP(int, firePower);
    CC_RWVALUEIMP(int, AviTorpedo);
    CC_RWVALUEIMP(int, AviBomb);
    CC_RWVALUEIMP(int, antiAir);
    CC_RWVALUEIMP(int, antiSubmarine);
    CC_RWVALUEIMP(int, searchEnemy);
    CC_RWVALUEIMP(int, hitRate);
    CC_RWVALUEIMP(int, dodge);
    CC_RWVALUEIMP(int, range);
    CC_RWVALUEIMP(int, armor);

    
public:
    EquipDec(ValueVector& _equipData,int _count=1):equipImp(new EquipImp(_equipData)),count(_count)
    {
        
    }
    
    void addCount(){++count;}
    
    void minusCount(){--count;}
    
    int getCount() const
    {
        return count;
    }
    
    ~EquipDec();
    
    EquipImp* getEquipImp(){return equipImp;}
private:
    EquipImp* equipImp;
    int count;
};





class EquipDecData
{
public:
    static EquipImp* insertEquip(ValueVector& _equipData);
    
    static void deleteEquip(int equipNumber);
    
    static EquipImp* insertEquip(int equipNumber);
    
private:
    static std::map<int,EquipDec*> impData;
};


class EquipPrint
{
public:
    void PrintEquipInfo(const Equip &_equip);
    
    void PrintEquipInfo(Equip *_equip);
};



#endif /* defined(__kancolle_alpha__Equip__) */
