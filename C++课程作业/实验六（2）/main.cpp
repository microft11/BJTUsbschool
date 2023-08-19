#include<iostream>
#include"CStudentL.h"
using namespace std;
CStudentList timely;
CStudentList copyaf;
int work();
int menu();
int working(int choic);
int read();
int showing();
int changing();
int dele();
int coppy();
int recover();
int creatFileTxt();
int readTxt();
int creatFileDat();
int readDat();
int main()
{
	work();
	cout << "�ټ�" << endl;
	return 0;
}
int work()
{
	int choic = -1;

	while (choic != 0) {
		choic = menu();
		working(choic);
	}
	return 0;
}
int menu()
{
	int choic = -1;
	cout << "��ѡ����\n";
	cout << "1.¼����Ϣ\n";
	cout << "2.��ʾ��¼���ѧ����Ϣ\n";
	cout << "3.�޸�ָ��ѧ����Ϣ\n";
	cout << "4.ɾ��ָ��ѧ����Ϣ\n";
	cout << "5.���Ѵ������Ϣ����һ��\n";
	cout << "6.�����ѿ�������Ϣ��ԭ��ǰ�б�\n";
	cout << "7.����һ���ı��ļ���������ѧ���б�\n";
	cout << "8.��ȡһ���ı��ļ������������ѧ���б���ʾ����Ļ��\n";
	cout << "9.����һ���������ļ���������ѧ���б�\n";
	cout << "10.��ȡһ���������ļ������������ѧ���б���ʾ����Ļ��\n";
	cout << "0.�˳�" << endl;
	if (1 != scanf("%d", &choic)) { cout << "�޷�ʶ��������룬���飡\n"; }
	while (getchar() != '\n') {
		continue;
	}
	return choic;
}
int working(int choic)
{
	switch (choic) {
	case 1:read(); break;
	case 2:showing(); break;
	case 3:changing(); break;
	case 4:dele(); break;
	case 5:coppy(); break;
	case 6:recover(); break;
	case 7:creatFileTxt(); break;
	case 8:readTxt(); break;
	case 9:creatFileDat(); break;
	case 10:readDat(); break;
	case 0: break;
	default:cout << "û�����ѡ�" << endl; break;
	}
	return 0;
}
int read()
{
	char tname[MAX_LENTH];
	char tid[MAX_LENTH];
	char tsubject[MAX_LENTH];
	int tgrade = 0;
	cout << "����������" << endl;
	cin >> tname;
	cout << "������ѧ��" << endl;
	cin >> tid;
	cout << "������רҵ" << endl;
	cin >> tsubject;
	while (1) {
		cout << "������ɼ�(0--710)" << endl;
		cin >> tgrade;
		while (getchar() != '\n') {
			continue;
		}
		if (tgrade <= 710 && tgrade >= 0) {
			break;
		}
		else {
			cout << "������Χ��" << endl;
		}
	}
	CStudent temp(tname, tid, tsubject, tgrade);
	timely.set_information(temp);
	return 0;
}
int showing()
{
	int choic = 0;
	char temp[MAX_LENTH] = { 0 };
	int temp1 = 0, temp2 = 0;
	cout << "��ѡ����\n";
	cout << "1.չʾ�ض�ѧ�ŵ�ѧ����Ϣ\n";
	cout << "2.չʾָ�����ֵ�ѧ����Ϣ\n";
	cout << "3.չʾ�ض��ɼ���ѧ����Ϣ\n";
	cout << "4.չʾһ���ɼ����������ѧ����Ϣ\n";
	cout << "5.չʾ�Ѿ�¼�������ѧ����Ϣ" << endl;
	if (!(cin >> choic)) {
		cout << "�������" << endl;
		while (getchar() != '\n') {
			continue;
		}
		return 1;
	}
	while (getchar() != '\n') {
		continue;
	}
	switch (choic) {
	case 1:cout << "������ѧ��" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.show_inform(temp)) {
			cout << "δ¼���ѧ��" << endl;
		}
		break;
	case 2:cout << "����������" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		if (timely.change_byna(temp) != NULL) {
			cout << "ѧ��\t" << "����\t" << "רҵ\t" << "�ɼ�" << endl;
			timely.show_inform(*timely.change_byna(temp));
		}
		else {
			cout << "δ¼���ѧ����Ϣ" << endl;
		}
		break;
	case 3:cout << "����ָ���ɼ�" << endl;
		cin >> temp1;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.show_inform(temp1)) {
			cout << "�Ҳ����ɼ�Ϊ" << temp1 << "��ѧ��" << endl;
		}
		break;
	case 4:cout << "�����������������ǽ���ʾ���ڶ���֮���ѧ����Ϣ" << endl;
		cin >> temp1 >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (timely.show_some_informs(temp1, temp2) == 1) {
			cout << "û�д��ڸ������ѧ��" << endl;
		}
		break;
	case 5:temp1 = 710;
		if (timely.show_some_informs(temp1) == 1) //Ĭ��ֵ������
		{
			cout << "û��¼����Ϣ" << endl;
		}
		break;
	default:cout << "û�����ѡ��" << endl; break;
	}
	return 0;
}
int changing()
{
	int choic;
	int newgrade;
	char temp[MAX_LENTH], temp2[MAX_LENTH];
	cout << "��ѡ����\n";
	cout << "1.�޸�ָ��ѧ�ŵĳɼ�\n";
	cout << "2.�޸�ָ��ѧ�ŵ�����\n";
	cout << "3.�޸�ָ��ѧ�ŵ�רҵ\n";
	cout << "4.�޸�ָ�����ֵĳɼ�\n";
	cout << "5.�޸�ָ�����ֵ�ѧ��\n";
	cout << "6.�޸�ָ�����ֵ�רҵ\n";
	if (!(cin >> choic)) {
		cout << "�������" << endl;
		exit(0);
	}
	while (getchar() != '\n') {
		continue;
	}
	if (choic == 1) {
		cout << "������ѧ��" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		while (1) {
			cout << "�������³ɼ�(0--710)" << endl;
			cin >> newgrade;
			while (getchar() != '\n') {
				continue;
			}
			if (newgrade <= 710 && newgrade >= 0) {
				break;
			}
			else {
				cout << "������Χ��" << endl;
			}
		}
		if (1 == timely.change_grade(timely.change_byid(temp), newgrade)) {
			cout << "�Ҳ�����ѧ��" << endl;
		};
	}
	else if (choic == 2) {
		cout << "������ѧ��" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "������������" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_name_byid(timely.change_byid(temp), temp2)) {
			cout << "�Ҳ�����ѧ��" << endl;
		}
	}
	else if (choic == 3) {
		cout << "������ѧ��" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "��������רҵ" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_subject(timely.change_byid(temp), temp2)) {
			cout << "�Ҳ�����ѧ��" << endl;
		}
	}
	else if (choic == 4) {
		cout << "����������" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		while (1) {
			cout << "�������³ɼ�(0--710)" << endl;
			cin >> newgrade;
			while (getchar() != '\n') {
				continue;
			}
			if (newgrade <= 710 && newgrade >= 0) {
				break;
			}
			else {
				cout << "������Χ��" << endl;
			}
		}
		if (1 == timely.change_grade(timely.change_byna(temp), newgrade)) {
			cout << "�Ҳ����������" << endl;
		}
	}
	else if (choic == 5) {
		cout << "����������" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "������ѧ��" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_id_byna(timely.change_byna(temp), temp2)) {
			cout << "�Ҳ���������" << endl;
		}
	}
	else if (choic == 6) {
		cout << "����������" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "��������רҵ" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_subject(timely.change_byna(temp), temp2)) {
			cout << "�Ҳ���������" << endl;
		}
	}
	else {
		cout << "û�����ѡ�" << endl;
	}
	return 0;
}
int dele()
{
	char temp[MAX_LENTH];
	cout << "������ѧ��" << endl;
	cin >> temp;
	while (getchar() != '\n') {
		continue;
	}
	if (1 == timely.dele_stud_byid(timely.change_byid(temp))) {
		cout << "�Ҳ�����ѧ��" << endl;
	}
	return 0;
}
int coppy()
{
	copyaf = timely;
	cout << "�������" << endl;
	return 0;
}
int recover()
{
	timely = copyaf;
	cout << "��ԭ���!" << endl;
	return 0;
}

int creatFileTxt()
{
	char tFileName[MAX_LENTH];
	cout << "�������ļ���(��Ҫ�Ӻ�׺��)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
			continue;
	if (cin.fail() == 1) {
		cout << "�������" << endl;
		return 1;
	}
	strcat(tFileName, ".txt");
	cout << "�����ı��ļ���д����" << endl;
	ofstream out(tFileName);
	if (!out.is_open()) {
		cout << "Can not open the txt file to write" << endl;
		exit(0);
	}
	timely.write(out);
	out.close();
	cout << "д��ɹ�!��ʼ��ȡ" << endl;
	return 0;
}
int readTxt()
{
	char tFileName[MAX_LENTH];
	cout << "������Ҫ�򿪵��ļ���(��Ҫ�Ӻ�׺��)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "�������" << endl;
		return 1;
	}
	strcat(tFileName, ".txt");
	ifstream in(tFileName, ios_base::in);
	if (!in.is_open()) {
		cout << "Can not open the file to write" << endl;
		exit(0);
	}
	CStudentList temp;
	temp.read(in);
	temp.show_some_informs(800);
	in.close();
	return 0;
}
int creatFileDat()
{
	char tFileName[MAX_LENTH];
	cout << "�������ļ���(��Ҫ�Ӻ�׺��)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "�������" << endl;
		return 1;
	}
	strcat(tFileName, ".dat");
	cout << "���ж������ļ���д����" << endl;
	ofstream out(tFileName, ios_base::binary);
	if (!out.is_open()) {
		cout << "Can not open the txt file to write" << endl;
		exit(0);
	}
	timely.E_write(out);
	out.close();
	cout << "д��ɹ�!��ʼ��ȡ" << endl;
	return 0;
}
int readDat()
{
	char tFileName[MAX_LENTH];
	cout << "������Ҫ�򿪵��ļ���(��Ҫ�Ӻ�׺��)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "�������" << endl;
		return 1;
	}
	strcat(tFileName, ".dat");
	ifstream in(tFileName, ios_base::ios_base::binary);
	if (!in.is_open()) {
		cout << "Can not open the file to write" << endl;
		exit(0);
	}
	CStudentList temp;
	temp.E_read(in);
	temp.show_some_informs(800);
	in.close();
	return 0;
}
