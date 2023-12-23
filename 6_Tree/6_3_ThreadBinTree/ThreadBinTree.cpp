#include"ThreadBinTree.h"

//////////////////////////////////////////////////////////////////////////////////////
// 1

// 申请结点
BinTreeNode* _buyNode(ElemType x)
{
    BinTreeNode *s = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    assert(s != NULL);
    s->data = x;
    s->leftChild = s->rightChild = NULL;
    s->ltag = s->rtag = LINK;

    return s;
}

// 初始化
void InitBinTree(BinTree *bt, ElemType ref)
{
    bt->root = NULL;
    bt->refvalue = ref;
}

// 创建二叉树
void CreateBinTree(BinTree *bt, char *str)
{
    CreateBinTree(bt, bt->root, str);
}
void CreateBinTree(BinTree *bt, BinTreeNode *&t, char *&str)
{
    if(*str == bt->refvalue)
        t = NULL;
    else
    {
        t = _buyNode(*str);
        CreateBinTree(bt, t->leftChild, ++str);
        CreateBinTree(bt, t->rightChild, ++str);
    }
}

// 中序线索化
void CreateInThread(BinTree *bt)
{
    BinTreeNode *pre = NULL;
    CreateInThread(bt->root, pre);
    pre->rightChild = NULL;
    pre->rtag = THREAD;
}
void CreateInThread(BinTreeNode *&t, BinTreeNode *&pre)
{
    if(t == NULL)
        return;
    
    CreateInThread(t->leftChild, pre);  // 循环遍历到root的左子树的最左边的结点
    // 由于t->leftChild==NULL时会return，因此执行到下一步if时，t已经指向最左边的那个结点
    if(t->leftChild == NULL)  // t为叶子结点，对其进行前驱化
    {
        t->ltag = THREAD;
        t->leftChild = pre;
    }
    if(pre != NULL && pre->rightChild == NULL)  // 此时需要对前驱结点进行后继化
    {
        pre->rtag = THREAD;
        pre->rightChild = t;
    }
    pre = t;
    CreateInThread(t->rightChild, pre);
}

//////////////////////////////////////////////////////////////////////////////////////
// 2

// 求解整棵树的第一个结点
BinTreeNode* First(BinTree *bt)
{
    return First(bt->root);
}
BinTreeNode* First(BinTreeNode *t)
{
    if(t == NULL)
        return NULL;
    BinTreeNode *p = t;
    while(p->ltag == LINK)
        p = p->leftChild;
    
    return p;
}

// 求解整棵树的最后一个结点
BinTreeNode* Last(BinTree *bt)
{
    return Last(bt->root);
}
BinTreeNode* Last(BinTreeNode *t)
{
    if(t == NULL)
        return NULL;
    BinTreeNode *p = t;
    while(p->rtag == LINK)
        p = p->rightChild;
    
    return p;
}

// 查找后继结点
BinTreeNode* Next(BinTree *bt, BinTreeNode *cur)
{
    return Next(bt->root, cur);
}
BinTreeNode* Next(BinTreeNode *t, BinTreeNode *cur)
{
    if(t == NULL || cur == NULL)
        return NULL;
    
    if(cur->rtag == THREAD)
        return cur->rightChild;
    
    // 若cur->rtag==LINK，则此时将cur作为子树的root来看待，那么其后继结点是访问cur之后紧接着要访问的第一个结点
    // 也即是其子树的右子树的第一个结点
    return First(cur->rightChild);
}

// 查找前驱结点
BinTreeNode* Prev(BinTree *bt, BinTreeNode *cur)
{
    return Prev(bt->root, cur);
}
BinTreeNode* Prev(BinTreeNode *t, BinTreeNode *cur)
{
    if(t == NULL || cur == NULL)
        return NULL;
    
    if(cur->ltag == THREAD)
        return cur->leftChild;
    
    // 若cur->ltag==LINK，则此时将cur作为子树的root来看待，那么其后继结点是访问cur前紧接着要访问的最后一个结点
    // 也即是其子树的左子树的最后一个结点
    return Last(cur->leftChild);
}

// 中序遍历
void InOrder(BinTree *bt)
{
    InOrder(bt->root);
}
void InOrder(BinTreeNode *t)
{
    BinTreeNode *p;
    for(p=First(t); p!=NULL; p=Next(t, p))
    {
        printf("%c ", p->data);
    }

    printf("\n");
}

// 查找当前结点
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

    BinTreeNode *p;
    for(p=First(t); p!=NULL; p=Next(t, p))
    {
        if(p->data == key)
            return p;
    }

    return NULL;
}

// 查找父结点
BinTreeNode* Parent(BinTree *bt, BinTreeNode *cur)
{
    return Parent(bt->root, cur);
}
BinTreeNode* Parent(BinTreeNode *t, BinTreeNode *cur)
{
    if(t == NULL || cur == NULL)
        return NULL;
    if(t == cur)  // 当前结点为根结点，不存在父结点
        return NULL;
        
    BinTreeNode *p;
    if(cur->ltag == THREAD)
    {
        p = cur->leftChild;
        if(p->rightChild == cur)
            return p;
    }
    if(cur->rtag == THREAD)
    {
        p = cur->rightChild;
        if(p->leftChild == cur)
            return p;
    }

    p = First(cur->leftChild);  // 顺着cur的左子树找到最左边的第一个结点（为叶子结点）
    p = p->leftChild;  // 将第一个结点的前驱赋值给p
    if(p != NULL && p->rightChild == cur)
        return p;
    
    p = Last(cur->rightChild);  // 上面的查找失败，则顺着cur的右子树找到右边的最后一个结点p
    return p->rightChild;   // 此时p的后继即为父结点
}