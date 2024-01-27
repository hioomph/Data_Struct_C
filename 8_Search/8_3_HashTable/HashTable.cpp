// #include<stdio.h>
// #include<malloc.h>
// #include<assert.h>

// #define P 13  // 对模数一般定义为素数
// #define ElemType int

// typedef struct HashNode
// {
//     ElemType data;
//     struct HashNode *link;
// }HashNode;

// typedef HashNode* HashTable[P];

// void InitHashTable(HashTable &ht)
// {
//     for(int i=0; i<P; ++i)
//     {
//         ht[i] = NULL;
//     }
// }

// int Hash(ElemType key)
// {
//     return key % P;  // 除留余数法
// }

// void InsertHashTable(HashTable &ht, ElemType x)
// {
//     int index = Hash(x);  // 获取当前x在哈希表中的映射
//     // 申请节点
//     HashNode *s = (HashNode*)malloc(sizeof(HashNode));
//     assert(s != NULL);
//     s->data = x;

//     // 把节点链接到相应下标的数组
//     s->link = ht[index];
//     ht[index] = s;
// }

// void ShowHashTable(HashTable &ht)
// {
//     for(int i=0; i<P; ++i)
//     {
//         printf("%d : ", i);
//         HashNode *p = ht[i];
//         while(p != NULL)
//         {
//             printf("%d-->", p->data);
//             p = p->link;
//         }
//         printf("Nul.\n");
//     }
// }

// HashNode* SearchHashTable(HashTable &ht, ElemType key)
// {
//     int index = Hash(key);
//     HashNode *p = ht[index];
//     // while(p != NULL)
//     // {
//     //     if(p->data == key)
//     //         return p;
//     // }

//     // return NULL;

//     // 优化写法
//     while(p!=NULL && p->data!=key)
//         p = p->link;
    
//     return p;
// }

// bool RemoveHashTable(HashTable &ht, ElemType key)
// {
//     int index = Hash(key);
//     HashNode *p = ht[index];
//     HashNode *s = NULL;
//     while(p!=NULL && p->data!=key)
//     {
//         s = p;
//         p = p->link;
//     }

//     if(p == NULL)
//         return false;
    
//     s->link = p->link;
//     free(p);

//     return true;

//     // HashNode *p = SearchHashTable(ht, key);
//     // if(p == NULL)
//     //     return false;
    
//     // int index = Hash(key);
//     // HashNode *q = ht[index];
//     // if(q == p)
//     // {
//     //     ht[index] = p->link;
//     //     free(p);
//     // }
//     // else
//     // {
//     //     while(q->link != p)
//     //         q = q->link;
//     //     q->link = p->link;
//     //     free(p);
        
//     // }
    
//     // return true;
// }

// ///////////////////////////////////////////////

// int main()
// {
//     HashTable ht;
//     InitHashTable(ht);

//     ElemType ar[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
//     int n = sizeof(ar)/sizeof(ElemType);

//     for(int i=0; i<n; ++i)
//     {
//         InsertHashTable(ht, ar[i]);
//     }

//     ElemType key = 27;
//     HashNode *p = SearchHashTable(ht, key);
//     if(p != NULL)
//         printf("%d find in ht[%d].\n", key, Hash(key));
//     else
//         printf("%d not exist.\n", key);

//     ShowHashTable(ht);
//     RemoveHashTable(ht, key);
//     ShowHashTable(ht);
     
// }