#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/**
 * @param pattern
 * @return stl string representation of pattern
 */
std::string toString(const std::vector<unsigned char> &pattern) {
    std::ostringstream oss;
    for (size_t i=0; i<pattern.size(); ++i)
        oss<<pattern[i];
    return oss.str();
}

/**
 * Determines strlen of unsigned char* without reinterpret or c-style casts.
 * @param unsigned char array
 * @return length
 */
const size_t ustrlen(const unsigned char *str) {
    size_t i=0, l=0;
    while (str[i++]!='\0') ++l;
    return l;
}

/**
 * Boyer-Moore-Horspool matching algorithm
 * @param text
 * @param pattern
 * @return true if matching occurs, false otherwise
 */
const bool boyerMooreHorspool(const unsigned char *text,  const std::vector<unsigned char> &pattern) {

    const int patternLength=pattern.size();
    const int textLength=ustrlen(text);
 
    if (patternLength>textLength) return false;
    if (patternLength==0 && textLength>0) return false;

    int cache[1<<8];
    std::fill(cache, cache+(1<<8), -1);
    for (int i=0; i<patternLength; ++i)
        cache[(unsigned char)(pattern[i])]=i;
 
    int shift = 0;
    while (shift<=(textLength-patternLength)) {
        int rhsIdx=patternLength-1;
        while (rhsIdx>=0 && pattern[rhsIdx]==text[shift+rhsIdx])
            --rhsIdx;
        if (rhsIdx<0)
            return true;
        int minShift=1;
        shift+=std::max(minShift, rhsIdx-cache[text[shift+rhsIdx]]);
    }
    return false;
}

/**
 * Expands pattern according to grammar.
 * @param original unparsed pattern
 * @param subsequent parsed pattern
 * @return Returns true if success, false in the event of invalid grammar
 */
const bool grammarParser(const unsigned char* pattern, std::vector<unsigned char> &parsedPattern) {
    
    size_t i=0;
    while (pattern[i]!='\0') {
        if (pattern[i]=='\\') {   //Case 1: escape character
            parsedPattern.push_back(pattern[++i]);
        } else if (pattern[i]==']') { //Case 2: closing square bracket
            if (parsedPattern.empty() || pattern[++i]!='{') return false;
            size_t numRepetitions=0;
            while (pattern[++i]!='}') {
                if (pattern[i]>='0' && pattern[i]<='9')  //checks s[i] in {0,...9}
                    numRepetitions=(numRepetitions*10)+(pattern[i]-'0'); //calculates number of repetitions
                else return false;
            }
            if (pattern[i]!='}') return false;
            std::vector<unsigned char> vt;
            bool success=false;
            while (!parsedPattern.empty()) {  //unroll stack to latest '['
                unsigned char ch=parsedPattern.back();
                parsedPattern.pop_back();
                if (ch=='[') {
                    success=true;
                    break;
                } else {
                    vt.push_back(ch);
                }
            }

            if (!success) return false;

            size_t currentIdx=parsedPattern.size();
            parsedPattern.resize(parsedPattern.size()+(numRepetitions*vt.size())); //resize for operator[] usage
            for (size_t k=0; k<numRepetitions; ++k)
                for (ptrdiff_t kk=vt.size()-1; kk>=0; --kk)
                    parsedPattern[currentIdx++]=vt[kk];

        }
        else {    //Case 3: normal characters including '['
            parsedPattern.push_back(pattern[i]);
        }
        ++i;   
    }
    
    std::cout<<"Expanded Pattern: ";
    for (size_t k=0; k<parsedPattern.size(); ++k)
        std::cout<<parsedPattern[k];
    std::cout<<std::endl;
    
    return true;
}

/**
 * Main calling function
 * @param text
 * @param pattern
 * @return pattern as stl string if found, ERROR if unvalid grammar syntax, empty string otherwise
 */
std::string PatternSearch(const unsigned char* pStr, const unsigned char* pMatch) {
    static const std::string ERROR="ERROR";
    std::vector<unsigned char> expandedPattern;
    expandedPattern.reserve(ustrlen(pMatch));
    if (!grammarParser(pMatch, expandedPattern)) return ERROR;
    return boyerMooreHorspool(pStr, expandedPattern)==true?toString(expandedPattern):"";
}
int main() {
    unsigned char Str[]="ÿaÿþcc";//"qÿ";//"abcdeabc abcffaÿaa";
    unsigned char Match[]="ÿaÿþcc";//"a[b[c[d]{2}e]{2}]{2}";//"abc[def[ghi]{3}jkl]{2}mno";//"abc";"abc[def]{3}ghi[j]{4}z";//"a[b]{2}c";//"abc[de[fg]{2}h]{2}";//"a[þ]{2}cc";//"qÿ";//"abc[def[gh[i]{3}]{20000}jkl]{2000}mno";//"a[b\\[]{2}";//"aÿ";//"abc[def[gh[i]{3}]{20000}jkl]{2000}mno";////"¢a¢bc";
    const unsigned char *pStr=Str;
    const unsigned char *pMatch=Match;
    std::cout<<PatternSearch(pStr, pMatch)<<std::endl;
    std::cout<<"Finished."<<std::endl;
    std::cin.get();
    return 0;
}
