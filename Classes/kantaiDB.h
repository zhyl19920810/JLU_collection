//
//  kantaiDB.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__kantaiDB__
#define __kancolle_alpha__kantaiDB__

#include "cocos2d.h"
#include "databaseBase.h"
#include "equipDB.h"

using namespace cocos2d;

NS_KCL_BEGIN

class KantaiDB:public DBBase
{
public:
    int getNewKantaiByNumber(int kantaiNumber);
    
    int getNewKantaiByNumber(ValueVector& _kantaiData); //返回kantaikey
    
    static KantaiDB* getInstance();
    
    std::vector<std::pair<int,int>>  getNewKantaiEquip(int _kantaiKey,ValueVector& _kantaiData);
    
    std::vector<std::pair<int,int>>  getNewKantaiEquip(int _kantaiKey,std::vector<int> equipVec);
    
    void deleteKantaiKey(int kantaiKey,bool InFleet);
    
    void deleteKantaiFleet(int kantaiKey);
    
    void changeKantaiPosition(int _kantaiKey,int _fleetNumber,int _position);
    
    
    
    //kantai attribute update
    void setCurrLV(int kantaiKey,int currLV);
    
    void setCurrFuel(int kantaiKey,int currFuel);
    
    void setCurrAmmo(int kantaiKey,int currAmmo);
    
    void setCurrRange(int kantaiKey,int currRange);
    
    void setCurrHp(int kantaiKey,int currHp);
    
    void setCurrExp(int kantaiKey,int currExp);
    
    void setUpdateExp(int kantaiKey,int updateExp);
    
    void setFirePower(int kantaiKey,int firePower);
    
    void setArmor(int kantaiKey,int armor);
    
    void setTorpedo(int kantaiKey,int torpedo);
    
    void setDodge(int kantaiKey,int dodge);
    
    void setAntiAir(int kantaiKey,int antiAir);
    
    void setAntiSubmarine(int kantaiKey,int antiSubmarine);
    
    void setSearchEnemy(int kantaiKey,int searchEnemy);
    
    void setLuck(int kantaiKey,int luck);
    
    void setFatigueValue(int kantaiKey,int fatigueValue);
    
    void setKantaiLock(int kantaiKey,int kantaiLock);
    
    void setKantaiStar(int kantaiKey,int kantaiStar);
    
    void setKantaiState(int kantaiKey,int kantaiState);
    
    
protected:
    KantaiDB();
    
private:
    static KantaiDB* kantaiDB;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__kantaiDB__) */
