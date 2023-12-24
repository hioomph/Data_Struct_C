#include"ThreadBinTree.h"

int main()
{
    char *str = (char *)"ABC##DE##F##G#H##";
    BinTree mytree;
    InitBinTree(&mytree, '#');
    CreateBinTree(&mytree, str);

    CreateInThread(&mytree);

    BinTreeNode *p = First(&mytree);
    printf("First Node = %c\n", p->data);
    BinTreeNode *q = Last(&mytree);
    printf("Last Node = %c\n", q->data);

    BinTreeNode *cur = Search(&mytree, 'B');
    BinTreeNode *m = Next(&mytree, cur);
    printf("%c\'s next %c\n", cur->data, m->data);
    BinTreeNode *n = Prev(&mytree, cur);
    printf("%c\'s previous is %c\n", cur->data, n->data);

    printf("中序遍历：");
    InOrder(&mytree);

    BinTreeNode *parent = Parent(&mytree, cur);
    printf("%c\'s parent Node = %c\n", cur->data, parent->data);

}  