#include"BST.h"

int main(int argc, char const *argv[])
{
    T ar[] = {45, 12, 53, 3, 37, 100, 24, 61, 90, 78};
    int n = sizeof(ar)/sizeof(int);
    BST bst;
    InitBSTree(&bst);

    for(int i=0; i<n; ++i)
    {
        InsertBSTree(&bst, ar[i]);
    }

    T min = Min(&bst);
    printf("min = %d\n", min);

    T max = Max(&bst);
    printf("max = %d\n", max);

    Sort(&bst);
    printf("\n");

    int key = 24;
    BSTNode *p = Search(&bst, key);
    if(p != NULL)
        printf("search of %d is succeed!\n", key);
    else
        printf("search of %d is false!\n", key);

    BOOL flag = RemoveBSTree(&bst, key);
    if(flag)
        Sort(&bst);

    MakeEmptyBSTree(&bst);
    printf("\n");

    return 0;
}
