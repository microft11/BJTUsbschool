#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 1000
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>

char task1_exe_file_name[] = "������1.exe";//������1��exe�ļ����ļ���
char task2_exe_file_name[] = "������2.exe";//������2��exe�ļ����ļ���

char temp[MAX_LEN];//��ת�ַ����Ŀ��ַ���

char task1_exe_absolute_path[MAX_LEN];//������1��exe�ļ��ľ���·��
char task2_exe_absolute_path[MAX_LEN];//������2��exe�ļ��ľ���·��

char general_content_name[] = "ʵ����\0";//��Ŀ¼����
char general_content[MAX_LEN];//��Ŀ¼

char confi_file_name[] = "Lab5_confi.ini\0";//��ʼ�������ļ�����
char confi_file_absolute_path[MAX_LEN];//��ʼ�������ļ��ľ���·��

char* English_file_name_off_postfix;//Ӣ�ﲻ����׺�����ı��ļ�������
char English_file_absolute_path[MAX_LEN];//Ӣ���ı��ļ��ľ���·��

char statistic_file_head_name[MAX_LEN];//ͳ���ļ�ͷ����
char pr_statistic_file_absolute_path[MAX_LEN];//ͳ�ƽ���ļ��ľ���·��ǰ����
char statistic_file_absolute_path[MAX_LEN];//ͳ�ƽ���ļ��ľ���·��

char html_file_head_name[MAX_LEN];//��ҳ�ļ�ͷ����
char pr_html_file_absolute_path[MAX_LEN];//��ҳ�ļ��ľ���·��ǰ����
char html_file_absolute_path[MAX_LEN];//��ҳ�ļ��ľ���·��

char headline_individual[MAX_LEN];//����ҳ����
char headline_summary[MAX_LEN];//����ҳ�����

char cmd_task1_exe[MAX_LEN];//����������1�������в���
char cmd_task2_exe[MAX_LEN];//����������2�������в���

char file_AP_of_English_files[MAX_LEN];//Ӣ���ĵ������ļ��еľ���·��
char file_name_for_search_txt[MAX_LEN];//�����ı�txt�ļ������

char summary_html_name[MAX_LEN];//����html�ļ�������
char summary_html_AP[MAX_LEN];//����html�ļ��ľ���·��


void print_menu()//��ӡ�˵�
{
	printf("*************************************************\n");
	printf("*     ��˶���ڼ���������诵�ʵ��5����         *\n");
	printf("*                                               *\n");
	printf("*     1.�Ե���Ӣ���ĵ�����ͳ��                  *\n");
	printf("*                                               *\n");
	printf("*     2.������Ӣ���ĵ�����ͳ��                  *\n");
	printf("*                                               *\n");
	printf("*     0.�˳�                                    *\n");
	printf("*                                               *\n");
	printf("*************************************************\n");
	printf("��������Ҫִ�еĳ�����ţ�\n");
}


/*************************************************
* ������Ϣ��get_name_off_postfix��
* 1.�������ƣ�get_name_off_postfix(char* s)
* 2.�������ܣ���ȡ������׺�����ļ���
* 3.����˵����
*   s���ļ������ļ�����·���ַ������׵�ַ
* 4.����ֵ��ȥ����׺�����ļ������׵�ַ
**************************************************/
char* get_name_off_postfix(char* s)
{
	strcpy(temp, s);
	for (int i = strlen(temp) - 1; i >= 0; i--)
	{
		if (temp[i] == '.')
		{
			strcpy(temp + i, "\0");//ȥ����׺��
		}
		if (temp[i] == '\\' || temp[i] == '/')
		{
			return temp + i + 1;
		}
	}
	return temp;
}


/*********************************************
* ������Ϣ����init_confi��
* 1.�������ƣ�init_confi(int argc, char* argv[])
* 2.����˵����
* ��1��argc�������в�������
* ��2��argv�������в����ַ���ָ�������׵�ַ
* 3.�������ܣ���ʼ�����ݣ�
* ��1����Ŀ¼
* ��2�������ļ�����·��
* ��3��ͳ�ƽ���ļ�ͷ����
* ��4��ͳ�ƽ���ļ�ǰ����
* ��5����ҳ�ļ�ͷ����
* ��6����ҳ�ļ�����·��ǰ����
* ��7����ҳ����
* ��8��������1��2��exe�ļ��ľ���·��
* ��9������html�ļ�������
* ��10������htmlҳ��ı���
* 4.����ֵ����
**********************************************/
void init_confi(int argc, char* argv[])
{
	FILE* fp;
	int n = 0;//������ȡ�����ļ��е���Ϣ
	char temp[MAX_LEN];//ת���ж���Ŀ¼
	char current_content_name[MAX_LEN];//��ǰĿ¼����
	strcpy_s(temp, MAX_LEN, argv[0]);
	for (int i = strlen(temp) - 1; i >= 0; i--)//��ȡ��Ŀ¼
	{
		if (temp[i] == '\\' || temp[i] == '/')
		{
			strcpy_s(current_content_name, MAX_LEN, temp + i + 1);
			if (strcmp(current_content_name, general_content_name) == 0)//�жϵ�ǰĿ¼�Ƿ�Ϊ��Ŀ¼
			{
				strcpy_s(general_content, MAX_LEN, temp);//��ȡ��Ŀ¼
				break;
			}
			strcpy_s(temp + i, MAX_LEN - i, "\0");
		}
	}
	if (strlen(general_content) > 0)//�ɹ���ȡ��Ŀ¼
	{
		sprintf(confi_file_absolute_path, "%s\\%s", general_content, confi_file_name);
		fp = fopen(confi_file_absolute_path, "r");
		if (fp != NULL)
		{
			while (fgets(temp, MAX_LEN, fp) != NULL)
			{
				n++;
				if (n == 1 * 2)//��ȡͳ�ƽ���ļ�ͷ����
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(statistic_file_head_name, temp);
					n = 1 * 2;
				}
				if (n == 2 * 2)//��ȡͳ�ƽ���ļ��ľ���·��ǰ����
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(pr_statistic_file_absolute_path, "%s\\%s\\%s-\0", general_content, temp, statistic_file_head_name);
					n = 2 * 2;
				}
				if (n == 3 * 2)//��ȡ��ҳ�ļ���ͷ����
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(html_file_head_name, temp);
					n = 3 * 2;
				}
				if (n == 4 * 2)//��ȡ��ҳ�ļ��ľ��Ե�ַǰ����
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(pr_html_file_absolute_path, "%s\\%s\\%s-\0", general_content, temp, html_file_head_name);
					n = 4 * 2;
				}
				if (n == 5 * 2)//��ȡ����ҳ�ı���
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy(headline_individual, temp);
					n = 5 * 2;
				}
				if (n == 6 * 2)//��ȡ������1��exe�ļ��ľ���·��
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(task1_exe_absolute_path, "%s\\%s\\%s", general_content, temp, task1_exe_file_name);
					n = 6 * 2;
				}
				if (n == 7 * 2)//��ȡ������2��exe�ļ��ľ���·��
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					sprintf(task2_exe_absolute_path, "%s\\%s\\%s", general_content, temp, task2_exe_file_name);
					n = 7 * 2;
				}
				if (n == 8 * 2)//��ȡ����html�ļ�������
				{
					n = strlen(temp) - 1;
					temp[n] = '\0';
					strcpy_s(summary_html_name, temp);
					n = 8 * 2;
				}
				if (n == 9 * 2)//��ȡ����html��ҳ�ı���
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
* ������Ϣ��solve_one_file��
* 1.�������ƣ�solve_one_file()
* 2.�������ܣ�
*   �����Ѷ����ȫ�ֱ���ʵ�ֵ���������1��2�ĳ���Ե���Ӣ���ĵ����д���
* 3.����ֵ����
************************************************/
void solve_one_file()
{
	//���ɶ�Ӧ��������1�����в�������Ҫģʽ��
	sprintf(cmd_task1_exe, "%s %s 2\0", task1_exe_absolute_path, English_file_absolute_path);

	//���ɶ�Ӧ��������2�����в�������Ĭ���չʾģʽ��
	sprintf(cmd_task2_exe, "%s %s%s.txt 2\0", task2_exe_absolute_path, pr_statistic_file_absolute_path, English_file_name_off_postfix);

	//����������1��2��exe�ļ�
	system(cmd_task1_exe);
	system(cmd_task2_exe);
}


/*****************************************************************
* ������Ϣ��solve_files��
* 1.�������ƣ�solve_files()
* 2.�������ܣ�
*   �����Ѷ����ȫ�ֱ���ʵ�ֵ���������1��2�������ļ����д���
* 3.����ֵ����
******************************************************************/
void solve_files()
{
	int handle;
	_finddata_t file;//�ļ���Ϣ

	sprintf(summary_html_AP, "%s%s", pr_html_file_absolute_path, summary_html_name);

	FILE* fp = fopen(summary_html_AP, "w");
	if (fp != NULL)
	{
		//�ļ�������ͷ������
		fprintf(fp, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"ANSI\">\n");

		//��ҳ���ⲿ��
		fprintf(fp, "<title>The Summary of Statistic Data</title>\n</head>\n");

		//ҳ����ⲿ��
		fprintf(fp, "<body style=\"text-align:justify; background-color:antiquewhite; font-size:35px\">\n<h1>\n%s\n</h1>\n", headline_summary);

		//ҳ�����Ӳ���

		handle = _findfirst(file_name_for_search_txt, &file);
		if (handle != -1)
		{
			sprintf(English_file_absolute_path, "%s\\%s", file_AP_of_English_files, file.name);
			English_file_name_off_postfix = get_name_off_postfix(file.name);
			//��������ļ��ľ���·��
			sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
			sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
			//���ó�����ɶԵ���Ӣ���ĵ���ͳ��
			solve_one_file();

			fprintf(fp, "<p><a style=\"text-decoration:none\" href=\".\\%s-%s.html\">%s.txt</a></p>\n", html_file_head_name, English_file_name_off_postfix, English_file_name_off_postfix);

			while (_findnext(handle, &file) != -1)//ѭ������
			{
				sprintf(English_file_absolute_path, "%s\\%s", file_AP_of_English_files, file.name);
				English_file_name_off_postfix = get_name_off_postfix(file.name);
				//��������ļ��ľ���·��
				sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
				sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
				//���ó�����ɶԵ���Ӣ���ĵ���ͳ��
				solve_one_file();

				fprintf(fp, "<p><a style=\"text-decoration:none\" href=\".\\%s-%s.html\">%s.txt</a></p>\n", html_file_head_name, English_file_name_off_postfix, English_file_name_off_postfix);

			}
			_findclose(handle);

			//��ҳβ������
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
* ������Ϣ��run��
* 1.�������ƣ�run(int argc, char* argv[])
* 2.�������ܣ�
*   ʵ��������������У�����˵������ú�����ɶ�Ӧ���ܣ�
* 3.����˵���������в�����Ϊִ������
* 4.����ֵ����
*************************************/
void run(int argc, char* argv[])
{
	init_confi(argc, argv);//��ʼ������
	int choice;
	
	char temp;
	for (;;)
	{
		print_menu();
		scanf_s("%d", &choice);
		temp = getchar();
		if (choice == 0)
		{
			printf("�������˳���\n");
			break;
		}
		else
		{
			if (choice == 1)//����Ӣ���ĵ�
			{
				printf("������Ӣ���ı��ļ��ľ���·����\n");
				gets_s(English_file_absolute_path);
				English_file_name_off_postfix = get_name_off_postfix(English_file_absolute_path);
				//��������ļ��ľ���·��
				sprintf(statistic_file_absolute_path, "%s%s.txt", pr_statistic_file_absolute_path, English_file_name_off_postfix);
				sprintf(html_file_absolute_path, "%s%s.html", pr_html_file_absolute_path, English_file_name_off_postfix);
				//���ó�����ɶԵ���Ӣ���ĵ���ͳ��
				solve_one_file();
				//�Զ�չʾ���
				system(html_file_absolute_path);
			}
			else
			{
				if (choice == 2)//����Ӣ���ĵ�
				{
					printf("������������ļ��еľ���·����\n");
					gets_s(file_AP_of_English_files);
					//���ļ�����·��ת��Ϊ�������
					sprintf(file_name_for_search_txt, "%s\\*.txt", file_AP_of_English_files);
					
					solve_files();

					//�Զ����չʾģʽ
					system(summary_html_AP);
				}
				else
				{
					printf("�����ѡ������������������룡\n");
				}
			}
		}
	}
}

/*******************************************
* ��������
* 1.�����в���˵������
* 2.�������ܣ�
*   ʵ���������������
*   ����˵������û�����
********************************************/
int main(int argc, char* argv[])
{
	run(argc, argv);
	return 0;
}
