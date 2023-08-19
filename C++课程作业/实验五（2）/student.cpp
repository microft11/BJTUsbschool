#include"student.h"
namespace N21281165 {
	CStudent::CStudent(int num, MyString & name, MyString & major, double score)
		: number(num), name(name), major(major), score(score) {
	}
	/*复制构造函数。调用该函数时的执行过程是：先调用MyString类的复制构造函数初始化学
	生类的成员name和major，然后执行函数体中的内容*/
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
	CStudentList::CStudentList() {	/*构造函数重载：无参构造函数*/
		gStu = NULL;
		count = 0;
		available = 0;
	}
	CStudentList::CStudentList(const CStudent &stu) {	/*构造函数重载：有参构造函数*/
		gStu = new CStudent[BLOCK];
		gStu[0] = stu;//调用默认的赋值运算符函数
		count = 1;
		available = BLOCK - 1;
	}
	CStudentList::CStudentList(const CStudentList &stu) :count(stu.count), available(stu.available) { /*构造函数重载：复制构造函数*/
		int len = stu.count + stu.available;
		gStu = new CStudent[len];
		count = stu.count;
		available = stu.available;
		for (int i = 0; i < stu.count; i++) {
			gStu[i] = stu.gStu[i];
		}
	}
	CStudentList & CStudentList::operator = (const CStudentList &stu) {	/*赋值运算符函数*/
		if (this != &stu) { //防止自赋值
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
	//加号运算符函数
	CStudentList CStudentList::operator+(const CStudentList &stu) const {
		CStudentList sum(*this);
		for(int i=0; i<stu.count; i++) {
			//这里新开辟一个内存空间，否则每次添加的学生类地址一样，内容会覆盖
			CStudent *add_stu=new CStudent(stu.gStu[i]);
			sum.add_student(*add_stu);
		}
		return sum;
	}

//下标运算符函数，返回引用，便于作为左值
	CStudent & CStudentList::operator[](const int i) {
		if(i<0||i>=count)
			cout<<"CStudentList的下标运算符函数被调用，但超出下标范围"<<endl;
		else
			return gStu[i];
	}

//下标运算符函数，常成员函数版本，返回值
	const CStudent CStudentList::operator[](const int i) const {
		if(i<0||i>=count)
			cout<<"CStudentList的常版本下标运算符函数被调用，但超出下标范围"<<endl;
		else
			return gStu[i];
	}
	CStudentList::~CStudentList() {/*析构*/
		delete [] gStu;
	}
	void CStudentList::add_student(CStudent &stu) {	/*添加学生*/
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
	删除学生重载：按姓名删除学生
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
	删除学生重载;按学号删除学生
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

	CStudent &CStudentList::get_stu(char *name) {	/*获取学生信息函数重载：根据姓名获取*/
		for (int i = 0; i < count; i++) {
			if (strcmp(name, gStu[i].get_name().get_string()) == 0) {
				return gStu[i];
			}
		}
		return gStu[-1];//返回非法的STUDENT，满足返回值类型的要求
	}
	CStudent &CStudentList::get_stu(int num) {	/*获取学生信息函数重载：根据学号获取*/
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_number() == num) {
				return gStu[i];
			}
		}
		return gStu[-1];//返回非法的STUDENT，满足返回值类型的要求
	}
	void CStudentList::display(int num) {	/*显示学生信息函数重载：根据学号显示学生信息*/
		cout << "学号\t姓名\t专业\t成绩" << endl;
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_number() == num) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(char *name) {	/*显示学生信息函数重载：根据姓名显示学生信息*/
		cout << "学号\t姓名\t专业\t成绩" << endl;
		for (int i = 0; i < count; i++) {
			if (strcmp(gStu[i].get_name().get_string(),name)==0) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(double max_score, double min_score) {	/*显示学生信息函数重载：显示成绩区间内学生信息*/
		cout << "学号\t姓名\t专业\t成绩" << endl;
		for (int i = 0; i < count; i++) {
			if (gStu[i].get_score() >= min_score && gStu[i].get_score() <= max_score) {
				cout << gStu[i].get_number() << "\t" << gStu[i].get_name().get_string() << "\t" <<gStu[i].get_major().get_string() <<"\t"<< gStu[i].get_score() << "\t" << endl;
			}
		}
	}
	void CStudentList::display(CStudent &p) {
		cout<<"学号\t姓名\t专业\t成绩"<<endl;
		for(int i=0; i<count; i++) {
			if(strcmp(p.get_name().get_string(),gStu[i].get_name().get_string())==0) {
				cout<<gStu[i].get_number()<<"\t"<<gStu[i].get_name().get_string()
				    <<"\t"<<gStu[i].get_major().get_string()<<"\t"<<gStu[i].get_score()<<endl;
			}
		}
	}
}

