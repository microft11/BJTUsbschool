#include"student.h"
	CStudent::CStudent(int num, MyString & name, MyString & major, double score)
		: number(num), name(name), major(major), score(score) {
	}
	/*���ƹ��캯�������øú���ʱ��ִ�й����ǣ��ȵ���MyString��ĸ��ƹ��캯����ʼ��ѧ
	����ĳ�Աname��major��Ȼ��ִ�к������е�����*/
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
