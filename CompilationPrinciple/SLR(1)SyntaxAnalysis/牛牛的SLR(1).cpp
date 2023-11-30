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
string s,Head;set<string>Vn,Vt;
map<string, set<string> > Production,Production_simple;
int cnt,num_of_Vn,num_of_Vt;
int GOTO[505][505];
map<string,int>Vnsnum,Vtsnum;
string ACTION[505][505];
map<string,set<string> > Follow;
int IsFinal[505];
map<int,string>Old_to_New;
inline int read()
{
	int x=0,w=0;char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}
int the_num_of_Production;
map<string,int>Num_of_Production;
map<int,string>Num_to_Production;
stack<string>ans_4;
int ans_num=0,NUM=0;
struct info
{
	string op,arg1,arg2,Result;	
}ans[10005];
inline void Make_Pro(string S1,string S2)//S1产生式左部，S2产生式右部，开始加点 
{
	string res="",temp="";
	for (int i=0; i<S2.length(); ++i)
	{
		res=temp+"·"+S2.substr(i);
		Production[S1].insert(res);
		cout<<S1<<"->"<<res<<endl;temp+=S2[i]; 
	}
	Production[S1].insert(res);//Production记录带点的产生式 
	res=temp+"·";cout<<S1<<"->"<<res<<endl; 
	Production_simple[S1].insert(S2);//Production_simple记录原来的产生式 
	Num_of_Production[S1+"->"+S2+"·"]=++the_num_of_Production;
	Num_to_Production[the_num_of_Production]=S1+"->"+S2;
}
inline void Init()//读入文法，记录终结符和非终结符，拓广文法 
{
	int One=0;Vn.insert("A");
	while (cin>>s)
	{
		int position=s.find("->");
		for (int i=0; i<s.length(); ++i)
		if ((s[i]=='-' && s[i+1]=='>') || s[i]=='>' || s[i]=='|') continue;
		else 
		{
			string S="";S+=s[i];
			if (s[i]>='A' && s[i]<='Z') Vn.insert(S); 
			else Vt.insert(S);
		}
		string S1=s.substr(0,position),res="";
		if (!One) {Make_Pro("A",S1);One=1;Head=S1;}
		for (int i=position+2; i<s.length(); ++i)
		if (s[i]=='|')
		{
			Make_Pro(S1,res);
			res="";
		}else res+=s[i];//分割出一堆产生式 
		Make_Pro(S1,res);//进行加点 
	}
	Vt.insert("#");
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++) Vnsnum[*it]=++num_of_Vn;
	for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) Vtsnum[*it]=++num_of_Vt;
}
map<set<string>,int> Have;//记录某集合是否已经出现过 
map<int,set<string> >C;//记录C_? 
map<string,bool> Used[505];//判断该集合是否喂过某一个字母，防止重复喂 
inline int Expand(int num,string S1)//拓广集合，当点后面是非终结符时把非终结符的也进去 
{
	Used[num][S1]=1;
	set<string> res=Production_simple[S1];
	for (set<string>::iterator it=res.begin(); it!=res.end(); it++)
	{
		string S=*it,S2="";S2+=S[0];
		C[num].insert(S1+"->·"+S);
		if (Vn.find(S2)!=Vn.end() && !Used[num][S2]) Expand(num,S2);
		Used[num][S2]=1;
	}
}
inline string Change(int x)
{
	string res="";
	if (!x) return "0";
	while (x) res=(char)(x%10+48)+res,x/=10;
	return res;	
}
inline void Check(int now)
{
	for (set<string>::iterator it=C[now].begin(); it!=C[now].end(); it++)
	{	
		string res=*it;int position=res.find("->");
		string S1=res.substr(0,position);
		if ("A->"+Head+"·"==res) {ACTION[now][Vtsnum["#"]]="ACC";continue;}
		if (Num_of_Production[res]) 
		{
			IsFinal[now]=Num_of_Production[res];
			for (set<string>::iterator it2=Follow[S1].begin(); it2!=Follow[S1].end(); it2++)
			ACTION[now][Vtsnum[*it2]]="r"+Change(Num_of_Production[res]);
		}
	}
}
inline void Make_DFA()//制作那个C_i 
{
	C[0].insert("A->·"+Head);
	Expand(0,Head);int now=0;Have[C[0]]=0;
	while (now<=cnt)
	{
		for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)//喂非终结符 
		{
			string SH=*it;int flag=0;cnt++;
			for (set<string>::iterator it2=C[now].begin(); it2!=C[now].end(); it2++)	
			{
				string res=*it2,temp="",Ned="";int position1=res.find("·"),position2=position1+2; 
				Ned+=res[position2];
				if (Ned!=SH) continue;//看·后边是否是我喂养的非终结符 
				flag=1;
				C[cnt].insert(res.substr(0,position1)+SH+"·"+res.substr(position2+1));
				if (position2!=res.length()-1) 
				{
					temp+=res[position2+1];
					if (Vn.find(temp)==Vn.end()) continue;
					Expand(cnt,temp);
				}
			}
			if (!flag || Have[C[cnt]]) //如果是新的项目集进行记录，如果是旧的进行加边和清除 
			{
				if (flag) GOTO[now][Vnsnum[SH]]=Have[C[cnt]];
				C[cnt].clear();
				for (set<string>::iterator it2=Vn.begin(); it2!=Vn.end(); it2++)
				Used[cnt][*it2]=0;
				for (set<string>::iterator it2=Vt.begin(); it2!=Vt.end(); it2++)
				Used[cnt][*it2]=0;
				cnt--;
			}else Have[C[cnt]]=cnt,GOTO[now][Vnsnum[SH]]=cnt;
		}
		
		for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++)//喂终结符 
		{
			string SL=*it;int flag=0;cnt++;
			for (set<string>::iterator it2=C[now].begin(); it2!=C[now].end(); it2++)	
			{
				string res=*it2,temp="",Ned="";int position1=res.find("·"),position2=position1+2; 
				Ned+=res[position2];
				if (Ned!=SL) continue;
				flag=1;
				C[cnt].insert(res.substr(0,position1)+SL+"·"+res.substr(position2+1));
				if (position2!=res.length()-1) 
				{
					temp+=res[position2+1];
					if (Vn.find(temp)==Vn.end()) continue;
					Expand(cnt,temp);
				}
			}
			if (!flag || Have[C[cnt]]) 
			{
				if (flag) ACTION[now][Vtsnum[SL]]="S"+Change(Have[C[cnt]]);
				C[cnt].clear();
				for (set<string>::iterator it2=Vn.begin(); it2!=Vn.end(); it2++)
				Used[cnt][*it2]=0;
				for (set<string>::iterator it2=Vt.begin(); it2!=Vt.end(); it2++)
				Used[cnt][*it2]=0;
				cnt--;
			}else Have[C[cnt]]=cnt,ACTION[now][Vtsnum[SL]]="S"+Change(cnt);
		}
		Check(now);now++;
	}
}
inline void Get_follow()//由于该文法有左递归用之前方法会死循环 直接读入 
{
	Follow["A"].insert("#");
	Follow["S"].insert("#");
	Follow["E"].insert("#");Follow["E"].insert(")");Follow["E"].insert("+");Follow["E"].insert("-");
	Follow["T"].insert("#");Follow["T"].insert(")");Follow["T"].insert("+");Follow["T"].insert("-");Follow["T"].insert("*");Follow["T"].insert("/");
	Follow["F"].insert("#");Follow["F"].insert(")");Follow["F"].insert("+");Follow["F"].insert("/");Follow["F"].insert("*");Follow["F"].insert("/");
	Follow["V"].insert("=");
}
stack<string>St1;stack<int>St2;//St1是状态栈,St2是符号栈 
inline int CChange(string S)
{
	if (S=="ACC") 
	{
		printf("Succeed!\n");
		for (int i=1; i<ans_num; ++i)
		{
			cout<<"("<<ans[i].op<<","<<ans[i].arg1<<","<<ans[i].arg2<<","<<ans[i].Result<<")"<<endl;	
		}
		exit(0);	
	}
	int res=0;
	for (int i=0; i<S.length(); ++i) 
	if (S[i]>='0' && S[i]<='9') res=res*10+S[i]-'0';
	return res;	
}
inline void Print(int num,string S)//输出状态栈 符号栈 读入字符串 
{
	stack<string>St3;stack<int>St4;
	string S1="",S2="",S3="";
	while (!St1.empty()) St3.push(St1.top()),St1.pop();
	while (!St2.empty()) St4.push(St2.top()),St2.pop();
	while (!St3.empty()) S1+=St3.top(),St1.push(St3.top()),St3.pop();
	for (int i=num+1; i<S.length(); ++i) S3+=S[i];
	while (!St4.empty()) 
	{
		if (St4.top()<=9) S2+=Change(St4.top());
		else S2+="("+Change(St4.top())+")";
		St2.push(St4.top()),St4.pop();
	} 
	cout<<setw(40)<<S2<<setw(25)<<S1<<setw(30)<<S3;
}
inline void Do_it(string S)//进行 分析 
{
	cout<<"分析过程如下:\n"; 
	cout<<"--------------------------------------------------------------------------------------------"<<endl;
	cout<<setw(40)<<"状态栈"<<setw(25)<<"符号栈"<<setw(30)<<"输入串"<<setw(5)<<"ACTION"<<setw(5)<<"GOTO"<<endl; 
	St1.push("#");St2.push(0);
	Print(-1,S);
	for (int i=0; i<S.length(); ++i)
	{
		string res="",Next="";res+=S[i];Next+=S[i+1];St1.push(res);
		if (res!="(" && res!=")") ans_4.push(Old_to_New[i]);//用来存储原来式子符号，用于构建四元组 
		if (Vt.find(res)!=Vt.end()) //非终结符，去调用ACTION 
		{
			if (ACTION[St2.top()][Vtsnum[res]]=="") {printf("Failed!");exit(0);}
			cout<<setw(5)<<ACTION[St2.top()][Vtsnum[res]]<<setw(5)<<" "<<endl; 
			St2.push(CChange(ACTION[St2.top()][Vtsnum[res]]));
		}
		else //终结符去调用GOTO 
		{
			if (!GOTO[St2.top()][Vnsnum[res]]) {printf("Failed!");exit(0);}
			cout<<setw(5)<<" "<<setw(5)<<GOTO[St2.top()][Vnsnum[res]]<<endl;
			St2.push(GOTO[St2.top()][Vnsnum[res]]);
		}
		Print(i,S);
		while (IsFinal[St2.top()] && (ACTION[St2.top()][Vtsnum[Next]].find("r")!=-1 ||ACTION[St2.top()][Vtsnum[Next]]==""))
		{//该状态是个终结状态，并且要看他下一个字符看是直接读入还是当前直接进行规约 
			res=Num_to_Production[IsFinal[St2.top()]];
			string tmp=ACTION[St2.top()][Vtsnum[Next]];
			int position=res.find("->");
			string S1=res.substr(0,position),S2=res.substr(position+2);
			for (int j=0; j<S2.length(); ++j) St1.pop(),St2.pop(); 
			if (S2.length()>1 && S2[S2.length()-1]!=')')
			{
				++ans_num;string Baga="result"+Change(++NUM);
				ans[ans_num].arg2=ans_4.top();ans_4.pop();
				ans[ans_num].op=ans_4.top();ans_4.pop();
				ans[ans_num].arg1=ans_4.top();ans_4.pop();
				ans[ans_num].Result=Baga;
				ans_4.push(Baga);
			}
			St1.push(S1);
			if (Vt.find(S1)!=Vt.end()) cout<<setw(5)<<ACTION[St2.top()][Vtsnum[S1]]<<setw(5)<<" "<<endl,St2.push(CChange(ACTION[St2.top()][Vtsnum[S1]]));
			else cout<<setw(5)<<tmp<<setw(5)<<GOTO[St2.top()][Vnsnum[S1]]<<endl,St2.push(GOTO[St2.top()][Vnsnum[S1]]);
			Print(i,S);
		}
	}
}
int main()
{
	freopen("shiyan5.in","r",stdin);
	Get_follow();
	freopen("5_11.out","w",stdout);
	printf("拓广文法如下：\n");Init();
	cout<<endl;
	Make_DFA();
	for (int i=0; i<=cnt; ++i)
	{
		printf("C%d:\n",i);
		for (set<string>::iterator it=C[i].begin(); it!=C[i].end(); it++)
		cout<<*it<<endl;	
	}
	cout<<setw(5)<<"";
	for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++)
	cout<<setw(5)<<*it;
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	cout<<setw(5)<<*it;
	cout<<endl;
	for (int i=0; i<=cnt; ++i,cout<<endl)
	{
		cout<<setw(5)<<i;
		for (int j=1; j<=num_of_Vt; ++j) 
		cout<<setw(5)<<ACTION[i][j];
		for (int j=1; j<=num_of_Vn; ++j)
		cout<<setw(5)<<GOTO[i][j];
	}
	freopen("5_1.out","r",stdin);
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
			if (mid==L+2 && s[L+1]=='1') 
			{
				shizi_zhen+='i';
				string res="";
				for (int i=mid+1; i<R; ++i) res+=s[i];
				Old_to_New[shizi_zhen.length()-1]=res;
			}
			else  for (int i=mid+1; i<R; ++i) 
			{
				shizi_zhen+=s[i];
				if (s[i]=='(' || s[i]==')') continue;
				string res="";res+=s[i];
				Old_to_New[shizi_zhen.length()-1]=res;
			}
			for (int i=mid+1; i<R; ++i) shizi+=s[i];
			L=R+1;mid=L+1;R=mid+1;if (L==len) break;
			while (s[mid]!=',') mid++;
			while (s[R]!=')' || s[R]==')' && s[R+1]!='(') R++;	
		}
		cout<<"原来表达式："<<shizi<<endl<<"抽象为："<<shizi_zhen<<endl;
		shizi_zhen+='#';Do_it(shizi_zhen);
	}
}

