#include<list>
#include<vector> 
#include<iostream>
#include<algorithm>
#include"MyString.h"
using namespace std;

template<class T> void output(const T & v)
{
	cout << v << " ";
}

int main()
{
	cout << " vector 的应用" << endl;
	vector<int> v0;
	v0.push_back(1);
	v0.push_back(0);
	v0.push_back(2);
	v0.push_back(3);
	v0.insert(v0.begin() + 2, 0);
	v0.insert(v0.begin(), 2);

	vector<int>::iterator iter0;
	for(iter0 = v0.begin(); iter0 < v0.end(); iter0++)
		cout << *iter0 << " " ;
	cout << endl;
	cout << endl;
	
	
	list<int> v;
	v.push_back(1);	
	v.push_back(0);
	v.push_back(2);
	v.push_back(3);
	list<int>::iterator it = v.begin();
	++it;
	v.insert(it, 2);

	cout << "逆序前： ";
	for (it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;

	reverse(v.begin(), v.end()); // 逆序
	cout << "逆序后： ";
	for_each(v.begin(), v.end(), output<int>);
	cout << endl;

	// 演示vector和函数对象等
	list<MyString> v2;
	v2.push_back(MyString("11"));
	v2.push_back(MyString("00"));
	v2.push_back(MyString("22"));
	v2.push_back(MyString("22"));
	v2.push_back(MyString("33"));

	cout << "逆序前： ";
	for_each(v2.begin(), v2.end(), output<MyString>);
	cout << endl;

	reverse(v2.begin(), v2.end()); // 逆序
	cout << "逆序后： ";
	for_each(v2.begin(), v2.end(), output<MyString>);
	cout << endl;

	return 0;
}
