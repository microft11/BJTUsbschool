#include"MyString.h"
#include<string.h>
bool testMyStringIO()
{
	MyString str("I love C++ programming!"), str2("haha");
	ofstream out("MyString.txt");
	//1. 文本模式：使用插入符写数据，使用read_text读数据
	out << str;
	out.close();
	ifstream in("MyString.txt");
	str2.read_text(in);
	in.close();
	//读取的字符串与原字符串不同则测试不通过
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	//2. 文本模式：使用write_text写数据，使用read_text读数据
	out.open("MyString.txt"); //打开文件并清空原数据
	str.write_text(out);
	out.close();
	in.open("MyString.txt");
	str2.read_text(in);
	in.close();
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	//3. 二进制模式：使用write_binary写数据，使用read_binary读数据
	out.open("MyString.dat");
	str.write_binary(out);
	out.close();
	in.open("MyString.dat");
	str2.read_binary(in);
	in.close();
	if (strcmp(str2.get_string(), str.get_string()) != 0)
		return false;
	return true;
}
int main()
{
	if (testMyStringIO()) //测试MyString类的文件读写功能是否正确
		cout << "MyString IO OK" << endl;
	else
		cout << "MyString IO failed" << endl;
	return 0;
}
