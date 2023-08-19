#include "Lab4_run.h"
#include "Lab4_fun.h"
#include <stdlib.h>
#define MAX_LEN 100
const char exe_3_path[] = "C:\\Users\\ren\\Desktop\\。\\Lab4\\3.exe";
const char data_path[] = "C:\\Users\\ren\\Desktop\\。\\Lab4\\output.txt";
int num = 0;
int data_arr[MAX_LEN][3];

struct Data_str data_str[MAX_LEN];
int* data_p[MAX_LEN];

struct node* data_l = NULL;

void run() {
	FILE* fp;
	int num = 0;
	while (1) {
		int opt = page_1();
		struct node* cur;
		switch (opt) {
		case 0:
			break;
		case 1:
			system(exe_3_path);
			break;
		case 2:
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_arr[i][0], &data_arr[i][1], &data_arr[i][2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_arr[i][0], data_arr[i][1], data_arr[i][2]);
			}
			break;
		case 3:
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_str[i].a0, &data_str[i].a1, &data_str[i].a2);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_str[i].a0, data_str[i].a1,data_str[i].a2);
			}
			break;
		case 4:
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				data_p[i] = (int*)malloc(3 * sizeof(int));
				fscanf_s(fp, "%d,%d,%d,", &data_p[i][0], &data_p[i][1], &data_p[i][2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_p[i][0], data_p[i][1], data_p[i][2]);
			}
			break;
		case 5:
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				struct node* tmp = malloc(sizeof(struct node));
				fscanf_s(fp, "%d,%d,%d,", &tmp->a0, &tmp->a1, &tmp->a2);
				tmp->next = data_l;
				data_l = tmp;
			}
			printf("数据如下：\r\n");
			cur = data_l;
			while (cur != NULL) {
				printf("%d,%d,%d,\r\n", cur->a0, cur->a1, cur->a2);
				cur = cur->next;
			}
			fclose(fp);
			break;
		case 6:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_arr[i][0], &data_arr[i][1], &data_arr[i][2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_arr[i][0], data_arr[i][1], data_arr[i][2]);
			}
			break;
		case 7:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_str[i].a0, &data_str[i].a1, &data_str[i].a2);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,", data_str[i].a0, data_str[i].a1, data_str[i].a2);
			}
			break;
		case 8:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				data_p[i] = (int*)malloc(3 * sizeof(int));
				fscanf_s(fp, "%d,%d,%d,", data_p[0], data_p[1], data_p[2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_p[i][0], data_p[i][1], data_p[i][2]);
			}
			break;
		case 9:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				struct node* tmp = malloc(sizeof(struct node));
				fscanf_s(fp, "%d,%d,%d,", &tmp->a0, &tmp->a1, &tmp->a2);
				tmp->next = data_l;
				data_l = tmp;
			}
			fclose(fp);
			printf("数据如下：\r\n");
			cur = data_l;
			while (cur != NULL) {
				printf("%d,%d,%d,\r\n", cur->a0, cur->a1, cur->a2);
				cur = cur->next;
			}
			break;
		case 10:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_arr[i][0], &data_arr[i][1], &data_arr[i][2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_arr[i][0], data_arr[i][1], data_arr[i][2]);
			}
			qsort(data_arr, num, 3*sizeof(int), cmp1);
			printf("排序后：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_arr[i][0], data_arr[i][1], data_arr[i][2]);
			}
			break;
		case 11:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				fscanf_s(fp, "%d,%d,%d,", &data_str[i].a0, &data_str[i].a1, &data_str[i].a2);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_str[i].a0, data_str[i].a1, data_str[i].a2);
			}
			qsort(data_str, num, sizeof(struct Data_str), cmp2);
			printf("排序如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_str[i].a0, data_str[i].a1, data_str[i].a2);
			}
			break;
		case 12:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				data_p[i] = (int*)malloc(3 * sizeof(int));
				fscanf_s(fp, "%d,%d,%d,", &data_p[i][0], &data_p[i][1], &data_p[i][2]);
			}
			fclose(fp);
			printf("数据如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_p[i][0], data_p[i][1], data_p[i][2]);
			}
			qsort(data_p, num, sizeof(int*), cmp3);
			printf("排序后如下：\r\n");
			for (int i = 0; i < num; i++) {
				printf("%d,%d,%d,\r\n", data_p[i][0], data_p[i][1], data_p[i][2]);
			}
			break;
		case 13:
			system(exe_3_path);
			fopen_s(&fp,data_path, "r");
			fscanf_s(fp, "%d", &num);
			for (int i = 0; i < num; i++) {
				struct node* tmp = malloc(sizeof(struct node));
				fscanf_s(fp, "%d,%d,%d,", &tmp->a0, &tmp->a1, &tmp->a2);
				tmp->next = data_l;
				data_l = tmp;
			}
			fclose(fp);
			printf("数据如下：\r\n");
			cur = data_l;
			while (cur != NULL) {
				printf("%d,%d,%d,\r\n", cur->a0, cur->a1, cur->a2);
				cur = cur->next;
			}
			data_l = bubblesort(data_l, num);
			printf("排序后结果：\r\n");
			cur = data_l;
			while (cur != NULL) {
				printf("%d,%d,%d,\r\n", cur->a0, cur->a1, cur->a2);
				cur = cur->next;
			}
			break;
		default:
			break;
		}
	}
}