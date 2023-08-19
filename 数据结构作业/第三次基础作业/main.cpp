//1:void test(int n){
//
//02:    int i;
//
//03:    i=n;
//
//04:    while (i>1)
//
//05:        Printf(i--);
//
//06:}

//递归调用实现
#include<iostream>
using namespace std;

void recursion(int n)
{
	if(n > 1)
	{
		cout << n << endl;
		recursion(n - 1);
	}
	return ;
}

int main()
{
	int n;
	cin >> n;
	recursion(n);
	return 0;
} 
