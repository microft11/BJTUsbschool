#include<iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <iomanip>
#include <stack>
#define Re register int
using namespace std;
char s[505];int now;
inline int read()
{
	int x=0,w=0;char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}
inline void F();
inline void E();
inline void T();
inline void M()
{
	if (s[now]=='*' || s[now]=='/') now++;
	else {printf("error in M\n");exit(0);}	
}
inline void A()
{
	if (s[now]=='+' || s[now]=='-') now++;
	else {printf("error in A\n");exit(0);} 	
}
inline void T2()
{
	if (s[now]=='+' || s[now]=='-' || s[now]==')' || s[now]=='#') return;
	if (s[now]!='*' && s[now]!='/') {printf("error in T2\n");exit(0);}M();F();T2();
}
inline void F()
{
	if (s[now]=='i') {now++;return;}
	if (s[now]!='(') {printf("error in F\n");exit(0);}now++;E();
	if (s[now]!=')') {printf("error in F\n");exit(0);}now++;
}
inline void E2()
{
	if (s[now]==')' || s[now]=='#') return;
	if (s[now]!='+' && s[now]!='-') {printf("error in E2\n");exit(0);}A();
	if (s[now]!='(' && s[now]!='i') {printf("error in E2\n");exit(0);}T();
	if (s[now]==')' || s[now]=='#') return;
	if (s[now]!='+' && s[now]!='-') {printf("error in E2\n");exit(0);}E2();
}
inline void T()
{
	if (s[now]!='(' && s[now]!='i') {printf("error in F\n");exit(0);}F();
	if (s[now]=='+' || s[now]=='-' || s[now]==')' || s[now]=='#') return;	
	if (s[now]!='*' && s[now]!='/') {printf("error in F\n");exit(0);}T2();
}
inline void E()
{
	if (s[now]!='(' && s[now]!='i') {printf("error in E\n");exit(0);}T();
	if (s[now]==')' || s[now]=='#') return; 
	if (s[now]!='+' && s[now]!='-') {printf("error in E\n");exit(0);}E2();
}
inline void V()
{
	if (s[now]=='i') ++now;
	else {printf("error in V\n");exit(0);} 
}
inline void S()
{
	if (s[now]=='i') 
	{
		V();if (s[now]=='=') ++now,E();
		else {printf("error in S\n");exit(0);} 
	}
	else {printf("error in S\n");exit(0);} 
}
int main()
{
	freopen("8.out","r",stdin);
	freopen("88.out","w",stdout);
	while (scanf("%s",s)!=EOF)
	{
		int len=strlen(s),L=0,mid,R;s[len]='(';	
		string shizi="",shizi_zhen="";
		for (int i=0; i<len; ++i)
		{
			if (s[i]==',') mid=i;
			if (s[i]==')' && s[i+1]=='(') {R=i;break;}
		}
		while (L<len)
		{
			if (mid==L+2 && s[L+1]=='1') shizi_zhen+='i';
			else  for (int i=mid+1; i<R; ++i) shizi_zhen+=s[i];
			for (int i=mid+1; i<R; ++i) shizi+=s[i];
			L=R+1;mid=L+1;R=mid+1;if (L==len) break;
			while (s[mid]!=',') mid++;
			while (s[R]!=')' || s[R]==')' && s[R+1]!='(') R++;	
		}
		cout<<shizi<<endl<<shizi_zhen<<endl;
		shizi_zhen+='#';
		for(int i=0; i<shizi_zhen.length(); ++i) s[i]=shizi_zhen[i];
		s[shizi_zhen.length()]='\0';now=0;
		S();
	}
	if (s[now]=='#') printf("���Ϸ�\n");else printf("error!"); 
}

