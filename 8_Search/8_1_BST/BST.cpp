#include"BST.h"

// 初始化
void InitBSTree(BST *bst)
{
    bst->root = NULL;
}

// 插入数据
BOOL InsertBSTree(BST *bst, T x)
{
    return InsertBSTree(&bst->root, x);
}
BOOL InsertBSTree(BSTNode **t, T x)
{    
    // 1、若根节点为空，先创建根节点
    if(*t == NULL)
    {
        *t = (BSTNode*)malloc(sizeof(BSTNode));
        assert(*t != NULL);
        (*t)->data = x;
        (*t)->leftChild = NULL;
        (*t)->rightChild = NULL;
        return TRUE;
    }
    // 2、判断数据大小，若要插入的数据小则往左子树插入；否则往右子树插入
    else if(x < (*t)->data)
    {
        InsertBSTree(&(*t)->leftChild, x);
    }
    else if(x > (*t)->data)
    {
        InsertBSTree(&(*t)->rightChild, x);
    }

    // 3、若存在相等的情况，则无法构成二叉排序树
    return FALSE;
}

// 求最小值
T Min(BST *bst)
{
    assert(bst->root != NULL);
    return Min(bst->root);
}
T Min(BSTNode *t)
{
    while(t->leftChild != NULL)
        t = t->leftChild;
    
    return t->data;
}

// 求最大值
T Max(BST *bst)
{
    assert(bst->root != NULL);
    return Max(bst->root);
}
T Max(BSTNode *t)
{
    while(t->rightChild != NULL)
        t = t->rightChild;
    
    return t->data;
}

// 中序遍历
void Sort(BST *bst)
{
    return Sort(bst->root);
}
void Sort(BSTNode *t)
{
    if(t != NULL)
    {
        Sort(t->leftChild);
        printf("%d ", t->data);
        Sort(t->rightChild);
    }
}

// 获取BSTree的数据
void Get(BST *bst, int array[], int* index)
{
    return Get(bst->root, array, index);
}
void Get(BSTNode *t, int array[], int* index)
{
    if (t != NULL) 
    {
        Get(t->leftChild, array, index);
        array[(*index)++] = t->data;
        Get(t->rightChild, array, index);
    }
}

// 搜索
BSTNode* Search(BST *bst, T key)
{
    return Search(bst->root, key);
}
BSTNode* Search(BSTNode *t, T key)
{
    if(t == NULL)
        return NULL;
    
    if(t->data == key)
        return t;
    else if(t->data > key)
        Search(t->leftChild, key);
    else
        Search(t->rightChild, key);
}

// 删除节点
BOOL RemoveBSTree(BST *bst, T key)
{
    assert(bst->root != NULL);
    return RemoveBSTree(&(bst->root), key);
}
BOOL RemoveBSTree(BSTNode **t, T key)
{
    T *arr = (T*)malloc(sizeof(T) * MAX_SIZE); 
    assert(arr != NULL);
    int index = 0;
    Get(*t, arr, &index);

    int len = index;

    BSTNode *p = Search(*t, key);    
    if(p == NULL)
        return FALSE;
    else
    {
        for(int i=0; i<len; ++i)
        {
            if(arr[i] == p->data)
            {   
                for(int j=i; j<len-1; ++j) 
                {
                    arr[j] = arr[j+1];
                }
                break;
            }
        }

        MakeEmptyBSTree(t);
        for(int i=0; i<len-1; ++i)
        {
            InsertBSTree(t, arr[i]);
        }
    }

    return TRUE;
}

// 清空
void MakeEmptyBSTree(BST *bst)
{
    return MakeEmptyBSTree(&(bst->root));
}
void MakeEmptyBSTree(BSTNode **t)
{
    if((*t) != NULL)
    {
        MakeEmptyBSTree(&(*t)->leftChild);
        MakeEmptyBSTree(&(*t)->rightChild);
        free(*t);
        *t = NULL;
    }
}
