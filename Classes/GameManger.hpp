//
//  GameManger.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#ifndef GameManger_hpp
#define GameManger_hpp

#include "KantaiMgr.hpp"
#include "EquipMgr.hpp"
#include "ExpMgr.hpp"
#include "SallyScene.h"
#include "GameScene.h"
#include "Singleton.hpp"


class GameManger:public Singleton<GameManger>
{
    friend class Singleton<GameManger>;
public:
    GameManger();
    ~GameManger();
    
    
public:
    void LoadResource();
    void ClearResource();
    void LoadConfig();
public:
    void SetSallyScene(SallyScene* scene)
    {
        pSallyScene=scene;
    }
    SallyScene* GetSallyScene()
    {
        return pSallyScene;
    }
    void SetGameScene(GameScene* scene)
    {
        pGameScene=scene;
    }
    GameScene* GetGameScene()
    {
        return pGameScene;
    }
    
    
private:
    SallyScene* pSallyScene;
    GameScene* pGameScene;
};

#define sGameManger GameManger::getInstance()


#endif /* GameManger_hpp */
