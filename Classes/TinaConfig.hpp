//
//  TinaConfig.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/4/16.
//
//

#ifndef TinaConfig_hpp
#define TinaConfig_hpp

#include <string>
#include "tinaMacros.hpp"

TINA_NS_BEGIN


class TinaConfig
{
public:
    TinaConfig();
    ~TinaConfig();
    
    
    
private:
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _imageDir, ImageDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _txmlDir, TxmlDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _fontDir, FontDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _xmlDir, XmlDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _soundDir, SoundDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _shaderDir, ShaderDir);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _resDir, ResDir);
    
    
};



TINA_NS_END

#endif /* TinaConfig_hpp */
