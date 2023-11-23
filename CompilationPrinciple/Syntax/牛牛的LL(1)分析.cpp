#include <iostream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

string s, Be;
int Fir;
map<string, set<string>> First, Follow, Chan;
map<string, bool> Using;
set<string> Vn, Vt;
string tab[505][505];
map<string,int> num_Vn, num_Vt;
int Vn_num, Vt_num;

inline int read()
{
    int x = 0, w = 0;  
    char ch = 0;      

    while (!isdigit(ch))
        w |= (ch == '-'), ch = getchar();

    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();

    return w ? -x : x;
}

/*first集，非终结符可以推出的所有终结符*/
inline void Find_First(string S1)
{
    if (Using[S1]) return; // 如果已经计算过S1的First集，直接返回

    for (set<string>::iterator it2 = Chan[S1].begin(); it2 != Chan[S1].end(); it2++)
    {
        string S2 = *it2;  // 获取产生式右侧的字符串
        bool All = true;
        if (S2 == "^")  // 如果产生式右侧是空串，将空串加入S1的First集
            First[S1].insert(S2);
        else
        {
            for (int i = 0; i < S2.length(); ++i)
            {
                bool flag = false;
                string SS = "";
                SS += S2[i];
                if (i + 1 < S2.length() && S2[i + 1] == '\'')
                    SS += S2[++i];  // 考虑产生式右侧的非终结符带撇号的情况

                Find_First(SS);  // 递归计算SS的First集

                for (set<string>::iterator it3 = First[SS].begin(); it3 != First[SS].end(); it3++)
                {
                    if (*it3 == "^")
                        flag = true;
                    else
                        First[S1].insert(*it3);  // 将SS的First集加入S1的First集
                }

                if (!flag)
                {
                    All = false;
                    break;  // 如果SS的First集不含空串，则退出循环
                }
            }

            if (All)
                First[S1].insert("^");  // 如果所有SS都能推导出空串，将空串加入S1的First集
        }
    }

    Using[S1] = true;  // 标记S1的First集已经计算过
}

inline void Finding_First(string S2) 
{
    if (Using[S2]) return;  // 如果已经计算过S2的First集，直接返回
    bool All = true;

    for (int i = 0; i < S2.length(); ++i) 
    {
        bool flag = false;
        string SS = "";
        SS += S2[i];
        if (i + 1 < S2.length() && S2[i + 1] == '\'')
            SS += S2[++i];  // 考虑产生式右侧的非终结符带撇号的情况

        for (set<string>::iterator it3 = First[SS].begin(); it3 != First[SS].end(); it3++)
        {
            if (*it3 == "^")
                flag = true;
            else
                First[S2].insert(*it3);  // 将SS的First集加入S2的First集
        }

        if (!flag)
        {
            All = false;
            break;  // 如果SS的First集不含空串，则退出循环
        }
    }

    if (All)
        First[S2].insert("^");  // 如果所有SS都能推导出空串，将空串加入S2的First集
    
    Using[S2] = 1;  // 标记S2的First集已经计算过
}

/*初始化一个栈 Stack，将终结符 # 和文法的起始符号 S 入栈。
进入一个循环，每次循环迭代都输出当前的分析栈、剩余输入串和分析表中使用的产生式。
根据 LL(1) 分析表的内容，不断从分析栈中取出符号，与输入串当前位置的符号进行匹配，并根据产生式进行推导。
如果推导出了产生式右侧的符号串，将这些符号按逆序入栈，模拟推导过程。
如果匹配失败，输出错误信息，并结束分析*/
inline void Do_it(string S)
{
	vector<string> Stack;
	int now=0;
	Stack.push_back("#"); Stack.push_back("S");
	cout << "------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(20) << "分析栈" << "|" << setw(30) << "剩余输入串" << "|" << setw(25) << "分析表中产生 |" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    while(1)
	{
		string s="";
		for (int i=0; i<Stack.size(); ++i) s+=Stack[i];
		cout<< "|"<<setw(20)<<s;
		s="";
		for (int i=now; i<S.length(); ++i) s+=S[i];
		cout<<"|"<<setw(30)<<s;
		string Xm=Stack[Stack.size()-1],Ai="";Ai+=S[now];
		if (Vn.find(Xm)!=Vn.end())
		{
			if (tab[num_Vn[Xm]][num_Vt[Ai]]=="") 
			{
				string res="error!";
				cout.width(25);cout<<res<<endl;exit(0);
			}
			Stack.pop_back();
			string temp=tab[num_Vn[Xm]][num_Vt[Ai]];
			string res=Xm;res+="->";res+=temp;
			cout<<"|";cout.width(25);cout<<res<<endl; 
			if (temp=="^") continue;
			for (int i=temp.length()-1; i>=0; --i) // 逆序压回栈中
			{
				string res="";
				if (temp[i]=='\'') res+=temp[i-1],res+=temp[i],--i;
				else res+=temp[i];
				Stack.push_back(res); 
			}
		}
		else if (Xm!="#")
		{
			if (Xm==Ai) 
			{
				string res=Ai;res+="匹配成功"; 
				Stack.pop_back();
				now++;cout.width(25);cout<<res<<endl;
			}else 
			{
				string res="error!";
				cout.width(25);cout<<res<<endl;exit(0);
			}
		}
		else
		{
			string res="全部匹配成功"; 
			if (Ai=="#") {cout<<"|";cout.width(25);cout<<res<<endl;return;}
			else 
			{
				string res="error!";
				cout.width(25);cout<<res<<endl;exit(0);
			} 
		}
	}
}
int main()
{
	freopen("shiyan3.in","r",stdin);
	First["^"].insert("^");
//	freopen("888.out","w",stdout);
    // 这段程序的作用是对LL(1)文法的输入进行处理，提取非终结符和终结符，初始化 Follow 集，并将产生式按照左部分类保存
	while((cin>>s)) 
	{
		cout<<s<<endl;
		if (!Fir) 
		{
			Be += s[0];
			Follow[Be].insert("#"); Fir=1;
		}
		int position=s.find("->");
		for (int i=0; i < s.length(); ++i)
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
		string res="";
		for (int i=0; i<S2.length(); ++i)
		if (S2[i]=='|')
		{
			Chan[S1].insert(res);
			res="";
		}else res+=S2[i];
		Chan[S1].insert(res);
		//for (set<string>::iterator it=Chan[S1].begin(); it!=Chan[S1].end(); it++)cout<<*it<<endl;cout<<endl;
	}	

	printf("非终结符号集合如下\n");
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++) 
	cout<<*it<<' ',num_Vn[*it]=++Vn_num;cout<<endl;
	printf("终结符号集合如下\n"); 
	for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) cout<<*it<<' ',Using[*it]=1,First[*it].insert(*it);
	cout<<endl;
	Vt.insert("#");
	for (set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) num_Vt[*it]=++Vt_num;

	printf("各非终结符对应的first集\n"); 
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++) 
	{
		string S1=*it;
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
		{
			string S2=*it2;bool All=true;
			if (S2=="^") First[S1].insert(S2);
			else 
			{
				for (int i=0; i<S2.length(); ++i) 
				{
					bool flag=false;string SS="";
					SS+=S2[i];if (i+1<S2.length() && S2[i+1]=='\'') SS+=S2[++i];
					Find_First(SS); 
					for (set<string>::iterator it3=First[SS].begin(); it3!=First[SS].end(); it3++)
					if (*it3=="^") flag=1;else First[S1].insert(*it3);
					if (!flag) {All=0;break;};
				}
				if (All) First[S1].insert("^");
			}	
		}
		cout<<S1<<' ';
		for (set<string>::iterator it3=First[S1].begin(); it3!=First[S1].end(); it3++)
		cout<<*it3<<' ';cout<<endl;
	}
	
	// 计算非终结符的 First 集合
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); ++it2)
		{
			string S2=*it2,SS="";
			for (int i=0; i<S2.length(); ++i) 
			{
				if (S2[i]=='\'') continue;
				SS=S2.substr(i);Finding_First(SS); 
			}
		}
	}
	
	// 计算非终结符的Follow集合
	for (int cs=1; cs<=10; ++cs)
	{
		for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
		{
			string S1=*it;
			for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
			{
				string S2=*it2;
				for (int i=0; i<S2.length(); ++i) 
				{
					string S="";S+=S2[i];
					if (i+1<S2.length() && S2[i+1]=='\'') S+=S2[++i];
					if (Vt.find(S)!=Vt.end()) continue;
					set<string> First_hou=First[S2.substr(i+1)];
					for (set<string>::iterator it3=First_hou.begin(); it3!=First_hou.end(); it3++)
					if (*it3!="^") Follow[S].insert(*it3);
					//if (i<S2.length() && First_hou.find("^")==First_hou.end()) continue;
					if (First_hou.find("^")!=First_hou.end() || i==S2.length()-1)
					{
						set<string> FollowA=Follow[S1];
						for (set<string>::iterator it3=FollowA.begin(); it3!=FollowA.end(); it3++)
						if (*it3!="^") Follow[S].insert(*it3);
					}
				}
			}
		}
	}
	printf("各非终结符对应的follow集\n"); 
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++)
	{
		string S1=*it;cout<<S1<<' '; 
		for (set<string>::iterator it3=Follow[S1].begin(); it3!=Follow[S1].end(); it3++)
		cout<<*it3<<' ';cout<<endl;
	}
	cout<<endl; 
	for (set<string>::iterator it=Vn.begin(); it!=Vn.end(); it++) 
	{
		string S1=*it;
		for (set<string>::iterator it2=Chan[S1].begin(); it2!=Chan[S1].end(); it2++)
		{
			string S2=*it2;
			for (set<string>::iterator it3=First[S2].begin(); it3!=First[S2].end(); it3++)	
			tab[num_Vn[S1]][num_Vt[*it3]]=*it2;
			if (First[S2].find("^")==First[S2].end()) continue;
			for (set<string>::iterator it3=Follow[S1].begin(); it3!=Follow[S1].end(); it3++)
			tab[num_Vn[S1]][num_Vt[*it3]]="^";
		}
	}
	cout<<"---------------------------------LL(1)分析表-------------------------------------"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"\t|";
    for(set<string>::iterator it=Vt.begin(); it!=Vt.end(); it++) cout << *it << "\t|";
    cout<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    set<string>::iterator it=Vn.begin();
    for (int i = 1; i <=Vn.size(); i++, it++) 
	{
        cout<<*it<<"\t|";
        for(int j=1; j<=Vt.size(); j++) cout<<tab[i][j]<<"\t|";
        cout<<endl;
        cout<<"---------------------------------------------------------------------------------";
        cout<<endl;
    }

    freopen("a.out","r",stdin);

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
		shizi_zhen+='#';
		Do_it(shizi_zhen);
	}
}

