#include"Tree.h"

int main()
{
    Tree tree;
    InitTree(&tree, '#');

    char *str = (char *)"RAD#E##B#CFG#H#K#####";  // 树对应二叉链表的先序表示
    CreateTree(&tree, str);

    TreeNode *r = Root(&tree);
    printf("根结点%c\n", r->data);

    TreeNode *m = FirstChild(&tree);
    if(m != NULL)
        printf("%c的第一个孩子结点为%c\n", r->data, m->data);
    else
        printf("没有找到第一个孩子结点！\n");

    TreeNode *n = nextSilbing(&tree);
    if(n != NULL)
        printf("%c的下一个兄弟结点为%c\n", r->data, n->data);
    else
        printf("没有找到下一个兄弟结点！\n");


    TreeNode *p = Find(&tree, 'B');
    if(p != NULL)
        printf("找到结点%c\n", p->data);
    else
        printf("没有找到结点！\n");
    
    TreeNode *parent = Parent(&tree, p);
    if(parent != NULL)
        printf("%c的父结点为%c\n", p->data, parent->data);
    else
        printf("没有找到父结点！\n");
}