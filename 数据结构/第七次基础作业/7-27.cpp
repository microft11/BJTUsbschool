#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct EdgeNode
{
    int adj;
    EdgeNode *next;
}EdgeNode;

typedef struct Node
{
    int data;
    EdgeNode *first;
}Node, List[MAX];

typedef struct
{
    List list;
    int nodenum, edgeenum;
}Graph;
//�����ڽӱ�洢�ṹ

int visit[MAX] = {0};//��ʼ�����е�Ϊδ����

void CreateGraph(Graph &G)
{
    printf("�����붥����\n");
    scanf("%d", &G.nodenum);
    printf("���ɶ�������Ϊ��");
    for(int i = 0; i < G.nodenum; i++)
    {
        G.list[i].data = 0;
        G.list[i].first = NULL;
        printf("%d ", i);
    }
    printf("\n");
    printf("������ߵ�����\n");
    scanf("%d", &G.edgeenum);
    int a, b;
    EdgeNode *p;
    printf("��ÿһ������ÿһ���ߵ������յ�,�ո�ֿ�\n");
    for(int i = 0; i < G.edgeenum; i++)
    {
        scanf("%d %d", &a, &b);
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->adj = b;//����ָ��ĵ�
        p->next = G.list[a].first;
        G.list[a].first = p;
    }
}

int Find(Graph &G, int node1, int node2, int k)
{
    if(node1 == node2 &&k == 0) return 1;//���������غ���k=0�����ҵ�������·��������1
    else if(k > 0)//k��Ϊ0��·�����Ҽ���
    {
        visit[node1] = 1;//���ʹ��ĵ���Ϊ1
        EdgeNode *p;
        for(p = G.list[node1].first; p != NULL; p = p->next)//�ӵ�ǰ����ڽӵ㿪ʼ��������
        {
            if(visit[p->adj] == 0)//��������û�б�����
                if(Find(G, p->adj, node2, k-1))//�������ò���·���ĺ���
                    return 1;
        }
        visit[node1] = 0;
    }
    return 0;//û�ҵ�������·������0
}

int main()
{
    Graph G;
    CreateGraph(G);
    printf("����Ҫ������������֮���ͨ·�Լ����ǵ�·������(�������ÿո�ֿ�)\n");
    int node1, node2, k;
    scanf("%d %d %d", &node1, &node2, &k);
    if(Find(G, node1, node2, k))
        printf("����������·��\n");
    else
        printf("û�ҵ�������·��\n");
    system("pause"); 
    return 0;
}