#include"SString.h"

int main()
{
    // 赋值
    // SString S;
    // InitString(S);
    // SString T;
    // InitString(T);

    // char *str = "abcdef";
    // StrAssign(S, str);
    // PrintString(S);

    // // 复制
    // SString T;
    // InitString(T);
    // StrCopy(T, S);
    // PrintString(T);

    // // 比较
    // SString S;
    // InitString(S);
    // SString T;
    // InitString(T);
    // StrAssign(S, "abc");
    // StrAssign(T, "xyz");
    // int res = StrCompare(S, T);
    // printf("res=%d", res);

    // // 拼接
    // SString S;
    // InitString(S);
    // SString T;
    // InitString(T);
    // StrAssign(S, "abc");
    // StrAssign(T, "xyz");

    // SString Y;
    // InitString(Y);
    // StrConcat(Y, S, T);
    // PrintString(Y);

    // // 求子串
    // SString S;
    // InitString(S);
    // StrAssign(S, "abc");

    // SString sub;
    // InitString(sub);

    // SubString(S, sub, 2, 4);
    // PrintString(sub);

    // // 插入
    // SString S;
    // InitString(S);
    // SString T;
    // InitString(T);

    // StrAssign(S, "abc");
    // StrAssign(T, "xyz");
    // StrInsert(S, 1, T);
    // PrintString(S);

    // // 删除
    // SString S;
    // InitString(S);
    // StrAssign(S, "abcdefg");
    // StrDelete(S, 2, 3);
    // PrintString(S);
    
    // // 清空
    // Clear(S);
    // PrintString(S);

    // 模式匹配
    SString S;
    InitString(S);
    StrAssign(S, "ababcababcab");

    SString T;
    InitString(T);
    StrAssign(T, "abc");

    int index = StrIndex(S, T, 0);
    printf("index=%d\n", index);

    SString V;
    InitString(V);
    StrAssign(V, "xy");
    StrReplace(S, T, V);
    printf("替换后的串S为：");
    PrintString(S);


    printf("ok");
}

