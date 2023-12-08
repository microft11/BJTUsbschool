#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include<iostream>
#include<string.h>
using namespace std;

class MyString
{
	static int total;
    public:
    	
    	static int get_total(){ return total; }//定义静态函数 
    	
        const char * get_string()
	    {
            return m_pbuf;
        }//取得字符串首地址，设为常成员 
        
        const char * set_string(const char * p=NULL);//p指向的字符串保存在类
  
        const char * append(const char * p=NULL);//p指向的字符串追加到原字符串后 
  
        MyString&append(MyString&s);//将对象s中的字符串追加到当前对象字符串后并返回对象
  
        int get_length(); //取得保存的字符串长度
    
        MyString();//不带参构造函数，默认形式 
  
        MyString(const char *p);//一个参构造函数 
  
        ~MyString() ;//析构函数 
  
        MyString (const MyString&str);//复制构造函数 
  
        MyString& operator=(const MyString&s);//赋值运算符函数 
  
    private:
    	char *m_pbuf; 
};

inline int MyString::get_length()
	    {
           return strlen(m_pbuf);
        } 

#endif
