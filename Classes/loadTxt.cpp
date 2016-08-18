//
//  loadTxt.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#include "loadTxt.hpp"
#include "cocos2d.h"
#include <stdint.h>
#include <stdio.h>

using namespace cocos2d;
using namespace std;


NS_KCL_BEGIN

typedef uint32_t uint32;

std::vector<std::string> splitText(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//¿©’π◊÷∑˚¥Æ“‘∑Ω±„≤Ÿ◊˜
    uint32 size = static_cast<uint32>(str.size());
    
    for(uint32 i = 0; i < size; i++)
    {
        pos=str.find(pattern,i);
        if(pos < size)
        {
            std::string s = str.substr(i,pos - i) + '\0';
            i = static_cast<uint32>(pos + pattern.size() - 1);
            
            if (s.substr(s.length() - pattern.length(), pattern.length()) == pattern) {
                s = s.substr(0, s.length() - pattern.length());
            }
            
            result.push_back(s);
        }
    }
    
    return result;
}

vector<string> readFileTxt(const char *aFileName)
{
    vector<string> linesBuff;
    if (NULL == aFileName)
    {
        return linesBuff;
    }
    
    unsigned char *fileText = NULL;
    ssize_t len = 0;
    fileText =FileUtils::getInstance()->getFileData(aFileName, "r", &len);
    
    string text = "";
    text.assign((char *)fileText, len);
    text += "\0";
    free(fileText);
    
    return splitText(text, "\n");
}

void g_loadtxt(const char* aFileName, fnParseLine pfnCallBack, string aSplitChar, void* aArg){
    if (NULL == aFileName || NULL == pfnCallBack)
    {
        return;
    }
    
    vector<string> linesBuff = readFileTxt(aFileName);
    
    for (vector<string>::const_iterator iter = linesBuff.begin(); iter != linesBuff.end(); iter++)
    {
        char lineBuff[MAX_LINE_CHAR];
        strcpy(lineBuff, (*iter).c_str());
        
        const char* pStrArray[MAX_STRINLINE] = {0};
        int strArrayLen = 0;
        
        const size_t len = strlen(lineBuff);
        size_t incLen = len - 1;
        
        const char* oneStr = lineBuff;
        pStrArray[strArrayLen++] = oneStr;
        
        for (size_t i = 0; i < len; i++)
        {
            if (lineBuff[i] == aSplitChar[0])
            {
                lineBuff[i] = '\0';
                if (i <= incLen)
                {
                    oneStr = lineBuff + i + 1;
                    pStrArray[strArrayLen++] = oneStr;
                }
            }
        }
        
        if( len > 0 && (len >= 2 && !(lineBuff[0] == '/' && (lineBuff[1] == '/'))))
        {
            pfnCallBack(pStrArray, strArrayLen, aArg);
        }
    }
    
    //	free(fileText);
}

NS_KCL_END
