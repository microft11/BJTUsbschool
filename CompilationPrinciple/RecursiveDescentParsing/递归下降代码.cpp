#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include <cassert>
#include<fstream>
#define MAX_LINE 1024
using namespace std;

// 函数声明
void S();
void E(); 
void E_(); 
void T(); 
void T_(); 
void F(); 
void A(); 
void M(); 
void V(); 

// 定义一个长度为100的字符数组
char s[100];

// 用来作数组索引,当每次匹配成功存入数据时index自增1
int i;
//  用来标记语句是否正确
int SIGN;


int main()
{
//    printf("请输入你的语句（记得在最后带上#）\n");
	cout<<"读取文件可知输入语句："<<endl;
	FILE *fp;
	char buf[MAX_LINE];
	string shizi,like;
	if((fp = fopen("text.txt","r"))!=NULL){
		while(fgets(buf,MAX_LINE,fp) != NULL)
		{
			int len = strlen(buf);
		 	buf[len-1] = '\0';  /*去掉换行符*/
		 	printf("%s \n",buf);
		 	int flag=0;
		 	if(buf[1]=='1'){
		 		like+='i';
		 		
			}
			
		 	for(int i=0;i<len;i++){
		 		if(buf[i]=='"'&&flag==0){
		 			i++;
		 			while(buf[i]!='"'){
		 				shizi+=buf[i];
		 				if(buf[1]!='1'){
		 					like+=buf[i];
						 }
		 				i++;
					 }
				}
			}
		}
	}
	shizi+='#';
	like+='#';
	fclose(fp);
	
	cout<<"输入的语句为："<<shizi<<endl;
	cout<<"可以理解为："<<like<<endl;


    SIGN = 0;//语句是否正确用SIGN
    i=0;
    
	//将输入的式子按照修改为字符串格式char* 
	int length=like.length();
	for(int i=0;i<length;i++){
		s[i]=like[i];
	}
    
    // 当输入的第一个字符为#时,程序直接结束
    if( s[0] == '#')
        return 0;
         
    S();
    // 如果最后的字符以#结束则输出下面
    if(s[i]=='#'&&SIGN==0){
        printf("\n语句合法\n");
    }else{
        printf("\n语句不合法\n");
    }
//        printf("请输入你的语句（记得在最后带上#）\n");
//    }
    return 1;
}

void S()
{
    if(SIGN==0)
    {
    	printf("S检查  ");
        // 当输入的字符串中首字母为a时
        if(s[i]=='i'){
            V();
			if(SIGN==0&&s[i]=='='){
//				printf("(%c)  ",s[i]);
				i++;
				E();
			}
			else{
				SIGN=1;
				cout<<"S处出现错误"<<endl; 
			}
        }	
		else{
            SIGN=1;
            cout<<"S处出现错误"<<endl; 
        }
    }
}

void E()
{
    if(SIGN==0){
    	printf("E   ");
       if(s[i]=='('||s[i]=='i'){
            T();
            if(SIGN==0){
            	if(s[i]=='+'||s[i]=='-'){
            		E_();
				}   
				else if(s[i]==')'||s[i]=='#'){
        			return;
				}
				else{
					SIGN=1;
					cout<<"E处出现错误"<<endl; 
				}
			}  
        }
        else{
        	SIGN=1;
        	cout<<"E处出现错误"<<endl; 
		}
    }
}

void E_()
{
    if(SIGN==0){
    	printf("E'   ");
        if(s[i]=='+'||s[i]=='-'){
            A();
            if(SIGN==0){
            	if(s[i]=='('||s[i]=='i'){
            		T();
            		if(SIGN==0){
		            	if(s[i]=='+'||s[i]=='-'){
		            		E_();
						} 
						else if(s[i]==')'||s[i]=='#')  {
							return;
						}
						else{
							SIGN=1;
							cout<<"E'处出现错误"<<endl; 
						}
					}
				}
				else{
					SIGN=1;
					cout<<"E'处出现错误"<<endl; 
				}
			}
        }
        else if(s[i]==')'||s[i]=='#'){
        	return;
		}
        else{
        	SIGN=1;
        	cout<<"E'处出现错误"<<endl; 
		}
    }
}

void T()
{
    if(SIGN==0){
    	printf("T   ");
        if(s[i]=='('||s[i]=='i'){
            F();
            if(SIGN==0){
            	if(s[i]=='*'||s[i]=='/'){
            		T_();
				}
				else if(s[i]=='+'||s[i]=='-'||s[i]==')'||s[i]=='#') {
					return;
				}
				else{
					SIGN=1;
					cout<<"T处出现错误"<<endl; 
				}
			}
        }
        else{
        	SIGN=1;
        	cout<<"T处出现错误"<<endl; 
		}
    }
}

void T_()
{
	if(SIGN==0){
		printf("T'   ");
		if(s[i]=='*'||s[i]=='/'){
			M();
			if(SIGN==0){
				F();
				if(SIGN==0){
					T_();
				}
			}
		}
		else if(s[i]=='+'||s[i]=='-'||s[i]==')'||s[i]=='#'){
			return;			
		}
		else{
			SIGN=1;
			cout<<"T'处出现错误"<<endl; 
		}
	}
}

void F()
{
	if(SIGN==0){
		printf("F   ");
		if(s[i]=='('){
//			printf("(%c)  ",s[i]);
			i++;
			if(s[i]=='('||s[i]=='i'){
				E();
				if(SIGN==0){
					if(s[i]==')'){
//						printf("(%c)  ",s[i]);
						i++;
					}
					else{
						SIGN=1;
						cout<<"F处出现错误"<<endl; 
					}
				}
			}
			else{
				SIGN=1;
				cout<<"F处出现错误"<<endl; 
			}
		}
		else if(s[i]=='i'){
//			printf("(%c)  ",s[i]);
			i++;
		}
		else{
			SIGN=1;
			cout<<"F处出现错误"<<endl; 
		}
	}
}

void A()
{
	if(SIGN==0){
		printf("A   ");
		if(s[i]=='+'||s[i]=='-'){
//			printf("(%c)  ",s[i]);
			i++;
		}
		else{
			SIGN=1;
			cout<<"A处出现错误"<<endl; 
		}
	}
}

void M()
{
	if(SIGN==0){
		printf("M   ");
		if(s[i]=='*'||s[i]=='/'){
//			printf("(%c)  ",s[i]);
			i++;
		}
		else{
			SIGN=1;
			cout<<"M处出现错误"<<endl; 
		}
	}
}

void V()
{
	if(SIGN==0){
		printf("V   ");
		if(s[i]=='i'){
//			printf("(%c)  ",s[i]);
			i++;
		}
		else{
			SIGN=1;
			cout<<"V处出现错误"<<endl; 
		}
	}
}
