#include<stdio.h>
#include<tchar.h>
#include<stdlib.h> 
#include<time.h>
void fun(char* argv[], int x)
{
	FILE* fp;
	int** data = (int**)malloc(sizeof(int*) * x);       //����n�ж�̬�ڴ����ռ�
	fopen_s(&fp, argv[2],"w");           //�ļ�ָ��ָ
	fprintf(fp, "%d\n", x);                 //��������
	
	for (int p = 0; p < x; p++)
	{
		data[p] = (int*)malloc(sizeof(int) * 3);   //����3�ж�̬�ڴ����ռ�
	}
	srand((int)time(0));                       //�������������
	for (int p = 0; p < x; p++)
		for (int q = 0; q < 3; q++)
			data[p][q] = rand() % 100; //���������      
	for (int p = 0; p < x; p++)
	{
		for (int q = 0; q < 3; q++)
			fprintf(fp, "%d,", data[p][q]);  
		fprintf(fp, "\n");
	}
	for (int p = 0; p < x; p++)
		free(data[p]);      //�ͷ��ڴ�                            
	free(data);//�ͷ��ڴ�
	fclose(fp); //�ͷ��ļ�
}
