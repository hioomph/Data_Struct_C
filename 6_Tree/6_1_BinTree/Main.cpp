#include"BinTree.h"

// ABC##DE##F##G#H##
 
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
    PreOrder(&mytree);
    printf("\n");

    printf("中序遍历：");
    InOrder(&mytree);
    printf("\n");

    printf("后序遍历：");
    PostOrder(&mytree);
    printf("\n");

    printf("层序遍历：");
    LevelOrder(&mytree);
    printf("\n");

    printf("ok");
}