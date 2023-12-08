#include"MyString.h"
int MyString::total = 0;
ostream& operator<< (ostream& o, const MyString& s)
{
	o << s.get_length() << " " << s.m_pbuf; return o; //�ڳ��Ⱥ����һ���ո���Ϊ�ָ���
}
MyString& MyString::read_text(istream& in)
{
	delete[] m_pbuf; //���Ȼ���֮ǰ���ڴ�
	int len;
	in >> len; //��ȡ�ַ����ĳ���
	m_pbuf = new char[len + 1]; //׼���������ݵĿռ�
	in.get(); //�׵�����Ŀո�
	in.read(m_pbuf, len); //��ȡ����
	m_pbuf[len] = '\0'; //�������Ͻ�β����
	return *this;
}
MyString& MyString::read_binary(istream& in)
{
	delete[] m_pbuf; //���Ȼ���֮ǰ���ڴ�
	int len;
	in.read((char*)&len, sizeof(int)); //�ȶ�ȡ��Ҫ��ȡ���ַ����ĳ���
	m_pbuf = new char[len + 1]; //׼���������ݵĿռ䣺Ҫ��һ���ֽ����ڱ������ַ�
	in.read(m_pbuf, len); //��ȡlen���ֽڵ�m_pbufָ��Ŀռ�
	m_pbuf[len] = '\0'; //�������Ͻ�β����
	return *this;
}
void MyString::write_text(ostream& o) // �ı�ģʽ�������
{
	o << *this; //ͨ�����ò��������ʵ���ı�ģʽ�����
}
void MyString::write_binary(ostream& o) // ������ģʽ�������
{
	int len = strlen(m_pbuf); //ȡ���ַ���ռ�õĿռ�Ĵ�С�����ַ����ĳ���
	o.write((char*)&len, sizeof(int)); //���������д���ַ�����ռ�ռ�Ĵ�С
	o.write(m_pbuf, len);//��m_pbuf��ʼд��len���ֽڣ�ע�����һ�����ַ���δд��
}
