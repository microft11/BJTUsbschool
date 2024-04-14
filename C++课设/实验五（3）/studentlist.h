#pragma once
#include "student(1).h"
class CNode {
		friend class CStudentList;
		friend class CAssociation;
	public:
		CNode(CStudent *p):pstu(p),ref(0),next(NULL) { }
		~CNode() {
			delete pstu;
		}
	private:
		CNode(const CNode &);
		CNode &operator=(const CNode &node);
		CStudent *pstu;
		int ref;
		CNode *next;
};
class CStudentList {
	public:
		CStudentList():head(NULL),count(0) {}
		~CStudentList() {
			CNode *tmp=head.next;
			while(NULL!=tmp) {
				head.next=tmp->next;
				delete tmp;
				tmp=head.next;
			}
		}
		void add(CStudent *p) {
			CNode *tmp=new CNode(p);
			tmp->next=head.next;
			head.next=tmp;
			++count;
		}
		int del(int num) {
			CNode *tmp=head.next,*pre=NULL;
			while(NULL!=tmp) {
				if(tmp->pstu->get_number()!=num) {
					pre=tmp;
					tmp=tmp->next;
				} else {
					break;
				}
			}
			if(NULL==tmp) {
				return 1;
			} else if(tmp->ref>0) {
				return 2;
			} else {
				if(pre!=NULL) {
					pre->next=tmp->next;
					delete tmp;
					--count;
					return 0;
				} else {
					head.next = tmp->next;
					delete tmp;
					count--;
					return 0;
				}
			}
		}
		CNode *get(int num)const {
			CNode *tmp=head.next;
			while(NULL!=tmp) {
				if(tmp->pstu->get_number()!=num)
					tmp=tmp->next;
				else
					break;
			}
			if(NULL==tmp)
				return NULL;
			else
				return tmp;
		}
		int get_count() const {
			return count;
		}
		void display()const {
			cout<<"学号\t姓名\t专业\t成绩\t引用计数"<<endl;
			CNode *tmp=head.next;
			while(NULL!=tmp) {
				cout<<tmp->pstu->get_number()<<"\t"
				    <<tmp->pstu->get_name().get_string()<<"\t"
				    <<tmp->pstu->get_major().get_string()<<"\t"
				    <<tmp->pstu->get_score()<<"\t"
				    <<tmp->ref<<endl;
				tmp=tmp->next;
			}
		}
	private:
		CStudentList(const CStudentList &);
		CStudentList &operator=(const CStudentList &);
		CNode head;
		int count;
};
class CAssociation {
	public:
		CAssociation(MyString &s):name(s),ppList(NULL),count(0) {}
		~CAssociation() {
			for(int i=0; i<count; i++) {
				--ppList[i]->ref;
			}
			delete[] ppList;
		}
		//加号运算符函数
		CAssociation operator+(const CAssociation &s) const {
			ppList[count-1]->next=s.ppList[0];
			return *this;
		}

//下标运算符函数，返回引用，便于作为左值
		CNode & operator[](const int i) {
			if(i<0||i>=count)
				cout<<"CAssociation的下标运算符函数被调用，但超出下标范围"<<endl;
			else
				return *ppList[i];
		}

//下标运算符函数，常成员函数版本，返回值
		const CNode operator[](const int i) const {
			if(i<0||i>=count)
				cout<<"CAssociation的常版本下标运算符函数被调用，但超出下标范围"<<endl;
			else
				return *ppList[i];
		}

		int index(CNode *p) {
			int i=0;
			for(i=0; i<count; i++) {
				if(p==ppList[i])
					return i;
			}
			return -1;
		}
		void add(CNode *p) {
			if(NULL==p||index(p)>=0)
				return;
			else {
				CNode **tmp=new CNode*[count+1];
				for(int i=0; i<count; i++)
					tmp[i]=ppList[i];
				tmp[count]=p;
				++tmp[count]->ref;
				delete[] ppList;
				ppList=tmp;
				++count;
			}
		}
		int del(CNode *p) {
			int i=index(p);
			if(i<0)
				return 3;
			else {
				--ppList[i]->ref;
				CNode **tmp=NULL;
				if(count>1)
					tmp=new CNode *[count-1];
				for(int j=0; j<count; j++) {
					if(j==i)
						continue;
					if(j<i)
						tmp[j]=ppList[j];
					else
						tmp[j-1]=ppList[j];
				}
				delete[] ppList;
				ppList=tmp;
				--count;
				return 0;
			}
		}
		void display()const {
			cout<<name.get_string()<<"成员名单："<<endl;
			cout<<"学号\t姓名\t专业\t成绩"<<endl;
			for(int i=0; i<count; i++) {
				cout<<ppList[i]->pstu->get_number()<<"\t"
				    <<ppList[i]->pstu->get_name().get_string()<<"\t"
				    <<ppList[i]->pstu->get_major().get_string()<<"\t"
				    <<ppList[i]->pstu->get_score()<<endl;
			}
		}
	private:
		CAssociation(const CAssociation &);
		CAssociation &operator=(const CAssociation &);
		MyString name;
		CNode **ppList;
		int count;
};
void showError(int idx);
