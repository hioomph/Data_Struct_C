#include"GenList.h"

int main()
{
	GenList gl, glt;
	InitGenList(gl);
	InitGenList(glt);
	
	char *ga = (char *)"(1,2,3)";
	char *gb = (char *)"(1,(2,3))";
	char *gc = (char *)"(1,(2,3),4)";
	char *gd = (char *)"((1,2),3)";
	char *ge = (char *)"((1,2,3))";
	char *gf = (char *)"()";
	char *gg = (char *)"(41,(2,(3,(10,20),4),5),6)";
	char *gh = (char *)"((((41,2),41),1),6,1)";

	CreateGenList(gl, gg);

	printf("gl：");
    ShowGenList(gl);
    printf("\n");

	bool flag = GenListEmpty(gl);
	if(!flag)
		printf("Genlist非空！\n");
	else
		printf("GenList为空！\n");
	
	int length = GenListLength(gl);
	printf("length = %d\n", length);

	int depth = GenListDepth(gl);
	printf("depth = %d\n", depth);

	CopyGenList(gl, glt);
	printf("复制gl后得到的glt为：");
	ShowGenList(glt);
	printf("\n");

	ClearGenList(glt);
	printf("清空glt后得到的glt为：");
	ShowGenList(glt);
    printf("\n");

	printf("gl的表头为：");
	GetHead(gl);
	printf("\n");

	printf("gl的表尾为：");
	GetTail(gl);
	printf("\n");

	InsertFirst(gl, (char *)"((1,2))");
	printf("头插(1,2)后，gl：");
    ShowGenList(gl);
    printf("\n");
	DeleteFirst(gl);	
	printf("头删后，gl：");
    ShowGenList(gl);
    printf("\n");

	
}