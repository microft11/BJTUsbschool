#include "MyString05(1).h"
int MyString::total = 0; // 定义MyString类的静态成员并初始化为0
const char * MyString::set_string(const char * p) {
	delete[]m_pbuf;
	if(NULL==p)
		m_pbuf=new char('\0');
	else {
		int len = strlen(p)+1;
		m_pbuf=new char[len];
		strcpy(m_pbuf,p);
	}
	return m_pbuf;
}
const char * MyString::append(const char * p) {
	if(NULL!=p) {
		int len = strlen(m_pbuf)+strlen(p)+1;
		char * tmp =new char[len];
		sprintf(tmp,"%s%s",m_pbuf,p);
		delete[]m_pbuf;
		m_pbuf=tmp;
	}
	return m_pbuf;
}
MyString & MyString::append(MyString & s) {
	int len = strlen(m_pbuf)+strlen(s.m_pbuf)+1;
	char * tmp =new char[len];
	sprintf(tmp,"%s%s",m_pbuf,s.m_pbuf);
	delete[]m_pbuf;
	m_pbuf=tmp;
	return * this;
}
MyString & MyString::append(const MyString & s) {
	int len = strlen(m_pbuf)+strlen(s.m_pbuf)+1;
	char * tmp =new char[len];
	sprintf(tmp,"%s%s",m_pbuf,s.m_pbuf);
	delete[]m_pbuf;
	m_pbuf=tmp;
	return * this;
}
MyString::MyString() {//不带参数的构造函数
	++total;
	m_pbuf = new char('\0');
}
MyString::MyString(const char *p) {//带一个参数的构造函数
	++total;
	if (NULL == p)
		m_pbuf = new char('\0');
	else {
		int len = strlen(p) + 1;
		m_pbuf = new char[len];
		strcpy(m_pbuf, p);
	}
}
MyString::MyString(const MyString &str) {//复制构造函数
	++total;
	int len = strlen(str.m_pbuf) + 1;
	m_pbuf = new char[len];
	strcpy(m_pbuf, str.m_pbuf);
}
MyString & MyString::operator =(const MyString &s) {//赋值运算符重载，用等号进行字符串赋值
	if (this != &s) {
		delete[] m_pbuf;
		int len = strlen(s.m_pbuf) + 1;
		m_pbuf = new char[len];
		strcpy(m_pbuf, s.m_pbuf);
	}
	return *this;
}
MyString MyString::operator + (const MyString &str)const {//赋值运算符重载，用加号拼接字符串
	MyString tmp(*this);
	tmp.append(str);
	return tmp;
}
char & MyString::operator [](const int idx) {
	if(idx<0||idx>=strlen(m_pbuf))
		exit(1);
	return m_pbuf[idx];
}
const char & MyString::operator [](const int idx)const {
	if(idx<0||idx>=strlen(m_pbuf))
		exit(1);
	return m_pbuf[idx];
}
MyString & MyString ::operator ()(const char * p) {
	set_string(p);
	return *this;
}
MyString::~MyString() {//析构
	--total;
	delete[] m_pbuf;
}
int MyString::operator < (const MyString &str)const
{
	if(strcmp(m_pbuf,str.get_string())<0) {
		return 1;
	} else return 0;
}
int MyString::operator <= (const MyString &str)const
{
	if(strcmp(m_pbuf,str.get_string())<=0) {
		return 1;
	} else return 0;
}
int MyString::operator > (const MyString &str)const
{
	if(strcmp(m_pbuf,str.get_string())>0) {
		return 1;
	} else return 0;
}
int MyString::operator >= (const MyString &str)const
{
	if(strcmp(m_pbuf,str.get_string())>=0) {
		return 1;
	} else return 0;
}


