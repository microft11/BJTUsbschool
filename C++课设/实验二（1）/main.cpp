#include<iostream>
#include"MyString.h.h"
using namespace std;
int main()
{
	//���ù��캯������������ 
	MyString str1;
	MyString str2("i love c++,yeah");
	MyString str3[3];

	MyString str("i love c++,yeah");
	MyString str4(str);//���ƹ��캯�� 

	MyString str5;
    str5 = (str);//��ֵ��������� 

	return 0;
}
