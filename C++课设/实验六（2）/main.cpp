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
	cout << "再见" << endl;
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
	cout << "请选择功能\n";
	cout << "1.录入信息\n";
	cout << "2.显示已录入的学生信息\n";
	cout << "3.修改指定学生信息\n";
	cout << "4.删除指定学生信息\n";
	cout << "5.将已存入的信息拷贝一份\n";
	cout << "6.利用已拷贝的信息复原当前列表\n";
	cout << "7.创建一个文本文件，并存入学生列表\n";
	cout << "8.读取一个文本文件，将它储存的学生列表显示到屏幕上\n";
	cout << "9.创建一个二进制文件，并存入学生列表\n";
	cout << "10.读取一个二进制文件，将它储存的学生列表显示到屏幕上\n";
	cout << "0.退出" << endl;
	if (1 != scanf("%d", &choic)) { cout << "无法识别你的输入，请检查！\n"; }
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
	default:cout << "没有这个选项！" << endl; break;
	}
	return 0;
}
int read()
{
	char tname[MAX_LENTH];
	char tid[MAX_LENTH];
	char tsubject[MAX_LENTH];
	int tgrade = 0;
	cout << "请输入姓名" << endl;
	cin >> tname;
	cout << "请输入学号" << endl;
	cin >> tid;
	cout << "请输入专业" << endl;
	cin >> tsubject;
	while (1) {
		cout << "请输入成绩(0--710)" << endl;
		cin >> tgrade;
		while (getchar() != '\n') {
			continue;
		}
		if (tgrade <= 710 && tgrade >= 0) {
			break;
		}
		else {
			cout << "超出范围！" << endl;
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
	cout << "请选择功能\n";
	cout << "1.展示特定学号的学生信息\n";
	cout << "2.展示指定名字的学生信息\n";
	cout << "3.展示特定成绩的学生信息\n";
	cout << "4.展示一个成绩区间的所有学生信息\n";
	cout << "5.展示已经录入的所有学生信息" << endl;
	if (!(cin >> choic)) {
		cout << "输入错误" << endl;
		while (getchar() != '\n') {
			continue;
		}
		return 1;
	}
	while (getchar() != '\n') {
		continue;
	}
	switch (choic) {
	case 1:cout << "请输入学号" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.show_inform(temp)) {
			cout << "未录入该学号" << endl;
		}
		break;
	case 2:cout << "请输入姓名" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		if (timely.change_byna(temp) != NULL) {
			cout << "学号\t" << "姓名\t" << "专业\t" << "成绩" << endl;
			timely.show_inform(*timely.change_byna(temp));
		}
		else {
			cout << "未录入该学生信息" << endl;
		}
		break;
	case 3:cout << "输入指定成绩" << endl;
		cin >> temp1;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.show_inform(temp1)) {
			cout << "找不到成绩为" << temp1 << "的学生" << endl;
		}
		break;
	case 4:cout << "请输入两个数，我们将显示处于二者之间的学生信息" << endl;
		cin >> temp1 >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (timely.show_some_informs(temp1, temp2) == 1) {
			cout << "没有处于该区间的学生" << endl;
		}
		break;
	case 5:temp1 = 710;
		if (timely.show_some_informs(temp1) == 1) //默认值的运用
		{
			cout << "没有录入信息" << endl;
		}
		break;
	default:cout << "没有这个选项" << endl; break;
	}
	return 0;
}
int changing()
{
	int choic;
	int newgrade;
	char temp[MAX_LENTH], temp2[MAX_LENTH];
	cout << "请选择功能\n";
	cout << "1.修改指定学号的成绩\n";
	cout << "2.修改指定学号的名字\n";
	cout << "3.修改指定学号的专业\n";
	cout << "4.修改指定名字的成绩\n";
	cout << "5.修改指定名字的学号\n";
	cout << "6.修改指定名字的专业\n";
	if (!(cin >> choic)) {
		cout << "输入错误" << endl;
		exit(0);
	}
	while (getchar() != '\n') {
		continue;
	}
	if (choic == 1) {
		cout << "请输入学号" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		while (1) {
			cout << "请输入新成绩(0--710)" << endl;
			cin >> newgrade;
			while (getchar() != '\n') {
				continue;
			}
			if (newgrade <= 710 && newgrade >= 0) {
				break;
			}
			else {
				cout << "超出范围！" << endl;
			}
		}
		if (1 == timely.change_grade(timely.change_byid(temp), newgrade)) {
			cout << "找不到该学号" << endl;
		};
	}
	else if (choic == 2) {
		cout << "请输入学号" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "请输入新姓名" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_name_byid(timely.change_byid(temp), temp2)) {
			cout << "找不到该学号" << endl;
		}
	}
	else if (choic == 3) {
		cout << "请输入学号" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "请输入新专业" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_subject(timely.change_byid(temp), temp2)) {
			cout << "找不到该学号" << endl;
		}
	}
	else if (choic == 4) {
		cout << "请输入姓名" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		while (1) {
			cout << "请输入新成绩(0--710)" << endl;
			cin >> newgrade;
			while (getchar() != '\n') {
				continue;
			}
			if (newgrade <= 710 && newgrade >= 0) {
				break;
			}
			else {
				cout << "超出范围！" << endl;
			}
		}
		if (1 == timely.change_grade(timely.change_byna(temp), newgrade)) {
			cout << "找不到这个名字" << endl;
		}
	}
	else if (choic == 5) {
		cout << "请输入姓名" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "请输入学号" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_id_byna(timely.change_byna(temp), temp2)) {
			cout << "找不到该名字" << endl;
		}
	}
	else if (choic == 6) {
		cout << "请输入姓名" << endl;
		cin >> temp;
		while (getchar() != '\n') {
			continue;
		}
		cout << "请输入新专业" << endl;
		cin >> temp2;
		while (getchar() != '\n') {
			continue;
		}
		if (1 == timely.change_subject(timely.change_byna(temp), temp2)) {
			cout << "找不到该名字" << endl;
		}
	}
	else {
		cout << "没有这个选项！" << endl;
	}
	return 0;
}
int dele()
{
	char temp[MAX_LENTH];
	cout << "请输入学号" << endl;
	cin >> temp;
	while (getchar() != '\n') {
		continue;
	}
	if (1 == timely.dele_stud_byid(timely.change_byid(temp))) {
		cout << "找不到该学号" << endl;
	}
	return 0;
}
int coppy()
{
	copyaf = timely;
	cout << "拷贝完成" << endl;
	return 0;
}
int recover()
{
	timely = copyaf;
	cout << "复原完成!" << endl;
	return 0;
}

int creatFileTxt()
{
	char tFileName[MAX_LENTH];
	cout << "请输入文件名(不要加后缀名)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
			continue;
	if (cin.fail() == 1) {
		cout << "输入错误！" << endl;
		return 1;
	}
	strcat(tFileName, ".txt");
	cout << "进行文本文件读写测试" << endl;
	ofstream out(tFileName);
	if (!out.is_open()) {
		cout << "Can not open the txt file to write" << endl;
		exit(0);
	}
	timely.write(out);
	out.close();
	cout << "写入成功!开始读取" << endl;
	return 0;
}
int readTxt()
{
	char tFileName[MAX_LENTH];
	cout << "请输入要打开的文件名(不要加后缀名)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "输入错误！" << endl;
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
	cout << "请输入文件名(不要加后缀名)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "输入错误！" << endl;
		return 1;
	}
	strcat(tFileName, ".dat");
	cout << "进行二进制文件读写测试" << endl;
	ofstream out(tFileName, ios_base::binary);
	if (!out.is_open()) {
		cout << "Can not open the txt file to write" << endl;
		exit(0);
	}
	timely.E_write(out);
	out.close();
	cout << "写入成功!开始读取" << endl;
	return 0;
}
int readDat()
{
	char tFileName[MAX_LENTH];
	cout << "请输入要打开的文件名(不要加后缀名)" << endl;
	cin >> tFileName;
	while (getchar() != '\n')
		continue;
	if (cin.fail() == 1) {
		cout << "输入错误！" << endl;
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
