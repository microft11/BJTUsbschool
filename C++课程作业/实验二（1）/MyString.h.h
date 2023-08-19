#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include<iostream>
#include<string.h>
using namespace std;

class MyString
{
    public:
        const char * get_string()
	    {
            return m_pbuf;
        }//ȡ���ַ����׵�ַ
        
        const char * set_string(const char * p=NULL);//pָ����ַ�����������
  
        const char * append(const char * p=NULL);//pָ����ַ���׷�ӵ�ԭ�ַ����� 
  
        MyString&append(MyString&s);//������s�е��ַ���׷�ӵ���ǰ�����ַ����󲢷��ض���
  
        int get_length()  //ȡ�ñ�����ַ�������
    
        MyString();//�����ι��캯����Ĭ����ʽ 
  
        MyString(const char *p);//һ���ι��캯�� 
  
        ~MyString() ;//�������� 
  
        MyString (const MyString&str);//���ƹ��캯�� 
  
        MyString& operator=(const MyString&s);//��ֵ��������� 
  
    private:
    	char *m_pbuf; 
};

inline int get_length()
	    {
           return strlen(m_pbuf);
        } 

#endif
