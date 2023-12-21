#include"GenList.h"

// 广义表的初始化
void InitGenList(GenList &gl)
{
	gl = NULL;
}

// 创建广义表：通过字符串str来创建广义表gl
void CreateGenList(GenList &gl, char *str)
{
	int n = strlen(str);  // 求解字符串长度
	// 存储表内元素
	char *sub = (char *)malloc(sizeof(char) * (n-2));
	// 存储表头
	char *hsub = (char *)malloc(sizeof(char) * (n-2));
	assert(sub!=NULL && hsub!=NULL);

	// "1,2,3"
	// 去掉sub左右两边的括号
	strncpy(sub,str+1,n-2); 
	sub[n-2] = '\0';//加上结束符

	// 判断广义表是否为空
	if(gl == NULL)  // 为空
	{   
		//  创建头结点(广义表的第一个结点为头结点，其余都为尾结点)
		gl = (GLNode*)malloc(sizeof(GLNode));
		assert(gl != NULL);
		gl->tag = HEAD;  // 结点标记为头结点
		gl->hp = gl->tp = NULL;  // 把子表指针和尾指针都指向空
	}

	GLNode *p = gl;  // 为了不丢失gl的指向，定义一个指针来操作
	// 求子串长度，当sub长度不为零时，说明广义表还未创建完成
	while(strlen(sub) != 0)
	{  
		//  采用尾插法,在后面插入结点
		/*
			1、创建一个结点
			2、让p所指结点的尾指针指向新建的结点
			3、让p指向新建结点
		*/
		p = p->tp = (GLNode*)malloc(sizeof(GLNode));
		assert(p != NULL);
		p->hp = p->tp = NULL;  // 将新建结点的子表指针和尾指针都赋空

		//  "1,2,3"     ==>  "1"      hsub="1"  sub="2,3";
		//  "(1,2),3,4" ==>  "(1,2)"  hsub="(1,2)" sub="3,4"
		if(sever(sub,hsub))  // sever函数分离表头，并将表头存入hsub中
		{

			// 对分离出来的表头进行判断，是否包含括号
			if(hsub[0] == '(')
			{
				// 说明要创建的结点是子表类型
				p->tag = CHILDLIST;  // 设置子表标记
				CreateGenList(p->hp,hsub);  // 在p的表头结点处，创建hsub子表
			}
			else
			{
				// 说明要创建的结点是原子类型
				p->tag = ATOM;  // 设置原子标记
				p->atom = atoi(hsub);  // 将表头字符串转换成整型数据，赋值给原子数据
			}
		}
	}
}

// 广义表表头分割函数，将sub中的表头分割到hsub中
bool sever(char *sub, char *hsub)
{
	//  判断sub是否为空
	if(*sub=='\0' || strcmp(sub,"()")==0)
	{
        // 是 情况：""  或  "()"
		hsub[0] = '\0';  // 将hsub赋空
		return true;
	}
	
	int n = strlen(sub);  // 求sub的长度
	int i=0;
	char ch = sub[0];  // 获取第一个字符
	int k = 0;  // 表示括号的信息
	/*
        当sub还没遍历完成且还未检测到括号外的逗号，继续遍历
	    注：当检测到括号外的逗号时，说明找到表头分割点，如："(1,2),3,4" 表头即为(1,2)
	*/
	while(i<n && (ch!=','|| k!=0))
	{
		// 判断是否运到左括号
		if(ch == '(')
			k++;  // k++表示进入一层括号
		else if(ch == ')')  // 判断是否遇到右括号
			k--;   // k--表示退出一层括号

		// 获取下一个元素
		i++;
		ch = sub[i];
	}

	// 判断是否是因为检测到括号外的逗号而结束的
	if(i < n)
	{
        // 是
		// 在i位置截断，前面部分就是表头
		sub[i] = '\0';
		// 将取得的表头放入hsub中
		strcpy(hsub,sub);
		// 更新sub的值：此时的sub应该去掉表头hsub
		strcpy(sub,sub+i+1);
	}
	else if(k != 0)  // 判断是否是因为内部括号不匹配
		return false; // 是，分割失败
	else  // 判断是否是因为i>=n而结束
	{
        // 是，情况 "(1,2)"  ==> hsub ="(1,2)"  sub = ""
		// 说明sub整个就是表头
		strcpy(hsub,sub);  // 把sub整个赋值给hsub
		sub[0] = '\0';  // sub赋给hsub后，此时sub为空
	}

	return true;
}

// 访问广义表
void ShowGenList(GenList &gl)
{
    GLNode *p = gl->tp;  // 指向下一个节点
    printf("(");
    while(p != NULL)
    {
        if(p->tag == ATOM)  // 标记值=ATOM，直接访问数据
        {
            printf("%d",p->atom);
            p = p->tp;
        }
        else if(p->tag == CHILDLIST)  // 标记值=CHILDLIST，说明此时访问广义表的子表
        {
            // 递归访问
            ShowGenList(p->hp);
            p = p->tp;
        }

        // 检查是否为最后一个元素，如果是则不打印逗号
        if(p != NULL)
            printf(",");
    }
    printf(")");
}

// 广义表判空
bool GenListEmpty(GenList &gl)
{
    return gl->tp == NULL;
}

// 广义表长度
int GenListLength(GenList &gl)
{
    // 不关心子表内部，只关心最高层次的指针个数
    int length = 0;
    GLNode *p = gl->tp;
    while(p != NULL)
    {
        length++;
        p = p->tp;
    }

    return length;
}

// 广义表深度
int GenListDepth(GenList &gl)
{
    if(gl->tp == NULL)
        return 1;
    
    GLNode *p = gl->tp;
    int maxdepth = 0;

    int dep;
    while(p != NULL)
    {
        if(p->tag == CHILDLIST)
        {
            dep = GenListDepth(p->hp->tp);
            if(dep > maxdepth)
                maxdepth = dep;
        }
        p = p->tp;
    }

    return maxdepth+1;
}

// 拷贝广义表
void CopyGenList(GenList &gl, GenList &glt)
{
    if(gl == NULL)
        return;
    
    if(glt != NULL)
        DestroyGenList(glt);

    // 创建新节点
    glt = (GLNode*)malloc(sizeof(GLNode));
    assert(glt != NULL);
    glt->tag = gl->tag;  // 结点标记为头结点
    glt->hp = gl->hp;
    glt->tp = gl->tp;  // 把子表指针和尾指针都指向空

    GLNode *p = gl->tp;
    GLNode *q = glt;

    while(p != NULL)
    {
        // 创建结点
		q = q->tp = (GLNode*)malloc(sizeof(GLNode));
		assert(q != NULL);
		q->tag = p->tag; // 结点标记为头结点
		q->hp = q->tp = NULL;  // 将新建结点的子表指针和尾指针都赋空

        if(p->tag == ATOM)
        {
            q->atom = p->atom;
            p = p->tp;
        }
        else if(p->tag == CHILDLIST)
        {
            CopyGenList(p->hp, q->hp);
            p = p->tp;
        }
    }
}

//将整数转换成字符串
void NumToStr(int num, char* str, int& i)
{
	char temp[25];
    snprintf(temp, sizeof(temp), "%d", num);
	for(unsigned j=0;j<strlen(temp);++j)
		str[i++]=temp[j];
}

// 获取表内元素
void GetGenList(GenList &gl, char *str, int &i)
{    
    // 获取头指针
    GLNode *p = gl->tp;
    if(p->tag == ATOM)
    {   
        NumToStr(p->atom, str, i);  // 将数字转换成字符串存入str中
        if(p->tp != NULL)
            str[i++] = ',';
        p = p->tp;
    }
    else if(p->tag == CHILDLIST)
    {
        // 针对单个CHILDLIST
        str[i++] = '(';  // 添加 '('
        GetGenList(p->hp, str, i);  // 递归调用，更新 str 的位置
        i = strlen(str);  // 更新 i 到当前字符串的末尾
        str[i++] = ')';  // 添加 ')'
        if(p->tp != NULL)
            str[i++] = ',';
        p = p->tp;
    }
}

// 获取表头元素
void GetHead(GenList &gl)
{
    // 表头为ATOM时：直接返回atom值即可
    if(gl->tp->tag == ATOM)
    {
        char str[1000];
        int i = 0;
        NumToStr(gl->tp->atom, str, i);
        str[i] = '\0';
        printf("%s", str);

    }
    // 表头为CHILDLIST时，取hp指针，将此时的表头作为一个新的GenList来遍历输出即可
    else
    {
        ShowGenList(gl->tp->hp);
    }
}

// 获取表尾元素
void GetTail(GenList &gl)
{
    if(GenListEmpty(gl))
    {
        printf("gl为空，不存在表尾！");
        return;
    }

    ShowGenList(gl->tp);
}

// 首插
void InsertFirst(GenList &gl, char *str)
{
    GenList t;
    InitGenList(t);
    CreateGenList(t, str);

    // 遍历创建的子表t，使得p指向当前表的末尾，以便和gl衔接
    GLNode *p = t->tp;
    while(p->tp != NULL)
    {
        p = p->tp;
    }

    // 将新创建的广义表t放到gl的前面
	p->tp = gl->tp;

	// 将gl的头结点连上广义表t
	gl->tp = t->tp;

	free(t);  // t的头结点无用，释放
}

// 首删
void DeleteFirst(GenList &gl)
{
    if (gl != NULL && gl->tp != NULL)
    {
        GenList t = gl->tp;
        gl->tp = t->tp;
        // DestroyGenList(t);
        free(t);
    }
    else
    {
        // 处理空表或表只有一个元素的情况
        ClearGenList(gl);
    }
}

// 清空广义表
void ClearGenList(GenList &gl)
{
    if(gl == NULL)
        return;

    GLNode *p = gl->tp;
    while(p != NULL)
    {
        if(p->tag == ATOM)
        {
            gl->tp = p->tp;
            free(p);
            p = gl->tp;
        }
        else if(p->tag == CHILDLIST)
        {
            ClearGenList(p->hp);
            p = p->tp;
        }
    }
}

// 摧毁广义表
void DestroyGenList(GenList &gl)
{
    ClearGenList(gl);
    free(gl);
    gl = NULL;
}