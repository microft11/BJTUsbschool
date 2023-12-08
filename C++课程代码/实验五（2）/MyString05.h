#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include<string.h>
using namespace std;
class MyString {
		static int total; // 声明静态数据成员
	public:
		MyString();//不带参数的构造函数（重载版本1）
		MyString(const char *p);//带一个参数的构造函数 （重载版本2）
		const char * get_string() const {
			return m_pbuf;
		}
		const char * set_string(const char * p=NULL);
		const char * append(const char * p=NULL);
		MyString & append(MyString & s);
		MyString & append(const MyString & s);
		~MyString();//析构
		MyString(const MyString&);//复制构造函数 （重载版本3）
		MyString & operator = (const MyString &s);//赋值运算符重载
		MyString operator + (const MyString &str)const;//加号运算符重载
		char & operator[](const int idx);//下标运算符重载，非常版本，返回引用
		const char & operator[](const int idx)const; //下标运算符重载，常版本，返回值
		MyString & operator () (const char * p);//函数调用运算符重载
		int operator < (const MyString &str)const;
		int operator <= (const MyString &str)const;
		int operator > (const MyString &str)const;
		int operator >= (const MyString &str)const;
		operator const char*()const{return m_pbuf;}
		// 取得保存的字符串的长度，设为常成员
		int get_length() const;
		static int get_total() {
			return total;    // 定义静态函数
		}
	private:
		char * m_pbuf;

};
inline int MyString::get_length()const {
	return strlen(m_pbuf);
}
#endif

