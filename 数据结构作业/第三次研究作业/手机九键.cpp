#include<iostream>
using namespace std;
int n;
int nums[10];
char s[10][5]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};//用一个数组来记录 
void dfs(int cur,string f)
{
	if(cur==n)
	{
		cout<<f<<endl;
		return;
	}
	for(int i=0;s[nums[cur]][i]!='\0';i++)
	{
		dfs(cur+1,f+s[nums[cur]][i]);
	}
} 
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>nums[i];
	dfs(0,"");
} 

