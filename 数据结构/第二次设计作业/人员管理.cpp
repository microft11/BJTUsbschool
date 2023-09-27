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

void initList(LinkList &W)  //��ʼ��
{
    W -> next = NULL;  //��ʼ ָ��Ϊ��
}

int input(LinkList &W)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(Worker));
	
	if(!p) return 0;
	else
	{
		printf("������������\n");
		scanf("%s", p -> name);
		getchar();

		printf("�����빤�ţ�\n");
		scanf("%s", p -> num);
		getchar();
		
		printf("������ְλ��\n");
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
		printf("ɾ���ɹ�\n");
	}
	else printf("error!");
	
	return 1;
}


void show(LinkList &W)
{
	LinkList p;
	for(p = W -> next; p; p -> next)
	{
		printf("����:%s   \n", p -> name);
		printf("����:%s   \n", p -> num);
		printf("ְλ:%s   \n", p -> job);
	}
	
}

int main()
{
	LinkList W;
	int a;
	char str[20], str2[20];
	
	printf("�����������\n");
	initList(W);
	
	
	while(scanf("%s", str) != EOF)
	{
		if(!strcmp(str, "input"))
		{
			printf("��������: \n");
			scanf("%d", a);
			while(a --)
			{
				input(W);
			}
		}
		else if(!strcmp(str, "del"))
		{
			printf("����Ҫɾ���Ĺ��ţ�\n");
			scanf("%s", str2);
			del(W, str2);
		}
		else if(!strcmp(str, "show"))
		{
			show(W);
		}
		else printf("error!");
		printf("�����������\n");
	}
	
	return 0;
}





















