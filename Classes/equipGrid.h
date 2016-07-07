//
//  equipGrid.h
//  kancolle_alpha
//
//  Created by 岩林张 on 8/3/15.
//
//

#ifndef __kancolle_alpha__equipGrid__
#define __kancolle_alpha__equipGrid__

#include "cocos2d.h"
#include "Equip.h"

NS_KCL_BEGIN

#define CC_GETVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\

#define CC_RWVALUE(varType,varName)\
public: varType get##varName(void) const {return varName;}\
public: void set##varName(varType var) {varName=var;}\


USING_NS_CC;



class EquipGrid
{
    CC_GETVALUE(int, kantaiEquipSize);

    
public:
    EquipGrid(int _kantaiEquipSize,ValueMapIntKey _kantaiEquipInit,ValueVector _planeLoad);
    
    virtual ~EquipGrid();
    
    std::map<equilp_iter,plane_load> getplaneLoad() const
    {
        return planeLoad;
    }
    
    std::map<equilp_iter,Equip*> getequipData() const
    {
        return equipData;
    }
    
private:
    //equipSize  poi
    int kantaiEquipSize;
    
    //equipData stores the current equipment the kantai have poi
    //the first parameter "int" is  the order of the equipment poi
    //the second parameter "equip*" is the equipment abstract objects poi
    std::map<equilp_iter,Equip*> equipData;
    
    //show how many plane can load for that equipment poi
    //if that equipment is not plane poi
    //plane_load=0 poi
    std::map<equilp_iter,plane_load> planeLoad;
    
};

NS_KCL_END



#endif /* defined(__kancolle_alpha__equipGrid__) */
