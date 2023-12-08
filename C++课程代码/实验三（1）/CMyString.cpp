#include"CMyString.h"
#include<string.h>

int MyString:: total = 0;//����MyString��ľ�̬��Ա����ʼ��Ϊ0 

MyString::MyString()//�޲����Ĺ��캯�� 
{
	total ++;
    m_pbuf = new char('\0');
    cout << "MyString��Ĭ�Ϲ��캯��������" << endl;
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


MyString::MyString(const char* p)//���캯�� 
{
	total ++; 
    if (NULL == p)
    {
        m_pbuf = new char('\0');
        cout << "MyString���вι��캯��������" << endl;
	}
    else
    {
        int len = strlen(p) + 1;
        m_pbuf = new char[len];
        strcpy(m_pbuf, p);
        cout << "MyString���вι��캯��������" << endl;
    }
}

MyString::~MyString()//�������� 
{
	total --;
    delete m_pbuf;
    cout << "MyString����������������" << endl;
}

MyString::MyString(const MyString& str)//���ƹ��캯�� 
{
	total ++;
    int len = strlen(str.m_pbuf) + 1;
    m_pbuf = new char[len];       
    
    strcpy(m_pbuf, str.m_pbuf);
}

MyString& MyString::operator=(const MyString& s) //��ֵ��������� 
{
    if (this != &s)//��ֹ�Ը�ֵ 
    {
        delete[] m_pbuf;
        int len = strlen(s.m_pbuf) + 1;
        m_pbuf = new char[len];
        strcpy(m_pbuf, s.m_pbuf);
    }
    cout << "MyString�ĸ�ֵ���������������" << endl;
    return*this;
}
