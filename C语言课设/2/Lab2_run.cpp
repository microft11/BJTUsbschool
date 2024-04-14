#include<stdio.h>
#include<tchar.h>
#include<stdlib.h> 
#include<string.h>
#include"Lab2_fun.h"
void fun(char* argv[], int x);
void run(int argc, char* argv[])
{
	switch (argc)
	{
	case 1:
	{   
		int t = 1;
	    printf("您未输入参数,请补充:");
		char* m_argv[3];
		m_argv[0] = (char*)malloc(20);
		m_argv[1] = (char*)malloc(20);
		m_argv[2] = (char*)malloc(20);
		while (t<2 && scanf_s("%s", m_argv[t], 20) != EOF)
		{
			t++;
		}
		if (t ==2)
		{
			int x = atoi(m_argv[0]);
			m_argv[2] = (char*)"output.txt";
			fun(m_argv, x);
		}
		else printf("输入参数非法");
		break;
	}
	case 2:
		printf("输入参数非法");
		break;
	case 3:
	{
		int x = atoi(argv[1]);
		fun(argv, x);
		break;
	}
	default:
	{printf("输入参数非法");}
	}
}