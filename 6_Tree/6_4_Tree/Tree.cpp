#include"Tree.h"

// 初始化树
void InitTree(Tree *tree, ElemType ref)
{
    tree->root = NULL;
    tree->refvalue = ref;
}

// 创建树
void CreateTree(Tree *tree, char *str)
{
    CreateTree(tree, tree->root, str);
}
void CreateTree(Tree *tree, TreeNode *&t, char *&str)
{
    if(*str == tree->refvalue)
        t = NULL;
    else
    {
        t = (TreeNode*)malloc(sizeof(TreeNode));
        assert(t != NULL);
        t->data = *str;
        CreateTree(tree, t->firstChild, ++str);
        CreateTree(tree, t->nextSilbing, ++str);
    }
}

// 求根结点
TreeNode* Root(Tree *tree)
{
    return tree->root;
}

// 求第一个孩子结点（根据传递的根结点不同，得到不同的结果）
TreeNode* FirstChild(Tree *tree)
{
    return FirstChild(tree->root);
}
TreeNode* FirstChild(TreeNode *t)
{
    if(t == NULL)
        return NULL;
    return t->firstChild;
}

// 求下一个兄弟结点（根据传递的根结点不同，得到不同的结果）
TreeNode* nextSilbing(Tree *tree)
{
    return nextSilbing(tree->root);
}
TreeNode* nextSilbing(TreeNode *t)
{
    if(t == NULL)
        return NULL;
    return t->nextSilbing;
}

// 查找结点
TreeNode *Find(Tree *tree, ElemType key)
{
    return Find(tree->root, key);
}
TreeNode *Find(TreeNode *t, ElemType key)
{
    if(t == NULL)
        return NULL;

    if(t->data == key)
        return t;
    
    TreeNode *p = Find(t->firstChild, key);
    if(p != NULL)
        return p;
    return Find(t->nextSilbing, key);
}

// 查找父结点
TreeNode* Parent(Tree *tree, TreeNode *p)
{
    return Parent(tree->root, p);
}
TreeNode* Parent(TreeNode *t, TreeNode *p)
{
    if(t == NULL || p == NULL || p == t)
        return NULL;
    
    TreeNode *q = t->firstChild;
    TreeNode *parent;
    while(q != NULL && q != p)
    {
        parent = Parent(q, p);  // 在第一个孩子结点中查找parent结点
        if(parent != NULL)
            return parent;
        q = q->nextSilbing;
    }

    if(q != NULL && q == p)  // q(t->firstChild)==p说明要查找的结点p的父结点即为t
        return t;
    return NULL;
}