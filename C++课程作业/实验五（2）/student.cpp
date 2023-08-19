#include"student.h"
namespace N21281165 {
	CStudent::CStudent(int num, MyString & name, MyString & major, double score)
		: number(num), name(name), major(major), score(score) {
	}
	/*���ƹ��캯�������øú���ʱ��ִ�й����ǣ��ȵ���MyString��ĸ��ƹ��캯����ʼ��ѧ
	����ĳ�Աname��major��Ȼ��ִ�к������е�����*/
	CStudent::CStudent(const CStudent & stu)
		: number(stu.number), name(stu.name), major(stu.major), score(stu.score) {
	}
	MyString & CStudent::set_name(const MyString & name) {
		this->name = name;
		return this->name;
	}
	MyString & CStudent::set_major(const MyString & major) {
		this->major = major;
		return this->major;
	}
	CStudentList::CStudentList() {	/*���캯�����أ��޲ι��캯��*/
		gStu = NULL;
		count = 0;
		available = 0;
	}
	CStudentList::CStudentList(const CStudent &stu) {	/*���캯�����أ��вι��캯��*/
		gStu = new CStudent[BLOCK];
		gStu[0] = stu;//����Ĭ�ϵĸ�ֵ���������
		count = 1;
		available = BLOCK - 1;
	}
	CStudentList::CStudentList(const CStudentList &stu) :count(stu.count), available(stu.available) { /*���캯�����أ����ƹ��캯��*/
		int len = stu.count + stu.available;
		gStu = new CStudent[len];
		count = stu.count;
		available = stu.available;
		for (int i = 0; i < stu.count; i++) {
			gStu[i] = stu.gStu[i];
		}
	}
	CStudentList & CStudentList::operator = (const CStudentList &stu) {	/*��ֵ���������*/
		if (this != &stu) { //��ֹ�Ը�ֵ
			delete[] gStu;
			int len = stu.count + stu.available;
			gStu = new CStudent[len];
			count = stu.count;
			available = stu.available;
			for (int i = 0; i < stu.count; i++) {
				gStu[i] = stu.gStu[i];
			}
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
	void CStudentList::add_student(CStudent &stu) {	/*���ѧ��*/
		if (available == 0) {
			CStudent *tmp = new CStudent[count + BLOCK];
			for (int i = 0; i < count; i++) {
				tmp[i] = gStu[i];
			}

			delete gStu;
			gStu = tmp;
			available = BLOCK;
		}

		gStu[count] = stu;
		count++;
		available--;
	}
	/*
	ɾ��ѧ�����أ�������ɾ��ѧ��
	*/
	void CStudentList::delete_student(char*name) {
		int i;
		for (i = 0; i < count; i++) {
			if (strcmp(gStu[i].get_name().get_string(), name) == 0) {
				CStudent *tmp = new CStudent[count + available - 1];
				for (int j = 0; j < count; j++) {
					int cout = 0;
					if (j != i) {
						tmp[cout] = gStu[j];
						cout++;
					}
				}
				delete[] gStu;
				gStu = tmp;
				count--;
				break;
			}
		}
	}

	/*
	ɾ��ѧ������;��ѧ��ɾ��ѧ��
	*/
	void CStudentList::delete_student(int num) {
		int i;
		for (i = 0; i < count; i++) {
			if (gStu[i].get_number() == num) {
				CStudent *tmp = new CStudent[count + available - 1];
				for (int j = 0; j < count; j++) {
					int cout = 0;
					if (j != i) {
						tmp[cout] = gStu[j];
						cout++;
					}
				}
				delete[] gStu;
				gStu = tmp;
				count--;
				break;
			}
		}
	}

	CStudent &CStudentList::get_stu(char *name) {	/*��ȡѧ����Ϣ�������أ�����������ȡ*/
		for (int i = 0; i < count; i++) {
			if (strcmp(name, gStu[i].get_name().get_string()) == 0) {
				return gStu[i];
			}
		}
		return gStu[-1];//���طǷ���STUDENT�����㷵��ֵ���͵�Ҫ��
	}
	CStudent &CStudentList::get_stu(int num) {	/*��ȡѧ����Ϣ�������أ�����ѧ�Ż�ȡ*/
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_number() == num) {
				return gStu[i];
			}
		}
		return gStu[-1];//���طǷ���STUDENT�����㷵��ֵ���͵�Ҫ��
	}
	void CStudentList::display(int num) {	/*��ʾѧ����Ϣ�������أ�����ѧ����ʾѧ����Ϣ*/
		cout << "ѧ��\t����\tרҵ\t�ɼ�" << endl;
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_number() == num) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(char *name) {	/*��ʾѧ����Ϣ�������أ�����������ʾѧ����Ϣ*/
		cout << "ѧ��\t����\tרҵ\t�ɼ�" << endl;
		for (int i = 0; i < count; i++) {
			if (strcmp(gStu[i].get_name().get_string(),name)==0) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(double max_score, double min_score) {	/*��ʾѧ����Ϣ�������أ���ʾ�ɼ�������ѧ����Ϣ*/
		cout << "ѧ��\t����\tרҵ\t�ɼ�" << endl;
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_score() >= min_score && gStu[i].get_score() <= max_score) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(CStudent &p) {
		cout<<"ѧ��\t����\tרҵ\t�ɼ�"<<endl;
		for(int i=0; i<count; i++) {
			if(strcmp(p.get_name().get_string(),gStu[i].get_name().get_string())==0) {
				cout<<gStu[i].get_number()<<"\t"<<gStu[i].get_name().get_string()
				    <<"\t"<<gStu[i].get_major().get_string()<<"\t"<<gStu[i].get_score()<<endl;
			}
		}
	}
}

