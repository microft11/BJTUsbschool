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
PNode create_node()     //�½���㺯��
{
	PNode q = (PNode)malloc(sizeof(struct node));
	if (q == NULL) return NULL;
	else return q;
}
LinkList inti_list(int* key, int n)    //ѭ�������ʼ�� 
{
	LinkList palist = (LinkList)malloc(sizeof(struct node));
	PNode p;
	int i, j = 1;
	p = create_node();
	if (p)         //��ʼ��ÿ������������Կֵ ��������˳��Ӻ���һ�ֵ�ѭ������
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
	while (t->link != palist)    //��ʼ��ÿ���˵�λ��ֵ 
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
		for (int i = 0; i < m - 2; i++) p = p->link;  //�Ҽ�������Ԫ�ص�ǰ�����p 
		printf("\nout element is %d\n", p->link->info);
		res[count++] = p->link->info;
		int next_m = p->link->key;     //������Ԫ�ص���Կֵ���������Ӻ����Ĳ������Ա���һ��ѭ��
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
	printf("���ӹ������£�\n");
	jose_out(list, m, 7);
	printf("\n���Գ���˳��Ϊ��\n");
	for (int i = 0; i < 7; i++)
	{
		printf("%d\t", res[i]);
	}
}

