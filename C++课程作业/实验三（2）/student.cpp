#include"student.h"
CStudent::CStudent(int num, MyString& name, MyString& major, double score)
{
	number = num;
	this -> name = name;
	this -> major = major;
	this -> score = score;
}

CStudent::CStudent(const CStudent& stu)
{
	number = stu.number;
	name = stu.name;
	major = stu.major;
	score = stu.score;
}

MyString& CStudent::set_name(const MyString& name)
{
	this->name = name;
	return this->name;
}

MyString& CStudent::set_major(const MyString& major)
{
	this->major = major;
	return this->major;
}
