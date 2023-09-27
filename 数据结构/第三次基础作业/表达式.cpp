#include<iostream>
#include<stdlib.h>
using namespace std;
#define maxsize 100

int flag = 0;
char useless;

//定义顺序表
typedef struct {
	string s;
	int length;
}SeqList;

//定义栈 
typedef struct {
	int top;
	char elem[maxsize];
}Stack;

void initList(SeqList& L)
{
	L.length = 0;
}

void initStack(Stack& S)
{
	S.top = -1;
}

void createList(SeqList& L)
{
	cin >> L.s;
	L.length = L.s.length();
}

//入栈 
bool push(Stack &S, char ch)
{
	if(S.top == maxsize - 1) return false;
	S.top ++;
	S.elem[S.top] = ch;
}

//出栈
bool pop(Stack &S, char &ch)
{
	if(S.top == -1) return false;
	ch = S.elem[S.top];
	S.top --;
	return true;
} 

bool is_empty(Stack S)
{
	if(S.top == -1) return true;
	else return false;
}

char top_elem(Stack S)
{
	return S.elem[S.top];
}

void matchBracket(Stack& S, char lbracket)
{
	while(S.elem[S.top] != lbracket) pop(S, useless);
	pop(S, useless);
	flag --;
}

bool checkExp(SeqList L, Stack S)
{
	int i = 0;
	int count = L.length;
	
	while(count --)
	{
		if(L.s[i] >= '0' && L.s[i] <= '9')
		{
			i ++;
			continue;
		}
		else
		{
			if(L.s[i] == '(' || L.s[i] == '[' || L.s[i] == '{')
			{
				push(S, L.s[i]);
				flag ++;
			}
			else if(L.s[i] == '+' || L.s[i] == '-' || L.s[i] == '*' || L.s[i] == '/')
			{
				char top = top_elem(S);
				if(top == '+' || top == '-' || top == '*' || top == '/')
				{
					pop(S, useless);
				}
				else
				{
					push(S, L.s[i]);
				}
			} 
			else if(L.s[i] == ')' || L.s[i] == ']' || L.s[i] == '}')
			{
				if(flag > 0)
				{
					if(L.s[i] == ')') matchBracket(S, '(');
					else if(L.s[i] == ']') matchBracket(S, '[');
					else matchBracket(S, '{');
				}
				else return false;
			}
			else 
			{
			    puts("ERROR!");
			    return false;
			}
		}
		i ++; 
	}
	if(is_empty(S)) return true;
	else
	{
		char top = top_elem(S);
		if (top == '+' || top == '-' || top == '*' || top == '/') return true;
		else return false;
	}
}


int main()
{
	SeqList l;
	Stack s;
	
	initList(l);
	initStack(s);
	createList(l);
	
	if(checkExp(l, s))  cout << "yes" << endl;
	else cout << "no" << endl;
	
	return 0;
}


























