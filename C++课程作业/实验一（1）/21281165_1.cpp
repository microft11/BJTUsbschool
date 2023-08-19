#include<iostream>
#include<cstring>
#include"21281165_2.h"
#define BLOCK 10
using namespace std; 


namespace N123456
{
	STUDENT * gStu = NULL;
	int count = 0;
	int available = 0;
	
	void add_student(STUDENT &stu)
{
	if(available == 0)
	{
		STUDENT * tmp = new STUDENT[count + BLOCK];
		for(int i = 0; i < count; i ++)
		{
			tmp[i].number = gStu[i].number;
			strcpy(tmp[i].name, gStu[i].name);
			strcpy(tmp[i].major, gStu[i].major);
			tmp[i].score = gStu[i].score;
		}
		delete[] gStu;
		gStu = tmp;
		available = BLOCK;
	}
	
	gStu[count].number = stu.number;
	strcpy(gStu[count].name, stu.name);
	strcpy(gStu[count].major, stu.major);
	gStu[count].score = stu.score;
	
	count ++;
	available --;
}

void display()
{
	cout << "学号\t姓名\t专业\t成绩" << endl;
	for(int i = 0; i < count; i ++)
	{
		cout << gStu[i].number << "\t" << gStu[i].name << "\t" << gStu[i].major << "\t" << gStu[i].score << "\n";
	 } 
}
}


using namespace N123456;

int main()
{
	char choice = '\0';
	STUDENT s;
	while(choice != '0')
	{
		cout << "学生信息管理系统\n";
		cout << "1 录入学生信息\n";
		cout << "2 显示学生信息\n";
		cout << "0 退出系统\n";
		cout << "请选择所需要的操作：";
		cin >> choice;
		
		switch (choice)
		{
			case'1':
				cout << "请依次输入学号、姓名、专业和成绩\n";
				cin >> s.number >> s.name >> s.major >> s.score;
				add_student(s);
				cout << endl;
				break;
			case'2':
				display();
				cout << endl;
				break;
			case'0':
				break;
			default:
				cout << "你的选择有误，请重新选择！" << endl;
		}
	}
	return 0;
}


