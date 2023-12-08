#include"student.h"
	CStudent::CStudent(int num, MyString & name, MyString & major, double score)
		: number(num), name(name), major(major), score(score) {
	}
	/*复制构造函数。调用该函数时的执行过程是：先调用MyString类的复制构造函数初始化学
	生类的成员name和major，然后执行函数体中的内容*/
	CStudent::CStudent(const CStudent & stu)
		: number(stu.number), name(stu.name), major(stu.major), score(stu.score) {
	}
	MyString & CStudent::set_name(const MyString & name) {
		this->name = name;
		return this->name;
	}
	MyString & CStudent::set_major(const MyString & major) {
		this->major = major;
		return this->major;
	}
