#include"HString.h"

int main()
{
    HString S;
    HString T;
    InitString(&S); // 传入结构体变量的地址
    InitString(&T); // 传入结构体变量的地址

    // 赋值
    StrAssign(&S, "abc");
    PrintString(&S);

    // 拷贝
    // StrCopy(&T, &S);
    // PrintString(&T);

    // 判空
    if(StrEmpty(&S) == 1)
        printf("串为空！\n");
    else
        printf("串不为空！\n");

    // 比较大小
    // StrAssign(&T, "xyz");
    // int res = StrCompare(&S, &T);
    // printf("res=%d\n", res);

    // 链接字符串
    StrAssign(&T, "def");

    HString Y;
    InitString(&Y);
    StrConcat(&Y, &S, &T);
    PrintString(&Y);

    // 求子串
    HString sub;
    InitString(&sub);
    SubString(&Y, &sub, 2, 3);
    PrintString(&sub);

    // 插入
    StrInsert(&S, 2, &sub);
    PrintString(&S);  // abcdec

    // 删除
    StrDelete(&S, 2, 3);
    PrintString(&S);

    // 清空
    Clear(&S);
    PrintString(&S);


    printf("ok.\n");
}