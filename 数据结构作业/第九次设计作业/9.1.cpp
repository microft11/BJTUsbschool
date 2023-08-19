#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define ENDKEY 0

typedef int KeyType;

typedef struct  node
{
	KeyType  key ; /*�ؼ��ֵ�ֵ*/
	struct node  *lchild,*rchild;/*����ָ��*/
}BSTNode, *BSTree;

int InsertBST(BSTree *bst, KeyType key)
/*���ڶ����������в����ڹؼ��ֵ���key��Ԫ�أ������Ԫ��*/
{ 
	BSTree s;
	if(*bst==NULL)
	{
		s=(BSTree)malloc(sizeof(BSTNode));
		s->key=key;
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if(key<(*bst)->key)
       InsertBST(&((*bst)->lchild),key);
	else if(key>(*bst)->key)
		InsertBST(&((*bst)->rchild),key);
	return 0;
		//����ɱ������Ĺ���
}

void  CreateBST(BSTree  *bst)
/*�Ӽ�������Ԫ�ص�ֵ��������Ӧ�Ķ���������*/
{ 
	KeyType key;
	*bst=NULL;
    scanf("%d",&key);
	while(key!=ENDKEY)
	{
		InsertBST(bst,key);
		scanf("%d",&key);
	}
	//����ɱ������Ĺ���
}

void  InOrder(BSTree bst)  
/*�������������, rootΪָ�������(��ĳһ����)������ָ��*/
{
	if (bst!=NULL)
	{
		InOrder(bst ->lchild);   /*�������������*/
		printf("%d->",bst->key);        /*���ʸ����*/
		InOrder(bst ->rchild);   /*�������������*/
	}
}

BSTree  SearchBST(BSTree bst, KeyType key)
/*�ڸ�ָ��bst��ָ�����������У��ݹ����ĳ�ؼ��ֵ���key��Ԫ�أ������ҳɹ�������ָ���Ԫ�ؽ��ָ�룬���򷵻ؿ�ָ��*/
{ 
	if(!bst)
	return NULL;
	else if(bst->key==key) 
		return bst;
	else if(bst->key>key)
		return SearchBST(bst->lchild,key);
	else
		return SearchBST(bst->rchild,key);
	//����ɱ������Ĺ���
}
int DelBST(BSTree t, KeyType  k) /*�ڶ���������t��ɾȥ�ؼ���Ϊk�Ľ��*/
{
	BSTNode  *p, *f,*s ,*q;
	p=t; 
	f=NULL;
	while(p)  /*���ҹؼ���Ϊk�Ĵ�ɾ���p*/
	{ 
		if(p->key==k )  break;  /*�ҵ�������ѭ��*/
		f=p;   /*fָ��p����˫�׽��*/
		if(p->key>k)  
			p=p->lchild;
		else 
			p=p->rchild;
	} 
	if(p==NULL)  return 0;  /*���Ҳ���������ԭ���Ķ���������*/
	if(p->lchild==NULL)  /*p��������*/
	{ 
		if(f==NULL) 
			t=p->rchild;  /*p��ԭ�����������ĸ�*/
		else 
			if(f->lchild==p)  /*p��f������*/
				f->lchild=p->rchild ;  /*��p������������f��������*/
			else  /*p��f���Һ���*/
				f->rchild=p->rchild ;  /*��p������������f��������*/
			free(p);  /*�ͷű�ɾ���Ľ��p*/
	}
	else  /*p��������*/
	{ 
		q=p; 
		s=p->lchild;
		while(s->rchild)  /*��p���������в��������½��*/
		{
			q=s; 
			s=s->rchild;
		}
		if(q==p) 
			q->lchild=s->lchild ;  /*��s������������q��*/
		else 
			q->rchild=s->lchild;
		p->key=s->key;  /*��s��ֵ����p*/
		free(s);
	}
	return 1;
}  /*DelBST*/

int main()
{
	BSTree T,p;
	int keyword,temp;
	char ch,j='y';
	T=NULL;
	while(j!='n')
    {
		printf("1.��������������\n");
		printf("2.��ʾ���������\n");
		printf("3.��������\n");
		printf("4.�ڲ������в���һ������\n");
		printf("5.�ڲ�������ɾ��һ������\n");
		printf("6.����������˳�\n");
		scanf(" %c",&ch); //�������ѡ��
		switch(ch)
		{
		case '1':
			printf("���������ݣ���0��Ϊ�������������\n");
			CreateBST(&T);
			break;
		case '2':
			if(!T) printf("������������û�����ݡ�\n");
			else {InOrder(T);printf("\b\b  \n");}
			break;
       case '3':
			printf("��������ҵ�����ֵ:\n");
			scanf("%d",&keyword); //����Ҫ����Ԫ�صĹؼ���
			p=SearchBST(T, keyword);
			if(!p) printf("%d û���ҵ���\n",keyword); //û���ҵ�
			else printf("%d ���ҳɹ���\n",keyword); //�ɹ��ҵ�
			break;
       case '4':
			printf("��������������:");
			scanf("%d",&keyword); //����Ҫ����Ԫ�صĹؼ���
			temp=InsertBST(&T, keyword);
			if(temp==FALSE)
				printf("%d ���ڶ�������!\n",keyword); //��Ԫ���Ѿ�����
			else
				printf("%d ����ɹ���\n",keyword);
			break;
       case '5':
			printf("�����ɾ��������:");
			scanf("%d",&keyword); //����Ҫɾ��Ԫ�صĹؼ���
			temp=DelBST(T, keyword);
			if(temp==FALSE) printf("%d ������!\n",keyword); //��Ԫ�ز�����
			else printf("�ɹ�ɾ��%d\n",keyword); //�ɹ�ɾ��
			break;
       default: 
			j='n';
		}
 }
 printf("�������!\nPress any key to shut off the window!\n");
 getchar();
 getchar();
}

