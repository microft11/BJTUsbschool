#include "CStudentList.h"
#include<string.h>
CStudentList::CStudentList()
{
	p_st =new SNode;
	p_st->num = 0;
}
CStudentList::CStudentList(const Student s)
{
	if (s->num==0)
	{
		p_st = new SNode;
		p_st->num = 0;
	}
	else {
		p_st = new SNode[s->num+1];
		p_st->num = s->num;
		p_st->next = new SNode;
		Student p=p_st->next;
		Student p1 = s->next;
		for (int i = 0; i < s->num; i++)
		{
			strcpy(p->name, p1->name);
			p->num = p1->num;
			p->score = p1->score;
			p->next = new SNode;
			p = p->next;
			p1 = p1->next;
		}
	}
}
CStudentList::~CStudentList()
{
	delete[] p_st;
}
CStudentList& CStudentList::operator=(const CStudentList& sl)
{
	if (this != &sl)
	{
		delete[] p_st;
		p_st = new SNode[sl.p_st->num+1];
		p_st->num = sl.p_st->num;
		p_st->next = new SNode;
		Student p = p_st->next;
		Student p1 = sl.p_st->next;
		for (int i = 0; i < p_st->num; i++)
		{
			strcpy(p->name, p1->name);
			p->num = p1->num;
			p->score = p1->score;
			p->next = new SNode;
			p = p->next;
			p1 = p1->next;
		}
	}
	return *this;
}
bool CStudentList::get_inform(const int& i)
{
	int len = this->getlen();
	int r = 0;
	cout << "学号为" << i << "的学生：" << endl;
	Student p = p_st->next;
	for (int j=0; j < len; j++)
	{
		if (p->num == i)
		{
			r = 1;
			cout <<"学生姓名:" << p->name <<'\t'<<"学生学号：" << p->num << '\t' << "学生成绩：" << p->score << endl;
		}
		p = p->next;
	}
	if (r == 1)
	{
		return true;
	}
	else {
		cout << "不存在该学号" << endl;
		return false;
	}
}
bool CStudentList::get_inform(const int low_sc,const int high_sc)
{
	int len = this->getlen();
	Student p = p_st->next;
	if (low_sc < 0 || high_sc<0 || low_sc>high_sc)
	{
		cout << "输入错误" << endl;
		return false;
	}
	if (low_sc == high_sc)
	{
		cout << "分数为" << low_sc << "的学生:" << endl;
	}
	else {
		cout << "分数在" << low_sc << "与" << high_sc << "之间的学生:" << endl;
	}
	for (int i = 0; i < len; i++)
	{
		if (p->score >= low_sc && p->score <= high_sc)
		{
			cout<<"学生姓名:" << p->name << '\t' << "学生学号：" << p->num << '\t' << "学生成绩：" << p->score << endl;
		}
		p = p->next;
	}
	return true;
}
bool CStudentList::get_inform(const char* nm,SNode& s)
{
	Student p = p_st->next;
	int len = this->getlen();
	for (int j = 0; j < len; j++)
	{
		if (!strcmp(p->name, nm))
		{
			cout << "学生姓名:" << p->name << '\t' << "学生学号：" << p->num << '\t' << "学生成绩：" << p->score << endl;
			strcpy(s.name, p->name);
			s.num = p->num;
			s.score = p->score;
			return true;
		}
		p = p->next;
	}
	cout << "不存在该姓名" << endl;
	return false;
}
bool CStudentList::modify_score(const SNode s)
{
	Student p = p_st->next;
	int len = this->getlen();
	for (int j = 0; j < len; j++)
	{
		if (!strcmp(p->name, s.name))
		{
			int new_score;
			cout << "将该学生的成绩改为:";
			cin >> new_score;
			p->score = new_score;
			cout << "更改后的学生信息:" << endl;
			cout << "学生姓名:" << p->name << '\t' << "学生学号：" << p->num << '\t' << "学生成绩：" << p->score << endl;
			return true;
		}
		p = p->next;
	}
	return false;
}

CStudentList::CStudentList(const CStudentList & stu)
{
	p_st = new SNode[stu.p_st -> num + 1];
	p_st -> num = stu.p_st -> num;
	p_st -> next = new SNode;
	Student p = p_st -> next;
	Student p1 = stu.p_st -> next;
	for(int i = 0; i < p_st -> num; i ++)
	{
		strcpy(p -> name, p1 -> name);
		p -> num = p1 -> num;
		p -> score = p1 -> score;
		p -> next = new SNode;
		p = p -> next;
		p1 = p1 -> next;
	}
}

int main()
{
	Student p1=new SNode;
	p1->num = 1;
	p1->next = new SNode;
	Student p = p1->next;
	strcpy(p->name, "ssss");
	p->num = 1;
	p->score = 100;
	CStudentList s(p1);
	SNode e;
	s.get_inform("ssss",e);
	s.modify_score(e);
	return 0;
}
