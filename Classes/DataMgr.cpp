////
////  DataMgr.cpp
////  kancolle_beta
////
////  Created by 岩林张 on 8/2/16.
////
////
//
//#include "DataMgr.hpp"
//#include "SupplyInfo.hpp"
//
//NS_KCL_BEGIN
//
//
//DataMgr* DataMgr::m_instance = nullptr;
//
//DataMgr* DataMgr::getInstance()
//{
//    if (!m_instance)
//    {
//        m_instance = new DataMgr;
//        if (!m_instance->init())
//        {
//            CC_SAFE_DELETE(m_instance);
//        }
//    }
//    return m_instance;
//}
//
//
//SupplyInfo* DataMgr::getSupplyInfo()
//{
//    return m_supplyInfo;
//}
//
//bool DataMgr::init()
//{
//    bool bRet=false;
//    
//    do
//    {
//        m_supplyInfo=SupplyInfo::create();
//        
//        
//        
//        bRet=true;
//    }while(0);
//    
//    return true;
//}
//
//
//NS_KCL_END