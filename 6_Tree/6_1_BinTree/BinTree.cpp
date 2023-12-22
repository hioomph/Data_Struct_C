#include"BinTree.h"
#include"Queue.h"
#include"Stack.h"

//////////////////////////////////////////////////////////////
// 1 创建

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

//////////////////////////////////////////////////////////////
// 2 递归遍历

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

//////////////////////////////////////////////////////////////
// 3 方法实现

// 求结点个数
int Size(BinTree *bt)
{
    return Size(bt->root);
}
int Size(BinTreeNode *t)
{
    // 求解整个二叉树的节点个数=根节点的左子树节点个数+右子树节点个数
    // 而左子树又是由其根节点和其左右子树构成的，右节点同理
    // 因此，依然涉及到一个递归的概念
    if(t == NULL)
        return 0;
    else
        return Size(t->leftChild)+Size(t->rightChild)+1;
}

// 求深度
int Height(BinTree *bt)
{
    return Height(bt->root);
}
int Height(BinTreeNode *t)
{
    if(t == NULL)
        return 0;
    else
    {
        int height = Height(t->leftChild)>Height(t->rightChild)?Height(t->leftChild):Height(t->rightChild);
        return height+1;
    }
}

// 查找结点
BinTreeNode* Search(BinTree *bt, ElemType key)
{
    return Search(bt->root, key);
}
BinTreeNode* Search(BinTreeNode *t, ElemType key)
{
    if(t == NULL)
        return NULL;
    if(t->data == key)
        return t;
    
    BinTreeNode *p = Search(t->leftChild, key);
    if(p != NULL)  // 这一步很重要，一定是左子树内查不到，才遍历右子树
        return p;
    return Search(t->rightChild, key);
}

// 查找父节点
BinTreeNode* Parent(BinTree *bt, BinTreeNode *p)
{
    return Parent(bt->root, p);
}
BinTreeNode* Parent(BinTreeNode *t, BinTreeNode *p)
{
    if(t == NULL || p == NULL)  // 树为空或查找的节点为空
        return NULL;    
    if(t->leftChild == p || t->leftChild == p)
        return t;
    
    BinTreeNode *q = Parent(t->leftChild, p);
    if(q != NULL)
        return q;
    return Parent(t->rightChild, p);
}

// 求左子树
BinTreeNode* LeftChild(BinTreeNode *p)
{
    if(p != NULL)
        return p->leftChild;
    
    return NULL;
}

// 求右子树
BinTreeNode* RightChild(BinTreeNode *p)
{
    if(p != NULL)
        return p->rightChild;
    
    return NULL;
}

// 判空
bool BinTreeIsEmpty(BinTree *bt)
{
    return bt->root == NULL;
}

// 拷贝
void Copy(BinTree *bt1, BinTree *bt2)
{
    Copy(bt1->root, bt2->root);
}
void Copy(BinTreeNode *&t1, BinTreeNode *t2)
{
    // 1、拷贝根节点    2、拷贝左子树   3、拷贝右子树
    if(t2 == NULL)
        t1 = NULL;
    else
    {
        t1 = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t1 != NULL);
        t1->data = t2->data;

        Copy(t1->leftChild, t2->leftChild);
        Copy(t1->rightChild, t2->rightChild);
    }
}

// 清空
void BinTreeClear(BinTree *bt)
{
    BinTreeClear(bt->root);
}
void BinTreeClear(BinTreeNode *&t)
{
    // 1、清空左子树    2、清空右子树   3、释放根节点
    if(t != NULL)
    {
        BinTreeClear(t->leftChild);
        BinTreeClear(t->rightChild);
        free(t);
        t = NULL;
    }
}

//////////////////////////////////////////////////////////////
// 4 非递归遍历

// 前序非递归遍历
void PreOrder_1(BinTree *bt)
{
    PreOrder_1(bt->root);
}
void PreOrder_1(BinTreeNode *t)
{
    if(t != NULL)
    {
        SeqStack st;
        InitStack(&st);

        Push(&st, t);
        BinTreeNode *p;  // 节点p的地址
        while(!IsEmpty(&st))
        {
            GetTop(&st, &p);  // GetTop需要的参数为BinTreeNode* *p,也即是指向p的指针，所以传入p的地址即&p
            Pop(&st);
            printf("%c ", p->data);
            if(p->rightChild != NULL)
                Push(&st, p->rightChild);
            if(p->leftChild != NULL)
                Push(&st, p->leftChild);
        }
    }
}

// 中序遍历
void InOrder_1(BinTree *bt)
{
    InOrder_1(bt->root);
}
void InOrder_1(BinTreeNode *t)
{
    if(t != NULL)
    {
        SeqStack st;
        InitStack(&st);

        Push(&st, t);
        BinTreeNode *p;  // 节点p的地址
        while(!IsEmpty(&st))
        {
            while(t != NULL && t->leftChild != NULL)
            {
                Push(&st, t->leftChild);
                t = t->leftChild;
            }
            GetTop(&st, &p);
            Pop(&st);
            printf("%c ", p->data);

            if(p->rightChild != NULL)
            {
                Push(&st, p->rightChild);
                t = p->rightChild;
            }
        }
    }  
}

//////////////////////////////////////////////////////////////
// 5 恢复

// 前序+中序恢复二叉树
void CreateBinTree_5(BinTree *bt, char *VLR, char*LVR, int n)
{
    CreateBinTree_5(bt->root, VLR, LVR, n);
}
void CreateBinTree_5(BinTreeNode *&t, char *VLR, char*LVR, int n)
{
    if(n == 0)
        t = NULL;
    else
    {
        int k = 0;
        while(VLR[0] != LVR[k])
            k++;

        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = LVR[k];

        CreateBinTree_5(t->leftChild, VLR+1, LVR, k);
        CreateBinTree_5(t->rightChild, VLR+k+1, LVR+k+1, n-k-1);
    }
}

// 中序+后序恢复二叉树
void CreateBinTree_6(BinTree *bt, char *LVR, char*LRV, int n)
{
    CreateBinTree_6(bt->root, LVR, LRV, n);
}
void CreateBinTree_6(BinTreeNode *&t, char *LVR, char*LRV, int n)
{
    if(n == 0)
        t = NULL;
    else
    {
        int k = 0;
        while(LRV[n-1] != LVR[k])
            k++;
        
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = LVR[k];

        CreateBinTree_6(t->rightChild, LVR+k+1, LRV+k, n-k-1);
        CreateBinTree_6(t->leftChild, LVR, LRV, k);
    }
}