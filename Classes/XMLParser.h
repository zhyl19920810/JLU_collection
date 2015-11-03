//
//  XMLParser.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/23/15.
//
//

#ifndef __kancolle_alpha__XMLParser__
#define __kancolle_alpha__XMLParser__

#include "cocos2d.h"
#include "XMLBase.h"
#include "Mission.h"


USING_NS_CC;



class XMLParser
{
public:
    static XMLParser* getInstance();
    
    Mission* readMissionXml(std::string id);
    
    
private:
    XMLParser();
    
    static XMLParser* instance;
    
    
};



#endif /* defined(__kancolle_alpha__XMLParser__) */
