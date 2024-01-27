#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>


#define Type int
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct AVLNode
{
    Type data;
    AVLNode *leftChild;
    AVLNode *rightChild;
    int bf;  // 平衡因子
}AVLNode;

typedef struct AVLTree
{
    AVLNode *root;
}AVLTree;

//////////////////////////////////////
void initAVLTree(AVLTree *avl);
AVLNode* buyNode(Type x);

BOOL InsertAVLTree(AVLTree *avl, Type x);
BOOL InsertAVLTree(AVLNode *&t, Type x);
BOOL RemoveAVL(AVLTree *avl, Type key);
BOOL RemoveAVL(AVLNode *&t, Type key);

void RotateR(AVLNode *&ptr);
void RotateL(AVLNode *&ptr);
void RotateLR(AVLNode *&ptr);
void RotateRL(AVLNode *&ptr);

void PreOrder(AVLTree *avl);
void PreOrder(AVLNode *t);



#endif // _AVLTREE_H_