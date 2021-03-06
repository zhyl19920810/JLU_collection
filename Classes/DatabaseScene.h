//
//  DatabaseScene.h
//  kancolle_alpha
//
//  Created by 岩林张 on 7/30/15.
//
//

#ifndef __kancolle_alpha__DatabaseScene__
#define __kancolle_alpha__DatabaseScene__

#include "cocos2d.h"

#define FONT_ADDRESS "/Volumes/opengl/kancolle_alpha/Resources/fonts/arial.ttf"

USING_NS_CC;

class DatabaseLayer:public Layer
{
public:
    CREATE_FUNC(DatabaseLayer);
    
    static Scene* createScene();
    
    //init
    virtual bool init() override;
    
    //database control button
    void InitButton();
    
    
    
    void ReadDatabaseCallback(Ref* pSender);
    
    void InsertDatabaseCallback(Ref* pSender);
    
    void DataToXML(Ref* pSender);
    
    void readXMLCallback(Ref* pSender);
    
    void writeXmlCallback(Ref* pSender);
private:
    
    
    
    
    
};









#endif /* defined(__kancolle_alpha__DatabaseScene__) */
