#include<ostream>
#include"MyString.h"
using namespace std;
int MyString::num = 0;
MyString::MyString() :MAXlenth(100)
{
	m_pbuf = new char('\0');
	//cout << "MyString类的默认构造函数被调用" << endl;
	num++;
}
MyString::MyString(const char* str) : MAXlenth(100)
{
	m_pbuf = new char[strlen(str) + 1];
	strcpy(m_pbuf, str);
	//cout << "MyString类的有参构造函数被调用，当前字符串为：" << m_pbuf << endl;
	num++;
}
MyString::MyString(const MyString& s) :MAXlenth(100)
{
	m_pbuf = new char[strlen(s.m_pbuf) + 1];
	strcpy(m_pbuf, s.m_pbuf);
	//cout << "MyString类的复制构造函数被调用，当前字符串为：" << m_pbuf << endl;
	num++;
}
const char* MyString::set_string(const char* str)
{
	if (m_pbuf != NULL) {
		delete[]m_pbuf;
	}
	m_pbuf = new char[strlen(str) + 1];
	strcpy(m_pbuf, str);

	return m_pbuf;
}
MyString& MyString::append(const char* str)
{
	int lenth_m = strlen(m_pbuf);
	char* temp = new char[lenth_m + strlen(str) + 1];
	strcpy(temp, m_pbuf);
	strcpy(temp + lenth_m, str);
	delete[] m_pbuf;
	m_pbuf = temp;

	// TODO: 在此处插入 return 语句
	return *this;
}
MyString& MyString::append(const MyString& s)
{
	int lenth_m = strlen(m_pbuf);
	char* temp = new char[lenth_m + strlen(s.m_pbuf) + 1];
	strcpy(temp, m_pbuf);
	strcpy(temp + lenth_m, s.m_pbuf);
	delete[] m_pbuf;
	m_pbuf = temp;

	// TODO: 在此处插入 return 语句
	return *this;
}
MyString& MyString::operator=(const MyString& p) {
	if (p.m_pbuf != m_pbuf)
	{
		if (m_pbuf != NULL) {
			delete[] m_pbuf;
		}
		m_pbuf = new char[strlen(p.m_pbuf) + 1];
		strcpy(m_pbuf, p.m_pbuf);
	}
	//cout << "MyString类的赋值运算符被调用，当前字符串为：" << m_pbuf << endl;
	return *this;
}
char & MyString::operator[](const int idx)
{
	if (idx < 0 || idx >= strlen(m_pbuf)) {
		exit(1);
	}
	return m_pbuf[idx];
}
const char MyString::operator[](const int idx) const
{
	if (idx < 0 || idx >= strlen(m_pbuf)) {
		exit(1);
	}
	return m_pbuf[idx];
}
MyString& MyString::operator()(const char* p)
{
	set_string(p);
	return *this;
}
MyString& MyString::operator()(const char* p, int n)
{
	int i = 0;
	for (i = 0; i < n && i < strlen(p); i++) {
		m_pbuf[i] = p[i];
	}
	m_pbuf[i] = '\0';
	return *this;
}
MyString& MyString::operator=(const char* p)
{
	this->set_string(p);
	return *this;
	// TODO: 在此处插入 return 语句
}
MyString::~MyString()
{
	//cout << "MyString类的析构函数被调用，当前字符串为：" << m_pbuf << endl;
	delete[] m_pbuf;
	num--;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MyString operator+(const MyString &str1, const MyString &str2)
{
	MyString temp(str1);
	temp.append(str2);
	return temp;
}
const bool operator<(const MyString & str1, const MyString &str2)
{
	if (str1.get_length() < str2.get_length()) {
		return true;
	}
	else {
		return false;
	}
}
const bool operator<=(const MyString &str1, const MyString &str2)
{
	if (str1.get_length() <=str2.get_length()) {
		return true;
	}
	else {
		return false;
	}
}
const bool operator>(const MyString &str1, const MyString &str2)
{
	if (str1.get_length() > str2.get_length()) {
		return true;
	}
	else {
		return false;
	}
}
const bool operator>=(const MyString  &str1, const MyString  &str2)
{
	if (str1.get_length() >= str2.get_length()) {
		return true;
	}
	else {
		return false;
	}
}
ostream & operator<<(ostream  & o,  const MyString  &str)
{
	o<<str.m_pbuf;
	return o;
	// TODO: 在此处插入 return 语句
}
istream& operator>>(istream& in, MyString& str)
{
	char* p = new char[MAX_LENTH];
	in >> p;
	if (in.eof()||in.fail()) {
		printf("输入有误\n");
		exit(0);
	}
	str.set_string(p);
	return in;
	// TODO: 在此处插入 return 语句
}
MyString& MyString::read(ifstream& in)
{
	char tem;
	if (m_pbuf != NULL) {
		delete[]m_pbuf;
	}
	int len;
	in >> len;
	tem=in.get();
	m_pbuf = new char[len + 1];
	in.read(m_pbuf, len);
	m_pbuf[len] = '\0';
	return *this;
	// TODO: 在此处插入 return 语句
}
void MyString::write(ofstream &o) const
{
	o << strlen(m_pbuf) << " " << m_pbuf;
}
void MyString::E_write(ofstream& o) const
{
	int len = strlen(m_pbuf);
	o.write((char*)&len, sizeof(int));
	o.write(m_pbuf, sizeof(char) * (len + 1));
}
MyString& MyString::E_read(ifstream& in) {
	delete[]m_pbuf;
	int len;
	in.read((char*)&len, sizeof(int));
	m_pbuf = new char[len + 1];
	in.read(m_pbuf, len + 1);
	return *this;
}