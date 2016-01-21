//
//  ExpMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#ifndef ExpMgr_hpp
#define ExpMgr_hpp

#include "loadTxt.hpp"
#include "Singleton.hpp"
#include <map>

#define MAX_PLAYER_LV 100
#define MAX_KANTAI_LV 100

class ExpMgr:public Singleton<ExpMgr>
{
    friend class Singleton<ExpMgr>;
    
protected:
    ExpMgr();
    ~ExpMgr();
    
public:
    
    typedef int MAPID;
    typedef int MAPDATA;
    
    bool loadConf();
    
    static void playerExpMapTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        ExpMgr* map = (ExpMgr*)aArg;
        map->initPlayerExpMap(aStrArray, aArrayLen);
    }
    void initPlayerExpMap(const char* aStrArray[], int aArrayLen);
    
    
    static void kantaiExpMapTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        ExpMgr* map = (ExpMgr*)aArg;
        map->initKantaiExpMap(aStrArray, aArrayLen);
    }
    
    void initKantaiExpMap(const char* aStrArray[], int aArrayLen);
    
    int getPlayerUpdateExp(int lv);
    
    int getKantaiUpdateExp(int lv);
    
    const map<MAPID,MAPDATA>* GetPlayerExpMap (){return &playerExpMap;}
    const map<MAPID,MAPDATA>* GetKantaiExpMap (){return &playerExpMap;}
private:
    std::map<MAPID,MAPDATA> playerExpMap;
    std::map<MAPID,MAPDATA> kantaiExpMap;
};

#define sExpMgr ExpMgr::getInstance()


#endif /* ExpMgr_hpp */
