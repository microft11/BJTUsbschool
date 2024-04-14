#include<iostream>
#include"student(1).h"
#include"studentlist.h"
using namespace std;
int main() {
	int code = 0;
	CNode *p = NULL;
	CStudentList stuList;//默认构造函数
	CStudent stu;//默认构造函数
	MyString AssociationName("football");//有参构造函数
	CAssociation association(AssociationName);
	char choice = '\0';
	while(choice!='0') {
		cout << "请选择操作：" << endl;
		cout << "学生社团信息管理系统：" << endl;
		cout << "1.录入新的学生" << endl;
		cout << "2.删除学生列表中的学生" << endl;
		cout << "3.录入新的学生到学生社团" << endl;
		cout << "4.删除学生社团中的学生" << endl;
		cout << "5.显示学生列表中的学生" << endl;
		cout << "6.显示学生社团中的学生" << endl;
		cout << "7.测试加法运算符" << endl;
		cout << "8.测试下标运算符" << endl;
		cout << "0.退出系统" << endl;
		cin >> choice;
		switch (choice) {
			case 1: {
				int number;
				char stuname[20];
				char stumajor[20];
				double score;
				cout<<"请依次输入学号、姓名、专业和成绩："<< endl;
				cin>>number>>stuname>>stumajor>>score;
				MyString name(stuname);
				MyString major(stumajor);
				stu.set_number(number);
				stu.set_name(name);
				stu.set_major(major);
				stu.set_score(score);
				CStudent *add_stu = new CStudent(stu);//为新添加的学生类来开辟新的内存空间
				stuList.add(add_stu);
				break;
			}
			case 2: {
				int num;
				cout << "请输入要删除的学生的学号：" << endl;
				cin >> num;
				code=stuList.del(num);
				showError(code);
				break;
			}

			case 3: {
				int number;
				cout << "请输入要加入的学生的学号:" << endl;
				cin >> number;
				p = stuList.get(number);
				association.add(p);
				break;
			}

			case 4: {
				int num;
				cout << "请输入要删除的学生的学号：" << endl;
				cin >> num;
				p = stuList.get(num);
				code=association.del(p);
				showError(code);
				break;
			}
			case 5: {
				stuList.display();
				break;
			}
			case 6: {
				association.display();
				break;
			}
			
			case 0: {
				return 0;
				break;
			}
			default:
				cout << "输入有误" << endl;
		}
	}
}
