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
	CStudentList();//Ĭ�Ϲ��캯��
	CStudentList(const Student s);//���캯��
	~CStudentList();//��������
	int getlen() { return p_st->num; }
	CStudentList& operator=(const CStudentList& sl);//��ֵ���������
	CStudentList(const CStudentList & stu);//��ֵ���캯�� 
	bool get_inform(const int& i=-1);//ͨ��ѧ�Ų���ѧ����Ϣ
	bool get_inform(const int low_sc=-1, const int high_sc=-1);//ͨ������(��)����ѧ����Ϣ
	bool modify_score(const SNode s);//�޸ķ���
	bool get_inform(const char* nm, SNode& s);//ͨ����������ѧ����Ϣ
private:
	Student p_st;
};
#endif
