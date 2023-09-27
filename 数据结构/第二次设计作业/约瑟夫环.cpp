#include<stdio.h>
#include<stdlib.h>
int count = 0;
int res[7];
typedef struct node* PNode;
struct node {
	int info;
	int key;
	PNode link;
};
typedef struct node* LinkList;
PNode create_node()     //新建结点函数
{
	PNode q = (PNode)malloc(sizeof(struct node));
	if (q == NULL) return NULL;
	else return q;
}
LinkList inti_list(int* key, int n)    //循环链表初始化 
{
	LinkList palist = (LinkList)malloc(sizeof(struct node));
	PNode p;
	int i, j = 1;
	p = create_node();
	if (p)         //初始化每个人所带的密钥值 ，即这个人出队后下一轮的循环次数
	{
		p->key = key[0];
		p->link = NULL;
		palist = p;
	}
	for (i = 1; i < n; i++)
	{
		PNode q = create_node();
		if (q) {
			q->key = key[i];
			p->link = q;
			q->link = NULL;
			p = q;
		}
	}
	if (i == 7) {
		p->link = palist;
	}
	PNode t = palist;
	while (t->link != palist)    //初始化每个人的位置值 
	{
		t->info = j;
		j++;
		t = t->link;
	}
	t->info = 7;
	return palist;
}
void jose_out(LinkList palist, int m, int n)
{
	if (n > 0)
	{
		PNode p = palist;
		for (int i = 0; i < m - 2; i++) p = p->link;  //找即将出队元素的前驱结点p 
		printf("\nout element is %d\n", p->link->info);
		res[count++] = p->link->info;
		int next_m = p->link->key;     //将出队元素的密钥值保留作出队函数的参数，以便下一轮循环
		p->link = p->link->link;
		palist = p->link;
		--n;
		jose_out(palist, next_m, n);
	}
}
int main()
{
	int m = 20;
	int key[7] = { 3,1,7,2,4,8,6 };
	LinkList list = inti_list(key, 7);
	printf("出队过程如下：\n");
	jose_out(list, m, 7);
	printf("\n所以出队顺序为：\n");
	for (int i = 0; i < 7; i++)
	{
		printf("%d\t", res[i]);
	}
}

