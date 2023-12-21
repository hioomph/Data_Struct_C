#include"BinTree.h"
#include"Queue.h"

// 初始化二叉树
void InitBinTree(BinTree *bt, ElemType ref)
{
    bt->root = NULL;
    bt->refvalue = ref;
}

// 前序遍历创建二叉树
void CreateBinTree_1(BinTree *bt)
{
    CreateBinTree_1(bt, &(bt->root));
}
void CreateBinTree_1(BinTree *bt, BinTreeNode **t)
{
    ElemType Item;
    scanf("%c", &Item);
    if(Item == bt->refvalue)
        (*t) = NULL;
    else
    {
        (*t) = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert((*t) != NULL);
        (*t)->data = Item;
        // 递归调用
        CreateBinTree_1(bt, &((*t)->leftChild));
        CreateBinTree_1(bt, &((*t)->rightChild));
    }
}

void CreateBinTree_2(BinTree *bt)
{
    CreateBinTree_2(bt, bt->root);
}
void CreateBinTree_2(BinTree *bt, BinTreeNode *&t)
{
    ElemType Item;
    scanf("%c", &Item);
    if(Item == bt->refvalue)
        t = NULL;
    else
    {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = Item;
        // 递归调用
        CreateBinTree_1(bt, &(t->leftChild));
        CreateBinTree_1(bt, &(t->rightChild));
    }    
}

void CreateBinTree_3(BinTree *bt)
{
    bt->root = CreateBinTree_3_(bt);
}
BinTreeNode* CreateBinTree_3_(BinTree *bt)
{
    ElemType Item;
    scanf("%c", &Item);
    if(Item == bt->refvalue)
        return NULL;
    else
    {
        BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = Item;
        t->leftChild = CreateBinTree_3_(bt);
        t->rightChild = CreateBinTree_3_(bt);
        return t;
    }
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

// 前序遍历
void PreOrder(BinTree *bt)
{
    PreOrder(bt->root);
}
void PreOrder(BinTreeNode *t)
{
    if(t != NULL)
    {
        printf("%c ", t->data);
        PreOrder(t->leftChild);
        PreOrder(t->rightChild);
    }
}

// 中序遍历
void InOrder(BinTree *bt)
{
    InOrder(bt->root);
}
void InOrder(BinTreeNode *t)
{
    if(t != NULL)
    {
        InOrder(t->leftChild);  
        // 当t->leftChild为空时，退出对自己的循环调用，由于函数为void，直接返回空，然后执行下一步
        printf("%c ", t->data);
        InOrder(t->rightChild);
    }
}

// 后序遍历
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

// 层次遍历
void LevelOrder(BinTree *bt)
{
    LevelOrder(bt->root);
}
void LevelOrder(BinTreeNode *t)
{
    if(t != NULL)
    {
        LinkQueue Q;
        InitQueue(&Q);
        BinTreeNode *v;

        // 入队t
        EnQueue(&Q, t);

        while(!QueueIsEmpty(&Q))
        {
            // 出队队头元素
            GetHead(&Q, &v);
            DeQueue(&Q); 
            printf("%c ", v->data);

            // 入队v->leftChild & rightChild
            if(v->leftChild != NULL)
                EnQueue(&Q, v->leftChild);
            if(v->rightChild != NULL)
                EnQueue(&Q, v->rightChild);

            // 更新v
            GetHead(&Q, &v);
        }


    }
}