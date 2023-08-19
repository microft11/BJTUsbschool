#ifndef _STUDENT_H_
#define _STUDENT_H_

#include"MyString.h"

class CStudent
{
public:
	CStudent() { } //默认的构造函数
	
	CStudent(int num, MyString& name, MyString& major, double score);
	//因不涉及深复制，故可省去；赋值运算符函数因同样的原因可省去
	
	CStudent(const CStudent& stu);
	
	~CStudent() { } //默认的析构函数
	
	void set_number(int num) { number = num; }
	
	int get_number() const { return number; }
	
	MyString& set_name(const MyString& name);
	//返回引用，从而可以对name作进一步运算
	
	MyString& get_name() { return name; }
	//常成员函数返回值对象，给常对象使用；调用该函数时会调用MyString的复制构造函数
	//初始化返回值对象，等返回语句执行完毕，会调用析构函数析构该临时对象
	
	MyString get_name() const { return name; }
	MyString& set_major(const MyString& major);
	MyString& get_major() { return major; }
	//与 常成员函数get_name的设计思路一致
	MyString get_major() const { return major; }
	void set_score(double score) { this->score = score; }
	double get_score() const { return score; } //不改变数据成员的值，设为常成员
	//默认的赋值运算符；因不涉及深复制，故可省去
	CStudent& operator=(const CStudent& stu)
	{
		if (this != &stu)
		{
			number = stu.number;
			name = stu.name; //调用MyString类的赋值运算符函数
			major = stu.major; //调用MyString类的赋值运算符函数
			score = stu.score;
		}
		return *this;
	}
private:
	int number;
	MyString name;
	MyString major;
	double score;
};

#endif
