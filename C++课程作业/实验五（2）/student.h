#ifndef _21281165_2_H_
#define _21281165_2_H_
#include<iostream>
#include"MyString05.h"
using namespace std;
namespace N21281165 {
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
		private:
			int number;
			MyString name;
			MyString major;
			double score;
	};
	class CStudentList {
#define BLOCK 10
		public:
			CStudentList();//无参构造函数
			CStudentList(const CStudent &stu);//含参构造函数
			CStudentList(const CStudentList &stu);//复制构造函数
			CStudentList & operator = (const CStudentList &stu);//赋值运算符函数
			CStudentList operator+(const CStudentList &s) const;	//加号运算符函数
			CStudent &operator[](const int i);		//下标运算符函数，返回引用，便于作为左值
			const CStudent operator[](const int i) const;	//下标运算符函数，常成员函数版本，返回值
			~CStudentList();//析构函数
			void add_student(CStudent &stu);	//添加学生
			void delete_student(char *name);//输入学号名字删除学生
			void delete_student(int num);//输入学号删除学生
			CStudent &get_stu(char *name);//重载：获取对应姓名学生信息
			CStudent &get_stu(int num);//重载：获取对应学号学生信息
			void display(int num);//显示学生信息函数重载：根据学号显示学生信息
			void display(char *name);//显示学生信息函数重载：根据姓名显示学生信息
			void display(double max_score = 100, double min_score = 60);//显示学生信息函数重载：根据给定的成绩区间显示学生信息(默认形参值）
			void display(CStudent &p);
		private:
			CStudent *gStu;
			int count;//已经加入的学生个数
			int available;//剩余的可用空间
	};
}
#endif

