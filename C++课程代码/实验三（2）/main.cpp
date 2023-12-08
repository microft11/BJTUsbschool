#include<iostream>
#include"student.h"
using namespace std;
int main()
{
	//调用CStudent的默认构造函数构造对象stu，此时name和major成员也会使用
	//MyString类的默认构造函数构造它们
	CStudent stu;
	//申请2个CStudent对象的空间，对于每个对象都会调用CStudent类的默认构造函数；
	//如果没有默认构造函数则会出现编译错误
	CStudent* stu2 = new CStudent[2];
	delete[] stu2; //此时会析构两个CStudent类型的对象：对于每个对象，先调用
	//CStudent的析构函数，然后调用两次MyString类的析构函数
	//调用两次MyString类的对应的构造函数
	MyString name("zhangsan"), major("computer");
	//首先调用两次MyString类的复制构造函数初始化学生类对象的name和major成员，
	//然后调用学生类对应的构造函数
	CStudent stu3(1234, name, major, 100);
	//首先调用两次MyString类的复制构造函数初始化学生类对象的name和major成员，
	//然后调用学生类的复制构造函数
	CStudent stu4(stu3);
	//首先调用两次MyString类的复制构造函数初始化学生类对象的name和major成员，
	//然后调用学生类的复制构造函数
	const CStudent stu5 = stu4;
	//stu4不是常对象，可以调用非常成员函数get_name()
	cout << stu4.get_name().get_string() << endl;
	//stu5是常对象，可以调用常成员函数get_name()；如果没有提供该常成员函数，
	//则该语句会出现编译错误
	cout << stu5.get_name().get_string() << endl;
	stu = stu4; //调用学生类的赋值运算符函数
	cout << MyString::get_total() << endl; //输出MyString类的当前对象数，此时为10
	return 0;

}
