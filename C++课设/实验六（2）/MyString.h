#ifndef MYSTRING_H
#define MYSTRING_H
#include<string.h>
#include<ostream>
#include<istream>
#include<fstream>
#define MAX_LENTH 100
using namespace std;
class MyString {
	//重载插入符
	friend ostream& operator <<(ostream& o, const MyString & str);//
	friend istream& operator >>(istream& in,MyString& str);
	friend MyString operator +(const MyString& str1, const MyString& str2);
	friend const bool operator <(const MyString &str1, const MyString &str2);
	friend const bool operator <=(const MyString &str1, const MyString &str2);
	friend const bool operator >(const MyString &str1, const MyString &str2);
	friend const bool operator >=(const MyString &str1, const MyString &str2);
public:
	//构造函数(无参数）
	MyString();
	//构造函数（一个参数，指向字符数组的指针）
	MyString(const char* str);
	//复制构造函数
	MyString(const MyString& s);
	//赋值函数
	const char* set_string(const char* str);
	//取值函数
	const char* get_string() const;
	//返回长度
	const int get_length() const;
	//追加字符串
	MyString& append(const char* str);
	MyString& append(const MyString& s);
	//赋值运算符函数
	MyString& operator =(const MyString& p);
	//其他重载函数
	char & operator[](const int idx);//非常成员使用
	const char operator[](const int idx) const;//常成员使用
	MyString& operator()(const char* p);
	MyString& operator()(const char* p, int n);
	//转型赋值函数
	MyString& operator =(const char* p);
	//文本读写
	MyString& read(ifstream& in);
	void write(ofstream &o)const;
	//二进制文件读写函数
	void E_write(ofstream& o) const;//
	MyString& E_read(ifstream& in);//
	//构析函数
	~MyString(); 
private:
	char* m_pbuf;
	const int MAXlenth;
	static int num;
};

//取值函数
inline const char* MyString::get_string() const {
	return m_pbuf;
}
//返回长度
inline const int MyString::get_length()const
{
	return strlen(m_pbuf);
}
#endif 

