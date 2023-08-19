#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
#define STACKINITSIZE 20//栈初始空间大小
#define INCREASEMENT 10//栈空间大小的增量
using namespace std;

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode
{
	ElemType Date;
	BinTree Left;
	BinTree Right;
};

typedef struct SqStack
{
	BinTree base;
	BinTree top;
	int stacksize;
}SqStack;

void InitStack(SqStack &S)
{
	S.base = (BinTree)malloc(STACKINITSIZE * sizeof(TreeNode));
	
	S.top = S.base;
	S.stacksize = STACKINITSIZE;
}

void Push(SqStack &S, TreeNode e)
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (BinTree)realloc(S.base,(STACKINITSIZE + INCREASEMENT) * sizeof(TreeNode));

		S.stacksize = 30;
	}
	*S.top = e;
	S.top ++;
}

void Pop(SqStack &S,TreeNode &e)
{
	S.top --;
	e = *S.top;
}

bool is_Empty(SqStack S)
{
	if(S.base == S.top)
		return true;
	else
		return false;
}

//先序建树
BinTree CreateBinTree(BinTree &T)
{
    char ch;
    scanf("%c", &ch);
    
    if(ch == '!') T = NULL;
    else
    {
    	T = (BinTree)malloc(sizeof(TreeNode));
    	T -> Date = ch;
        CreateBinTree(T -> Left);
        CreateBinTree(T -> Right);
	}
	
	return T;
}

void InOrderTraverse(BinTree BT)
{
	BinTree T = BT;
	SqStack S;
	InitStack(S);
	
	TreeNode e; 
	while(T || is_Empty(S))
	{
		while(T)
		{
			Push(S, *T);
			T = T -> Left;
		}
		if(!is_Empty(S))
		{
			Pop(S,e);
			printf("%c", e.Date);
			T = e.Right;
		}
	}
}

int main()
{
	BinTree T = NULL;
	printf("请输入二叉树-按照先序序列建立二叉树\n");
	CreateBinTree(T);
	printf("中序遍历二叉树结果为：\n");
	InOrderTraverse(T);
	return 0;
}

