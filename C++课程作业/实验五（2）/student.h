#ifndef _21281165_2_H_
#define _21281165_2_H_
#include<iostream>
#include"MyString05.h"
using namespace std;
namespace N21281165 {
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
		private:
			int number;
			MyString name;
			MyString major;
			double score;
	};
	class CStudentList {
#define BLOCK 10
		public:
			CStudentList();//�޲ι��캯��
			CStudentList(const CStudent &stu);//���ι��캯��
			CStudentList(const CStudentList &stu);//���ƹ��캯��
			CStudentList & operator = (const CStudentList &stu);//��ֵ���������
			CStudentList operator+(const CStudentList &s) const;	//�Ӻ����������
			CStudent &operator[](const int i);		//�±�������������������ã�������Ϊ��ֵ
			const CStudent operator[](const int i) const;	//�±����������������Ա�����汾������ֵ
			~CStudentList();//��������
			void add_student(CStudent &stu);	//���ѧ��
			void delete_student(char *name);//����ѧ������ɾ��ѧ��
			void delete_student(int num);//����ѧ��ɾ��ѧ��
			CStudent &get_stu(char *name);//���أ���ȡ��Ӧ����ѧ����Ϣ
			CStudent &get_stu(int num);//���أ���ȡ��Ӧѧ��ѧ����Ϣ
			void display(int num);//��ʾѧ����Ϣ�������أ�����ѧ����ʾѧ����Ϣ
			void display(char *name);//��ʾѧ����Ϣ�������أ�����������ʾѧ����Ϣ
			void display(double max_score = 100, double min_score = 60);//��ʾѧ����Ϣ�������أ����ݸ����ĳɼ�������ʾѧ����Ϣ(Ĭ���β�ֵ��
			void display(CStudent &p);
		private:
			CStudent *gStu;
			int count;//�Ѿ������ѧ������
			int available;//ʣ��Ŀ��ÿռ�
	};
}
#endif

