#include"CStudentL.h"
CStudentList::CStudentList() :head(NULL), lenth(0)
{
}
CStudentList::CStudentList(CStudent& p) : head(new Cnode(&p)), lenth(1)
{
}
CStudentList::CStudentList(const CStudentList& p):head(NULL), lenth(0)
{
	if (p.lenth >= 1) {
		head = new Cnode(p.head->pstu);
		lenth++;
		Cnode* dp = p.head->next;
		Cnode* per = head;
		for (int i = 0; i < p.lenth-1; i++) {
			Cnode* temp = new Cnode(dp->pstu);
			per->next = temp;
			per = per->next;
			dp = dp->next;
			lenth++;
		}
	}
}
int CStudentList::show_inform(const char* id)//只能找到第一个学号与id相同的学生
{
	Cnode* fp = head;
	for (int i = 0; i < lenth; i++) {
		if (strcmp((*(*fp).pstu).get_id().get_string(), id) == 0) {
			std::cout << "学号\t" << "姓名\t" << "专业\t" << "成绩" << std::endl;
			show_inform((*(*fp).pstu));
			return 0;
		}
		fp = fp->next;
	}
	return 1;//不存在
}
int CStudentList::show_inform(const int grade)
{
	int flag = 0;
	Cnode* fp = head;
	for (int i = 0; i < lenth; i++) {
		if ((*(*fp).pstu).get_grade() == grade) {
			if (flag == 0) {
				std::cout << "学号\t" << "姓名\t" << "专业\t" << "成绩" << std::endl;
			}
			show_inform((*(*fp).pstu));
			flag++;
		}
		fp = fp->next;
	}
	if (flag == 0) {
		return 1;//不存在
	}
	else {
		return 0;
	}
}
int CStudentList::show_some_informs(int high, int low)
{
	int flag = 0;
	Cnode* fp = head;
	if (high < low) {
		flag = high;
		high = low;
		low = flag;
		flag = 0;
	}
	for (int i = 0; i < lenth; i++) {
		if ((*(*fp).pstu).get_grade() <= high && (*(*fp).pstu).get_grade() >= low) {
			if (flag == 0) {
				std::cout << "学号\t" << "姓名\t" << "专业\t" << "成绩" << std::endl;
			}
			show_inform((*(*fp).pstu));
			flag++;
		}
		fp = fp->next;
	}
	if (flag == 0) {
		return 1;//不存在
	}
	else {
		return 0;
	}
}
int CStudentList::show_inform(CStudent& p)
{
	std::cout << p.get_id().get_string() << '\t' << p.get_name().get_string() << '\t' << p.get_subject().get_string() << '\t' << p.get_grade() << '\n';
	return 0;
}
CStudent* CStudentList::change_byna(const char* name)
{
	Cnode* fp = head;
	for (int i = 0; i < lenth; i++) {
		if (0 == strcmp((*(*fp).pstu).get_name().get_string(), name)) {
			return (*fp).pstu;
		}
		fp = fp->next;
	}
	return NULL;
}
CStudent* CStudentList::change_byid(const char* id)
{
	Cnode* fp = head;
	for (int i = 0; i < lenth; i++) {
		if (0 == strcmp((*(*fp).pstu).get_id().get_string(), id)) {
			return (*fp).pstu;
		}
		fp = fp->next;
	}
	return NULL;
	// TODO: 在此处插入 return 语句
}
Cnode* CStudentList::set_information(CStudent& p)
{
	CStudent* fp = new CStudent(p);
	Cnode* ne = new Cnode;
	ne->pstu = fp;
	ne->next = head;
	head = ne;
	lenth++;
	return ne;
}
int CStudentList::change_grade(CStudent* p, const int newgrade)
{
	if (p == NULL) {
		return 1;//不存在
	}
	(*p).change_grade(newgrade);
	return 0;
}
int CStudentList::change_subject(CStudent* p, const char* newsubj)
{
	if (p == NULL) {
		return 1;//不存在
	}
	(*p).change_subject(newsubj);
	return 0;
}
int CStudentList::change_id_byna(CStudent* p, const char* newid)
{
	if (p == NULL) {
		return 1;//不存在
	}
	(*p).change_id(newid);
	return 0;
}
int CStudentList::change_name_byid(CStudent* p, const char* newname)
{
	if (p == NULL) {
		return 1;//不存在
	}
	(*p).change_name(newname);
	return 0;
}
int CStudentList::dele_stud_byid(CStudent* p)
{
	if (p == NULL) {
		return 1;//不存在
	}
	int j = 0;
	Cnode* temp = head;
	Cnode* pre = head;
	for (int i = 0; i < lenth; i++) {
		if (temp->pstu == p) {
			if (temp->ref != 0) {
				std::cout << "被社团引用中，无法删除\n" << std::endl;
				return 0;
			}
			else {
				if (pre == temp) {
					head = head->next;
					std::cout << "已删除" << pre->pstu->get_name().get_string() << std::endl;
					delete pre;
					break;
				}
				else {
					pre->next = temp->next;
					std::cout << "已删除" << temp->pstu->get_name().get_string() << std::endl;
					delete temp;
					break;
				}
			}
		}
		pre = temp;
		temp = temp->next;
	}
	lenth--;
	return 0;
}
CStudentList& CStudentList::operator=(const CStudentList& p)//深复制
{
	if (&p == this) {
		return *this;
	}
	else if (p.lenth >= 1) {
		head = new Cnode(p.head->pstu);
		lenth++;
		Cnode* dp = p.head->next;
		Cnode* per = head;
		for (int i = 0; i < p.lenth - 1; i++) {
			Cnode* temp = new Cnode(dp->pstu);
			per->next = temp;
			per = per->next;
			dp = dp->next;
			lenth++;
		}
		return *this;
	}
}
Cnode& CStudentList::operator[](int idx)
{
	Cnode* dp = head;
	if (idx < 0 || idx >= lenth) {
		exit(1);
	}
	for (int i = 0; i < idx; i++) {
		dp = dp->next;
	}
	// TODO: 在此处插入 return 语句
}
CStudentList& CStudentList::read(ifstream& in)
{
	char tem;
	in >> lenth;
	in.get();
	Cnode* dp = new Cnode;
	(*dp).pstu = new CStudent;
	(*dp).pstu->read(in);
	head = dp;
	for (int i = 0; i < lenth - 1; i++) {
		in.get();
		Cnode* temp = new Cnode;
		(*temp).pstu = new CStudent;
		(*temp).pstu->read(in);
		(*dp).next = temp;
		dp = temp;
	}
	return *this;
	// TODO: 在此处插入 return 语句
}
void CStudentList::write(ofstream& o) const
{
	o << lenth;
	Cnode* dp = head;
	for (int i = 0; i < lenth; i++) {
		o << " ";
		dp->pstu->write(o);
		dp = dp->next;
	}
}
void CStudentList::E_write(ofstream& o)
{
	o.write((char*)&lenth, sizeof(int));
	for (Cnode* temp = head; temp != NULL;temp=temp->next) {
		temp->pstu->E_write(o);
	}
}
CStudentList& CStudentList::E_read(ifstream& in)
{
	in.read((char*)&lenth, sizeof(int));
	Cnode* dp = new Cnode;
	(*dp).pstu = new CStudent;
	(*dp).pstu->E_read(in);
	head = dp;
	for (int i = 0; i < lenth - 1; i++) {
		Cnode* temp = new Cnode;
		(*temp).pstu = new CStudent;
		(*temp).pstu->E_read(in);
		(*dp).next = temp;
		dp = temp;
	}
	return *this;
}
CStudentList::~CStudentList()
{
	for (Cnode* temp = head; temp != NULL;) {
		Cnode* pp;
		pp = temp;
		temp = temp->next;
		delete pp;
	}
	//std::cout << "CStudentList的析构函数被调用" << std::endl;
}
CStudentList CStudentList::operator+(const CStudentList & List)
{
	CStudentList temp(*this);
	if (temp.lenth >= 1) {
		Cnode* per = &temp[temp.lenth - 1];
		if (List.lenth >= 1) {
			Cnode* dp = List.head;
			for (int i = 0; i < List.lenth - 1; i++) {
				Cnode* tp = new Cnode(dp->pstu);
				per->next = tp;
				per = per->next;
				dp = dp->next;
				temp.lenth++;
			}
		}
	}
	else {
		if (List.lenth >= 1) {
			temp.head = new Cnode(List.head->pstu);
			temp.lenth++;
			Cnode* dp = List.head->next;
			Cnode* per = temp.head;
			for (int i = 0; i < List.lenth - 1; i++) {
				Cnode* tp = new Cnode(dp->pstu);
				per->next = tp;
				per = per->next;
				dp = dp->next;
				temp.lenth++;
			}
		}
	}
	return temp;
	// TODO: 在此处插入 return 语句
}
