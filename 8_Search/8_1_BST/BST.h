#ifndef _BST_H_
#define _BST_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define T int
#define FALSE 0
#define TRUE  1
#define BOOL  int

#define MAX_SIZE 100

typedef struct BSTNode
{
    T data;
    BSTNode *leftChild;
    BSTNode *rightChild;
}BSTNode;

typedef struct BST
{
    BSTNode *root;
}BST;

void InitBSTree(BST *bst);

BOOL InsertBSTree(BST *bst, T x);
BOOL InsertBSTree(BSTNode **t, T x);
T Min(BST *bst);
T Min(BSTNode *t);
T Max(BST *bst);
T Max(BSTNode *t);
void Sort(BST *bst);
void Sort(BSTNode *t);

void Get(BST *bst, int array[], int* index);
void Get(BSTNode *t, int array[], int* index);

BSTNode* Search(BST *bst, T key);
BSTNode* Search(BSTNode *t, T key);

BOOL RemoveBSTree(BST *bst, T key);
BOOL RemoveBSTree(BSTNode **t, T key);

void MakeEmptyBSTree(BST *bst);
void MakeEmptyBSTree(BSTNode **t);

#endif // _BST_H_