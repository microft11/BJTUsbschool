#include<iostream>
#include"student(1).h"
#include"studentlist.h"
using namespace std;
int main() {
	int code = 0;
	CNode *p = NULL;
	CStudentList stuList;//Ĭ�Ϲ��캯��
	CStudent stu;//Ĭ�Ϲ��캯��
	MyString AssociationName("football");//�вι��캯��
	CAssociation association(AssociationName);
	char choice = '\0';
	while(choice!='0') {
		cout << "��ѡ�������" << endl;
		cout << "ѧ��������Ϣ����ϵͳ��" << endl;
		cout << "1.¼���µ�ѧ��" << endl;
		cout << "2.ɾ��ѧ���б��е�ѧ��" << endl;
		cout << "3.¼���µ�ѧ����ѧ������" << endl;
		cout << "4.ɾ��ѧ�������е�ѧ��" << endl;
		cout << "5.��ʾѧ���б��е�ѧ��" << endl;
		cout << "6.��ʾѧ�������е�ѧ��" << endl;
		cout << "7.���Լӷ������" << endl;
		cout << "8.�����±������" << endl;
		cout << "0.�˳�ϵͳ" << endl;
		cin >> choice;
		switch (choice) {
			case 1: {
				int number;
				char stuname[20];
				char stumajor[20];
				double score;
				cout<<"����������ѧ�š�������רҵ�ͳɼ���"<< endl;
				cin>>number>>stuname>>stumajor>>score;
				MyString name(stuname);
				MyString major(stumajor);
				stu.set_number(number);
				stu.set_name(name);
				stu.set_major(major);
				stu.set_score(score);
				CStudent *add_stu = new CStudent(stu);//Ϊ����ӵ�ѧ�����������µ��ڴ�ռ�
				stuList.add(add_stu);
				break;
			}
			case 2: {
				int num;
				cout << "������Ҫɾ����ѧ����ѧ�ţ�" << endl;
				cin >> num;
				code=stuList.del(num);
				showError(code);
				break;
			}

			case 3: {
				int number;
				cout << "������Ҫ�����ѧ����ѧ��:" << endl;
				cin >> number;
				p = stuList.get(number);
				association.add(p);
				break;
			}

			case 4: {
				int num;
				cout << "������Ҫɾ����ѧ����ѧ�ţ�" << endl;
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
				cout << "��������" << endl;
		}
	}
}
