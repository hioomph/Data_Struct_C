#ifndef _TREE_H_
#define _TREE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType char

typedef struct TreeNode
{
    ElemType data;
    struct TreeNode *firstChild;   // 第一个孩子结点
    struct TreeNode *nextSilbing;  // 下一个兄弟结点
}TreeNode;

typedef struct Tree
{
    TreeNode *root;
    ElemType  refvalue;
}Tree;

void InitTree(Tree *tree, ElemType ref);
void CreateTree(Tree *tree, char *str);
void CreateTree(Tree *tree, TreeNode *&t, char *&str);

TreeNode* Root(Tree *tree);
TreeNode* FirstChild(Tree *tree);
TreeNode* FirstChild(TreeNode *t);
TreeNode* nextSilbing(Tree *tree);
TreeNode* nextSilbing(TreeNode *t);

TreeNode *Find(Tree *tree, ElemType key);
TreeNode *Find(TreeNode *t, ElemType key);

TreeNode* Parent(Tree *tree, TreeNode *p);
TreeNode* Parent(TreeNode *t, TreeNode *p);


#endif // _TREE_H_