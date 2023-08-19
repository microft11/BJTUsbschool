#include<stdio.h>
#include<tchar.h>
#include<stdlib.h> 
#include<time.h>
void fun(char* argv[], int x)
{
	FILE* fp;
	int** data = (int**)malloc(sizeof(int*) * x);       //申请n行动态内存分配空间
	fopen_s(&fp, argv[2],"w");           //文件指针指
	fprintf(fp, "%d\n", x);                 //条数参数
	
	for (int p = 0; p < x; p++)
	{
		data[p] = (int*)malloc(sizeof(int) * 3);   //申请3列动态内存分配空间
	}
	srand((int)time(0));                       //设置随机数种子
	for (int p = 0; p < x; p++)
		for (int q = 0; q < 3; q++)
			data[p][q] = rand() % 100; //产生随机数      
	for (int p = 0; p < x; p++)
	{
		for (int q = 0; q < 3; q++)
			fprintf(fp, "%d,", data[p][q]);  
		fprintf(fp, "\n");
	}
	for (int p = 0; p < x; p++)
		free(data[p]);      //释放内存                            
	free(data);//释放内存
	fclose(fp); //释放文件
}
