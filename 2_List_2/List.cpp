#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define ElemType int

// List中单个节点Node的定义
typedef struct ListNode
{
    ElemType data;
    struct ListNode *next;  // 自身类型的指针类型    
}ListNode;

typedef ListNode* List;

// 新建空List
void InitList(List *head)
{
    /*
        List *head = ListNode **head
        
        这里的 *head 与传入的 &mylist对应，假如传入 mylist，则相当于 head = NULL，是值传递，
        当跳出InitList函数后 head 的指向又回变成任意值。
    */
    // (*head) = NULL;

    *head = (ListNode*)malloc(sizeof(ListNode));
    assert(*head != NULL);
    (*head)->next = NULL;
}

// 尾插法创建List
void Tail_CreateList(List *head)
{
    ListNode *p = *head;
    for(int i=1; i<=10; ++i)
    {
        p = p->next = (ListNode*)malloc(sizeof(ListNode));  // 理解这行代码非常重要
        assert(p != NULL);

        p->data = i;
        p->next = NULL;      
    }
}

// 头插法创建List
void Head_CreateList(List *head)
{
    for(int i=1; i<=10; ++i)
    {
        ListNode *s = (ListNode*)malloc(sizeof(ListNode));
        assert(s != NULL);

        s->data = i;
        s->next = (*head)->next;
        (*head)->next = s;
    }
}
 
// 不包含空的头节点的版本
// // 尾插法创建List
// void Tail_CreateList(List *head)
// {
//     *head = (ListNode *)malloc(sizeof(ListNode));  // 申请一个节点交给head
//     assert(*head != NULL);
//     (*head)->data = 1;  // ->的优先级高于*，需要括号
//     (*head)->next = NULL;

//     ListNode *p = *head;  // 申请一个p指针，指向第一个节点，即head
//     for(int i=2; i<=10; ++i)
//     {
//         ListNode *s = (ListNode*)malloc(sizeof(ListNode));  // 申请一个s指针，指向第二个节点
//         assert(s != NULL);
//         s->data = i;
//         s->next = NULL;

//         p->next = s;  // 将第一个节点和第二个节点链接起来，本质是将s的指针赋给p的next
//         p = s;  // 让p移动到第二个节点上，使得这个过程可以继续链接下去
//     }
// }

// // 头插法创建List
// void Head_CreateList(List *head)
// {
//     *head = (ListNode*)malloc(sizeof(ListNode));
//     assert(*head != NULL);
//     (*head)->data = 1;
//     (*head)->next = NULL;

//     for(int i=2; i<=10; ++i)
//     {
//         ListNode *s = (ListNode*)malloc(sizeof(ListNode));
//         assert(s != NULL);
//         s->data = i;
//         s->next = *head;
//         *head = s;
//     }
// }

// 遍历输出List
void ShowList(List head)
{
    // ListNode *p = head;
    ListNode *p = head->next;
    while(p != NULL)
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("Nul.\n");
}
   
int main()
{
    List mylist;  // mylist是链表的指针，此时不指向任何节点
    InitList(&mylist);  // 当执行(*head) = NULL;后，mylist在内存中的地址为0x0        
    Tail_CreateList(&mylist);
    Head_CreateList(&mylist);
    ShowList(mylist);
}