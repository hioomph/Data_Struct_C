#include "SeqList.h"

/*
int main()
{
    SeqList mylist;  // 这里只是创建了mylist这个结构，其内部的base、cap和size此时均为随机值
    InitSeqList(&mylist);

    ElemType Item;
    int pos = 0;
    int select = 1;
    while(select)
    {
        printf("******************************************\n");
        printf("*  [1]  push_back       [2]  push_front  *\n");
        printf("*  [3]  show_list       [4]  pop_back    *\n");
        printf("*  [5]  pop_front       [6]  insert_pos  *\n");
        printf("*  [7]  find            [8]  lenth       *\n");
        printf("*  [9]  delete_pos      [10] delete_val  *\n");
        printf("*  [11] sort            [12] reverse     *\n");
        printf("*  [13] clear           [14] destroy*    *\n");
        printf("*  [0]  quit_system                      *\n");
        printf("******************************************\n");
        printf("请选择：>");
        scanf("%d", &select);
        if(select == 0)
            break;
        
        switch (select)
        {
        case 1:
            printf("请输入要尾插入的数据（-1结束）：>");
            while(scanf("%d", &Item), Item != -1)
            {
                push_back(&mylist, Item);                
            }
            break;
        
        case 2:
            printf("请输入要头插入的数据（-1结束）：>");
            while(scanf("%d", &Item), Item != -1)
            {
                push_front(&mylist, Item);                
            }
            break;  
        
        case 3:
            show_list(&mylist);
            break; 

        case 4:
            pop_back(&mylist);
            break;  

        case 5:
            pop_front(&mylist);
            break; 
        
        case 6:
            printf("请输入要插入的数据：>");
            scanf("%d", &Item);
            printf("请输入要插入的位置：>");
            scanf("%d", &pos);
            insert_pos(&mylist, pos, Item);
            break; 

        case 7:
            printf("请输入要查找的数据：>");
            scanf("%d", &Item);
            pos = find(&mylist, Item);
            if(pos == -1)
                printf("要查找的数据%d不存在！\n", Item);
            else
                printf("要查找的数据%d在顺序表中的%d下标位置。\n", Item, pos);
            break; 

        case 8:
            printf("SeqList的长度为：>%d\n", length(&mylist));
            break; 

        case 9:
            printf("请输入要删除数据的位置：>");
            scanf("%d", &pos);
            delete_pos(&mylist, pos);
            break; 

        case 10:
            printf("请输入要删除数据的值：>");
            scanf("%d", &Item);
            delete_val(&mylist, Item);
            break;    

        case 11:
            sort(&mylist);
            break;  

        case 12:
            reverse(&mylist);
            break;   

        case 13:
            clear(&mylist);
            break;

        // case 14:
            // destroy(&mylist);
            // break; 

        default:
            printf("输入的选择错误，请重新输入！\n");
            break;
        }
    }
    // 结束对表的相关操作后，释放对应空间
    destroy(&mylist);
}
*/

int main()
{
    SeqList mylist, ulist, list;
    InitSeqList(&mylist);
    InitSeqList(&ulist);

    push_back(&mylist, 1);
    // push_back(&mylist, 3);
    push_back(&mylist, 5);
    // push_back(&mylist, 7);
    push_back(&mylist, 9);

    push_back(&ulist, 2);
    push_back(&ulist, 4);
    push_back(&ulist, 6);
    push_back(&ulist, 8);
    push_back(&ulist, 10);

    merge(&list, &mylist, &ulist);
    show_list(&list);
}