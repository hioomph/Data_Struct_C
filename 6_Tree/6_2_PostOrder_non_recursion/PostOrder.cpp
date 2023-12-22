#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include"Stack.h"

#define ElemType char

typedef struct BinTreeNode  // 二叉树结点
{
    ElemType data;                  // 数据
    struct BinTreeNode *leftChild;  // 左孩子
    struct BinTreeNode *rightChild; // 右孩子
}BinTreeNode;

typedef struct BinTree
{
    BinTreeNode *root;      // 根节点
    ElemType     refvalue;  // stop flag
}BinTree;

void InitBinTree(BinTree *bt, ElemType ref);
void CreateBinTree_4(BinTree *bt, char *str);
void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str);
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);
void PostOrder_1(BinTree *bt);
void PostOrder_1(BinTreeNode *t);

///////////////////////////////////////////////////////////////////////////

// 初始化二叉树
void InitBinTree(BinTree *bt, ElemType ref)
{
    bt->root = NULL;
    bt->refvalue = ref;
}

void CreateBinTree_4(BinTree *bt, char *str)
{
    CreateBinTree_4(bt, bt->root, str);
}
void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str)
{
    if(*str == bt->refvalue)
        t = NULL;
    else
    {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = *str;
        CreateBinTree_4(bt, t->leftChild, ++str);
        CreateBinTree_4(bt, t->rightChild, ++str);
    }
}

// 后序遍历（递归）
void PostOrder(BinTree *bt)
{
    PostOrder(bt->root);
}
void PostOrder(BinTreeNode *t)
{
    if(t != NULL)
    {
        PostOrder(t->leftChild);
        PostOrder(t->rightChild);
        printf("%c ", t->data);
    }
}

// 后序遍历（非递归）
void PostOrder_1(BinTree *bt)
{
    PostOrder_1(bt->root);
}
void PostOrder_1(BinTreeNode *t)
{
    if(t != NULL)
    {
        SeqStack st;
        InitStack(&st);
        BinTreeNode *p;
        StkNode sn;
        do
        {
            while(t != NULL)
            {
                sn.ptr = t;
                sn.tag = L;
                Push(&st, sn);
                t = t->leftChild;
            }
            bool flag = true; // continue visit
            while(flag && !IsEmpty(&st))
            {
                GetTop(&st, &sn);
                Pop(&st);
                p = sn.ptr;
                switch(sn.tag)
                {
                case R:
                    printf("%c ", p->data);
                    break;
                case L:
                    sn.tag = R;
                    Push(&st, sn);
                    flag = false;
                    t = p->rightChild;
                    break;
                }
            }
        }while(!IsEmpty(&st));
    }
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    ElemType *s = (char *)"ABC##DE##F##G#H##";
    BinTree mytree;
    InitBinTree(&mytree, '#');

    CreateBinTree_4(&mytree, s);
    
    printf("后序遍历：");
    // 递归
    // PostOrder(&mytree);

    // 非递归
    PostOrder_1(&mytree);
    printf("\n");
}