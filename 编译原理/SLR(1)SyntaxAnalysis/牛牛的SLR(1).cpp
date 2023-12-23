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
string s, Head;
set<string> Vn, Vt;
map<string, set<string>> Production, Prouction_simple;
int cnt, num_of_Vn, num_of_Vt;
int GOTO[505][505];
map<string, int> Vnsnum, Vtsnum;
string ACTION[505][505];
map<string, set<string>> Follow;
int IsFinal[505];
map<int, string> Old_to_New;
inline int read()
{
    int x = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
        w |= ch == '-', ch = getchar();
    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return w ? -x : x;
}

int the_num_of_Production;
map<string, int> Num_of_Production;
map<int, string> Num_to_Production;
stack<string> ans_4;
int ans_num = 0, NUM = 0;

struct info
{
    string op, arg1, arg2, Result;
} ans[10005];


/*目的：生成LR(1)产生式，并将其添加到集合Production中。
参数：
S1：产生式的左部。
S2：产生式的右部。
功能：为给定的产生式添加LR(1)产生式到集合Production中，并打印它们*/
inline void Make_Pro(string S1, string S2) {
    string res = "", temp = "";

    // 循环遍历产生式右部的每个字符
    for (int i = 0; i < S2.length(); ++i) {
        // 在每个位置加点，形成LR(1)产生式
        res = temp + "·" + S2.substr(i);
        
        // 将产生式加入到Production集合中
        Production[S1].insert(res);
        cout << S1 << "->" << res << endl;
        
        // 更新temp，用于构建下一个位置的LR(1)产生式
        temp += S2[i];
    }

    // 将最后一个位置加点的产生式加入到Production集合中
    Production[S1].insert(res);

    // 输出带点的产生式
    res = temp + "·";
    cout << S1 << "->" << res << endl;

    // 将原始产生式添加到Production_simple集合中
    Prouction_simple[S1].insert(S2);

    // 记录产生式的编号
    Num_of_Production[S1 + "->" + S2 + "·"] = ++the_num_of_Production;
    Num_to_Production[the_num_of_Production] = S1 + "->" + S2;
}

/*目的：读取文法，记录终结符和非终结符，并创建LR(1)产生式。
功能：读取产生式，记录终结符（Vt）、非终结符（Vn），并使用Make_Pro创建LR(1)产生式。还添加了拓广文法的产生式。*/
inline void Init() {
    int One = 0;
    Vn.insert("A");

    // 从标准输入中读取文法
    while (cin >> s) {
        int position = s.find("->");

        // 遍历文法字符串的每个字符
        for (int i = 0; i < s.length(); ++i) {
            // 跳过箭头、大于号和竖线等分隔符
            if ((s[i] == '-' && s[i + 1] == '>') || s[i] == '>' || s[i] == '|') continue;
            else {
                string S = ""; S += s[i];

                // 判断字符是终结符还是非终结符，并分别加入到对应的集合中
                if (s[i] >= 'A' && s[i] <= 'Z') Vn.insert(S);
                else Vt.insert(S);
            }
        }

        // 提取产生式左部
        string S1 = s.substr(0, position), res = "";

        // 若第一次读入，拓广文法
        if (!One) {
            Make_Pro("A", S1);
            One = 1;
            Head = S1;
        }

        // 分割产生式右部，调用Make_Pro加点
        for (int i = position + 2; i < s.length(); ++i) {
            if (s[i] == '|') {
                Make_Pro(S1, res);
                res = "";
            } else {
                res += s[i];
            }
        }

        // 处理最后一个产生式
        Make_Pro(S1, res);
    }

    // 将结束符号 # 加入到终结符集合中
    Vt.insert("#");

    // 为非终结符和终结符分别编号
    for (set<string>::iterator it = Vn.begin(); it != Vn.end(); it++) {
        Vnsnum[*it] = ++num_of_Vn;
    }

    for (set<string>::iterator it = Vt.begin(); it != Vt.end(); it++) {
        Vtsnum[*it] = ++num_of_Vt;
    }
}

map<set<string>,int> Have;//记录某集合是否已经出现过 
map<int,set<string> > C;//记录C_? 
map<string,bool> Used[505];//判断该集合是否喂过某一个字母，防止重复喂 
inline int Expand(int num, string S1) {
    // 标记已经扩展过的状态集合
    Used[num][S1] = 1;

    // 从 Production_simple[S1] 中获取产生式
    set<string> res = Prouction_simple[S1];

    // 遍历产生式集合
    for (set<string>::iterator it = res.begin(); it != res.end(); it++) {
        string S = *it, S2 = "";
        S2 += S[0];

        // 将点添加到非终结符后面，形成新的产生式，并加入到C集合中
        C[num].insert(S1 + "->·" + S);

        // 如果点后面是非终结符，且该非终结符没有被使用过，则递归扩展
        if (Vn.find(S2) != Vn.end() && !Used[num][S2]) {
            Expand(num, S2);
        }

        // 标记非终结符已被使用过
        Used[num][S2] = 1;
    }
}

/*目的：将整数转换为字符串。
参数：
x：要转换的整数。
功能：将整数转换为字符串。*/
inline string Change(int x)
{
	string res="";
	if (!x) return "0";
	while (x) res=(char)(x%10+48)+res,x/=10;
	return res;	
}

/*目的：检查并设置LR(1)产生式集的动作表项。
参数：
now：LR(1)产生式集的编号。
功能：检查集合中的每个LR(1)产生式，并相应地设置ACTION表中的项*/
inline void Check(int now) {
    // 遍历状态集合中的每个产生式
    for (set<string>::iterator it = C[now].begin(); it != C[now].end(); it++) {
        string res = *it;
        int position = res.find("->");
        string S1 = res.substr(0, position);

        // 如果是拓广文法的结束状态，则在 ACTION 表中标记为 "ACC" (Accept)
        if ("A->" + Head + "·" == res) {
            ACTION[now][Vtsnum["#"]] = "ACC";
            continue;
        }

        // 如果产生式在产生式编号表中有记录
        if (Num_of_Production[res]) {
            // 将该状态标记为最终状态，并在 ACTION 表中填充规约动作
            IsFinal[now] = Num_of_Production[res];

            // 对于产生式右部的每个 FOLLOW 集合中的符号，在 ACTION 表中填充 "r" + 规约产生式编号
            for (set<string>::iterator it2 = Follow[S1].begin(); it2 != Follow[S1].end(); it2++) {
                ACTION[now][Vtsnum[*it2]] = "r" + Change(Num_of_Production[res]);
            }
        }
    }
}


/*目的：构建LR(1)产生式集，建立动作和转移表。
功能：迭代LR(1)产生式集，拓广它们，并为终结符和非终结符创建转移。然后检查并设置ACTION和GOTO表中的项*/
inline void Make_DFA() {
    // 初始化初始状态
    C[0].insert("A->·" + Head);
    Expand(0, Head);
    int now = 0;
    Have[C[0]] = 0;

    // 循环直到所有状态集合都处理完毕
    while (now <= cnt) {
        // 喂非终结符
        for (set<string>::iterator it = Vn.begin(); it != Vn.end(); it++) {
            string SH = *it;
            int flag = 0;
            cnt++;

            // 遍历当前状态集合的每个产生式
            for (set<string>::iterator it2 = C[now].begin(); it2 != C[now].end(); it2++) {
                string res = *it2, temp = "", Ned = "";
                int position1 = res.find("·"), position2 = position1 + 2;
                Ned += res[position2];

                // 检查·后边是否是当前非终结符
                if (Ned != SH) continue;

                flag = 1;

                // 构建新的产生式，加入下一个状态集合，并递归扩展
                C[cnt].insert(res.substr(0, position1) + SH + "·" + res.substr(position2 + 1));
                if (position2 != res.length() - 1) {
                    temp += res[position2 + 1];
                    if (Vn.find(temp) == Vn.end()) continue;
                    Expand(cnt, temp);
                }
            }

            // 处理新的状态集合或更新 GOTO 表
            if (!flag || Have[C[cnt]]) {
                if (flag) GOTO[now][Vnsnum[SH]] = Have[C[cnt]];
                C[cnt].clear();

                // 清除使用标记
                for (set<string>::iterator it2 = Vn.begin(); it2 != Vn.end(); it2++)
                    Used[cnt][*it2] = 0;
                for (set<string>::iterator it2 = Vt.begin(); it2 != Vt.end(); it2++)
                    Used[cnt][*it2] = 0;

                cnt--;
            } else {
                // 记录新的状态集合并更新 GOTO 表
                Have[C[cnt]] = cnt;
                GOTO[now][Vnsnum[SH]] = cnt;
            }
        }

        // 喂终结符
        for (set<string>::iterator it = Vt.begin(); it != Vt.end(); it++) {
            string SL = *it;
            int flag = 0;
            cnt++;

            // 遍历当前状态集合的每个产生式
            for (set<string>::iterator it2 = C[now].begin(); it2 != C[now].end(); it2++) {
                string res = *it2, temp = "", Ned = "";
                int position1 = res.find("·"), position2 = position1 + 2;
                Ned += res[position2];

                // 检查·后边是否是当前终结符
                if (Ned != SL) continue;

                flag = 1;

                // 构建新的产生式，加入下一个状态集合，并递归扩展
                C[cnt].insert(res.substr(0, position1) + SL + "·" + res.substr(position2 + 1));
                if (position2 != res.length() - 1) {
                    temp += res[position2 + 1];
                    if (Vn.find(temp) == Vn.end()) continue;
                    Expand(cnt, temp);
                }
            }

            // 处理新的状态集合或更新 ACTION 表
            if (!flag || Have[C[cnt]]) {
                if (flag) ACTION[now][Vtsnum[SL]] = "S" + Change(Have[C[cnt]]);
                C[cnt].clear();

                // 清除使用标记
                for (set<string>::iterator it2 = Vn.begin(); it2 != Vn.end(); it2++)
                    Used[cnt][*it2] = 0;
                for (set<string>::iterator it2 = Vt.begin(); it2 != Vt.end(); it2++)
                    Used[cnt][*it2] = 0;

                cnt--;
            } else {
                // 记录新的状态集合并更新 ACTION 表
                Have[C[cnt]] = cnt;
                ACTION[now][Vtsnum[SL]] = "S" + Change(cnt);
            }
        }

        // 检查状态集合，填充规约动作
        Check(now);
        now++;
    }
}

/*目的：为文法中的非终结符初始化后继集。
功能：手动设置文法中非终结符的后继集。*/
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

/*目的：将动作字符串转换为相应的数字。
参数：
S：动作字符串。
功能：将动作字符串转换为数字*/ 
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
/*目的：打印LR分析器的当前状态。
参数：
num：输入字符串的索引。
S：输入字符串。
功能：打印LR分析器的当前状态，包括状态栈、符号栈和剩余输入。*/
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
/*目的：对输入字符串执行LR(1)分析。
参数：
S：输入字符串。
功能：开始LR(1)分析，逐步打印分析过程。*/
inline void Do_it(string S) {
    cout << "分析过程如下:\n";
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << setw(40) << "状态栈" << setw(25) << "符号栈" << setw(30) << "输入串" << setw(5) << "ACTION" << setw(5) << "GOTO" << endl;
    St1.push("#");
    St2.push(0);
    Print(-1, S);

    for (int i = 0; i < S.length(); ++i) {
        string res = "", Next = "";
        res += S[i];
        Next += S[i + 1];
        St1.push(res);

        // 将原始表达式符号入栈，用于构建四元式
        if (res != "(" && res != ")")
            ans_4.push(Old_to_New[i]);

        // 非终结符，调用 ACTION 表
        if (Vt.find(res) != Vt.end()) {
            if (ACTION[St2.top()][Vtsnum[res]] == "") {
                printf("Failed!");
                exit(0);
            }
            cout << setw(5) << ACTION[St2.top()][Vtsnum[res]] << setw(5) << " " << endl;
            St2.push(CChange(ACTION[St2.top()][Vtsnum[res]]));
        } else {  // 终结符，调用 GOTO 表
            if (!GOTO[St2.top()][Vnsnum[res]]) {
                printf("Failed!");
                exit(0);
            }
            cout << setw(5) << " " << setw(5) << GOTO[St2.top()][Vnsnum[res]] << endl;
            St2.push(GOTO[St2.top()][Vnsnum[res]]);
        }

        Print(i, S);

        // 规约过程
        while (IsFinal[St2.top()] && (ACTION[St2.top()][Vtsnum[Next]].find("r") != -1 || ACTION[St2.top()][Vtsnum[Next]] == "")) {
            res = Num_to_Production[IsFinal[St2.top()]];
            string tmp = ACTION[St2.top()][Vtsnum[Next]];
            int position = res.find("->");
            string S1 = res.substr(0, position), S2 = res.substr(position + 2);

            // 弹出符号栈和状态栈对应的数量
            for (int j = 0; j < S2.length(); ++j)
                St1.pop(), St2.pop();

            // 如果产生式右侧长度大于1且最后一个符号不是')'，生成新的四元式
            if (S2.length() > 1 && S2[S2.length() - 1] != ')') {
                ++ans_num;
                string Baga = "result" + Change(++NUM);
                ans[ans_num].arg2 = ans_4.top();
                ans_4.pop();
                ans[ans_num].op = ans_4.top();
                ans_4.pop();
                ans[ans_num].arg1 = ans_4.top();
                ans_4.pop();
                ans[ans_num].Result = Baga;
                ans_4.push(Baga);
            }

            // 将产生式左侧入栈
            St1.push(S1);

            // 非终结符，调用 ACTION 表
            if (Vt.find(S1) != Vt.end())
                cout << setw(5) << ACTION[St2.top()][Vtsnum[S1]] << setw(5) << " " << endl, St2.push(CChange(ACTION[St2.top()][Vtsnum[S1]]));
            else  // 终结符，调用 GOTO 表
                cout << setw(5) << tmp << setw(5) << GOTO[St2.top()][Vnsnum[S1]] << endl, St2.push(GOTO[St2.top()][Vnsnum[S1]]);

            Print(i, S);
        }
    }
}

/*目的：主函数，应用LR分析器于输入字符串。
功能：读取文法，构建LR(1)产生式集，然后应用解析器于输入字符串。*/
int main()
{
    freopen("shiyan5.in", "r", stdin);
    Get_follow();
    freopen("5_11.out", "w", stdout);
    printf("拓广文法如下：\n");
    Init();
    cout << endl;
    Make_DFA();

    for (int i = 0; i <= cnt; ++i)
    {
        printf("C%d:\n", i);
        for (set<string>::iterator it = C[i].begin(); it != C[i].end(); it++)
            cout << *it << endl;
    }

    cout << setw(5) << "";
    for (set<string>::iterator it = Vt.begin(); it != Vt.end(); it++)
        cout << setw(5) << *it;
    for (set<string>::iterator it = Vn.begin(); it != Vn.end(); it++)
        cout << setw(5) << *it;
    cout << endl;

    for (int i = 0; i <= cnt; ++i, cout << endl)
    {
        cout << setw(5) << i;
        for (int j = 1; j <= num_of_Vt; ++j)
            cout << setw(5) << ACTION[i][j];
        for (int j = 1; j <= num_of_Vn; ++j)
            cout << setw(5) << GOTO[i][j];
    }

    freopen("5_1.out", "r", stdin);
    char s[505];
    while (scanf("%s", s) != EOF)
    {
        int len = strlen(s), L = 0, mid, R;
        s[len] = '(';
        string shizi = "", shizi_zhen = "";
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == ',')
                mid = i;
            if (s[i] == ')' && s[i + 1] == '(')
            {
                R = i;
                break;
            }
        }

        while (L < len)
        {
            if (mid == L + 2 && s[L + 1] == '1')
            {
                shizi_zhen += 'i';
                string res = "";
                for (int i = mid + 1; i < R; ++i)
                    res += s[i];
                Old_to_New[shizi_zhen.length() - 1] = res;
            }
            else
                for (int i = mid + 1; i < R; ++i)
                {
                    shizi_zhen += s[i];
                    if (s[i] == '(' || s[i] == ')')
                        continue;
                    string res = "";
                    res += s[i];
                    Old_to_New[shizi_zhen.length() - 1] = res;
                }

            for (int i = mid + 1; i < R; ++i)
                shizi += s[i];
            L = R + 1;
            mid = L + 1;
            R = mid + 1;
            if (L == len)
                break;
            while (s[mid] != ',')
                mid++;
            while (s[R] != ')' || s[R] == ')' && s[R + 1] != '(')
                R++;
        }

        cout << "原来表达式：" << shizi << endl
             << "抽象为：" << shizi_zhen << endl;
        shizi_zhen += '#';
        Do_it(shizi_zhen);
    }
}