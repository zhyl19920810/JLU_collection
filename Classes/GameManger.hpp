////
////  GameManger.hpp
////  kancolle_beta
////
////  Created by 岩林张 on 1/21/16.
////
////
//
//#ifndef GameManger_hpp
//#define GameManger_hpp
//
//#include "KantaiMgr.hpp"
//#include "EquipMgr.hpp"
//#include "ExpMgr.hpp"
//#include "SallyScene.h"
//#include "GameScene.h"
//#include "Singleton.hpp"
//#include "portScene.h"
//#include "EquipPicMgr.hpp"
//#include "RepairFactorMgr.hpp"
//
//NS_KCL_BEGIN
//
//#define sGameManger GameManger::getInstance()
//
//
//class GameManger:public Singleton<GameManger>
//{
//    friend class Singleton<GameManger>;
//public:
//    GameManger();
//    ~GameManger();
//    
//    
//public:
//    void LoadResource();
//    void ClearResource();
//    void LoadConfig();
//public:
//    void setSallyScene(SallyScene* scene)
//    {
//        pSallyScene=scene;
//    }
//    SallyScene* getSallyScene()
//    {
//        return pSallyScene;
//    }
//    void setGameScene(GameScene* scene)
//    {
//        pGameScene=scene;
//    }
//    GameScene* getGameScene()
//    {
//        return pGameScene;
//    }
//    void setPortScene(PortScene* scene)
//    {
//        pPortScene=scene;
//    }
//    PortScene* getPortScene()
//    {
//        return pPortScene;
//    }
//private:
//    SallyScene* pSallyScene;
//    GameScene* pGameScene;
//    PortScene* pPortScene;
//};
//
//
//
//NS_KCL_END
//
//#endif /* GameManger_hpp */
