#include<conio.h>
#include"playround.h"

int main()
{
	double len, w, lane;
	while(true)
	{
		cout << "���������򳡳�����ܵ����" << endl;
		cin >> len >> w >> lane;
		CPlaygragh g(len, w);
		CPlayground ground(g, lane);
		cout << "�����" << ground.computer_cost() << endl;
		cout << "��e�˳�������������" << endl;
		if(_getch() == 'e') break; 
	}
	return 0;
}
