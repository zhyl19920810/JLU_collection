//
//  TinaMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/4/16.
//
//

#include "TinaMgr.hpp"


TINA_NS_BEGIN


TinaMgr* TinaMgr::getInstance()
{
    static TinaMgr m_instance;
    return &m_instance;
}

TinaMgr::TinaMgr()
{
    m_config=new TinaConfig;
}

TinaMgr::~TinaMgr()
{
    delete m_config;
}

void TinaMgr::destroy()
{
}

std::string TinaMgr::getImageFullPath(const std::string& file)
{
    return m_config->getImageDir() + file;
}

std::string TinaMgr::getResFullPath(const std::string& file)
{
    return m_config->getResDir() + file;
}

std::string TinaMgr::getTxmlFullPath(const std::string& file)
{
    return m_config->getTxmlDir() + file;
}

std::string TinaMgr::getFontFullPath(const std::string& file)
{
    return m_config->getFontDir() + file;
}

std::string TinaMgr::getXmlFullPath(const std::string& file)
{
    return m_config->getXmlDir() + file;
}

std::string TinaMgr::getSoundFullPath(const std::string& file)
{
    return m_config->getSoundDir() + file;
}

std::string TinaMgr::getShaderFullPath(const std::string& file)
{
    return m_config->getShaderDir() + file;
}



TINA_NS_END