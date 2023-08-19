#include"MyString.h"
#include<string.h>
bool testMyStringIO()
{
	MyString str("I love C++ programming!"), str2("haha");
	ofstream out("MyString.txt");
	//1. �ı�ģʽ��ʹ�ò����д���ݣ�ʹ��read_text������
	out << str;
	out.close();
	ifstream in("MyString.txt");
	str2.read_text(in);
	in.close();
	//��ȡ���ַ�����ԭ�ַ�����ͬ����Բ�ͨ��
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	//2. �ı�ģʽ��ʹ��write_textд���ݣ�ʹ��read_text������
	out.open("MyString.txt"); //���ļ������ԭ����
	str.write_text(out);
	out.close();
	in.open("MyString.txt");
	str2.read_text(in);
	in.close();
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	//3. ������ģʽ��ʹ��write_binaryд���ݣ�ʹ��read_binary������
	out.open("MyString.dat");
	str.write_binary(out);
	out.close();
	in.open("MyString.dat");
	str2.read_binary(in);
	in.close();
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	return true;
}
int main()
{
	if (testMyStringIO()) //����MyString����ļ���д�����Ƿ���ȷ
		cout << "MyString IO OK" << endl;
	else
		cout << "MyString IO failed" << endl;
	return 0;
}
