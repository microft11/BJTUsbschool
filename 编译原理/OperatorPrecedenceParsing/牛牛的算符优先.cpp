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
inline int read()
{
	int x=0,w=0;char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}
map<string, set<string> > FirstVt,LastVt,Chan,From_first,From_last;
string s;
map<string,int> num_Vn, num_Vt;
int Vn_num,Vt_num;
set<string> Vn,Vt;
string tab[505][505];
bool Find_FirstVt[505][505], Find_LastVt[505][505];
map<string,bool> Have;
char Zhan[505];

inline void Do_it(string S)
{
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); ++it)
	{
		string S1=*it;
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); ++it2)
		{
			string S2=*it2,res="";
			for (int i=0; i<S2.length(); ++i) 
			{
				if (S2[i]=='\'') continue;
				if ('A'<=S2[i] && S2[i]<='Z') res+="N";
				else res+=S2[i];
			}
			Have[res]=1;
		}
	}
	Zhan[0]='#';Zhan[1]='\0';int now=0,top=0;
	cout << "------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(20) << "分析栈" << "|" << setw(30) << "剩余输入串" << "|" << setw(25) << "大小关系 |" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
	while (1)
	{
		cout<<"|"<<setw(20)<<Zhan;
		string s="",ss="",res=""; ss+=S[now];
		for (int i=now; i<S.length(); ++i) s+=S[i];
		cout<<"|"<<setw(30)<<s;
		int R=top;s="";s+=Zhan[R];
		while (Vt.find(s)==Vt.end()) s="",s+=Zhan[--R];
		res+=s;res+=tab[num_Vt[s]][num_Vt[ss]];res+=ss;
		cout<<"|"<<setw(25)<<res<<endl;
		if (top==1 && Zhan[0]=='#' && Zhan[1]=='N' && now==S.length()-1) 
		{cout<<"匹配成功！"<<endl;exit(0);}
		if (tab[num_Vt[s]][num_Vt[ss]]=="<" || tab[num_Vt[s]][num_Vt[ss]]=="=")
		{Zhan[++top]=S[now],Zhan[top+1]='\0',now++;continue;}
		string sl="",sr=s;
		int L=R-1;sl+=Zhan[L];
		while (Vt.find(sl)==Vt.end()) sl="",sl+=Zhan[--L];
		while (tab[num_Vt[sl]][num_Vt[sr]]=="=") 
		{
			sr=sl;L--;sl="";sl+=Zhan[L];
			while (Vt.find(sl)==Vt.end()) sl="",sl+=Zhan[--L];
		}
		sl="";
		for (int i=L+1; i<=top; ++i) sl+=Zhan[i];
		if (!Have[sl]) 
		{
			printf("要规约的串形式为：");cout<<sl<<endl;
			printf("未找到符合形式的产生式，匹配出错!\n");exit(0);
		}
		top=L+1;Zhan[top]='N';Zhan[top+1]='\0';
	}
}
int main()
{
	freopen("shiyan4.in","r",stdin); 
//	freopen("4_44.out","w",stdout);
	string Be="";int One=0;
	while (cin>>s)
	{
		int position=s.find("->");
		for (int i=0; i<s.length(); ++i)
		if ((s[i]=='-' && s[i+1]=='>') || s[i]=='>' || s[i]=='|') continue;
		else 
		{
			string S="";S+=s[i];
			if (s[i]>='A' && s[i]<='Z') 
			{
				if (s[i+1]=='\'') S+=s[++i];
				Vn.insert(S);
			}
			else if (S!="^") Vt.insert(S);
		}
		string S1=s.substr(0,position),S2=s.substr(position+2,s.length());
		if (!One) Be=S1,One=1;
		string res="";
		for (int i=0; i<S2.length(); ++i)
		if (S2[i]=='|')
		{
			Chan[S1].insert(res);
			res="";
		}else res+=S2[i];
		Chan[S1].insert(res);
	}
	Vt.insert("#");
	printf("非终结符号集合如下\n");
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++) 
	cout<<*it<<' ',num_Vn[*it]=++Vn_num/*,num_to_Vn[Vn_num]=*it*/;cout<<endl;
	printf("终结符号集合如下：\n"); 
	for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) 
	cout<<*it<<' ',num_Vt[*it]=++Vt_num/*,num_to_Vt[Vt_num]=*it*/;cout<<endl;
	
	//构建firstVT集
	stack<string> StackVn, StackVt;
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;	
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
		{
			string S2=*it2,Xi="",Xii="";int now=0;
			Xi+=S2[0];if (S2[now+1]=='\'') Xi+=S2[++now];
			From_first[Xi].insert(S1);
			if (now+1<S2.length()) {Xii+=S2[++now];if (S2[now+1]=='\'') Xii+=S2[++now];}
			if (Vt.find(Xi)!=Vt.end()) 
			{
				FirstVt[S1].insert(Xi);
				if (Find_FirstVt[num_Vn[S1]][num_Vt[Xi]]==0)
				Find_FirstVt[num_Vn[S1]][num_Vt[Xi]]=1,StackVn.push(S1),StackVt.push(Xi);
			}
			else if (Vn.find(Xi)!=Vn.end() && Vt.find(Xii)!=Vt.end()) 
			{
				FirstVt[S1].insert(Xii);
				if (Find_FirstVt[num_Vn[S1]][num_Vt[Xii]]==0)
				Find_FirstVt[num_Vn[S1]][num_Vt[Xii]]=1,StackVn.push(S1),StackVt.push(Xii);
			}
		}
	} 
	while (!StackVn.empty())
	{
		string V=StackVn.top(),b=StackVt.top();StackVn.pop();StackVt.pop();
		for (set<string>::iterator it=From_first[V].begin(); it!=From_first[V].end(); it++)
		{
			string U=*it;
			if (!Find_FirstVt[num_Vn[U]][num_Vt[b]]) 
			{
				Find_FirstVt[num_Vn[U]][num_Vt[b]]=1;
				StackVn.push(U);StackVt.push(b);
			}
		}
	}
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;
		for (set<string>::iterator it2=Vt.begin(); it2!=Vt.end(); it2++)
		{
			string S2=*it2;
			if (Find_FirstVt[num_Vn[S1]][num_Vt[S2]]) FirstVt[S1].insert(S2);
		}
	}
	printf("各非终结符FirstVt集如下：\n"); 
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;cout<<*it<<":"<<' ';
		for (set<string>::iterator it2=FirstVt[S1].begin(); it2!=FirstVt[S1].end(); it2++)
		{
			cout<<*it2<<' ';
		}cout<<endl;
	} 
	
	
	//构造lastVt集合
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;	
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
		{
			string S2=*it2,Xi="",Xii="";int now=S2.length()-1;
			if (S2[now]=='\'') Xii+=S2[--now],Xii+=S2[now+1];else Xii+=S2[now];
			From_last[Xii].insert(S1);
			if (now) {now--;if (S2[now]=='\'') Xi+=S2[now-1],Xi+=S2[now];else Xi+=S2[now];}
			if (Vt.find(Xii)!=Vt.end())
			{
				LastVt[S1].insert(Xii);
				if (!Find_LastVt[num_Vn[S1]][num_Vt[Xii]])
				Find_LastVt[num_Vn[S1]][num_Vt[Xii]]=1,StackVn.push(S1),StackVt.push(Xii);
			}
			else if (Vt.find(Xi)!=Vt.end() && Vn.find(Xii)!=Vn.end())
			{
				LastVt[S1].insert(Xi);
				if (!Find_LastVt[num_Vn[S1]][num_Vt[Xi]])
				Find_LastVt[num_Vn[S1]][num_Vt[Xi]]=1,StackVn.push(S1),StackVt.push(Xi);
			}
		}
	} 
	while (!StackVn.empty())
	{
		string V=StackVn.top(),b=StackVt.top();StackVn.pop();StackVt.pop();
		for (set<string>::iterator it=From_last[V].begin(); it!=From_last[V].end(); it++)
		{
			string U=*it;
			if (!Find_LastVt[num_Vn[U]][num_Vt[b]]) 
			{
				Find_LastVt[num_Vn[U]][num_Vt[b]]=1;
				StackVn.push(U);StackVt.push(b);
			}
		}
	}
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;
		for (set<string>::iterator it2=Vt.begin(); it2!=Vt.end(); it2++)
		{
			string S2=*it2;
			if (Find_LastVt[num_Vn[S1]][num_Vt[S2]]) LastVt[S1].insert(S2);
		}
	}
	printf("各非终结符LastVt集如下：\n"); 
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;cout<<*it<<":"<<' ';
		for (set<string>::iterator it2=LastVt[S1].begin(); it2!=LastVt[S1].end(); it2++)
		{
			cout<<*it2<<' ';
		}cout<<endl;
	} 
	
	//制作算符优先分析表 
	tab[num_Vt["#"]][num_Vt["#"]]="=";
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;	
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
		{
			string S2=*it2;
			for (int i=0; i<S2.length()-1; ++i)
			{
				string Xi="",Xii="";
				Xi+=S2[i];if (S2[i+1]=='\'') Xi+=S2[++i];
				if (i==S2.length()-1) break;
				Xii+=S2[i+1];if (i+2<S2.length() && S2[i+2]=='\'') Xii+=S2[i+2]; 
				if (Vt.find(Xi)!=Vt.end() && Vt.find(Xii)!=Vt.end()) tab[num_Vt[Xi]][num_Vt[Xii]]="=";
				if (i<S2.length()-2)
				{
					string Xiii="";Xiii+=S2[i+2];
					if (Vn.find(Xii)!=Vn.end() && Vt.find(Xiii)!=Vt.end())
					tab[num_Vt[Xi]][num_Vt[Xiii]]="="; 	
				}
				if (Vt.find(Xi)!=Vt.end() && Vn.find(Xii)!=Vn.end()) 
				{
					for (set<string>::iterator it3=FirstVt[Xii].begin(); it3!=FirstVt[Xii].end(); it3++)
					tab[num_Vt[Xi]][num_Vt[*it3]]="<";
				}
				if (Vn.find(Xi)!=Vn.end() && Vt.find(Xii)!=Vt.end())
				{
					for (set<string>::iterator it3=LastVt[Xi].begin(); it3!=LastVt[Xi].end(); it3++)
					tab[num_Vt[*it3]][num_Vt[Xii]]=">";
				}
			}
		}
	}
	for (set<string>::iterator it3=FirstVt[Be].begin(); it3!=FirstVt[Be].end(); it3++)
	tab[num_Vt["#"]][num_Vt[*it3]]="<";
	for (set<string>::iterator it3=LastVt[Be].begin(); it3!=LastVt[Be].end(); it3++)
	tab[num_Vt[*it3]][num_Vt["#"]]=">";
	
	
	cout<<"----------------------------算符优先分析表-------------------------------"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"\t|";
    for(set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) cout << *it << "\t|";
    cout<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    set<string>::iterator it=Vt.begin();
    for (int i = 1; i <=Vt.size(); i++, it++) 
	{
        cout<<*it<<"\t|";
        for(int j=1; j<=Vt.size(); j++) cout<<tab[i][j]<<"\t|";
        cout<<endl;
        cout<<"-------------------------------------------------------------------------";
        cout<<endl;
    }
    
    //准备进行匹配
	freopen("4_4.out","r",stdin);
	char s[505];
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
		cout<<"原来表达式："<<shizi<<endl<<"抽象为："<<shizi_zhen<<endl;
		shizi_zhen+='#';Do_it(shizi_zhen);
	} 
}

