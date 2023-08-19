#include"student.h"

using namespace N21281165;

int main() {
	CStudentList STU;

	char choice = '\0';

	CStudent stu;

	while (choice != '0') {
		cout << "学生信息管理系统：" << endl;
		cout << "1.录入新的学生" << endl;
		cout << "2.删除学生信息" << endl;
		cout << "3.修改学生成绩信息" << endl;
		cout << "4.显示学生信息" << endl;
		cout << "5.使用有参构造函数初始化" << endl;
		cout << "6.使用复制构造函数初始化" << endl;
		cout << "7.测试将两个学生列表相加"<<endl;
		cout << "8.测试取指定下标的学生"<<endl;
		cout << "9.退出系统" << endl;
		cout << "请选择想要进行的操作：" << endl;
		cin >> choice;
		switch (choice) {
			case '1': {
				int number;
				char name[20];
				char major[20];
				double score;
				cout << "请依次输入学号、姓名、专业和成绩：" << endl;
				cin >> number >> name >> major >> score;
				stu.set_number(number);
				stu.set_name(name);
				stu.set_major(major);
				stu.set_score(score);
				STU.add_student(stu);
				break;
			}
			case '2': {
				char choice1 = '\0';
				cout << "请选择想要进行的删除操作：" << endl;
				cout << "1.按姓名删除学生信息" << endl;
				cout << "2.按学号删除学生信息" << endl;
				cin >> choice1;
				if (choice1 == '1') {
					char name[20];
					cout << "请输入要删除的学生的姓名：" << endl;
					cin >> name;
					STU.delete_student(name);
					break;
				} else if (choice1 == '2') {
					int num;
					cout << "请输入要删除的学生的学号：" << endl;
					cin >> num;
					STU.delete_student(num);
					break;
				} else {
					cout << "请输入正确的选项！" << endl;
					break;
				}
			}

			case '3': {
				char choice2 = '\0';
				cout << "请输入想要进行的修改操作：" << endl;
				cout << "1.输入要修改成绩的学生的姓名" << endl;
				cout << "2.输入要修改成绩的学生的学号" << endl;
				cin >> choice2;
				if (choice2 == '1') {
					char name[20];
					int score;
					cout << "请输入要修改的学生的姓名：" << endl;
					cin >> name;
					cout << "请输入新的成绩：" << endl;
					cin >> score;
					STU.get_stu(name).set_score(score);
					break;
				} else if (choice2 == '2') {
					int num;
					int score;
					cout << "请输入要修改的学生的学号：" << endl;
					cin >> num;
					cout << "请输入新的成绩：" << endl;
					cin >> score;
					STU.get_stu(num).set_score(score);
					break;
				} else {
					cout << "无此选项，请您重新选择" << endl;
				}
			}

			case '4': {
				char choice3 = '\0';
				cout << "请选择想要显示方式：" << endl;
				cout << "1.根据学号显示学生信息" << endl;
				cout << "2.根据姓名显示学生信息" << endl;
				cout << "3.显示成绩区间学生的信息" << endl;
				cin >> choice3;
				if (choice3 == '1') {
					int num;
					cout << "请输入学号：" << endl;
					cin >> num;
					STU.display(num);
					break;
				} else if (choice3 == '2') {
					char name[20];
					cout << "请输入姓名：" << endl;
					cin >> name;
					STU.display(name);
					break;
				} else if (choice3 == '3') {
					STU.display();
					break;
				} else {
					cout << "无此选项，请您重新选择" << endl;
				}
			}
			case '5': {
				MyString name("chen"), major("cs");
				//CStudent STU = { 99,name,major,100};
				CStudentList STU2(STU);
				STU2.display();
				break;
			}
			case '6': {
				CStudentList STU3(STU);
				STU3.display();
				break;

			}
			case '7': {
				CStudentList test2(STU),test3;
				test3=STU+test2;
				cout<<"将原列表再加到原列表后，显示如下："<<endl;
				test3.display(100,0);
				break;
			}
			case '8': {
				cout<<"测试取指定下标学生"<<endl<<"第3个学生信息如下："<<endl;
				STU.display(STU[2]);
				cout<<endl;
				break;
			}
			case '9':
				choice = '0';
				break;
			default:
				cout << "无此选项，请您重新选择" << endl;
		}
	}
}
