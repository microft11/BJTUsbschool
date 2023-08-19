#include<stdlib.h> 
#include<stdio.h>
#include <string.h>
#include <io.h> 
#include <direct.h>
#include "Lab3_fun.h"
static int rdm(int max, int min) //��������������޵�ֵ��ֵ��Ϊ[min, max]
{
	int number;
	number = ((rand() % (max - min + 1)) + min);
	return number;
}

//�ж��Ƿ�Ϊ���� 
int is_number(char* str)
{
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] < '0' || str[i]>'9') {
			return -1;
		}
	}
	return 1;
}

void read_conf(CONF* c)
{
	FILE* fp;
	fopen_s(&fp, "conf.ini", "r");           //���ļ�ָ��ָ��.txt�ļ�
	fscanf_s(fp, "%s", c->filesavepath, MAX_STR_LEN);
	fscanf_s(fp, "%s", c->filename, MAX_STR_LEN);
	fscanf_s(fp, "%d", &c->number);
	fscanf_s(fp, "%d", &c->minvalue1);
	fscanf_s(fp, "%d", &c->maxvalue1);
	fscanf_s(fp, "%d", &c->minvalue2);
	fscanf_s(fp, "%d", &c->maxvalue2);
	fscanf_s(fp, "%d", &c->recordcount1);
	fscanf_s(fp, "%d", &c->recordcount2);
	fclose(fp);
}

void recourcount(CONF* c)
{
	char tmp[MAX_STR_LEN];
	int temp;
	while (1) {
		printf("����?\r\n");
		scanf_s("%s", tmp, MAX_STR_LEN);
		if (is_number(tmp)==1) break;
	}
	printf("�Ƿ������������ 0 or 1\r\n");
	scanf_s("%d", &temp);
	if (temp == 0) {
		c->recordcount1 = atoi(tmp);
	}
	else {
		c->recordcount1=rdm(c->recordcount1, c->recordcount2);
	}
}

//�ٶȵĺ��� ��� �ļ�·����
int checkFilePath(char* path)  //���������ļ�·��path�Ƿ�Ϸ������Ϸ�����0���Ϸ�����1
{
	//������'//'��ͷ
	if (*path == '/')
	{
		return 0;
	}

	//������"\\"��"/"��β������������β�Ļ����൱���ļ���Ϊ��
	char* index1 = strrchr(path, '\\');//strrchr�������ڲ���һ���ַ���һ���ַ�����ĩ�γ��ֵ�λ��
	char* index2 = strrchr(path, '/');
	if (index1 - path + 1 == strlen(path) || index2 - path + 1 == strlen(path))
	{
		return 0;
	}

	//�ж������·���Ǿ���·���������·��
	char* p1 = strstr(path, ":\\"); //strstr�����������ַ����в��ҵ�һ�γ���ĳ�ַ�����λ��
	char* p2 = strstr(path, ":/");

	if (p1 || p2) //������Ǿ���·��
	{
		//�������̷�ȡ��
		char disk[3];
		char* index=NULL;
		if (p1)
		{
			strncpy_s(disk, path, p1 - path + 1);//strncpy�������ڽ�ָ�����ȵ��ַ������Ƶ��ַ�������
			index = p1;
		}
		if (p2)
		{
			strncpy_s(disk, path, p2 - path + 1);
			index = p2;
		}
		disk[2] = 0;//disk[0]��disk[1]��ֵ

		//�ж��̷��Ƿ����
		if (_access(disk, 0) != 0)//access���������ж�ָ�����ļ���Ŀ¼�Ƿ���ڣ����ڷ���0�������ڷ���-1
		{
			return 0;
		}

		//������·���̷�����ַ���ȡ��
		int full_len = strlen(path);
		int sub_index = index - path + 2;//�ӹ淶�̷�λ��������ֵΪ3
		char sub_path[MAX_STR_LEN];
		strncpy_s(sub_path, index + 2, full_len - sub_index);//��ȡ�ļ�·��������sub_path[]����Ϊfull_len-sub_index
		sub_path[full_len - sub_index] = 0;//����sub_path[]��0��full_len-sub_index-1��ֵ

		//�ж�·�����Ƿ��зǷ��ַ�
		if (strstr(sub_path, ":") || strstr(sub_path, "*") || strstr(sub_path, "?") || strstr(sub_path, "\"") || strstr(sub_path, "<") || strstr(sub_path, ">") || strstr(sub_path, "|"))
		{
			return 0;
		}
	}
	else
	{
		if (strstr(path, ":") || strstr(path, "*") || strstr(path, "?") || strstr(path, "\"") || strstr(path, "<") || strstr(path, ">") || strstr(path, "|"))
		{
			return 0;
		}
	}
	return 1;
}

//�ٶȵĺ��� ����ļ�·����
void splitFilePath(CONF* conf, char* path) //���ļ�·�����ļ������в�֣�Ȼ��洢���ṹ���Ա��
{
	//�ж������·���Ǿ���·���������·��
	char* p1 = strstr(path, ":\\");//�ڲ���path��ָ����ַ����в��ҵ�һ�γ����ض��ַ�����λ�ã���������ֹ�� '\0'
	char* p2 = strstr(path, ":/"); //����·��

	if (p1 || p2) //������Ǿ���·��
	{
		char* index1 = strrchr(path, '\\');//�ڲ���path��ָ����ַ������������һ�γ����ض��ַ�����λ�ã����������ַ���
		char* index2 = strrchr(path, '/');
		char* index;

		if (index1 > index2)
		{
			index = index1;//index�Ǵ��з��ŵ��ļ����ַ���
		}
		else
		{
			index = index2;
		}

		int full_len = strlen(path);
		int sub_index = index - path + 1;//�õ���ȥ�ļ������ַ�������
		strncpy_s(conf->filesavepath, path, sub_index);//���ڽ�ָ�����ȵ��ַ������Ƶ��ַ�������
		conf->filesavepath[sub_index] = 0;
		strncpy_s(conf->filename, index + 1, full_len - sub_index);
		conf->filename[full_len - sub_index] = 0;
	}

	else //����������·��
	{
		char* index1 = strrchr(path, '\\');//�ڲ���path��ָ����ַ������������һ�γ����ض��ַ�����λ�ã����������ַ���
		char* index2 = strrchr(path, '/');
		char* index;

		if (index1 > index2)
		{
			index = index1;
		}
		else
		{
			index = index2;
		}

		if (index)
		{
			//�����·���а���Ŀ¼��Ϣʱ����Ŀ¼��Ϣ���ļ�����Ϣ�ֱ���ȡ
			int full_len = strlen(path);
			int sub_index = index - path + 1;
			strncpy_s(conf->filesavepath, path, sub_index);
			conf->filesavepath[sub_index] = 0;
			strncpy_s(conf->filename, index + 1, full_len - sub_index);
			conf->filename[full_len - sub_index] = 0;
		}
		else
		{
			//�����·���в���Ŀ¼��Ϣʱ��ֱ����Ϊ�ļ�������
			if (!strcmp(path, "no"))
			{
				strcpy_s(path, 10,"test.txt");
				printf("��ʹ��Ĭ���ļ���:%s\n", conf->filename);
			}
			strcpy_s(conf->filename, path);
		}
	}
	//fixFileName(conf);
}

void recourpath(CONF* c)
{
	char tmp[MAX_STR_LEN];
	int temp;
	while (1) {
		printf("����·��\r\n");
		scanf_s("%s", tmp, MAX_STR_LEN);
		if (checkFilePath(tmp)) break;
	}
	printf("�Ƿ�ʹ��Ĭ��·�� 0 or 1\r\n");
	scanf_s("%d", &temp);
	if (temp == 0) {
		splitFilePath(c, tmp);
	}
}

void function(CONF* c)
{
	int choose;
	int** a=NULL;
	DATAITEM* b = NULL;
	int x = c->recordcount1;
	printf("1. �������ݼ�¼�ļ���ʹ�ö�ά����洢��\r\n2. �������ݼ�¼�ļ���ʹ�ýṹ������洢��\r\n��������Ҫִ�еĹ�����ţ�\r\n");
	scanf_s("%d", &choose);
	if (choose == 1) {
		a = (int**)malloc(sizeof(int*) * x);       //����n�ж�̬�ڴ����ռ�
		for (int i = 0; i < x; i++)
		{
			a[i] = (int*)malloc(sizeof(int) * 3);   //����3�ж�̬�ڴ����ռ�
		}
		                       //�������������
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				a[i][j] = rdm(c->maxvalue1,c->minvalue1);
			}
			a[i][2] = rdm(c->maxvalue2, c->minvalue2);
		}
	}else if(choose==2){
		//����n�ж�̬�ڴ����ռ�
		b = (DATAITEM*)malloc(sizeof(DATAITEM) * x);
		for (int i = 0; i < x; i++)
		{
			b[i].item1 = rdm(c->maxvalue1, c->minvalue1);
			while (1) {
				b[i].item2 = rdm(c->maxvalue1, c->minvalue1);
				if (b[i].item1 != b[i].item2)break;
			}
			b[i].item3 = rdm(c->maxvalue2, c->minvalue2);
		}
	}
	if (_access(c->filesavepath, 0)==-1) {
		//������Ŀ¼
		if (_mkdir(c->filesavepath) == -1) {
			exit(0);
		}
	}
	char fullpath[MAX_STR_LEN];
	strcpy_s(fullpath, c->filesavepath);
	strcat_s(fullpath, c->filename);
	FILE* fp;
	fopen_s(&fp, fullpath, "w");           //���ļ�ָ��ָ��.txt�ļ�
	fprintf(fp, "%d\n", x);                 //������������ӡ���ļ���
	if (choose == 1) {
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				fprintf(fp, "%d,", a[i][j]);
			}
			fprintf(fp, "\n");
		}
	}
	else {
		for (int i = 0; i < x; i++)
		{
			fprintf(fp, "%d,%d,%d\n", b[i].item1,  b[i].item2, b[i].item3);
		}
	}
	fclose(fp);
}
