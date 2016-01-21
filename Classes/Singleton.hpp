//
//  Singleton.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include "cocos2d.h"

template <class T>
class Singleton
{
public:
    Singleton() {}
    
    ~Singleton() {}
    
    static T& getInstance()
    {
        assert(instance);
        return *instance;
    }
    
    static void newInstance()
    {
        CC_SAFE_DELETE(instance);
        instance = new T();
    }
    
    static void delInstance()
    {
        CC_SAFE_DELETE(instance);
    }
protected:
    static T* instance;
};
template <class T> T* Singleton<T>::instance = 0;



#endif /* Singleton_hpp */
