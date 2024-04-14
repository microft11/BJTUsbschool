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
	//argc==1？
	if (argc == 1) {      
		recourcount(&my_conf);
		recourpath(&my_conf);
	}
	else
	{
		//argc==2？
		if (argc == 2) {
			// 命令行参数是数值？
			if (is_number(argv[1])) {
				// 命令行参数表示的记录条数值写入配置信息结构体变量
				my_conf.recordcount1 = atoi(argv[1]);
				recourpath(&my_conf);
			}
			else {
				//文件名是否合法？
				if (checkFilePath(argv[1])) {
					//命令行参数表示的文件路径拆分成文件名和文件存储目录写入配置信息结构体变量
					splitFilePath(&my_conf, argv[1]);
					recourcount(&my_conf);
				}
				else {
					printf("参数1作路径不合法\r\n");
					exit(0);
				}
			}
		}
		else {
			if (argc == 3) {
				//第一个参数是数值？
				if (is_number(argv[1])) {
					//命令行参数的第一个参数作为记录条数存入配置信息结构体变量
					my_conf.recordcount1 = atoi(argv[1]);
					//第二个参数是否合法？
					if (checkFilePath(argv[2])) {
						//命令行参数的第二个参数作为文件存储路径，拆分后存入配置信息结构体变量
						splitFilePath(&my_conf, argv[2]);
					}
					else {
						//提示命令行参数不合法
						printf("参数2作路径不合法\r\n");
						exit(0);
					}
				}
				else {
					if (is_number(argv[2])) {
						//命令行参数的第二个参数作为记录条数存入配置信息结构体变量
						my_conf.recordcount1 = atoi(argv[2]);
						if (checkFilePath(argv[1])) {
							//命令行参数的一个参数作为文件存储路径，拆分后存入配置信息结构体变量
							splitFilePath(&my_conf, argv[1]);
						}
						else {
							//提示命令行参数不合法
							printf("参数1作路径不合法\r\n");
							exit(0);
						}
					}
					else {
						//提示用户输入的两个命令行参数中找不到记录条数参数
						printf("找不到记录条数\r\n");
						exit(0);
					}
				}
			}
			else {
				//提示用户输入参数过多
				printf("参数过多\r\n");
				exit(0);
			}
		}
	}
	function(&my_conf);
}
