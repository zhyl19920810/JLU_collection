//
//  loadTxt.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#ifndef loadTxt_hpp
#define loadTxt_hpp


using namespace std;


#define MAX_LINE_CHAR 1024
#define MAX_STRINLINE 200

typedef void(*fnParseLine)(const char* aStrArray[], int aArrayLen, void* aArg);

void g_loadtxt(const char* aFileName, fnParseLine pfnCallBack, string aSplitChar, void* aArg);
std::vector<std::string> splitText(std::string str,std::string pattern);
vector<string> readFileTxt(const char *aFileName);


#endif /* loadTxt_hpp */
