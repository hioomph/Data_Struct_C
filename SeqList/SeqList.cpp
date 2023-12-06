#include "SeqList.h"

// 增配空间
bool Inc(SeqList *list)
{
    ElemType *newbase = (ElemType*)realloc(list->base, sizeof(ElemType)*(list->capacity + INC_SIZE));
    if(newbase == NULL)
    {
        printf("增配空间失败，内存不足！\n");
        return false;
    }

    list->base = newbase;
    list->capacity += INC_SIZE;

    return true;     
}

// 初始化SeqList
void InitSeqList(SeqList *list)
{
    // 初始化SeqList，给base、cap和size赋值

    // 开辟一段连续的空间
    list->base = (ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
    assert(list->base != NULL);

    // 定义容量和大小
    list->capacity = SEQLIST_INIT_SIZE;
    list->size = 0;
}

// 显示SeqList
void show_list(SeqList *list)
{
    for (int i = 0; i < list->size; ++i)
    {
        printf("%d ", list->base[i]);
    }
    printf("\n");
}

// SeqList长度
int length(SeqList *list)
{
    return list->size;
}

// 尾插数据
void push_back(SeqList *list, ElemType x)
{
    /*
        *list 指明要将数据插入到哪个list中
        x     当表未满时，size的值恰好为要插入元素的位置的下标值
    */
    if (list->size >= list->capacity && !Inc(list))
    {
        printf("SeqList空间已满，%d不能尾部插入数据。\n", x);
        return;
    }
    list->base[list->size] = x;
    list->size++;
}

// 头插数据
void push_front(SeqList *list, ElemType x)
{
    /*
        *list 指明要将数据插入到哪个list中
        x     当表未满时，size的值恰好为要插入元素的位置的下标值
    */
    if (list->size >= list->capacity && !Inc(list))
    {
        printf("SeqList空间已满，%d不能头部插入数据。\n", x);
        return;
    }
    // 移动数据
    for (int i = list->size; i > 0; --i)
    {
        list->base[i] = list->base[i - 1];
    }
    list->base[0] = x;
    list->size++;
}

// 尾删，要注意尾删并不是真正把数据从内存中删除，而是从逻辑上将其变为无效数据
void pop_back(SeqList *list)
{
    // 判定表是否为空
    if (list->size == 0)
    {
        printf("SeqList为空，不能尾部删除数据。\n");
        return;
    }

    list->size--;
}

// 头删
void pop_front(SeqList *list)
{
    // 判定表是否为空
    if (list->size == 0)
    {
        printf("SeqList为空，不能头部删除数据。\n");
        return;
    }
    for (int i = 0; i < list->size - 1; ++i)
    {
        list->base[i] = list->base[i + 1];
    }

    list->size--;
}

// 按照给定位置插入
void insert_pos(SeqList *list, int pos, ElemType x)
{
    // 容量判断
    if (list->size >= list->capacity && !Inc(list))
    {
        printf("SeqList空间已满，不能头部插入数据。\n");
        return;
    }

    // 边界判断
    if (pos < 0 || pos > list->size)
    {
        printf("插入位置非法，不能插入数据。\n");
        return;
    }

    for (int i = list->size; i > pos; --i)
        list->base[i] = list->base[i - 1];
    list->base[pos] = x;
    list->size++;
}

// 按照给定位置删除
void delete_pos(SeqList *list, int pos)
{
    if (pos < 0 || pos >= list->size)
    {
        printf("删除位置非法，不能删除数据。\n");
        return;
    }

    for (int i = pos; i < list->size - 1; ++i)
        list->base[i] = list->base[i + 1];
    list->size--;
}

// 按照给定值删除
void delete_val(SeqList *list, ElemType key)
{
    int pos = find(list, key);
    if (key == -1)
    {
        printf("要删除的数据不存在！\n");
        return;
    }

    delete_pos(list, pos);
}

// 查找（这里的查找只能匹配到第一个和key相等的值所在的位置）
int find(SeqList *list, ElemType key)
{
    for (int i = 0; i < list->size; ++i)
    {
        if (list->base[i] == key)
            return i;
    }

    return -1;
}

// 冒泡排序
void sort(SeqList *list)
{
    for (int i = 0; i < list->size - 1; ++i)
    {
        for (int j = 0; j < list->size - 1 - i; ++j)
        {
            if (list->base[j] > list->base[j + 1])
            {
                ElemType tmp = list->base[j];
                list->base[j] = list->base[j + 1];
                list->base[j + 1] = tmp;
            }
        }
    }
}

// 逆值排序
void reverse(SeqList *list)
{
    if (list->size == 0 || list->size == 1)
        return;

    int low = 0;
    int high = list->size - 1;
    ElemType tmp;
    while (low < high)
    {
        tmp = list->base[low];
        list->base[low] = list->base[high];
        list->base[high] = tmp;
        low++;
        high--;
    }
}

// 清除表
void clear(SeqList *list)
{
    list->size = 0;
}

// 摧毁表
void destroy(SeqList *list)
{
    // 释放空间
    free(list->base);

    list->base = NULL;
    list->capacity = 0;
    list->size = 0;
}

// 合并两个SeqList
void merge(SeqList *lt, SeqList *la, SeqList *lb)
{
    lt->capacity = la->size + lb->size;
    lt->base = (ElemType *)malloc(sizeof(ElemType) * lt->capacity);
    assert(lt->base != NULL);

    int ia = 0;
    int ib = 0;
    int ic = 0;

    while(ia<la->size && ib<lb->size)
    {
        if(la->base[ia] < lb->base[ib])
            lt->base[ic++] = la->base[ia++];
        else
            lt->base[ic++] = lb->base[ib++];
    }

    // la的长度大于lb的长度，剩下的合并工作在la中完成
    while(ia < la->size)
    {   
        lt->base[ic++] = la->base[ia++];
    }

    // lb的长度大于la的长度，剩下的合并工作在lb中完成
    while(ib < lb->size)
    {   
        lt->base[ic++] = lb->base[ib++];
    }

    lt->size = la->size + lb->size;
}