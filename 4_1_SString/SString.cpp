#include"SString.h"

// 初始化：定义一个空串
void InitString(SString S)
{
    S[0] = '\0';
}

// 打印字符串
void PrintString(SString S)
{
    printf("%s\n", S);
}

// 字符串赋值
void StrAssign(SString S, char *str)
{
    int len = strlen(str);
    for(int i=0; i<len; ++i)
    {
        S[i] = str[i];
    }

    S[len] = '\0';
}

// 字符串拷贝
void StrCopy(SString T, SString S)
{
    int len = StrLength(S);
    for(int i=0; i<len; ++i)
    {
        T[i] = S[i];
    }

    T[len] = '\0';
}

// 字符串判空
bool StrEmpty(SString S)
{
    return S[0] == '\0';
}

// 字符串比较
int StrCompare(SString S, SString T)
{
    // S>T -- 1
    // S<T -- -1
    // S=T -- 0
    int result = 0;
    while(*S != '\0' && *T != '\0')
    {
        result = *S - *T;
        if(result != 0)
            break;
        S++;
        T++;
    }

    if(result > 0)
        result = 1;
    else if(result < 0)
        result = -1;

    return result;   
}

// 字符串长度
int StrLength(SString S)
{
    int len = 0;
    while(*S != '\0')
    {
        len++;
        S++;
    }

    return len;
}

// 字符串拼接
void StrConcat(SString T, SString s1, SString s2)
{
    int len1 = StrLength(s1);
    int len2 = StrLength(s2);

    if(len1+len2 <= MAXSTRLEN)
    {
        for(int i=0; i<len1; ++i)
            T[i] = s1[i];
        for(int j=0; j<len2; ++j)
            T[j+len1] = s2[j];
        
        T[len1+len2] = '\0';
    }
    else if(len1 < MAXSTRLEN)
    {
        for(int i=0; i<len1; ++i)
            T[i] = s1[i];
        for(int j=0; j<MAXSTRLEN-len1; ++j)
            T[j+len1] = s2[j];
        
        T[MAXSTRLEN] = '\0';
    }
    else
    {
        for(int i=0; i<MAXSTRLEN; ++i)
            T[i] = s1[i];

        T[MAXSTRLEN] = '\0';
    }
}

// 求子串
void SubString(SString S, SString sub, int pos, int len)
{
    int s_len = StrLength(S);
    if(pos < 0 || pos >= s_len || len <= 0 || len > s_len)
        return;
    
    int j = pos;
    for(int i=0; i<len; ++i)
    {
        sub[i] = S[j+i];
    }
    sub[len] = '\0';
}

// 插入子串
void StrInsert(SString S, int pos, SString T)
{
    int s_len = StrLength(S);
    int t_len = StrLength(T);

    if(s_len+t_len > MAXSTRLEN)
        t_len = MAXSTRLEN - s_len;

    for(int i=s_len-1; i>=pos; --i)
        S[i+t_len] = S[i];
        
    for(int j=0; j<t_len; ++j)
        S[pos+j] = T[j];

    S[s_len+t_len] = '\0';
}

// 删除元素
void StrDelete(SString S, int pos, int len)
{
    int s_len = StrLength(S);
    for(int i=pos; i<s_len; ++i)
    {
        S[i] = S[i+len];
    }
    S[s_len-len] = '\0';
}

// 清空字符串
void Clear(SString S)
{
    S[0] = '\0';
}

// 模式匹配
int StrIndex(SString S, SString T, int pos)
{
    int i = pos;
    int j = 0;
    while(S[i]!='\0' && T[j] != '\0')
    {
        if(S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+1;
            j = 0;
        }       
    }

    if(T[j] == '\0')
        return i-j;
    
    return -1;
}

void StrReplace(SString S, SString T, SString V)
{
    int s_len = StrLength(S);
    int t_len = StrLength(T);
    int v_len = StrLength(V);

    int index = -1;
    int pos = 0;

    while(pos < s_len)
    {
        index = StrIndex(S, T, pos);
        if(index == -1)
            return;
        StrDelete(S, index, t_len);
        StrInsert(S, index, V);      

        pos = index + v_len;  
    }
}