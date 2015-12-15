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
#include <set>


USING_NS_CC;



#define CC_GETVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\

#define CC_RWVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\
public: void set##varName(varType var) {varName=var;}\


#define CC_GETVALUEIMP(varType,varName)\
public: varType get##varName(void) const {return equipImp->get##varName();}\

#define CC_RWVALUEIMP(varType,varName)\
public: varType get##varName(void) const {return equipImp->get##varName();}\
public: void set##varName(varType var) {equipImp->set##varName(var);}\



class EquipImp;
class EquipDec;
class EquipPoolManager;


class EquipImp
{
    CC_GETVALUE(int, equipNumber);
    
    CC_GETVALUE(std::string, equipName);
    CC_GETVALUE(Shooting_Range, equipScope);
    CC_GETVALUE(EquipType, equipType);
    CC_GETVALUE(bool, isPlane);
    
    CC_GETVALUE(int, firePower);
    CC_GETVALUE(int, AviTorpedo);
    CC_GETVALUE(int, AviBomb);
    CC_GETVALUE(int, antiAir);
    CC_GETVALUE(int, antiSubmarine);
    CC_GETVALUE(int, searchEnemy);
    CC_GETVALUE(int, hitRate);
    CC_GETVALUE(int, dodge);
    CC_GETVALUE(int, range);
    CC_GETVALUE(int, armor);
    
public:
    static EquipImp* create(int _equipNumber);
    
    std::set<KantaiType>& getSupKantaiType();
    
    ~EquipImp();
    
protected:
    EquipImp();
    
    friend class XMLParser;
private:
    int equipNumber;
    
    std::string equipName;
    
    Shooting_Range equipScope;
    
    EquipType equipType;
    
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
    
    std::set<KantaiType> supKantaiType;
    
};





class Equip:public Ref
{
    CC_RWVALUE(int,equipKey);
    CC_RWVALUE(int, equipNumber);
    
    CC_GETVALUEIMP(std::string, equipName);
    CC_GETVALUEIMP(Shooting_Range, equipScope);
    CC_GETVALUEIMP(EquipType, equipType);
    CC_GETVALUEIMP(bool, isPlane);
    
    CC_GETVALUEIMP(int, firePower);
    CC_GETVALUEIMP(int, AviTorpedo);
    CC_GETVALUEIMP(int, AviBomb);
    CC_GETVALUEIMP(int, antiAir);
    CC_GETVALUEIMP(int, antiSubmarine);
    CC_GETVALUEIMP(int, searchEnemy);
    CC_GETVALUEIMP(int, hitRate);
    CC_GETVALUEIMP(int, dodge);
    CC_GETVALUEIMP(int, range);
    CC_GETVALUEIMP(int, armor);
    
public:
    static Equip* create();
    
    static Equip* create(int equipKey,int equipNumber,Ref* parent=0);
    
    void init(int equipKey,int equipNumber,Ref* parent);
    
    void setKantai(Ref* parent);
    
    Ref* getKantai() const;
    
    ~Equip();
    
    std::set<KantaiType>& getSupKantaiType() const;
protected:
    Equip();
    
private:
    int equipKey;
    
    int equipNumber;
    
    EquipImp* equipImp;
    
    Ref* parent;
};



class EquipDec
{
    CC_GETVALUEIMP(int, equipNumber);
    
    CC_GETVALUEIMP(std::string, equipName);
    CC_GETVALUEIMP(Shooting_Range, equipScope);
    CC_GETVALUEIMP(EquipType, equipType);
    CC_GETVALUEIMP(bool, isPlane);
    
    CC_GETVALUEIMP(int, firePower);
    CC_GETVALUEIMP(int, AviTorpedo);
    CC_GETVALUEIMP(int, AviBomb);
    CC_GETVALUEIMP(int, antiAir);
    CC_GETVALUEIMP(int, antiSubmarine);
    CC_GETVALUEIMP(int, searchEnemy);
    CC_GETVALUEIMP(int, hitRate);
    CC_GETVALUEIMP(int, dodge);
    CC_GETVALUEIMP(int, range);
    CC_GETVALUEIMP(int, armor);

friend class EquipPoolManager;
public:
    EquipDec(EquipImp* equipimp);
    
    void clear();
    
    int getCount() const
    {
        return count;
    }
    
    EquipImp* getEquipImp() const
    {return equipImp;}
    
private:
    EquipImp* equipImp;
    int count;
};



class EquipPoolManager
{
public:
    static EquipPoolManager* getInstance();
    
    void deleteEquip(int equipNumber);
    
    EquipImp* insertEquip(int equipNumber);
    
    void clear();
    
    void print();
private:
    static EquipPoolManager* equipDecData;
    
    std::map<int,EquipDec*> impData;
};


class EquipPrint
{
public:
    static void PrintEquipInfo(const Equip &_equip);
    
    static void PrintEquipInfo(Equip *_equip);
};


#endif /* defined(__kancolle_alpha__Equip__) */
