#ifndef CSTUDENTL_H
#define CSTUDENTL_H
#include"Cnode.h"
#include<ostream>
#include<istream>
#include<fstream>
class CStudentList {
	//��Ԫ��
	friend ostream& operator <<(ostream& o, const MyString& str);
	friend class CAssociation;
public:
	CStudentList();
	CStudentList(CStudent& p);
	CStudentList(const CStudentList& p);//Ӧ�����
	///////////////////////////////////////////////////
	//����ѧ�������Ϣ
	int show_inform(const char* id);
	//���ݳɼ������Ϣ
	int show_inform(const int grade);
	//���ݳɼ����������Ϣ,Ĭ������Ϊ0
	int show_some_informs(int high, int low = 0);
	//�����õ�ѧ��������ڿ���̨��
	int show_inform(CStudent& p);
	//���ش����ѧ����Ϣ��ָ��
	CStudent* change_byna(const char* name);
	CStudent* change_byid(const char* id);
	//������Ϣ
	Cnode* set_information(CStudent& p);
	//����Ϣ
	int change_grade(CStudent* p, const int newgrade);
	int change_subject(CStudent* p, const char* newsubj);
	int change_id_byna(CStudent* p, const char* newid);
	int change_name_byid(CStudent* p, const char* newname);
	//ɾ��
	int dele_stud_byid(CStudent* p);
	//��ֵ���������
	CStudentList& operator =(const CStudentList& p);
	//�������������
	Cnode& operator[](int idx);
	CStudentList operator +(const CStudentList & List);
	//��ȡ����
	inline const int get_lenth() const ;
	//�ı���ȡ����
	CStudentList& read(ifstream & in);
	void write(ofstream& o) const;
	//�����ƶ�д����
	void E_write(ofstream& o);
	CStudentList & E_read(ifstream& in);
	//��������
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
