#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define P 7  // 对模数一般定义为素数
#define NULL_DATA -1
#define BUCKET_NODE_SIZE 3

struct bucket_node
{
    int data[BUCKET_NODE_SIZE];
    struct bucket_node *next;
};
bucket_node hash_table[P];  // hash_table：存放bucket_node类型元素的数组

void Init_bucket_node()
{
    for(int i=0; i<P; ++i)
    {
        for(int j=0; j<BUCKET_NODE_SIZE; ++j)
        {
            hash_table[i].data[j] = NULL_DATA;
        }
        hash_table[i].next = NULL;
    }
}

int Hash(int key)
{
    return key % P;
}

int Insert_new_element(int x)
{
    int index = Hash(x);
    for(int i=0; i<BUCKET_NODE_SIZE; ++i)
    {
        if(hash_table[index].data[i] == NULL_DATA)
        {
            hash_table[index].data[i] = x;
            return 0;
        }
    }

    // 溢出桶有空余，直接插入
    bucket_node *p = &hash_table[index];
    while(p->next != NULL)
    {
        p = p->next;
        for(int i=0; i<BUCKET_NODE_SIZE; ++i)
        {
            if(p->data[i] == NULL_DATA)
            {
                p->data[i] = x;
                return 0;
            }
        }
    }

    // 不存在有空余的溢出桶，则新建一个
    bucket_node *s = (bucket_node*)malloc(sizeof(bucket_node));
    assert(s != NULL);
    for(int i=0; i<BUCKET_NODE_SIZE; ++i)
        s->data[i] = NULL_DATA;
    s->next = NULL;

    s->data[0] = x;
    p->next = s;

    return 0;
}

void show_bucket()
{
    for(int i=0; i<P; ++i)
    {
        printf("%d : ", i);
        for(int j=0; j<BUCKET_NODE_SIZE; ++j)
        {
            printf("%d ", hash_table[i].data[j]);
        }
        printf("--> ");

        bucket_node *p = &hash_table[i];
        while(p->next != NULL)
        {
            p = p->next;
            for(int m=0; m<BUCKET_NODE_SIZE; ++m)
                printf("%d ", p->data[m]);
        }
        printf(" Nul.\n");
    }
}

/////////////////////////////////////////////////////////////////////////

int main()
{
    Init_bucket_node();
    int array[] = {1, 8, 15, 22};
    for(int i=0; i<sizeof(array)/sizeof(int); ++i)
    {
        Insert_new_element(array[i]);
    }

    show_bucket();

    return 0;
}