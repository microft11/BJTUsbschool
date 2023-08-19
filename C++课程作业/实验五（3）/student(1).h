#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "MyString05(1).h"
#include "studentlist.h"
#include<iostream>
using namespace std;
class CStudent {
	public:
		CStudent() { } //构造函数
		CStudent(int num, MyString & name, MyString & major, double score);//含参构造函数
		CStudent(const CStudent & stu);//构造函数
		~CStudent() { } //析构函数
		void set_number(int num) {
			this->number = num;
		}
//该函数不改变成员的值，故设计为常成员函数
		int get_number() const {
			return number;
		}
		MyString & set_name(const MyString & name);
//返回引用，从而可以对name作进一步运算
		MyString & get_name() {
			return name;
		}
//常成员函数返回值对象，给常对象使用；调用该函数时会调用MyString的复制构造函数
//初始化返回值对象，等返回语句执行完毕，会调用析构函数析构该临时对象
		MyString get_name() const {
			return name;
		}
		MyString & set_major(const MyString & major);
		MyString & get_major() {
			return major;
		}
//与 常成员函数get_name的设计思路一致
		MyString get_major() const {
			return major;
		}
		void set_score(double score) {
			this->score = score;
		}
		double get_score() const {
			return score;    //不改变数据成员的值，设为常成员
		}
//默认的赋值运算符
		CStudent & operator=(const CStudent & stu) {
			if (this != &stu) {
				number = stu.number;
				name = stu.name; //调用MyString类的赋值运算符函数
				major = stu.major; //调用MyString类的赋值运算符函数
				score = stu.score;
			}
			return *this;
		}
		//加号运算符函数
		CStudentList CStudentList::operator+(const CStudentList &stu) const {
			CStudentList sum(*this);
			for(int i=0; i<stu.count; i++) {
				//这里新开辟一个内存空间，否则每次添加的学生类地址一样，内容会覆盖
				CStudent *add_stu=new CStudent(stu.gStu[i]);
				sum.add_student(*add_stu);
			}
			return sum;
		}

//下标运算符函数，返回引用，便于作为左值
		CStudent & CStudentList::operator[](const int i) {
			if(i<0||i>=count)
				cout<<"CStudentList的下标运算符函数被调用，但超出下标范围"<<endl;
			else
				return gStu[i];
		}

//下标运算符函数，常成员函数版本，返回值
		const CStudent CStudentList::operator[](const int i) const {
			if(i<0||i>=count)
				cout<<"CStudentList的常版本下标运算符函数被调用，但超出下标范围"<<endl;
			else
				return gStu[i];
		}
		CStudentList::~CStudentList() {/*析构*/
			delete [] gStu;
		}
	private:
		int number;
		MyString name;
		MyString major;
		double score;
};
#endif
