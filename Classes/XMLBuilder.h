////
////  XMLBuilder.h
////  kancolle_alpha
////
////  Created by 岩林张 on 7/31/15.
////
////
//
//#ifndef __kancolle_alpha__XMLBuilder__
//#define __kancolle_alpha__XMLBuilder__
//
//#include "SystemHeader.h"
//#include "XMLBase.h"
//
//
//
//
//
//#define PRINT_READ_RESULT    //是否输出读取到的最后结果
//
//USING_NS_CC;
//using namespace tinyxml2;
//
//class Mission;
//
//
//class XMLBuilder:public Layer
//{
//public:
//    
//    CREATE_FUNC(XMLBuilder);
//    
//    static Scene* createScene();
//    
//    virtual bool init() override;
//    
//    void setButton();
//    
//    void readXMLCallback(Ref* pSender);
//    
//    void writeXMLCallback(Ref* pSender);
//    
//    static void writeXML(int _kantaiNumber);
//    
//    static void readXML(int _kantaiNumber);
//    
//    static ValueVector readXML1(int _kantaiNumber);
//    
//    static void writeXML1(ValueVector kantaiData);
//    
//    
//    
//    //往equip中写数据
//    static void writeEquipXml(ValueVector _equipData);
//    
//    static ValueVector readEquipXml(int _equipNumber);
//    
//    static ValueVector buildTheEquipXML();
//    
//    static void printEquipXML(ValueVector _equipData);
//    
//    //往kantai中读写数据
//    static void writeKantaiXml(ValueVector _equipData);
//    
//    static ValueVector readKantaiXML(int _equipNumber);
//    
//    static ValueVector buildTheKantaiXML();
//    
//    static void printKantaiXML(ValueVector _equipData);
//
//private:
//    //static XMLElement* findNodeByName(std::string name,ScriptType type);
//    
//    
//    
//};
//
//
//
//enum ScriptType{
//    characterInfo,
//    equipment,
//    strings,
//    mission
//};
//
//#endif /* defined(__kancolle_alpha__XMLBuilder__) */
