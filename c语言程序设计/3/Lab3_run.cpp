#include <stdio.h>
#include <stdlib.h>
#include"Lab3_run.h"
#include"Lab3_fun.h"
#include"Lab3_data.h"
void run(int argc, char* argv[])
{
	CONF my_conf;
	char tmp[MAX_STR_LEN];
	read_conf(&my_conf);
	//argc==1��
	if (argc == 1) {      
		recourcount(&my_conf);
		recourpath(&my_conf);
	}
	else
	{
		//argc==2��
		if (argc == 2) {
			// �����в�������ֵ��
			if (is_number(argv[1])) {
				// �����в�����ʾ�ļ�¼����ֵд��������Ϣ�ṹ�����
				my_conf.recordcount1 = atoi(argv[1]);
				recourpath(&my_conf);
			}
			else {
				//�ļ����Ƿ�Ϸ���
				if (checkFilePath(argv[1])) {
					//�����в�����ʾ���ļ�·����ֳ��ļ������ļ��洢Ŀ¼д��������Ϣ�ṹ�����
					splitFilePath(&my_conf, argv[1]);
					recourcount(&my_conf);
				}
				else {
					printf("����1��·�����Ϸ�\r\n");
					exit(0);
				}
			}
		}
		else {
			if (argc == 3) {
				//��һ����������ֵ��
				if (is_number(argv[1])) {
					//�����в����ĵ�һ��������Ϊ��¼��������������Ϣ�ṹ�����
					my_conf.recordcount1 = atoi(argv[1]);
					//�ڶ��������Ƿ�Ϸ���
					if (checkFilePath(argv[2])) {
						//�����в����ĵڶ���������Ϊ�ļ��洢·������ֺ����������Ϣ�ṹ�����
						splitFilePath(&my_conf, argv[2]);
					}
					else {
						//��ʾ�����в������Ϸ�
						printf("����2��·�����Ϸ�\r\n");
						exit(0);
					}
				}
				else {
					if (is_number(argv[2])) {
						//�����в����ĵڶ���������Ϊ��¼��������������Ϣ�ṹ�����
						my_conf.recordcount1 = atoi(argv[2]);
						if (checkFilePath(argv[1])) {
							//�����в�����һ��������Ϊ�ļ��洢·������ֺ����������Ϣ�ṹ�����
							splitFilePath(&my_conf, argv[1]);
						}
						else {
							//��ʾ�����в������Ϸ�
							printf("����1��·�����Ϸ�\r\n");
							exit(0);
						}
					}
					else {
						//��ʾ�û���������������в������Ҳ�����¼��������
						printf("�Ҳ�����¼����\r\n");
						exit(0);
					}
				}
			}
			else {
				//��ʾ�û������������
				printf("��������\r\n");
				exit(0);
			}
		}
	}
	function(&my_conf);
}
