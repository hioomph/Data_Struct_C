#include"AVLTree.h"

int main()
{
    Type ar[] = {50, 40, 60, 10, 45, 70, 5, 30, 48};
    int n = sizeof(ar)/sizeof(Type);

    AVLTree avl;
    initAVLTree(&avl);

    for(int i=0; i<n; ++i)
    {
        InsertAVLTree(&avl, ar[i]);
    }
    PreOrder(&avl);
    printf("\n");

    Type key = 48;
    RemoveAVL(&avl, key);

    PreOrder(&avl);
    printf("\n");
} 