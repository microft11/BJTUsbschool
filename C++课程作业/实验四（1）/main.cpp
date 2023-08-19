#include<conio.h>
#include"playround.h"

int main()
{
	double len, w, lane;
	while(true)
	{
		cout << "请输入足球场长宽和跑道宽度" << endl;
		cin >> len >> w >> lane;
		CPlaygragh g(len, w);
		CPlayground ground(g, lane);
		cout << "造价是" << ground.computer_cost() << endl;
		cout << "按e退出，按其他继续" << endl;
		if(_getch() == 'e') break; 
	}
	return 0;
}
