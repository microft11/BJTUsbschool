#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define ENDKEY 0

typedef int KeyType;

typedef struct  node
{
	KeyType  key ; /*关键字的值*/
	struct node  *lchild,*rchild;/*左右指针*/
}BSTNode, *BSTree;

int InsertBST(BSTree *bst, KeyType key)
/*若在二叉排序树中不存在关键字等于key的元素，插入该元素*/
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
		//请完成本函数的功能
}

void  CreateBST(BSTree  *bst)
/*从键盘输入元素的值，创建相应的二叉排序树*/
{ 
	KeyType key;
	*bst=NULL;
    scanf("%d",&key);
	while(key!=ENDKEY)
	{
		InsertBST(bst,key);
		scanf("%d",&key);
	}
	//请完成本函数的功能
}

void  InOrder(BSTree bst)  
/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{
	if (bst!=NULL)
	{
		InOrder(bst ->lchild);   /*中序遍历左子树*/
		printf("%d->",bst->key);        /*访问根结点*/
		InOrder(bst ->rchild);   /*中序遍历右子树*/
	}
}

BSTree  SearchBST(BSTree bst, KeyType key)
/*在根指针bst所指二叉排序树中，递归查找某关键字等于key的元素，若查找成功，返回指向该元素结点指针，否则返回空指针*/
{ 
	if(!bst)
	return NULL;
	else if(bst->key==key) 
		return bst;
	else if(bst->key>key)
		return SearchBST(bst->lchild,key);
	else
		return SearchBST(bst->rchild,key);
	//请完成本函数的功能
}
int DelBST(BSTree t, KeyType  k) /*在二叉排序树t中删去关键字为k的结点*/
{
	BSTNode  *p, *f,*s ,*q;
	p=t; 
	f=NULL;
	while(p)  /*查找关键字为k的待删结点p*/
	{ 
		if(p->key==k )  break;  /*找到则跳出循环*/
		f=p;   /*f指向p结点的双亲结点*/
		if(p->key>k)  
			p=p->lchild;
		else 
			p=p->rchild;
	} 
	if(p==NULL)  return 0;  /*若找不到，返回原来的二叉排序树*/
	if(p->lchild==NULL)  /*p无左子树*/
	{ 
		if(f==NULL) 
			t=p->rchild;  /*p是原二叉排序树的根*/
		else 
			if(f->lchild==p)  /*p是f的左孩子*/
				f->lchild=p->rchild ;  /*将p的右子树链到f的左链上*/
			else  /*p是f的右孩子*/
				f->rchild=p->rchild ;  /*将p的右子树链到f的右链上*/
			free(p);  /*释放被删除的结点p*/
	}
	else  /*p有左子树*/
	{ 
		q=p; 
		s=p->lchild;
		while(s->rchild)  /*在p的左子树中查找最右下结点*/
		{
			q=s; 
			s=s->rchild;
		}
		if(q==p) 
			q->lchild=s->lchild ;  /*将s的左子树链到q上*/
		else 
			q->rchild=s->lchild;
		p->key=s->key;  /*将s的值赋给p*/
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
		printf("1.创建二叉排序树\n");
		printf("2.显示排序的数据\n");
		printf("3.查找数据\n");
		printf("4.在查找树中插入一个数据\n");
		printf("5.在查找树中删除一个数据\n");
		printf("6.程序结束，退出\n");
		scanf(" %c",&ch); //输入操作选项
		switch(ch)
		{
		case '1':
			printf("请输入数据，以0作为数据输入结束。\n");
			CreateBST(&T);
			break;
		case '2':
			if(!T) printf("二叉排序树中没有数据。\n");
			else {InOrder(T);printf("\b\b  \n");}
			break;
       case '3':
			printf("输入待查找的数据值:\n");
			scanf("%d",&keyword); //输入要查找元素的关键字
			p=SearchBST(T, keyword);
			if(!p) printf("%d 没有找到。\n",keyword); //没有找到
			else printf("%d 查找成功。\n",keyword); //成功找到
			break;
       case '4':
			printf("输入待插入的数据:");
			scanf("%d",&keyword); //输入要插入元素的关键字
			temp=InsertBST(&T, keyword);
			if(temp==FALSE)
				printf("%d 已在二叉树中!\n",keyword); //该元素已经存在
			else
				printf("%d 插入成功！\n",keyword);
			break;
       case '5':
			printf("输入待删除的数据:");
			scanf("%d",&keyword); //输入要删除元素的关键字
			temp=DelBST(T, keyword);
			if(temp==FALSE) printf("%d 不存在!\n",keyword); //该元素不存在
			else printf("成功删除%d\n",keyword); //成功删除
			break;
       default: 
			j='n';
		}
 }
 printf("程序结束!\nPress any key to shut off the window!\n");
 getchar();
 getchar();
}

