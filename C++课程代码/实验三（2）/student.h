#ifndef _STUDENT_H_
#define _STUDENT_H_

#include"MyString.h"

class CStudent
{
public:
	CStudent() { } //Ĭ�ϵĹ��캯��
	
	CStudent(int num, MyString& name, MyString& major, double score);
	//���漰��ƣ��ʿ�ʡȥ����ֵ�����������ͬ����ԭ���ʡȥ
	
	CStudent(const CStudent& stu);
	
	~CStudent() { } //Ĭ�ϵ���������
	
	void set_number(int num) { number = num; }
	
	int get_number() const { return number; }
	
	MyString& set_name(const MyString& name);
	//�������ã��Ӷ����Զ�name����һ������
	
	MyString& get_name() { return name; }
	//����Ա��������ֵ���󣬸�������ʹ�ã����øú���ʱ�����MyString�ĸ��ƹ��캯��
	//��ʼ������ֵ���󣬵ȷ������ִ����ϣ����������������������ʱ����
	
	MyString get_name() const { return name; }
	MyString& set_major(const MyString& major);
	MyString& get_major() { return major; }
	//�� ����Ա����get_name�����˼·һ��
	MyString get_major() const { return major; }
	void set_score(double score) { this->score = score; }
	double get_score() const { return score; } //���ı����ݳ�Ա��ֵ����Ϊ����Ա
	//Ĭ�ϵĸ�ֵ����������漰��ƣ��ʿ�ʡȥ
	CStudent& operator=(const CStudent& stu)
	{
		if (this != &stu)
		{
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

#endif
