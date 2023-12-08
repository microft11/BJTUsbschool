#ifndef CNODE_H
#define CNODE_H
#include<ostream>
#include<istream>
#include<fstream>
#include"CStudent.h"
class Cnode {
	friend class CAssociation;
	friend class CStudentList;
public:
	Cnode() :pstu(NULL), next(NULL), ref(0) {
	}
	Cnode(CStudent* fp) :pstu(new CStudent (*fp)), next(NULL), ref(0) {

	}
	~Cnode() {
		delete pstu;
	}
private:
	class CStudent* pstu;
	class Cnode* next;
	int ref;
};

#endif

