#include"SeqStack.h"

// 数制转换
// void Convert_8(int value)
// {
//     SeqStack st;
//     InitStack(&st);
//     int v;

//     while(value)
//     {
//         Push(&st, value%8);
//         value /= 8;
//     }

//     // Show(&st);
//     while (!(IsEmpty(&st)))
//     {
//         GetTop(&st, &v);
//         Pop(&st);
//         printf("%d", v);
//     }
//     printf("\n");
// }

// 括号匹配
bool Check(char *str)
{
    SeqStack st;
    InitStack(&st);
    char v;

    while(*str != '\0')
    {
        if(*str == '[' || *str == '{' || *str == '(')
            Push(&st, *str);
        else if(*str == ']')
        {
            GetTop(&st, &v);
            if(v != '[')
                return false;
            Pop(&st);
        }
        else if(*str == ')')
        {
            GetTop(&st, &v);
            if(v != '(')
                return false;
            Pop(&st);
        }
        else if(*str == '}')
        {
            GetTop(&st, &v);
            if(v != '{')
                return false;
            Pop(&st);
        } 
        *str++;
    }

    return IsEmpty(&st);
}


int main()
{
    // 1.数制转换 ElemType int
    // int value = 47183;
    // Convert_8(value);

    // 2.括号匹配 ElemType char
    // char *str = "[([][])]"; // char *str    str是一个指向字符数组的指针
    // bool flag = Check(str);
    // if(flag)
    //     printf("Ok!\n");
    // else
    //     printf("Error!\n");

    // 3.行编辑程序
    SeqStack st;
    InitStack(&st);

    char ch = getchar();
    while(ch != '$')
    {
        while(ch !='$' && ch != '\n')
        {
            switch(ch)
            {
                case '#':
                    Pop(&st);
                    break;
                case '@':
                    Clear(&st);
                    break;
                default:
                    Push(&st, ch);
                    break;
            }

            ch = getchar();
        }
        Print(&st);
        ch = getchar();
    }
    Destroy(&st);
}