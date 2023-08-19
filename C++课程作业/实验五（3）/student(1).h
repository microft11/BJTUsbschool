#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "MyString05(1).h"
#include "studentlist.h"
#include<iostream>
using namespace std;
class CStudent {
	public:
		CStudent() { } //���캯��
		CStudent(int num, MyString & name, MyString & major, double score);//���ι��캯��
		CStudent(const CStudent & stu);//���캯��
		~CStudent() { } //��������
		void set_number(int num) {
			this->number = num;
		}
//�ú������ı��Ա��ֵ�������Ϊ����Ա����
		int get_number() const {
			return number;
		}
		MyString & set_name(const MyString & name);
//�������ã��Ӷ����Զ�name����һ������
		MyString & get_name() {
			return name;
		}
//����Ա��������ֵ���󣬸�������ʹ�ã����øú���ʱ�����MyString�ĸ��ƹ��캯��
//��ʼ������ֵ���󣬵ȷ������ִ����ϣ����������������������ʱ����
		MyString get_name() const {
			return name;
		}
		MyString & set_major(const MyString & major);
		MyString & get_major() {
			return major;
		}
//�� ����Ա����get_name�����˼·һ��
		MyString get_major() const {
			return major;
		}
		void set_score(double score) {
			this->score = score;
		}
		double get_score() const {
			return score;    //���ı����ݳ�Ա��ֵ����Ϊ����Ա
		}
//Ĭ�ϵĸ�ֵ�����
		CStudent & operator=(const CStudent & stu) {
			if (this != &stu) {
				number = stu.number;
				name = stu.name; //����MyString��ĸ�ֵ���������
				major = stu.major; //����MyString��ĸ�ֵ���������
				score = stu.score;
			}
			return *this;
		}
		//�Ӻ����������
		CStudentList CStudentList::operator+(const CStudentList &stu) const {
			CStudentList sum(*this);
			for(int i=0; i<stu.count; i++) {
				//�����¿���һ���ڴ�ռ䣬����ÿ����ӵ�ѧ�����ַһ�������ݻḲ��
				CStudent *add_stu=new CStudent(stu.gStu[i]);
				sum.add_student(*add_stu);
			}
			return sum;
		}

//�±�������������������ã�������Ϊ��ֵ
		CStudent & CStudentList::operator[](const int i) {
			if(i<0||i>=count)
				cout<<"CStudentList���±���������������ã��������±귶Χ"<<endl;
			else
				return gStu[i];
		}

//�±����������������Ա�����汾������ֵ
		const CStudent CStudentList::operator[](const int i) const {
			if(i<0||i>=count)
				cout<<"CStudentList�ĳ��汾�±���������������ã��������±귶Χ"<<endl;
			else
				return gStu[i];
		}
		CStudentList::~CStudentList() {/*����*/
			delete [] gStu;
		}
	private:
		int number;
		MyString name;
		MyString major;
		double score;
};
#endif
