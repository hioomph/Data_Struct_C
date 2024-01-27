#include"AVLTree.h"
#include"Stack.h"

// 初始化AVL
void initAVLTree(AVLTree *avl)
{
    avl->root = NULL;
}

AVLNode* buyNode(Type x)
{
    AVLNode *p = (AVLNode*)malloc(sizeof(AVLNode));
    assert(p != NULL);

    p->data = x;
    p->leftChild = p->rightChild = 0;
    p->bf = 0;

    return p;
}

// 插入数据
BOOL InsertAVLTree(AVLTree *avl, Type x)
{
    return InsertAVLTree(avl->root, x);
}
BOOL InsertAVLTree(AVLNode *&t, Type x)
{
    AVLNode *p = t;  // 定义一个指向结点的指针
    AVLNode *parent = NULL;

    Stack st;
    InitStack(&st);

    while(p != NULL)  // 根据插入的数据x的大小与当前根节点t的大小比较，对指针p进行移动
    {
        if(x == p->data)  
            return FALSE;  // 若相等，不符合BSTree的定义，退出

        parent = p;  // 记录parent父结点的指向
        Push(&st, parent);  // 将parent入栈，目的是为了在调整bf的那个循环中根据栈元素出栈的顺序进行回退

        if(x < p->data)  
            p = p->leftChild;  // 若小于t的数据，则移动到t的左子树
        else 
            p = p->rightChild;  // 若大于t的数据，则移动到t的右子树
    }

    // 退出循环时p为空，说明此时p已经指向了应该插入的位置，所以调用结点申请函数，申请一个新的结点存放x
    p = buyNode(x);

    // 若出了循环parent依然为空，则说明此时创建的为根节点
    if(parent == NULL)
    {
        t = p;
        return TRUE;
    }
    // 若p不为空，则需要建立parent和p之间的关系
    if(x < parent->data)
        parent->leftChild = p;
    else
        parent->rightChild = p;

    ///////////////////////////////////////////////////////////////
    // 调整BF
    while(!IsEmpty(&st))
    {
        parent = GetTop(&st);
        Pop(&st);
        if(parent->leftChild == p)
            parent->bf--;  // bf的定义为右子树高度减去左子树高度，因此左树有结点就会导致bf减少1
        else if(parent->rightChild == p)
            parent->bf++;  // 同理
        
        if(parent->bf == 0)  // 若bf为0，直接退出循环
            break;
        /*
            这一步 if(parent->bf == 0) break; 的目的是在循环中判断是否需要继续进行平衡调整。
            当一个节点插入后，如果其父节点的平衡因子 bf 为0，表示在插入节点之前该节点的左右子树高度相等。
            在插入节点后，如果插入导致了父节点的平衡因子 bf 的变化，那么在其祖先节点中可能也会发生平衡调整。

            如果父节点的平衡因子 bf 不变，即 bf == 0，
            则说明在插入节点后，以及从插入节点到根节点的路径上的节点高度没有发生变化，因此不需要进行更多的平衡调整。
            这是因为 AVL 树在插入操作后，只有从插入节点到根节点的路径上的节点的平衡因子可能发生变化，其他节点的平衡因子不受影响。

            因此，当检测到父节点的平衡因子 bf 为0时，就可以退出循环，不再进行更多的平衡调整。
            这样可以提高插入操作的效率，避免不必要的调整操作，因为只有发生失衡的节点路径上的调整才是必要的。
        */
        if(parent->bf == 1 || parent->bf == -1)
            p = parent;  // 栈非空，继续向上移动p调整bf的值
        else  // bf大于1
        {
            ///////////////////////////////////////////////////////
            // 旋转化平衡调整
            int flag = (parent->bf<0)?-1:1;  // 用正负号标记parent的bf
            if(p->bf == flag)  // 单旋转
            {
                if(flag == -1)
                    RotateR(parent);  //    '/'
                else
                    RotateL(parent);  //    '\'
            }
            else  // 处于一条折线，进行双旋转
            {
                if(flag == 1)
                    RotateRL(parent);  // >，向右突出，先右旋转再左旋转
                else
                    RotateLR(parent);  // <，向左突出，先左旋转再右旋转
            }
            break;  // important
        }
    }

    if(IsEmpty(&st))
    {
        t = parent;  // 指向调整后更新的根节点
    }
    else
    {
        AVLNode *q = GetTop(&st);  // important
        if(q->data > parent->data)
            q->leftChild = parent;
        else
            q->rightChild = parent;
    }

    return TRUE;
}

// 删除
BOOL RemoveAVL(AVLTree *avl, Type key)
{
    return RemoveAVL(avl->root, key);
}
BOOL RemoveAVL(AVLNode *&t, Type key)
{
    AVLNode *ppr = NULL;  // parent的结点
    AVLNode *parent = NULL;
    AVLNode *p = t;
    Stack st;  // 记录访问过的父结点
    InitStack(&st);

    while(p != NULL)
    {
        if(p->data == key)
            break;

        parent = p;
        Push(&st, parent);

        if(p->data < key)
            p = p->rightChild;
        else
            p = p->leftChild;
    }

    if(p == NULL)
        return FALSE;  // 没有找到要删除的结点


    AVLNode *q;
    int f;  //  leftChild NULL or rightChild NULL
    // 情况1：p的左右子树均存在
    if(p->leftChild != NULL && p->rightChild != NULL)
    {
        parent = p;
        Push(&st, parent);  // 记录走过的路线
        // 以p为根的树，找到其中序遍历下的前驱（左子树的最后一个结点）或后继q
        q = p->leftChild;
        while(q->rightChild != NULL)
        {   
            parent = q;
            Push(&st, q);  // 记录走过的路线
            q = q->rightChild;  // 注意这里是rightChild
        }
        // 将q的值赋值给p
        p->data = q->data;
        // 从而问题转换为删除q，且此时q最多只包含一个分支
        p = q;
    }
    // 情况2：p最多存在一个左子树或右子树
    if(p->leftChild != NULL)
        q = p->leftChild;
    else
        q = p->rightChild;
    
    if(parent == NULL)  // 根节点
        t = parent;
    else
    {
        // 将要删除结点存在的左右子树链接到要删除结点的父结点上
        if(parent->leftChild == p)
        {
            parent->leftChild = q;
            f = 0;  // L q赋给左树
        }
        else
        {
            parent->rightChild = q;
            f = 1;  // R q赋给右树
        }

        // 修改bf
        int link_flag = 0;  // 连接标记， -1 leftChild || 1 rightChild || 0 no_link
        while(!IsEmpty(&st))
        {
            parent = GetTop(&st);
            Pop(&st);

            // 1 对应修改parent的bf
            // if(parent->rightChild == q) 错误
            if(parent->rightChild == q && f == 1)  // important
                parent->bf--;
            else
                parent->bf++;

            // 2 记录parent和ppr的关系
            if(!IsEmpty(&st))
            {
                ppr = GetTop(&st);  // st的栈顶为parent的父结点
                link_flag = (ppr->leftChild == parent)?-1:1;  // 用link_flag记录parent是ppr的左子树还是右子树
            }
            else
            {
                link_flag = 0;
            }
            
            // 3 修改平衡因子bf
            // 3.1 若修改后bf为1/-1，则原bf为0，则修改后parent的平衡未被打破，可以直接退出
            if(parent->bf == -1 || parent->bf == 1)
                break;
            // 3.2 若修改后bf为0，说明较高的子树缩短，此时parent为根的子树平衡，但其高度减1，需要继续考察parent的父结点的平衡状态
            // 一旦往上回溯，某个父结点修改后的bf为1/-1，则退出
            if(parent->bf == 0)
                q = parent;  // 更新q
            // 3.3 bf=|2|，此时树不再平衡，需要进行旋转操作
            else  
            {
                // 定义flag，以判断需要进行什么旋转 
                int flag = 0;
                if(parent->bf < 0)
                {
                    flag = -1;
                    q = parent->leftChild;  // q指向parent较高的子树，后续进行旋转操作
                }
                else
                {
                    flag = 1;
                    q = parent->rightChild;  // 同理
                }

                // 3.3.1 q的bf为0时，直接进行单旋转
                if(q->bf == 0) 
                {
                    if(flag == -1)   // 左树高，右单旋转
                    {
                        RotateR(parent);
                        parent->bf = 1;
                        parent->rightChild->bf = -1;
                    }
                    else  // 右树高，左单旋转
                    {
                        RotateL(parent);
                        parent->bf = -1;
                        parent->rightChild->bf = 1;
                    }
                    
                    break;
                }
                // 3.3.2 q的bf与parent的bf同号，也直接进行单旋转
                if(q->bf == flag)  
                {
                    if(flag == -1)  // 右单旋转
                    {
                        RotateR(parent);
                    }
                    else  // 左单旋转
                    {
                        RotateL(parent);
                    }
                }
                // 3.3.3 q的bf与parent的bf异号，进行双旋转
                else  
                {
                    if(flag == -1)
                    {
                        RotateLR(parent);
                    }
                    else
                    {
                        RotateRL(parent);
                    }
                } 

                // 3.3.4 旋转调整结束后，更新当前新的parent和ppr的链接   
                if(link_flag == 1)
                    ppr->rightChild = parent;
                else if(link_flag == -1)
                    ppr->leftChild = parent;             
            }
        }

        if(IsEmpty(&st))  // 栈为空，说明已经回退到根结点
            t = parent;
        
    }
    free(p);

    return TRUE;
}

// 单旋转
// '/'
void RotateR(AVLNode *&ptr)
{
    // 结合笔记来理解
    AVLNode *subR = ptr;
    ptr = subR->leftChild;
    subR->leftChild = ptr->rightChild;
    ptr->rightChild = subR;
    ptr->bf = subR->bf = 0;
}
// '\'
void RotateL(AVLNode *&ptr)
{
    // 结合笔记来理解
    AVLNode *subL = ptr;
    ptr = subL->rightChild;
    subL->leftChild = ptr->leftChild;
    ptr->leftChild = subL;
    ptr->bf = subL->bf = 0;
}

// 双旋转
void RotateLR(AVLNode *&ptr)
{
    AVLNode *subR = ptr;
    AVLNode *subL = subR->leftChild;
    ptr = subL->rightChild;

    subL->rightChild = ptr->leftChild;  // 由于要把subL挂到ptr的左树上，所以把ptr原来的左树挂到subL的右树上
    ptr->leftChild = subL;
    if(ptr->bf <= 0)
        subL->bf = 0;
    else
        subL->bf = -1;

    subR->leftChild = ptr->rightChild;  // 由于要把subR挂到ptr的右树上，所以把ptr原来的右树挂到subR的左树上
    ptr->rightChild = subR;
    if(ptr->bf == -1)
        subR->bf = 1;
    else
        subR->bf = 0;

    ptr->bf = 0;
}
void RotateRL(AVLNode *&ptr)
{
    AVLNode *subL = ptr;
    AVLNode *subR = subL->rightChild;
    ptr = subR->leftChild;

    subR->leftChild = ptr->rightChild;  // 由于要把subR挂到ptr的右树上，所以把ptr原来的右树挂到subR的左树上
    ptr->rightChild = subR;
    if(ptr->bf >= 0)
        subR->bf = 0;
    else
        subR->bf = 1;

    subL->rightChild = ptr->leftChild;  // 由于要把subL挂到ptr的左树上，所以把ptr原来的左树挂到subL的右树上
    ptr->leftChild = subL;
    if(ptr->bf == -1)
        subL->bf = -1;
    else
        subL->bf = 0;

    ptr->bf = 0;
}

// 遍历
void PreOrder(AVLTree *avl)
{
    PreOrder(avl->root); 
}
void PreOrder(AVLNode *t)
{
    if(t != NULL)
    {
        printf("%d ", t->data);
        PreOrder(t->leftChild);
        PreOrder(t->rightChild);
    }
}