#include<stdlib.h> 
#include<stdio.h>
#include <string.h>
#include <io.h> 
#include <direct.h>
#include "Lab3_fun.h"
static int rdm(int max, int min) //随机生成有上下限的值，值域为[min, max]
{
	int number;
	number = ((rand() % (max - min + 1)) + min);
	return number;
}

//判断是否为数字 
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
	fopen_s(&fp, "conf.ini", "r");           //将文件指针指向.txt文件
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
		printf("条数?\r\n");
		scanf_s("%s", tmp, MAX_STR_LEN);
		if (is_number(tmp)==1) break;
	}
	printf("是否随机产生条数 0 or 1\r\n");
	scanf_s("%d", &temp);
	if (temp == 0) {
		c->recordcount1 = atoi(tmp);
	}
	else {
		c->recordcount1=rdm(c->recordcount1, c->recordcount2);
	}
}

//百度的函数 检查 文件路径的
int checkFilePath(char* path)  //检查输入的文件路径path是否合法，不合法返回0，合法返回1
{
	//不能以'//'开头
	if (*path == '/')
	{
		return 0;
	}

	//不能以"\\"或"/"结尾，以这两个结尾的话就相当于文件名为空
	char* index1 = strrchr(path, '\\');//strrchr函数用于查找一个字符在一个字符串中末次出现的位置
	char* index2 = strrchr(path, '/');
	if (index1 - path + 1 == strlen(path) || index2 - path + 1 == strlen(path))
	{
		return 0;
	}

	//判断输入的路径是绝对路径还是相对路径
	char* p1 = strstr(path, ":\\"); //strstr函数用于在字符串中查找第一次出现某字符串的位置
	char* p2 = strstr(path, ":/");

	if (p1 || p2) //输入的是绝对路径
	{
		//单独将盘符取出
		char disk[3];
		char* index=NULL;
		if (p1)
		{
			strncpy_s(disk, path, p1 - path + 1);//strncpy函数用于将指定长度的字符串复制到字符数组中
			index = p1;
		}
		if (p2)
		{
			strncpy_s(disk, path, p2 - path + 1);
			index = p2;
		}
		disk[2] = 0;//disk[0]和disk[1]有值

		//判断盘符是否存在
		if (_access(disk, 0) != 0)//access函数用来判断指定的文件或目录是否存在，存在返回0，不存在返回-1
		{
			return 0;
		}

		//将绝对路径盘符后的字符串取出
		int full_len = strlen(path);
		int sub_index = index - path + 2;//从规范盘符位置起算其值为3
		char sub_path[MAX_STR_LEN];
		strncpy_s(sub_path, index + 2, full_len - sub_index);//截取文件路径，数组sub_path[]长度为full_len-sub_index
		sub_path[full_len - sub_index] = 0;//数组sub_path[]从0到full_len-sub_index-1有值

		//判断路径中是否有非法字符
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

//百度的函数 拆分文件路径的
void splitFilePath(CONF* conf, char* path) //对文件路径和文件名进行拆分，然后存储到结构体成员中
{
	//判断输入的路径是绝对路径还是相对路径
	char* p1 = strstr(path, ":\\");//在参数path所指向的字符串中查找第一次出现特定字符串的位置，不包含终止符 '\0'
	char* p2 = strstr(path, ":/"); //绝对路径

	if (p1 || p2) //输入的是绝对路径
	{
		char* index1 = strrchr(path, '\\');//在参数path所指向的字符串中搜索最后一次出现特定字符串的位置，并输出其后字符串
		char* index2 = strrchr(path, '/');
		char* index;

		if (index1 > index2)
		{
			index = index1;//index是带有符号的文件名字符串
		}
		else
		{
			index = index2;
		}

		int full_len = strlen(path);
		int sub_index = index - path + 1;//得到除去文件名的字符串长度
		strncpy_s(conf->filesavepath, path, sub_index);//用于将指定长度的字符串复制到字符数组中
		conf->filesavepath[sub_index] = 0;
		strncpy_s(conf->filename, index + 1, full_len - sub_index);
		conf->filename[full_len - sub_index] = 0;
	}

	else //输入的是相对路径
	{
		char* index1 = strrchr(path, '\\');//在参数path所指向的字符串中搜索最后一次出现特定字符串的位置，并输出其后字符串
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
			//当相对路径中包含目录信息时，将目录信息和文件名信息分别提取
			int full_len = strlen(path);
			int sub_index = index - path + 1;
			strncpy_s(conf->filesavepath, path, sub_index);
			conf->filesavepath[sub_index] = 0;
			strncpy_s(conf->filename, index + 1, full_len - sub_index);
			conf->filename[full_len - sub_index] = 0;
		}
		else
		{
			//当相对路径中不含目录信息时，直接作为文件名处理
			if (!strcmp(path, "no"))
			{
				strcpy_s(path, 10,"test.txt");
				printf("已使用默认文件名:%s\n", conf->filename);
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
		printf("输入路径\r\n");
		scanf_s("%s", tmp, MAX_STR_LEN);
		if (checkFilePath(tmp)) break;
	}
	printf("是否使用默认路径 0 or 1\r\n");
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
	printf("1. 生成数据记录文件（使用二维数组存储）\r\n2. 生成数据记录文件（使用结构体数组存储）\r\n请输入您要执行的功能序号：\r\n");
	scanf_s("%d", &choose);
	if (choose == 1) {
		a = (int**)malloc(sizeof(int*) * x);       //申请n行动态内存分配空间
		for (int i = 0; i < x; i++)
		{
			a[i] = (int*)malloc(sizeof(int) * 3);   //申请3列动态内存分配空间
		}
		                       //设置随机数种子
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				a[i][j] = rdm(c->maxvalue1,c->minvalue1);
			}
			a[i][2] = rdm(c->maxvalue2, c->minvalue2);
		}
	}else if(choose==2){
		//申请n行动态内存分配空间
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
		//不存在目录
		if (_mkdir(c->filesavepath) == -1) {
			exit(0);
		}
	}
	char fullpath[MAX_STR_LEN];
	strcpy_s(fullpath, c->filesavepath);
	strcat_s(fullpath, c->filename);
	FILE* fp;
	fopen_s(&fp, fullpath, "w");           //将文件指针指向.txt文件
	fprintf(fp, "%d\n", x);                 //将条数参数打印到文件中
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
