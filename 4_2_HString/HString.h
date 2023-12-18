#ifndef _HSTRING_H_
#define _HSTRING_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

typedef struct HString
{
    char *ch;
    int   length;
}HString;

void InitString(HString *S);
void PrintString(HString *S);

void StrAssign(HString *S, char *str);
void StrCopy(HString *T, HString *S);
bool StrEmpty(HString *S);
int StrCompare(HString *S, HString *T);
int StrLength(HString *S);
void StrConcat(HString *T, HString *s1, HString *s2);
void SubString(HString *S, HString *sub, int pos, int len);
void StrInsert(HString *S, int pos, HString *T);
void StrDelete(HString *S, int pos, int len);
void Clear(HString *S);

/////////////////////// 模式匹配 ///////////////////////
void StrIndex(HString *S, HString *T, int pos);
void StrReplace(HString *S, HString *T, HString *V);


#endif // _HSTRING_H_