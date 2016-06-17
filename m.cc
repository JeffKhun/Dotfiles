#include <cmath>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <functional>
#include <ctime>
#include <cassert>
#include <fstream>

#include <memory>
using namespace std;

const size_t ustrlen(const unsigned char *s) {
    size_t i=0, l=0;
    while (s[i++]!='\0') ++l;
    return l;
}
const bool matches(const string &pStr, const string &pMatch) {
    const size_t sLen=pStr.length();
    const size_t pLen=pMatch.length();
    for (size_t i=0; i<sLen-1; ++i) {
        size_t j=0;
        for (; j<pLen;) {
            if (pStr[i+j]==pMatch[j])
                ++j;
            else
                break;
        }
        if (j==pLen) return true;
    }
    return false;
}
const bool grammarParser(const unsigned char* s, string &r) {
    vector<string> stk;
    size_t i=0;
    while (s[i]!='\0') {
        char ch=s[i];
        if (s[i]=='\\') {
            r+=s[++i];
        } else if (s[i]=='[') {
            stk.push_back(r);
            r.clear();
            stk.push_back(string(1, s[i]));
        } else if (s[i]==']') {
            if (stk.empty() || s[++i]!='{') return false;
            size_t num=0;
            while (s[++i]!='}') {
                if (s[i]>='0' && s[i]<='9')
                    num=(num*10)+(s[i]-'0');
                else return false;
            }
            if (s[i]!='}') return false;
            while (!stk.empty()) {
                if (stk.back()=="[") {
                    stk.pop_back();
                    break;
                }
                r=stk.back()+r;
                stk.pop_back();
            }
            string t;
            t.reserve(r.length()*num);
            for (size_t k=0; k<num; ++k)
                t+=r;
            stk.push_back(t);
            r.clear();
        } else {
            r+=s[i];
        }
        ++i;   
    }
    while (!stk.empty()) {
        r=stk.back()+r;
        stk.pop_back();
    }
    return true;
}
string PatternSearch(const unsigned char* pStr, const unsigned char* pMatch) {
    static const string ERROR="ERROR";
    string expandedPattern;
    const bool result=grammarParser(pMatch, expandedPattern);
    if (!result) return ERROR;
    cout<<"Expanded pattern: "<<expandedPattern<<endl;
    return (matches(string(pStr, pStr+ustrlen(pStr)), expandedPattern)==true?string(pMatch, pMatch+ustrlen(pMatch)):"");
}
int main() {
    unsigned char Str[]="¢a¢bcdeabc abcffaaa";
    unsigned char Match[]="¢a¢bc";//"abc[def[ghi]{3}jkl]{2}mno";//"abc[def]{3}ghi[j]{4}z";//"abc[def]{3}ghi[j]{4}z";//"abc";
    const unsigned char *pStr=Str;
    const unsigned char *pMatch=Match;
    cout<<PatternSearch(pStr, pMatch)<<endl;
    cin.get();
    return 0;
}
