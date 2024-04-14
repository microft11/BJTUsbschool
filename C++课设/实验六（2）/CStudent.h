#ifndef CSTUDENT_H
#define CSTUDENT_H
#include"MyString.h"
#include<iostream>
class CStudent {
public:
	friend ostream& operator <<(ostream& o, const CStudent& str);
	CStudent();
	CStudent(const MyString tname, const MyString tid, const MyString tsubject, int tgrade);
	CStudent(CStudent& p);
	const  MyString get_name();
	const MyString get_id();
	const MyString get_subject();
	const int get_grade();
	int change_stu(const char* tname, const char* tid, const char* tsubject,int tgrade);
	int change_name(const char* p);
	int change_id(const char* p);
	int change_subject(const char* p);
	int change_grade(int d);
	int back_lenth();
	CStudent& operator=(const CStudent& p);
	//文本读取
	CStudent& read(ifstream& in);
	void write(ofstream& o) const;//
	//二进制文本读取
	void E_write(ofstream& o) const;//
	CStudent& E_read(ifstream& in);//
	~CStudent();
private:
	MyString name;
	MyString id;
	MyString subject;
	int grade;
	static int lenth;
};
inline const MyString CStudent::get_name() {
	return name;
}
inline const MyString CStudent::get_id()
{
	return id;
}
inline const MyString CStudent::get_subject()
{
	return subject;
}
inline const int CStudent::get_grade()
{
	return grade;
}
inline int CStudent::back_lenth() {
	return lenth;
}
#endif
