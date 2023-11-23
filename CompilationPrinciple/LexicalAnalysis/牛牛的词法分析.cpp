#include <iostream>
#include <string>
using namespace std;

char c;
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
inline bool pdZM(char c)
{
	return 'a'<=c && c<='z' || 'A'<=c && c<='Z';	
}
inline bool pdSZ(char c)
{
	return '0'<=c && c<='9';	
}
inline int Getbsfid(char s[])
{
	if (strcmp(s,"void")==0) return 3;
	else if (strcmp(s,"int")==0) return 4;
	else if (strcmp(s,"main")==0) return 5;
	else if (strcmp(s,"float")==0) return 6;
	else if (strcmp(s,"double")==0) return 7;
	else if (strcmp(s,"if")==0) return 8;
	else if (strcmp(s,"else")==0) return 9;
	else if (strcmp(s,"for")==0) return 10;
	else if (strcmp(s,"do")==0) return 11;
	else if (strcmp(s,"while")==0) return 12;
	else if (strcmp(s,"return")==0) return 13;
	else if (strcmp(s,"break")==0) return 14;
	else if (strcmp(s,"exit")==0) return 15;
	else return 1;
}

inline int pdDZF(char c)
{
	if (c==',') return 20;
	else if (c==';') return 21;
	else if (c=='(') return 22;
	else if (c==')') return 23;
	else if (c=='{') return 24;
	else if (c=='}') return 25;
	else if (c=='[') return 51;
	else if (c==']') return 52;
	else if (c=='%') return 19;
	else if (c=='#') return 53; 
	else if (c=='.') return 54;
	else return 0;
}

inline void Change(int s)
{
	printf("(2,");
	int S[50],len=0;
	while (s) S[++len]=s%2,s/=2;
	while (len) printf("%d",S[len--]);
	printf(")");	
}
int main()
{
	freopen("lex.out","w",stdout);
	FILE *fp=NULL;
	fp=fopen("text.txt","r");
	c=fgetc(fp);
	while (!feof(fp))
	{
		if (c==' '|| c=='\t') {c=fgetc(fp); continue;}
		else if (c=='\n') {c=fgetc(fp),printf("\n"); continue;}
		else if (pdZM(c))
		{
			char s[50];
			int len=0;
			while (pdZM(c) || pdSZ(c)) 
			{
				s[len++]=c,c=fgetc(fp);
				if (len>32)
				{
					printf("��ʶ�����ȳ���\n");
					return 0;
				}	
			}
			s[len]='\0';
			printf("(%d,%s)",Getbsfid(s),s);
		}
		else if (pdSZ(c))
		{
			int len=0,s=0;
			while (pdSZ(c)) //s[len++]=c,c=fgetc(fp);
			s=s*10+(c-'0'),c=fgetc(fp);
			Change(s);
			//s[len]='\0';printf("(2,%s)",s);	
		}
		else if (pdDZF(c)) printf("(%d,%c)",pdDZF(c),c),c=fgetc(fp);
		else if (c=='>')
		{
			c=fgetc(fp);
			if (c=='=') printf("(27,>=)"),c=fgetc(fp);
			else if (c=='>') printf("(35,>>)"),c=fgetc(fp);
			else printf("(49,>)");	
		}
		else if (c=='<')
		{
			c=fgetc(fp);
			if (c=='=') printf("(28,<=)"),c=fgetc(fp);
			else if (c=='>') printf("(36,<<)"),c=fgetc(fp); 
			else printf("(47,<)");	
		}
		else if (c=='=')
		{
			c=fgetc(fp);
			if (c=='=') printf("(31,==)"),c=fgetc(fp);
			else printf("(48,=)");	
		}
		else if (c=='!')
		{
			c=fgetc(fp);
			if (c=='=') printf("(30,!=)"),c=fgetc(fp);
			else printf("(26,!)");	
		}
		else if (c=='&')
		{
			c=fgetc(fp);
			if (c=='&') printf("(41,&&)"),c=fgetc(fp);
			else printf("(46,&)");	
		}
		else if (c=='|')
		{
			c=fgetc(fp);
			if (c=='|') printf("(42,||)"),c=fgetc(fp);
			else printf("(45,|)");	
		}
		else if (c=='/')
		{
			c=fgetc(fp);
			if (c=='=') printf("(40,/=)"),c=fgetc(fp);
			else if (c=='*')
			{
				printf("(32,/*)");bool find=false;
				do
				{
					c=fgetc(fp);
					while (c=='*')
					{
						c=fgetc(fp);
						if (c=='/') printf("(43,*/)"),find=true,c=fgetc(fp); 	
					}
				}while (!find);
			}
			else if (c=='/') 
			{
				printf("(44,//)");bool find=false;
				while (c!='\n') c=fgetc(fp);
				printf("\n"),c=fgetc(fp);
			}
			else printf("(50,/)");
		}
		else if (c=='*')
		{
			c=fgetc(fp);
			if (c=='=') printf("(39,*=)"),c=fgetc(fp);
			else printf("(18,*)");	
		}
		else if (c=='+')
		{
			c=fgetc(fp);
			if (c=='+') printf("(33,++)"),c=fgetc(fp);
			else if (c=='=') printf("(37,+=)"),c=fgetc(fp);
			else printf("(16,+)");	
		}
		else if (c=='-')
		{
			c=fgetc(fp);
			if (c=='-') printf("(34,--)"),c=fgetc(fp);
			else if (c=='=') printf("(38,-=)"),c=fgetc(fp);
			else printf("(17,-)");
		}
		else printf("���󣬻���δ���壡��\n"),c=fgetc(fp); 
	}
	fclose(fp);
}

