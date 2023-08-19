
#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#include<iostream>
#include<string.h>
using namespace std;
class MyString
{
	static int total; // �˴�����Ϊ˽�����ݳ�Ա
public:
	MyString();
	MyString(const char* p);
	MyString(const MyString& s);
	~MyString();
	MyString& operator=(const MyString& s);
	// ȡ���ַ������׵�ַ
	const char* get_string() const { return m_pbuf; }
	// �� p ָ����ַ���������MyString����
	const char* set_string(const char* p = NULL);
	// �� p ָ����ַ���׷�ӵ�ԭ���ַ���֮��
	const char* append(const char* p = NULL);
	// �� s �����е��ַ���׷�ӵ���ǰ������ַ���֮�󲢷��ض���
	MyString& append(MyString& s);
	// ȡ�ñ�����ַ����ĳ���
	int get_length() const { return strlen(m_pbuf); }
	static int get_total() { return total; }
	MyString& read_text(istream& in); //�ı�ģʽ��ȡ����
	MyString& read_binary(istream& in); //������ģʽ��ȡ����
	void write_text(ostream& o); //�ı�ģʽ�������
	void write_binary(ostream& o); //������ģʽ�������
	//��������ı�ģʽ
	friend ostream& operator<< (ostream& o, const MyString& s);
private:
	char* m_pbuf;
};
#endif
