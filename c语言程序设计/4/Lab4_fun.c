#include "Lab4_fun.h"
#include "Lab4_run.h"
int page_1() {
	int ret = 0;
	printf("1. ����ʵ��3�������ɼ�¼�ļ�\r\n");
	printf("2.��ȡָ�����ݼ�¼�ļ�����ά����洢��ʽ��\r\n");
	printf(" 3.��ȡָ�����ݼ�¼�ļ����ṹ������洢��ʽ��\r\n");
	printf("4.��ȡָ�����ݼ�¼�ļ���ָ������洢��ʽ��\r\n");
	printf("5.��ȡָ�����ݼ�¼�ļ�������洢��ʽ��\r\n");
	printf("6. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����ά���鷽ʽ�洢��\r\n");
	printf(" 7. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ����ṹ�����鷽ʽ�洢��\r\n");
	printf("8. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ���ָ�����鷽ʽ�洢��\r\n");
	printf("9. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������ʽ�洢��\r\n");
	printf("10. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨶�ά���鷽ʽ�洢��\r\n");
	printf("11. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨽ṹ�����鷽ʽ�洢��\r\n");
	printf("12. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������ָ�����鷽ʽ�洢��\r\n");
	printf("13. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����������ʽ�洢��\r\n");
	printf("0. �˳�\r\n");
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
