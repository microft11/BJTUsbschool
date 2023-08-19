#ifndef CSTUDENTL_H
#define CSTUDENTL_H
#include"Cnode.h"
#include<ostream>
#include<istream>
#include<fstream>
class CStudentList {
	//友元类
	friend ostream& operator <<(ostream& o, const MyString& str);
	friend class CAssociation;
public:
	CStudentList();
	CStudentList(CStudent& p);
	CStudentList(const CStudentList& p);//应该深复制
	///////////////////////////////////////////////////
	//根据学号输出信息
	int show_inform(const char* id);
	//根据成绩输出信息
	int show_inform(const int grade);
	//根据成绩区间输出信息,默认下限为0
	int show_some_informs(int high, int low = 0);
	//将引用的学生类输出在控制台上
	int show_inform(CStudent& p);
	//返回储存该学生信息的指针
	CStudent* change_byna(const char* name);
	CStudent* change_byid(const char* id);
	//存入信息
	Cnode* set_information(CStudent& p);
	//改信息
	int change_grade(CStudent* p, const int newgrade);
	int change_subject(CStudent* p, const char* newsubj);
	int change_id_byna(CStudent* p, const char* newid);
	int change_name_byid(CStudent* p, const char* newname);
	//删除
	int dele_stud_byid(CStudent* p);
	//赋值运算符函数
	CStudentList& operator =(const CStudentList& p);
	//重载运算符函数
	Cnode& operator[](int idx);
	CStudentList operator +(const CStudentList & List);
	//获取长度
	inline const int get_lenth() const ;
	//文本读取函数
	CStudentList& read(ifstream & in);
	void write(ofstream& o) const;
	//二进制读写函数
	void E_write(ofstream& o);
	CStudentList & E_read(ifstream& in);
	//析构函数
	~CStudentList();
	//////////////////////////////////////////

private:
	Cnode* head;
	int lenth;
};
inline const int CStudentList::get_lenth() const
{
	return lenth;
}
#endif
