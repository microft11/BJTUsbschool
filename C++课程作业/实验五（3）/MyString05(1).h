#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include<string.h>
using namespace std;
class MyString {
		static int total; // ������̬���ݳ�Ա
	public:
		MyString();//���������Ĺ��캯�������ذ汾1��
		MyString(const char *p);//��һ�������Ĺ��캯�� �����ذ汾2��
		const char * get_string() const {
			return m_pbuf;
		}
		const char * set_string(const char * p=NULL);
		const char * append(const char * p=NULL);
		MyString & append(MyString & s);
		MyString & append(const MyString & s);
		~MyString();//����
		MyString(const MyString&);//���ƹ��캯�� �����ذ汾3��
		MyString & operator = (const MyString &s);//��ֵ���������
		MyString operator + (const MyString &str)const;//�Ӻ����������
		char & operator[](const int idx);//�±���������أ��ǳ��汾����������
		const char & operator[](const int idx)const; //�±���������أ����汾������ֵ
		MyString & operator () (const char * p);//�����������������
		int operator < (const MyString &str)const;
		int operator <= (const MyString &str)const;
		int operator > (const MyString &str)const;
		int operator >= (const MyString &str)const;
		operator const char*()const{return m_pbuf;}
		// ȡ�ñ�����ַ����ĳ��ȣ���Ϊ����Ա
		int get_length() const;
		static int get_total() {
			return total;    // ���徲̬����
		}
	private:
		char * m_pbuf;

};
inline int MyString::get_length()const {
	return strlen(m_pbuf);
}
#endif

