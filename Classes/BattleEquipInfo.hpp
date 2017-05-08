//
//  BattleEquipInfo.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/6/17.
//
//

#ifndef BattleEquipInfo_hpp
#define BattleEquipInfo_hpp

#include "SystemHeader.h"
#include "EquipMgr.hpp"

NS_KCL_BEGIN

USING_NS_CC;

class BattleEquipInfo:public Ref
{
public:
    static BattleEquipInfo* create(int equipNumber);
    
    bool init(int equipNumber);
    
    int getEquipNumber() const {return equipNumber;}
    char* getEquipName() const{return equipImp->equipName;}
    EquipScope getEquipScope() const{return equipImp->equipScope;}
    EquipType getEquipType() const{return equipImp->equipType;}
    bool isPlane() const{return equipImp->isPlane;}
    int getFirePower() const {return equipImp->firePower;}
    int getAviTorpedo() const {return equipImp->AviTorpedo;}
    int getAviBomb() const {return equipImp->AviBomb;}
    int getAntiAir() const {return equipImp->antiAir;}
    int getAntiSubmarine() const {return equipImp->antiSubmarine;}
    int getSearchEnemy() const {return equipImp->searchEnemy;}
    int getHitRate() const {return equipImp->hitRate;}
    int getDodge() const {return equipImp->dodge;}
    Shooting_Range getRange() const {return equipImp->range;}
    int getArmor() const {return equipImp->armor;}
    std::string getLabel() const{return "Equipment/btxt_flat/"+std::to_string(getEquipNumber())+".png";}
    std::string getIcon();
    //bool isSupKantaiType(KantaiType type);
    ~BattleEquipInfo();
protected:
    BattleEquipInfo();
private:
    int equipNumber;
    EquipMgr::stEquipData* equipImp;
};








NS_KCL_END

#endif /* BattleEquipInfo_hpp */
