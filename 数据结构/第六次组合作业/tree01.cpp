#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#define ElemType char
using namespace std;

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode{
	ElemType Date;
	BinTree Left;
	BinTree Right;
};


//先序建树
BinTree CreateBinTree()
{
    char ch;
    ch = getchar();
    BinTree T;
    
    if(ch == '!') T = NULL;
    else
    {
    	T = (BinTree)malloc(sizeof(TreeNode));
    	T -> Date = ch;
        T -> Left = CreateBinTree();
        T -> Right = CreateBinTree();
	}
	
	return T;
}

//前 
void PreOrderTraverse(BinTree T)
{
	if(T)
	{
		cout << T -> Date << " ";
		PreOrderTraverse(T -> Left);
		PreOrderTraverse(T -> Right);
	}
}

//中
 void InOrderTraverse(BinTree T)
{
	if(T)
	{
		PreOrderTraverse(T -> Left);
		cout << T -> Date << " ";
		PreOrderTraverse(T -> Right);
	}
}

//后
void  PostOrderTraverse(BinTree T)
{
	if(T)
	{
		PreOrderTraverse(T -> Left);
		PreOrderTraverse(T -> Right);
		cout << T -> Date << " ";
	}
}

int main()
{
	BinTree T;
	T = CreateBinTree();
	
    PreOrderTraverse(T);
    cout << endl;
    
    InOrderTraverse(T);
    cout << endl;
    
    PostOrderTraverse(T);
    cout << endl;
    
    system("pause");
}
