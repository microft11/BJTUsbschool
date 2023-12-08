#include"CMyString.h"
#include<string.h>

int MyString:: total = 0;//定义MyString类的静态成员并初始化为0 

MyString::MyString()//无参数的构造函数 
{
	total ++;
    m_pbuf = new char('\0');
    cout << "MyString的默认构造函数被调用" << endl;
}

const char* MyString::set_string(const char* p)
{
    delete[] m_pbuf;
    if (NULL == p)
        m_pbuf = new char('\0');
    else
    {
        int len = strlen(p) + 1;
        m_pbuf = new char[len];
        strcpy(m_pbuf, p);
    }
    return m_pbuf;
}

const char* MyString::append(const char* p)
{
    if (NULL != p)
    {
        int len = strlen(m_pbuf) + strlen(p) + 1;
        char* tmp = new char[len];
        sprintf(tmp, "%s%s", m_pbuf, p);
        delete[]m_pbuf;
        m_pbuf = tmp;
    }
    return m_pbuf;
}

MyString& MyString::append(MyString& s)
{
    int len = strlen(m_pbuf) + strlen(s.m_pbuf) + 1;
    char* tmp = new char[len];
    sprintf(tmp, "%s%s", m_pbuf, s.m_pbuf);
    delete[]m_pbuf;

    return *this;
}


MyString::MyString(const char* p)//构造函数 
{
	total ++; 
    if (NULL == p)
    {
        m_pbuf = new char('\0');
        cout << "MyString的有参构造函数被调用" << endl;
	}
    else
    {
        int len = strlen(p) + 1;
        m_pbuf = new char[len];
        strcpy(m_pbuf, p);
        cout << "MyString的有参构造函数被调用" << endl;
    }
}

MyString::~MyString()//析构函数 
{
	total --;
    delete m_pbuf;
    cout << "MyString的析构函数被调用" << endl;
}

MyString::MyString(const MyString& str)//复制构造函数 
{
	total ++;
    int len = strlen(str.m_pbuf) + 1;
    m_pbuf = new char[len];       
    
    strcpy(m_pbuf, str.m_pbuf);
}

MyString& MyString::operator=(const MyString& s) //赋值运算符函数 
{
    if (this != &s)//防止自赋值 
    {
        delete[] m_pbuf;
        int len = strlen(s.m_pbuf) + 1;
        m_pbuf = new char[len];
        strcpy(m_pbuf, s.m_pbuf);
    }
    cout << "MyString的赋值运算符函数被调用" << endl;
    return*this;
}
