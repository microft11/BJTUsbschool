#include "Lab4_fun.h"
#include "Lab4_run.h"
int page_1() {
	int ret = 0;
	printf("1. 调用实验3程序生成记录文件\r\n");
	printf("2.读取指定数据记录文件（二维数组存储方式）\r\n");
	printf(" 3.读取指定数据记录文件（结构体数组存储方式）\r\n");
	printf("4.读取指定数据记录文件（指针数组存储方式）\r\n");
	printf("5.读取指定数据记录文件（链表存储方式）\r\n");
	printf("6. 调用实验3生成数据记录文件，同时读取数据记录文件（二维数组方式存储）\r\n");
	printf(" 7. 调用实验3生成数据记录文件，同时读取数据记录文件（结构体数组方式存储）\r\n");
	printf("8. 调用实验3生成数据记录文件，同时读取数据记录文件（指针数组方式存储）\r\n");
	printf("9. 调用实验3生成数据记录文件，同时读取数据记录文件（链表方式存储）\r\n");
	printf("10. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（二维数组方式存储）\r\n");
	printf("11. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（结构体数组方式存储）\r\n");
	printf("12. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（指针数组方式存储）\r\n");
	printf("13. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（链表方式存储）\r\n");
	printf("0. 退出\r\n");
	scanf_s("%d", &ret);
	return ret;
}

int cmp1(const void* a, const void* b) {
	int* aa = (int*)a;
	int* bb = (int*)b;
	if (aa[0] != bb[0]) {
		return aa[0] - bb[0];
	}
	else if (aa[1] != bb[1]) {
		return aa[1] - bb[1];
	}
	else {
		return aa[2] - bb[2];
	}
}
int cmp2(const void* a, const void* b) {
	struct Data_str* aa = (struct Data_str*)a;
	struct Data_str* bb = (struct Data_str*)b;
	if (aa->a0 != bb->a0) {
		return aa->a0 - bb->a0;
	}
	else if (bb->a1 != bb->a1) {
		return bb->a1 - bb->a1;
	}
	else {
		return bb->a2 - bb->a2;
	}
}
int cmp3(const void* a, const void* b) {
	int** aa = (int**)a;
	int** bb = (int**)b;
	if ((*aa)[0] != (*bb)[0]) {
		return (*aa)[0] - (*bb)[0];
	}
	else if ((*aa)[1] != (*bb)[1]) {
		return (*aa)[1] - (*bb)[1];
	}
	else {
		return (*aa)[2] - (*bb)[2];
	}
}
static int cmp4(struct node* a, struct node* b) {
	if (b == NULL) return -1;
	if (a->a0!= b->a0) {
		return a->a0 - b->a0;
	}
	else if (a->a1 != b->a1) {
		return a->a1 - b->a1;
	}
	else {
		return a->a2 - b->a2;
	}
}
struct node* bubblesort(struct node* head,int num)
{
	if (head == NULL || head->next == NULL)
		return head;
	struct node* p = head->next, *p1;
	int tmp[3];
	for (int i = 0; i < num - 1; i++) {
		p1 = p;
		for (int j = 0; j < num - 1 - i; j++) {
			if (cmp4(p1 , p1->next)>0) {
				tmp[0] = p1->a0; tmp[1] = p1->a1; tmp[2] = p1->a2;
				p1->a0 = p1->next->a0; p1->a1 = p1->next->a1; p1->a2 = p1->next->a2;
				p1->next->a0 = tmp[0]; p1->next->a1 = tmp[1]; p1->next->a2 = tmp[2];
			}
			p1 = p1->next;
		}
	}
	return head;

}
