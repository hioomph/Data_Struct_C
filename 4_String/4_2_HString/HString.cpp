#include"HString.h"

// 初始化
void InitString(HString *S)
{
    // 此处仅仅初始化。并没有开辟空间
    S->ch = NULL;
    S->length = 0;
}

// 打印字符串
void PrintString(HString *S)
{
    for(int i=0; i<S->length; ++i)
    {
        printf("%c", S->ch[i]);
    }
    printf("\n");
}

// 字符串赋值
void StrAssign(HString *S, char *str)
{
    int len = strlen(str);
    // 开辟空间
    if(S->ch != NULL)  // 若S不为空，先释放原空间
      free(S->ch);
    S->ch = (char*)malloc(sizeof(char)*len);
    assert(S->ch != NULL);

    for(int i=0; i<len; ++i)
        S->ch[i] = str[i];
    S->length = len;
}

// 字符串拷贝
void StrCopy(HString *T, HString *S)
{
    int len = StrLength(S);
    if(T->ch != NULL)
        free(T->ch);
    T->ch = (char*)malloc(sizeof(char)*len);
    assert(T->ch != NULL);

    for(int i=0; i<len; ++i)
    {
        T->ch[i] = S->ch[i];
    }
    T->length = len;
}

// 字符串判空
bool StrEmpty(HString *S)
{
    return S->length == 0;
}

// 字符串比较
int StrCompare(HString *S, HString *T)
{
    if(S->length == 0 && T->length)
        return 0;
    
    int result = 0;
    
    int i = 0;
    int j = 0;
    while(i < S->length && j < T->length)
    {
        if(S->ch[i] > T->ch[j])
            return 1;
        else if(S->ch[i] < T->ch[j])
            return -1;
        else
        {
            i++;
            j++;
        }
    }

    if(i < S->length)
        result = 1;
    if(j < T->length)
        result = -1;
    
    return result;

}

// 字符串长度
int StrLength(HString *S)
{
    return S->length;
}

// 字符串拼接
void StrConcat(HString *T, HString *s1, HString *s2)
{
    if(T->ch != NULL)
        free(T->ch);
    
    int len1 = StrLength(s1);
    int len2 = StrLength(s2);
    T->ch = (char*)malloc(sizeof(char) * (len1+len2));
    assert(T->ch != NULL);

    for(int i=0; i<len1; ++i)
    {
        T->ch[i] = s1->ch[i];
    }
    for(int j=0; j<len2; ++j)
    {
        T->ch[j+len1] = s2->ch[j];
    }

    T->length = len1+len2;
}

// 求子串
void SubString(HString *S, HString *sub, int pos, int len)
{
    if(pos<0 || pos>S->length || len<0 || len>S->length-pos)
        return;

    if(sub->ch != NULL)
        free(sub->ch);
    sub->ch = (char*)malloc(sizeof(char) * len);
    assert(sub->ch);

    int j = pos;
    for(int i=0; i<len; ++i)
    {
        sub->ch[i] = S->ch[j+i];
    }

    sub->length = len;
}

// 插入子串
void StrInsert(HString *S, int pos, HString *T)
{
    if(pos<0 || pos>S->length)
        return;
    
    if(T->length == 0)
        return;
    
    char *ch = (char*)realloc(S->ch, sizeof(char*) * (S->length + T->length));
    assert(ch != NULL);
    S->ch = ch;

    for(int i=S->length-1; i>=pos; --i)
    {
        S->ch[i+T->length] = S->ch[i];
    }

    for(int j=0; j<T->length; ++j)
    {
        S->ch[pos+j] = T->ch[j];
    }

    S->length += T->length;
}

// 删除元素
void StrDelete(HString *S, int pos, int len)
{
    if(pos<0 || pos>S->length)
        return;
    
    if(len <= 0 || len>S->length)
        return;

    int j = pos;
    for(int i=0; i<len; ++i)
    {
        S->ch[i+j] = S->ch[i+j+len];
    }

    S->length -= len;
}

// 清空字符串
void Clear(HString *S)
{
    S->length = 0;
    if(S->ch != NULL)
        free(S->ch);
    
    S->ch = NULL;
}
