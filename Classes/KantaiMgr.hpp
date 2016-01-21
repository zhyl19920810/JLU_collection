//
//  KantaiMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//


#ifndef KantaiMgr_hpp
#define KantaiMgr_hpp

#define MAX_NAME_STRING 33
#define MAX_SUPSHIP 19
#define MAX_EQUIP_SIZE 4
#include "Singleton.hpp"
#include "loadTxt.hpp"
#include "SystemHeader.h"

class KantaiMgr:public Singleton<KantaiMgr>
{
    friend class Singleton<KantaiMgr>;
    
protected:
    KantaiMgr();
    ~KantaiMgr();
    
    
public:
    struct stKantaiData
    {
        int kantaiNumber;
        char kantaiName[MAX_NAME_STRING];
        char kantaiFullName[MAX_NAME_STRING];
        KantaiType kantaiType;
        int buildTime;
        int lv;
        int updateLv;
        int fuel;
        int ammo;
        int speed;
        int range;
        int maxHp;
        int transformTimes;
        int maxLuck;
        int maxAntiSubmarine;
        int maxDodge;
        int maxAntiAir;
        int maxTorpedo;
        int maxSearchEnemy;
        int maxFirePower;
        int maxArmor;
        int initSearchEnemy;
        int initArmor;
        int initLuck;
        int initAntiSubmarine;
        int initDodge;
        int initTorpedo;
        int initFirePower;
        int initAntiAir;
        int kantaiEquipSize;
        int kantaiEquipInit[MAX_EQUIP_SIZE];
        int planeLoad[MAX_EQUIP_SIZE];
        
        stKantaiData()
        {
            bzero (this, sizeof (*this));
        }
    };
    typedef int MAPID;
    typedef stKantaiData MAPDATA;
    
    bool loadConf();
    
    static void kantaiMapTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        KantaiMgr* map = (KantaiMgr*)aArg;
        map->initKantaiMap(aStrArray, aArrayLen);
    }
    
    
    void initKantaiMap(const char* aStrArray[], int aArrayLen);
    
    const map<MAPID,stKantaiData>* GetKantaiMap (){return &kantaiMap;}
    
    
private:
    map<MAPID,MAPDATA>	kantaiMap;
    
};


#define sKantaiMgr KantaiMgr::getInstance()



#endif /* KantaiMgr_hpp */
