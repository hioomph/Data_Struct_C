#ifndef _SSTRING_H_
#define _SSTRING_H_

#include<stdio.h>
#include<string.h>

#define MAXSTRLEN 20
#define u_char unsigned char

typedef u_char SString[MAXSTRLEN+1];

void InitString(SString S);
void PrintString(SString S);

void StrAssign(SString S, char *str);
void StrCopy(SString T, SString S);
bool StrEmpty(SString S);
int StrCompare(SString S, SString T);
int StrLength(SString S);
void StrConcat(SString T, SString s1, SString s2);
void SubString(SString S, SString sub, int pos, int len);
void StrInsert(SString S, int pos, SString T);
void StrDelete(SString S, int pos, int len);
void Clear(SString S);

/////////////////////// 模式匹配 ///////////////////////
int StrIndex(SString S, SString T, int pos);
void StrReplace(SString S, SString T, SString V);

#endif // _SSTRING_H_