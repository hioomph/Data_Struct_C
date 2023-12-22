#include"BinTree.h"

// ABC##DE##F##G#H##

// （前序）VLR = "ABCDEFGH"
// （中序）LVR = "CBEDFAGH"
// （后序）LRV = "CEFDBHGA"

int main()
{
    char *VLR = (char *)"ABCDEFGH";
    char *LVR = (char *)"CBEDFAGH";
    char *LRV = (char *)"CEFDBHGA";

    int n = strlen(VLR);

    BinTree mytree;
    InitBinTree(&mytree, '#');

    CreateBinTree_5(&mytree, VLR, LVR, n);
    printf("前序遍历mytree：");
    PreOrder(&mytree);
    printf("\n");

    BinTree utree;
    InitBinTree(&utree, '#');

    CreateBinTree_6(&utree, LVR, LRV, n);
    printf("前序遍历utree：");
    PreOrder(&utree);
    printf("\n");
}
 
/*
int main()
{
    ElemType *s = (char *)"ABC##DE##F##G#H##";
    BinTree mytree;
    InitBinTree(&mytree, '#');


    // CreateBinTree_1(&mytree);
    // CreateBinTree_2(&mytree);
    // CreateBinTree_3(&mytree);
    CreateBinTree_4(&mytree, s);

    printf("前序遍历：");
    // PreOrder(&mytree);
    PreOrder_1(&mytree);
    printf("\n");

    printf("中序遍历：");
    // InOrder(&mytree);
    InOrder_1(&mytree);
    printf("\n");

    printf("后序遍历：");
    PostOrder(&mytree);
    printf("\n");

    printf("层序遍历：");
    LevelOrder(&mytree);
    printf("\n");

    printf("Size = %d\n", Size(&mytree));
    printf("Height = %d\n", Height(&mytree));

    char n = 'B'; 
    BinTreeNode *p = Search(&mytree, n);
    if(p != 0)
    {
        printf("%c存在\n", n);
        BinTreeNode *parent = Parent(&mytree, p);
        if(parent != 0)
            printf("%c的parent存在，为%c\n", p->data, parent->data);
        else
            printf("parent不存在\n");
    }
    else
        printf("%c不存在\n", n);
    
    BinTree utree;
    InitBinTree(&utree, '#');
    Copy(&utree, &mytree);

    printf("前序遍历utree：");
    PreOrder(&utree);
    printf("\n");

    BinTreeClear(&utree);
    printf("清空utree：");
    PreOrder(&utree);
    printf("\n");


    printf("ok");
}
*/