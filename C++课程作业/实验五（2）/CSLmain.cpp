#include"student.h"

using namespace N21281165;

int main() {
	CStudentList STU;

	char choice = '\0';

	CStudent stu;

	while (choice != '0') {
		cout << "ѧ����Ϣ����ϵͳ��" << endl;
		cout << "1.¼���µ�ѧ��" << endl;
		cout << "2.ɾ��ѧ����Ϣ" << endl;
		cout << "3.�޸�ѧ���ɼ���Ϣ" << endl;
		cout << "4.��ʾѧ����Ϣ" << endl;
		cout << "5.ʹ���вι��캯����ʼ��" << endl;
		cout << "6.ʹ�ø��ƹ��캯����ʼ��" << endl;
		cout << "7.���Խ�����ѧ���б����"<<endl;
		cout << "8.����ȡָ���±��ѧ��"<<endl;
		cout << "9.�˳�ϵͳ" << endl;
		cout << "��ѡ����Ҫ���еĲ�����" << endl;
		cin >> choice;
		switch (choice) {
			case '1': {
				int number;
				char name[20];
				char major[20];
				double score;
				cout << "����������ѧ�š�������רҵ�ͳɼ���" << endl;
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
				cout << "��ѡ����Ҫ���е�ɾ��������" << endl;
				cout << "1.������ɾ��ѧ����Ϣ" << endl;
				cout << "2.��ѧ��ɾ��ѧ����Ϣ" << endl;
				cin >> choice1;
				if (choice1 == '1') {
					char name[20];
					cout << "������Ҫɾ����ѧ����������" << endl;
					cin >> name;
					STU.delete_student(name);
					break;
				} else if (choice1 == '2') {
					int num;
					cout << "������Ҫɾ����ѧ����ѧ�ţ�" << endl;
					cin >> num;
					STU.delete_student(num);
					break;
				} else {
					cout << "��������ȷ��ѡ�" << endl;
					break;
				}
			}

			case '3': {
				char choice2 = '\0';
				cout << "��������Ҫ���е��޸Ĳ�����" << endl;
				cout << "1.����Ҫ�޸ĳɼ���ѧ��������" << endl;
				cout << "2.����Ҫ�޸ĳɼ���ѧ����ѧ��" << endl;
				cin >> choice2;
				if (choice2 == '1') {
					char name[20];
					int score;
					cout << "������Ҫ�޸ĵ�ѧ����������" << endl;
					cin >> name;
					cout << "�������µĳɼ���" << endl;
					cin >> score;
					STU.get_stu(name).set_score(score);
					break;
				} else if (choice2 == '2') {
					int num;
					int score;
					cout << "������Ҫ�޸ĵ�ѧ����ѧ�ţ�" << endl;
					cin >> num;
					cout << "�������µĳɼ���" << endl;
					cin >> score;
					STU.get_stu(num).set_score(score);
					break;
				} else {
					cout << "�޴�ѡ���������ѡ��" << endl;
				}
			}

			case '4': {
				char choice3 = '\0';
				cout << "��ѡ����Ҫ��ʾ��ʽ��" << endl;
				cout << "1.����ѧ����ʾѧ����Ϣ" << endl;
				cout << "2.����������ʾѧ����Ϣ" << endl;
				cout << "3.��ʾ�ɼ�����ѧ������Ϣ" << endl;
				cin >> choice3;
				if (choice3 == '1') {
					int num;
					cout << "������ѧ�ţ�" << endl;
					cin >> num;
					STU.display(num);
					break;
				} else if (choice3 == '2') {
					char name[20];
					cout << "������������" << endl;
					cin >> name;
					STU.display(name);
					break;
				} else if (choice3 == '3') {
					STU.display();
					break;
				} else {
					cout << "�޴�ѡ���������ѡ��" << endl;
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
				cout<<"��ԭ�б��ټӵ�ԭ�б����ʾ���£�"<<endl;
				test3.display(100,0);
				break;
			}
			case '8': {
				cout<<"����ȡָ���±�ѧ��"<<endl<<"��3��ѧ����Ϣ���£�"<<endl;
				STU.display(STU[2]);
				cout<<endl;
				break;
			}
			case '9':
				choice = '0';
				break;
			default:
				cout << "�޴�ѡ���������ѡ��" << endl;
		}
	}
}
