#include<iostream>
#include"student.h"
using namespace std;
int main()
{
	//����CStudent��Ĭ�Ϲ��캯���������stu����ʱname��major��ԱҲ��ʹ��
	//MyString���Ĭ�Ϲ��캯����������
	CStudent stu;
	//����2��CStudent����Ŀռ䣬����ÿ�����󶼻����CStudent���Ĭ�Ϲ��캯����
	//���û��Ĭ�Ϲ��캯�������ֱ������
	CStudent* stu2 = new CStudent[2];
	delete[] stu2; //��ʱ����������CStudent���͵Ķ��󣺶���ÿ�������ȵ���
	//CStudent������������Ȼ���������MyString�����������
	//��������MyString��Ķ�Ӧ�Ĺ��캯��
	MyString name("zhangsan"), major("computer");
	//���ȵ�������MyString��ĸ��ƹ��캯����ʼ��ѧ��������name��major��Ա��
	//Ȼ�����ѧ�����Ӧ�Ĺ��캯��
	CStudent stu3(1234, name, major, 100);
	//���ȵ�������MyString��ĸ��ƹ��캯����ʼ��ѧ��������name��major��Ա��
	//Ȼ�����ѧ����ĸ��ƹ��캯��
	CStudent stu4(stu3);
	//���ȵ�������MyString��ĸ��ƹ��캯����ʼ��ѧ��������name��major��Ա��
	//Ȼ�����ѧ����ĸ��ƹ��캯��
	const CStudent stu5 = stu4;
	//stu4���ǳ����󣬿��Ե��÷ǳ���Ա����get_name()
	cout << stu4.get_name().get_string() << endl;
	//stu5�ǳ����󣬿��Ե��ó���Ա����get_name()�����û���ṩ�ó���Ա������
	//���������ֱ������
	cout << stu5.get_name().get_string() << endl;
	stu = stu4; //����ѧ����ĸ�ֵ���������
	cout << MyString::get_total() << endl; //���MyString��ĵ�ǰ����������ʱΪ10
	return 0;

}
