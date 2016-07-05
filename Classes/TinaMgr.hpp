//
//  TinaMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/4/16.
//
//

#ifndef TinaMgr_hpp
#define TinaMgr_hpp

#include "TinaConfig.hpp"
#include <string>

TINA_NS_BEGIN

#define TINA_MGR TinaMgr::getInstance()
class TinaMgr
{
public:
    static TinaMgr* getInstance();
    static void destroy();
    TinaConfig* getConfig()
    {
        return m_config;
    }
    
public:
    std::string getImageFullPath(const std::string& file);
    std::string getResFullPath(const std::string& file);
    std::string getTxmlFullPath(const std::string& file);
    std::string getAnimFullPath(const std::string& file);
    std::string getFontFullPath(const std::string& file);
    std::string getXmlFullPath(const std::string& file);
    std::string getLangFullPath(const std::string& file);
    std::string getSoundFullPath(const std::string& file);
    std::string getShaderFullPath(const std::string& file);
    std::string getParticleFullPath(const std::string& file);
    std::string getLuaFullPath(const std::string& file);
    //cocos2d::TTFConfig getTTFConfigWithFontName(const std::string& fontName);
    
private:
    TinaMgr();
    ~TinaMgr();
    
private:
    TinaConfig*		m_config;
};
TINA_NS_END



#endif /* TinaMgr_hpp */
