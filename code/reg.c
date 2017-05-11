/*************************************************************************
	> File Name: reg.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 19:39:18 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

bool isMatch(char*, char*);
bool matchstar(char c, char* s, char* p)
{
    do{
        if(isMatch(s, p)) return true;
    }while(*s != '\0' && (*s++ == c || c == '.'));
    return false;
}
bool isMatch(char* s, char* p)
{
    if(*p == '\0' && *s != '\0')
        return false;
    if(*s == '\0' && *p == '\0')
        return true;
    if(p[1] == '*')
        return matchstar(p[0], s, p+2);
    if(p[0] == s[0] || (p[0] == '.' && s[0] != '\0'))
        return isMatch(s+1, p+1);
    return false;
}
int main()
{
    printf("isMatch(\"aa\",\"a\"):%d\n",isMatch("aa","a"));
    printf("isMatch(\"aa\",\"aa\"):%d\n",isMatch("aa","aa"));
    printf("isMatch(\"aaa\",\"aa\"):%d\n",isMatch("aaa","aa"));
    printf("isMatch(\"aa\",\"a*\"):%d\n",isMatch("aa","a*"));
    printf("isMatch(\"aa\",\".*\"):%d\n",isMatch("aa",".*"));
    printf("isMatch(\"ab\",\".*\"):%d\n",isMatch("ab",".*"));
    printf("isMatch(\"aab\",\"c*a*b\"):%d\n",isMatch("aab","c*a*b"));
    printf("isMatch(\"a\",\".*..a*\"):%d\n",isMatch("a",".*..a*"));
    printf("isMatch(\"\",\"..*\"):%d\n",isMatch("","..*"));
    return 0;
}
