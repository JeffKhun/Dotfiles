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

/**
 * @author 
 * assessment
 */

/**
 * Determines strlen of unsigned char* without reinterpret or c-style casts.
 * @param unsigned char array
 * @return string length
 */
const size_t ustrlen(const unsigned char *s) {
    size_t i=0, l=0;
    while (s[i++]!='\0') ++l;
    return l;
}

/**
 * operator*= for string multiplication
 * @param base string
 * @param number of repetitions
 */
void operator*=(string &s, size_t &n) {
    ostringstream oss;
    while (n>0) {
        oss<<s;
        --n;
    }
    s=oss.str();
}
/**
 * String matching algorithm
 * @param text
 * @param pattern
 * @return true if matches, false otherwise
 */
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
/**
 * Expands pattern according to grammar rules.
 * @param original unparsed pattern
 * @param subsequent parsed pattern
 * @return Returns true if success, false in the event of invalid grammar
 */
const bool grammarParser(const unsigned char* s, string &r) {
    vector<string> stk; //stack
    size_t i=0;
    while (s[i]!='\0') {
        char ch=s[i];
        if (s[i]=='\\') { //Case 1: escape character
            r+=s[++i];
        } else if (s[i]=='[') { //Case 2: opening square bracket
            stk.push_back(r);
            r.clear();
            stk.push_back(string(1, s[i]));
        } else if (s[i]==']') { //Case 3: closing square bracket
            if (stk.empty() || s[++i]!='{') return false;
            size_t num=0;
            while (s[++i]!='}') {
                if (s[i]>='0' && s[i]<='9')  //checks s[i] in {0,...9}
                    num=(num*10)+(s[i]-'0'); //number of repetitions
                else return false;
            }
            if (s[i]!='}') return false;
            while (!stk.empty()) {  //unroll stack to latest '['
                if (stk.back()=="[") {
                    stk.pop_back();
                    break;
                }
                r=stk.back()+r;
                stk.pop_back();
            }
            r*=num; //overloaded operator*=
            stk.push_back(r);
            r.clear();
        } else { //Case 4: normal character
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
/**
 * Main calling function
 * @param text
 * @param pattern
 * @return pattern as stl string if found, ERROR if unvalid grammar syntax, empty string otherwise
 */
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
    unsigned char Match[]="abc[def[ghi]{3}jkl]{2}mno";//"¢a¢bc";//"abc[def]{3}ghi[j]{4}z";//"abc[def]{3}ghi[j]{4}z";//"abc";
    const unsigned char *pStr=Str;
    const unsigned char *pMatch=Match;
    cout<<PatternSearch(pStr, pMatch)<<endl;

    cin.get();
    return 0;
}
