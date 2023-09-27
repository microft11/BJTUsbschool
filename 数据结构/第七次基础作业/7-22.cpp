#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct EdgeNode
{
    int adj;
    struct EdgeNode* next;
}EdgeNode;

typedef struct Node
{
    int data;
    EdgeNode* first;
}Node, List[MAX];

typedef struct
{
    List list;
    int nodenum, edgenum;
}Graph;
//�����ڽӱ�洢�ṹ

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
    scanf("%d", &G.edgenum);
    int a, b;
    EdgeNode *p;
    printf("ÿ������һ���ߵ������յ�,�ÿո�ֿ�\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        scanf("%d %d", &a, &b);
        p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->adj = b;
        p->next = G.list[a].first;
        G.list[a].first = p;
    }//�ߵ����ݴ洢���ڽӱ�
}

int Find(Graph &G, int node1, int node2)
{
    EdgeNode *p;
    p = G.list[node1].first;//��ȡָ�������ڽӵ�
    while(p)//�������ڽӵ����
    {
        if(p->adj != node2 && Find(G, p->adj, node2))//�������㲻��ָ�����յ㣬������Ե�ǰ����ڽӵ����Find
            return 1;
        if(p->adj == node2)
            return 1;//����������ָ�����յ㣬���ҵ�ͨ·������1
        p = p->next;//û�ҵ���һ���ڽӵ�
    }
    return 0;//û�ҵ�����0
}

int main()
{
    Graph G;
    CreateGraph(G);
    printf("����Ҫ������������֮���ͨ·(�ÿո�ֿ�)\n");
    int node1, node2;
    scanf("%d %d", &node1, &node2);
    if(Find(G, node1, node2))
        printf("����ͨ·\n");
    else
        printf("������ͨ·\n");
    system("pause"); 
    return 0;
}

