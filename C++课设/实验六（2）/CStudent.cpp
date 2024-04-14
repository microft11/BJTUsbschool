#include"CStudent.h"
int CStudent::lenth = 0;
ostream& operator<<(ostream& o, const CStudent& str)
{
	o << str.name.get_length() << " " << str.name.get_string() << str.id.get_length() << " " << str.id.get_string() << " " << str.subject.get_length() << " " << str.subject.get_string() << " " << (char*)str.grade << " ";
	return o;
	// TODO: 在此处插入 return 语句
}
CStudent::CStudent():grade(-1)
{
	lenth++;
	//std::cout << "CStudent类的无参构造函数被调用" << std::endl;
}
CStudent::CStudent(const MyString tname, const MyString tid, const MyString tsubject, int tgrade) :name(tname), id(tid), subject(tsubject), grade(tgrade)
{
	lenth++;
	//std::cout << "CStudent类的有参构造函数被调用" << std::endl;
}
CStudent::CStudent(CStudent& p):name(p.get_name()),subject( p.get_subject()),id( p.get_id()), grade(p.get_grade())
{

}
int CStudent::change_stu(const char* tname, const char* tid, const char* tsubject,int tgrade)
{
	name.set_string(tname);
	id.set_string(tid);
	subject.set_string(tsubject);
	grade=tgrade;
	return 0;
}
int CStudent::change_name(const char* p)
{
	name.set_string(p);
	return 0;
}
int CStudent::change_id(const char* p)
{
	id.set_string(p);
	return 0;
}
int CStudent::change_subject(const char* p)
{
	subject.set_string(p);
	return 0;
}
int CStudent::change_grade(int d)
{
	grade = d;
	return 0;
}
CStudent& CStudent::operator=(const CStudent& p)
{
	if (&p != this) {
		name.set_string(p.name.get_string());
		id.set_string(p.id.get_string());
		subject.set_string(p.subject.get_string());
		grade = p.grade;
	}
	return *this;
	// TODO: 在此处插入 return 语句
}
CStudent& CStudent::read(ifstream& in)
{
	name.read(in);
	in.get();
	id.read(in);
	in.get();
	subject.read(in);
	in.get();
	in >> grade;
	return *this;
	// TODO: 在此处插入 return 语句
}
void CStudent::write(ofstream& o) const
{
	name.write(o);
	o << " ";
	id.write(o);
	o << " ";
	subject.write(o);
	o << " " << grade;
}
void CStudent::E_write(ofstream& o) const
{
	name.E_write(o);
	id.E_write(o);
	subject.E_write(o);
	o.write((char*)&grade, sizeof(int));
}
CStudent& CStudent::E_read(ifstream& in)
{
	name.E_read(in);
	id.E_read(in);
	subject.E_read(in);
	in.read((char*)&grade, sizeof(int));
	return *this;
	// TODO: 在此处插入 return 语句
}
CStudent::~CStudent()
{
	lenth--;
	//std::cout << "CStudent类的构析函数被调用" << std::endl;
}