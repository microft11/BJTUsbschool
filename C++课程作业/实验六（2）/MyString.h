#ifndef MYSTRING_H
#define MYSTRING_H
#include<string.h>
#include<ostream>
#include<istream>
#include<fstream>
#define MAX_LENTH 100
using namespace std;
class MyString {
	//���ز����
	friend ostream& operator <<(ostream& o, const MyString & str);//
	friend istream& operator >>(istream& in,MyString& str);
	friend MyString operator +(const MyString& str1, const MyString& str2);
	friend const bool operator <(const MyString &str1, const MyString &str2);
	friend const bool operator <=(const MyString &str1, const MyString &str2);
	friend const bool operator >(const MyString &str1, const MyString &str2);
	friend const bool operator >=(const MyString &str1, const MyString &str2);
public:
	//���캯��(�޲�����
	MyString();
	//���캯����һ��������ָ���ַ������ָ�룩
	MyString(const char* str);
	//���ƹ��캯��
	MyString(const MyString& s);
	//��ֵ����
	const char* set_string(const char* str);
	//ȡֵ����
	const char* get_string() const;
	//���س���
	const int get_length() const;
	//׷���ַ���
	MyString& append(const char* str);
	MyString& append(const MyString& s);
	//��ֵ���������
	MyString& operator =(const MyString& p);
	//�������غ���
	char & operator[](const int idx);//�ǳ���Աʹ��
	const char operator[](const int idx) const;//����Աʹ��
	MyString& operator()(const char* p);
	MyString& operator()(const char* p, int n);
	//ת�͸�ֵ����
	MyString& operator =(const char* p);
	//�ı���д
	MyString& read(ifstream& in);
	void write(ofstream &o)const;
	//�������ļ���д����
	void E_write(ofstream& o) const;//
	MyString& E_read(ifstream& in);//
	//��������
	~MyString(); 
private:
	char* m_pbuf;
	const int MAXlenth;
	static int num;
};

//ȡֵ����
inline const char* MyString::get_string() const {
	return m_pbuf;
}
//���س���
inline const int MyString::get_length()const
{
	return strlen(m_pbuf);
}
#endif 

