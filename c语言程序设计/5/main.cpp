#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 1000
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>

char task1_exe_file_name[] = "子任务1.exe";//子任务1的exe文件的文件名
char task2_exe_file_name[] = "子任务2.exe";//子任务2的exe文件的文件名

char temp[MAX_LEN];//中转字符串的空字符串

char task1_exe_absolute_path[MAX_LEN];//子任务1的exe文件的绝对路径
char task2_exe_absolute_path[MAX_LEN];//子任务2的exe文件的绝对路径

char general_content_name[] = "实验五\0";//总目录名称
char general_content[MAX_LEN];//总目录

char confi_file_name[] = "Lab5_confi.ini\0";//初始化配置文件名字
char confi_file_absolute_path[MAX_LEN];//初始化配置文件的绝对路径

char* English_file_name_off_postfix;//英语不含后缀名的文本文件的名字
char English_file_absolute_path[MAX_LEN];//英语文本文件的绝对路径

char statistic_file_head_name[MAX_LEN];//统计文件头名字
char pr_statistic_file_absolute_path[MAX_LEN];//统计结果文件的绝对路径前部分
char statistic_file_absolute_path[MAX_LEN];//统计结果文件的绝对路径

char html_file_head_name[MAX_LEN];//网页文件头名字
char pr_html_file_absolute_path[MAX_LEN];//网页文件的绝对路径前部分
char html_file_absolute_path[MAX_LEN];//网页文件的绝对路径

char headline_individual[MAX_LEN];//分网页标题
char headline_summary[MAX_LEN];//汇总页面标题

char cmd_task1_exe[MAX_LEN];//调用子任务1的命令行参数
char cmd_task2_exe[MAX_LEN];//调用子任务2的命令行参数

char file_AP_of_English_files[MAX_LEN];//英语文档所在文件夹的绝对路径
char file_name_for_search_txt[MAX_LEN];//搜索文本txt文件的语句

char summary_html_name[MAX_LEN];//汇总html文件的名字
char summary_html_AP[MAX_LEN];//汇总html文件的绝对路径


void print_menu()//打印菜单
{
	printf("*************************************************\n");
	printf("*     龙硕、于嘉阳、孙艺璇的实验5程序：         *\n");
	printf("*                                               *\n");
	printf("*     1.对单个英文文档进行统计                  *\n");
	printf("*                                               *\n");
	printf("*     2.对批量英文文档进行统计                  *\n");
	printf("*                                               *\n");
	printf("*     0.退出                                    *\n");
	printf("*                                               *\n");
	printf("*************************************************\n");
	printf("请输入您要执行的程序序号：\n");
}


/*************************************************
* 函数信息（get_name_off_postfix）
* 1.函数名称：get_name_off_postfix(char* s)
* 2.函数功能：获取不含后缀名的文件名
* 3.参数说明：
*   s：文件名或文件绝对路径字符串的首地址
* 4.返回值：去除后缀名的文件名的首地址
**************************************************/
char* get_name_off_postfix(char* s)
{
	strcpy(temp, s);
	for (int i = strlen(temp) - 1; i >= 0; i--)
	{
		if (temp[i] == '.')
		{
			strcpy(temp + i, "\0");//去除后缀名
		}
		if (temp[i] == '\\' || temp[i] == '/')
		{
			return temp + i + 1;
		}
	}
	return temp;
}


/*********************************************
* 函数信息：（init_confi）
* 1.函数名称：init_confi(int argc, char* argv[])
* 2.参数说明：
* （1）argc：命令行参数个数
* （2）argv：命令行参数字符串指针数组首地址
* 3.函数功能：初始化数据：
* （1）总目录
* （2）配置文件绝对路径
* （3）统计结果文件头名字
* （4）统计结果文件前部分
* （5）网页文件头名字
* （6）网页文件绝对路径前部分
* （7）网页标题
* （8）子任务1、2的exe文件的绝对路径
* （9）汇总html文件的名字
* （10）汇总html页面的标题
* 4.返回值：无
**********************************************/
void init_confi(int argc, char* argv[])
{
	FILE* fp;
	int n = 0;//辅助获取配置文件中的信息
	char temp[MAX_LEN];//转接判断总目录
	char current_content_name[MAX_LEN];//当前目录内容
	strcpy_s(temp, MAX_LEN, argv[0]);
	for (int i = strlen(temp) - 1; i >= 0; i--)//获取总目录
	{
		if (temp[i] == '\\' || temp[i] == '/')
		{
			strcpy_s(current_content_name, MAX_LEN, temp + i + 1);
			if (strcmp(current_content_name, general_content_name) == 0)//判断当前目录是否为总目录
			{
				strcpy_s(general_content, MAX_LEN, temp);//获取总目录
				break;
			}
			strcpy_s(temp + i, MAX_LEN - i, "\0");
		}
	}
	if (strlen(general_content) > 0)//成功获取总目录
	{
		sprintf(confi_file_absolute_path, "%s\\%s", general_content, confi_file_name);
		fp = fopen(confi_file_absolute_path, "r");
		if (fp != NULL)
		{
			while (fgets(temp, MAX_LEN, fp) != NULL)
			{
				n++;
				if (n == 1 * 2)//获取统计结果文件头名字
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(statistic_file_head_name, temp);
					n = 1 * 2;
				}
				if (n == 2 * 2)//获取统计结果文件的绝对路径前部分
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(pr_statistic_file_absolute_path, "%s\\%s\\%s-\0", general_content, temp, statistic_file_head_name);
					n = 2 * 2;
				}
				if (n == 3 * 2)//获取网页文件的头名字
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(html_file_head_name, temp);
					n = 3 * 2;
				}
				if (n == 4 * 2)//获取网页文件的绝对地址前部分
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(pr_html_file_absolute_path, "%s\\%s\\%s-\0", general_content, temp, html_file_head_name);
					n = 4 * 2;
				}
				if (n == 5 * 2)//获取分网页的标题
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(headline_individual, temp);
					n = 5 * 2;
				}
				if (n == 6 * 2)//获取子任务1的exe文件的绝对路径
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(task1_exe_absolute_path, "%s\\%s\\%s", general_content, temp, task1_exe_file_name);
					n = 6 * 2;
				}
				if (n == 7 * 2)//获取子任务2的exe文件的绝对路径
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(task2_exe_absolute_path, "%s\\%s\\%s", general_content, temp, task2_exe_file_name);
					n = 7 * 2;
				}
				if (n == 8 * 2)//获取汇总html文件的名字
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy_s(summary_html_name, temp);
					n = 8 * 2;
				}
				if (n == 9 * 2)//获取汇总html网页的标题
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy_s(headline_summary, temp);
					n = 0;
					break;
				}
			}
		}
		else
		{
			printf("Fail to open the file: %s !\n", confi_file_absolute_path);
			exit(0);
		}
		if (fp)fclose(fp);
	}
	else
	{
		printf("Fail to get the general content!\n");
	}
}


/***********************************************
* 函数信息（solve_one_file）
* 1.函数名称：solve_one_file()
* 2.函数功能：
*   根据已定义的全局变量实现调用子任务1、2的程序对单个英文文档进行处理
* 3.返回值：无
************************************************/
void solve_one_file()
{
	//生成对应的子任务1命令行参数（概要模式）
	sprintf(cmd_task1_exe, "%s %s 2\0", task1_exe_absolute_path, English_file_absolute_path);

	//生成对应的子任务2命令行参数（静默结果展示模式）
	sprintf(cmd_task2_exe, "%s %s%s.txt 2\0", task2_exe_absolute_path, pr_statistic_file_absolute_path, English_file_name_off_postfix);

	//调用子任务1、2的exe文件
	system(cmd_task1_exe);
	system(cmd_task2_exe);
}


/*****************************************************************
* 函数信息（solve_files）
* 1.函数名称：solve_files()
* 2.函数功能：
*   根据已定义的全局变量实现调用子任务1、2对批量文件进行处理
* 3.返回值：无
******************************************************************/
void solve_files()
{
	int handle;
	_finddata_t file;//文件信息

	sprintf(summary_html_AP, "%s%s", pr_html_file_absolute_path, summary_html_name);

	FILE* fp = fopen(summary_html_AP, "w");
	if (fp != NULL)
	{
		//文件声明和头部内容
		fprintf(fp, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"ANSI\">\n");

		//网页标题部分
		fprintf(fp, "<title>The Summary of Statistic Data</title>\n</head>\n");

		//页面标题部分
		fprintf(fp, "<body style=\"text-align:justify; background-color:antiquewhite; font-size:35px\">\n<h1>\n%s\n</h1>\n", headline_summary);

		//页面链接部分

		handle = _findfirst(file_name_for_search_txt, &file);
		if (handle != -1)
		{
			sprintf(English_file_absolute_path, "%s\\%s", file_AP_of_English_files, file.name);
			English_file_name_off_postfix = get_name_off_postfix(file.name);
			//生成相关文件的绝对路径
			sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
			sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
			//调用程序完成对单个英文文档的统计
			solve_one_file();

			fprintf(fp, "<p><a style=\"text-decoration:none\" href=\".\\%s-%s.html\">%s.txt</a></p>\n", html_file_head_name, English_file_name_off_postfix, English_file_name_off_postfix);

			while (_findnext(handle, &file) != -1)//循环查找
			{
				sprintf(English_file_absolute_path, "%s\\%s", file_AP_of_English_files, file.name);
				English_file_name_off_postfix = get_name_off_postfix(file.name);
				//生成相关文件的绝对路径
				sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
				sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
				//调用程序完成对单个英文文档的统计
				solve_one_file();

				fprintf(fp, "<p><a style=\"text-decoration:none\" href=\".\\%s-%s.html\">%s.txt</a></p>\n", html_file_head_name, English_file_name_off_postfix, English_file_name_off_postfix);

			}
			_findclose(handle);

			//网页尾部部分
			fprintf(fp, "</body>\n</html>\n");
		}
		else
		{
			printf("Fail to find the file or no document in this file: %s !\n", file_AP_of_English_files);
		}

	}
	else
	{
		printf("Fail to open the file: %s !\n", summary_html_AP);
		exit(0);
	}
	if (fp)fclose(fp);

}


/************************************
* 函数信息（run）
* 1.函数名称：run(int argc, char* argv[])
* 2.函数功能：
*   实现整个程序的运行（输出菜单、调用函数完成对应功能）
* 3.参数说明：命令行参数仅为执行命令
* 4.返回值：无
*************************************/
void run(int argc, char* argv[])
{
	init_confi(argc, argv);//初始化数据
	int choice;
	
	char temp;
	for (;;)
	{
		print_menu();
		scanf_s("%d", &choice);
		temp = getchar();
		if (choice == 0)
		{
			printf("程序已退出！\n");
			break;
		}
		else
		{
			if (choice == 1)//单个英文文档
			{
				printf("请输入英语文本文件的绝对路径：\n");
				gets_s(English_file_absolute_path);
				English_file_name_off_postfix = get_name_off_postfix(English_file_absolute_path);
				//生成相关文件的绝对路径
				sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
				sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
				//调用程序完成对单个英文文档的统计
				solve_one_file();
				//自动展示结果
				system(html_file_absolute_path);
			}
			else
			{
				if (choice == 2)//批量英文文档
				{
					printf("请输入待处理文件夹的绝对路径：\n");
					gets_s(file_AP_of_English_files);
					//将文件绝对路径转换为搜索语句
					sprintf(file_name_for_search_txt, "%s\\*.txt", file_AP_of_English_files);
					
					solve_files();

					//自动结果展示模式
					system(summary_html_AP);
				}
				else
				{
					printf("输入的选择序号有误！请重新输入！\n");
				}
			}
		}
	}
}

/*******************************************
* 主函数：
* 1.命令行参数说明：无
* 2.函数功能：
*   实现整个程序的运行
*   输出菜单，与用户交互
********************************************/
int main(int argc, char* argv[])
{
	run(argc, argv);
	return 0;
}
