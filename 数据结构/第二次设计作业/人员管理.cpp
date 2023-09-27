#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Worker
{
	char name[20];
	char num[10];
	char job[20];
	struct Worker * next;
}Worker, *LinkList;

void initList(LinkList &W)  //初始化
{
    W -> next = NULL;  //初始 指针为空
}

int input(LinkList &W)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(Worker));
	
	if(!p) return 0;
	else
	{
		printf("请输入姓名：\n");
		scanf("%s", p -> name);
		getchar();

		printf("请输入工号：\n");
		scanf("%s", p -> num);
		getchar();
		
		printf("请输入职位：\n");
		scanf("%s", p -> job);
		getchar();
		
	}
	
	p -> next = W -> next;
	W -> next = p;
	
	return 0;
}

int del(LinkList &W, char num[10])
{
	Worker *p, *q;
	p = W -> next;
	q = W;
	while(!(strcmp(p->num,num)==0)&&p)
	{
		q = p;
		p = p -> next;
	}
	if(p)
	{
		q -> next = p -> next;
		free(p);
		printf("删除成功\n");
	}
	else printf("error!");
	
	return 1;
}


void show(LinkList &W)
{
	LinkList p;
	for(p = W -> next; p; p -> next)
	{
		printf("姓名:%s   \n", p -> name);
		printf("工号:%s   \n", p -> num);
		printf("职位:%s   \n", p -> job);
	}
	
}

int main()
{
	LinkList W;
	int a;
	char str[20], str2[20];
	
	printf("请输入操作：\n");
	initList(W);
	
	
	while(scanf("%s", str) != EOF)
	{
		if(!strcmp(str, "input"))
		{
			printf("输入人数: \n");
			scanf("%d", a);
			while(a --)
			{
				input(W);
			}
		}
		else if(!strcmp(str, "del"))
		{
			printf("输入要删除的工号：\n");
			scanf("%s", str2);
			del(W, str2);
		}
		else if(!strcmp(str, "show"))
		{
			show(W);
		}
		else printf("error!");
		printf("请输入操作：\n");
	}
	
	return 0;
}





















