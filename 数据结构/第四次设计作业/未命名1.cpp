void InitStr(StringType &s);
  // 初始化s为空串。
void StrAssign(StringType &t, StringType s);
  // 将s的值赋给t。s的实际参数是串变量。
int StrCompare(StringType s, StringType t);
  // 比较s和t。若s>t，返回值>0；若s=t，返回值=0；若s<t，返回值<0。
int StrLength(StringType s);
  // 返回s中的元素个数，即该串的长度。
StringType Concat(StringType &s, StringType t); 
  // 返回由s和t联接而成的新串。
StringType SubString(StringType s, int start, int len);
  // 当1<=start<=StrLength(s)且0<=len<=StrLength(s)- start+1时，
  // 返回s中第start个字符起长度为len的子串，否则返回空串。
  
  
  void Replace(StringType &S, StringType T, StringType V)
//以串 v 置换串 s 中出现的所有和串 t 相同的非空串
{
    int n,m,k,i;
    StringType sub;
    InitStr(sub);
    n = StrLength(S);
    m = StrLength(T);
    k = StrLength(V);
    i = 1;
    while(i <= n-m+1){
        //将串S中的子串逐个提取出来与串T进行匹配
        StrAssign(sub,SubString(S,i,m));//将串S中的子串赋值给sub
        if(StrCompare(sub,T) == 0){//sun和T匹配相等时
            InitStr(sub);//初始化sub

            Concat(sub,SubString(S,1,i-1));//将匹配相等的子串的前面的子串连接到串sub后
            Concat(sub,V);//将替换串连接到串sub后
            Concat(sub,SubString(S,m+i,n-(m+i)+1));//将匹配相等的子串的后面的子串连接到串sub后
            StrAssign(S,sub);//将sub赋值给S
            i += k;//从匹配串之后的一个位置重新开始匹配
            n = StrLength(S);//操作完一次之后，串S已经改变，更新S的长度
        }
        else
        {//如果不匹配，就i向后移动
            i++;
        }
    }
}
