#include<iostream>
#include"MyString.h.h"
using namespace std;
int main()
{
	//调用构造函数与析构函数 
	MyString str1;
	MyString str2("i love c++,yeah");
	MyString str3[3];

	MyString str("i love c++,yeah");
	MyString str4(str);//复制构造函数 

	MyString str5;
    str5 = (str);//赋值运算符函数 

	return 0;
}
