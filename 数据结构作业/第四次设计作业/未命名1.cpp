void InitStr(StringType &s);
  // ��ʼ��sΪ�մ���
void StrAssign(StringType &t, StringType s);
  // ��s��ֵ����t��s��ʵ�ʲ����Ǵ�������
int StrCompare(StringType s, StringType t);
  // �Ƚ�s��t����s>t������ֵ>0����s=t������ֵ=0����s<t������ֵ<0��
int StrLength(StringType s);
  // ����s�е�Ԫ�ظ��������ô��ĳ��ȡ�
StringType Concat(StringType &s, StringType t); 
  // ������s��t���Ӷ��ɵ��´���
StringType SubString(StringType s, int start, int len);
  // ��1<=start<=StrLength(s)��0<=len<=StrLength(s)- start+1ʱ��
  // ����s�е�start���ַ��𳤶�Ϊlen���Ӵ������򷵻ؿմ���
  
  
  void Replace(StringType &S, StringType T, StringType V)
//�Դ� v �û��� s �г��ֵ����кʹ� t ��ͬ�ķǿմ�
{
    int n,m,k,i;
    StringType sub;
    InitStr(sub);
    n = StrLength(S);
    m = StrLength(T);
    k = StrLength(V);
    i = 1;
    while(i <= n-m+1){
        //����S�е��Ӵ������ȡ�����봮T����ƥ��
        StrAssign(sub,SubString(S,i,m));//����S�е��Ӵ���ֵ��sub
        if(StrCompare(sub,T) == 0){//sun��Tƥ�����ʱ
            InitStr(sub);//��ʼ��sub

            Concat(sub,SubString(S,1,i-1));//��ƥ����ȵ��Ӵ���ǰ����Ӵ����ӵ���sub��
            Concat(sub,V);//���滻�����ӵ���sub��
            Concat(sub,SubString(S,m+i,n-(m+i)+1));//��ƥ����ȵ��Ӵ��ĺ�����Ӵ����ӵ���sub��
            StrAssign(S,sub);//��sub��ֵ��S
            i += k;//��ƥ�䴮֮���һ��λ�����¿�ʼƥ��
            n = StrLength(S);//������һ��֮�󣬴�S�Ѿ��ı䣬����S�ĳ���
        }
        else
        {//�����ƥ�䣬��i����ƶ�
            i++;
        }
    }
}
