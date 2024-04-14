#ifndef _CStudentList_H
#define _CStudentList_H
#include<iostream>
using namespace std;
typedef struct student{
	char name[20];
	int num;
	int score;
	struct student* next;
}*Student,SNode;
class CStudentList
{
public:
	CStudentList();//默认构造函数
	CStudentList(const Student s);//构造函数
	~CStudentList();//析构函数
	int getlen() { return p_st->num; }
	CStudentList& operator=(const CStudentList& sl);//赋值运算符函数
	CStudentList(const CStudentList & stu);//赋值构造函数 
	bool get_inform(const int& i=-1);//通过学号查找学生信息
	bool get_inform(const int low_sc=-1, const int high_sc=-1);//通过分数(段)查找学生信息
	bool modify_score(const SNode s);//修改分数
	bool get_inform(const char* nm, SNode& s);//通过姓名查找学生信息
private:
	Student p_st;
};
#endif
