//
//  RepairFactorMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#ifndef RepairFactorMgr_hpp
#define RepairFactorMgr_hpp

#include "Singleton.hpp"
#include "loadTxt.hpp"
#include "SystemHeader.h"
#include <string>





class RepairFactorMgr:public Singleton<RepairFactorMgr>
{
    friend class Singleton<RepairFactorMgr>;
protected:
    RepairFactorMgr();
    ~RepairFactorMgr();
    
    
public:
    struct stRepairFactorData
    {
        float steelFactor;
        float ammoFactor;
        
        stRepairFactorData()
        {
            bzero(this, sizeof(this));
        }
    };
    typedef int MAPID;
    typedef stRepairFactorData MAPDATA;
    
    bool loadConf();
    
    static void repairFactorTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        RepairFactorMgr* map = (RepairFactorMgr*)aArg;
        map->initRepairFactorMap(aStrArray, aArrayLen);
    }
    
    void initRepairFactorMap(const char* aStrArray[], int aArrayLen);
    
    float getSteelFactor(int kantaiNumber)
    {
        auto it=repairFactorMap.find(kantaiNumber);
        if (it!=repairFactorMap.end())
        {
            return it->second.steelFactor;
        }
        CCASSERT(false,"can not find the kantai");
    }
    
    float getAmmoFactor(int kantaiNumber)
    {
        auto it=repairFactorMap.find(kantaiNumber);
        if (it!=repairFactorMap.end())
        {
            return it->second.ammoFactor;
        }
        CCASSERT(false,"can not find the kantai");
    }
    
    
private:
    map<MAPID,MAPDATA>	repairFactorMap;
    
};


#define sRepairFactorMgr RepairFactorMgr::getInstance()

#endif /* RepairFactorMgr_hpp */
