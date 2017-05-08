//
//  BattleCharacterInfo.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleCharacterInfo_hpp
#define BattleCharacterInfo_hpp

#include "SystemHeader.h"
#include "kantai.h"
#include "BattleEquipInfo.hpp"




NS_KCL_BEGIN

#define MAX_EQUIPMENT_NUMBER 4


USING_NS_CC;

class BattleCharacterInfo:public Ref
{
    friend class MissonLoader;
public:
    static BattleCharacterInfo* create(Kantai* kantai);
    static BattleCharacterInfo* create(int kantaiNumber);
    bool init(Kantai* kantai);
    bool init(int kantaiNumber);
    ~BattleCharacterInfo();

    
public:
    int getKantaiNumber() const{return kantaiNumber;}
    bool isEnemy() const{return m_bIsEnemy;}
    const char* getKantaiName() const {return m_KantaiImp->kantaiName;}
    const char* getKantaiFullName() const {return m_KantaiImp->kantaiFullName;}
    KantaiType getKantaiType() const{return m_KantaiImp->kantaiType;}
    int getBuildTime() const {return m_KantaiImp->buildTime;} //有可能进一步修改
    int getCurrLV() const{return currLV;}
    void setCurrLV(int lv);
    int getUpdateLV() const{return m_KantaiImp->updateLv;}
    int getMaxFuel() const{return m_KantaiImp->fuel;}
    int getMaxAmmo() const{return m_KantaiImp->ammo;}
    int getCurrFuel() const{return currFuel;}
    int getCurrAmmo() const{return currAmmo;}
    void setCurrFuel(int fuel);
    void setCurrAmmo(int ammo);
    Move_Speed getSpeed() const{return m_KantaiImp->speed;}
    Shooting_Range getRange() const {return m_KantaiImp->range;}
    int getMaxHp() const {return m_KantaiImp->maxHp;}
    int getCurrHp() const{return currHp;}
    void setCurrHp(int hp);
    int getTransformTimes() const{return m_KantaiImp->transformTimes;}
    int getMaxLuck() const{return m_KantaiImp->maxLuck;}
    int getMaxAntiSubmarine() const{return m_KantaiImp->maxAntiSubmarine;}
    int getMaxDodge() const{return m_KantaiImp->maxDodge;}
    int getMaxAntiAir() const{return m_KantaiImp->maxAntiAir;}
    int getMaxTorpedo() const{return m_KantaiImp->maxTorpedo;}
    int getMaxSearchEnemy() const{return m_KantaiImp->maxSearchEnemy;}
    int getMaxFirePower() const{return m_KantaiImp->maxFirePower;}
    int getMaxArmor() const{return m_KantaiImp->maxArmor;}
    int getInitSearchEnemy() const{return m_KantaiImp->initSearchEnemy;}
    int getInitArmor() const{return m_KantaiImp->initArmor;}
    int getInitLuck() const{return m_KantaiImp->initLuck;}
    int getInitAntiSubmarine() const{return m_KantaiImp->initAntiSubmarine;}
    int getInitDodge() const{return m_KantaiImp->initDodge;}
    int getInitTorpedo() const{return m_KantaiImp->initTorpedo;}
    int getInitFirePower() const{return m_KantaiImp->initFirePower;}
    int getInitAntiAir() const{return m_KantaiImp->initAntiAir;}
    int getKantaiEquipSize() const{return m_KantaiImp->kantaiEquipSize;}
    int getInitEquip(int number)
    {
        if (number<0&&number>=getKantaiEquipSize()) {
            CCASSERT(false, "getInitEquip error");
        }
        return m_KantaiImp->kantaiEquipInit[number];
    }
    int getInitPlaneLoad(int number)
    {
        CCASSERT(number>=1&&number<=getKantaiEquipSize(), "getInitPlaneLoad error");
        return m_KantaiImp->planeLoad[number-1];
    }
    int getSearchEnemy() const{return searchEnemy;}
    int getArmor() const{return armor;}
    int getLuck() const{return luck;}
    int getAntiSubMarine() const{return AntiSubMarine;}
    int getDodge() const{return dodge;}
    int getTorpedo() const;
    int getBomb() const;
    int getHitRate() const;
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
    void setBrokenType();
    BrokenType getBrokenType() const {return brokenType;}
    
    BattleEquipInfo* GetEquipInfo(int number)
    {
        return m_vEquipInfo[number-1];
    }
    
    BattleEquipInfo*  GetMainCannon();
    bool CanAirBattle();
private:
    void InitInfo();
    
    
    
private:
    

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
    //int currExp;
    //int updateExp;
    int fatigueValue;
    bool kantaiLock;
    int kantaiStar;
    BrokenType brokenType;
    
    
    std::vector<BattleEquipInfo*>    m_vEquipInfo;
    std::vector<int>                 m_vCurrPlaneLoad;
    bool                             m_bIsEnemy;
    const KantaiMgr::stKantaiData*   m_KantaiImp;
    Kantai*                          m_Kantai;
    
    
public:
    //void addEquipment(BattleEquipInfo* equipment,int index);
    bool CanAttack();
    void GetDamage(int damage);
    bool GetAirCraftId(std::string &plane1, std::string &plane2, std::string plane3);
};


NS_KCL_END


#endif /* BattleCharacterInfo_hpp */
