#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct EdgeNode
{
    int adj;//��ָ��Ķ���
    struct EdgeNode *next;//��һ����ָ��
}EdgeNode;

typedef struct Node
{
    int data;//�������Ϣ
    EdgeNode *first;//ָ���һ����
}Node, List[MAX];

typedef struct
{
    List list;//��������
    int nodenum, edgenum;//�ֱ��ʾ�������ͻ�������
}Graph;

int Find(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.list[i].data == node)//���ҵ�ָ���Ķ���
            return i;
    return -1;
}
//���Ҷ������б��е�λ��

void CreateGraph(Graph &G)
{
    printf("�����붥�����\n");
    scanf("%d", &G.nodenum);
    printf("��������һ����������ÿ������,���������ֱ�ʾ���ÿո�ָ�\n");
    for(int i = 0; i < G.nodenum; i++)
    {
        scanf("%d", &G.list[i].data);
        G.list[i].first = NULL;
    }
    printf("������ߵ�����\n");
    scanf("%d", &G.edgenum);
    printf("ÿ������һ���ߵ������˵�,�ÿո�ֿ�\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b;
        EdgeNode *p1, *p2;
        scanf("%d %d", &a, &b);
        a = Find(G, a);//�ҵ���Ӧa�Ķ���
        b = Find(G, b);//�ҵ���Ӧb�Ķ���
        p1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p1->adj = b;
        p1->next = G.list[a].first;
        G.list[a].first = p1;//�洢��a��b
        p2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p2->adj = a;
        p2->next = G.list[b].first;
        G.list[b].first = p2;//�洢��b��a
    }
}
//�ڽӱ�ĳ�ʼ��

int visit[MAX];

void DFS(Graph &G, int node)
{
    EdgeNode *p;
    p = G.list[node].first;
    visit[node] = 1;
    printf("%d", G.list[node].data);//����������ĵ�
    while(p)
    {
        if(visit[p->adj] == 0) DFS(G, p->adj);//��δ���ʾͼ�������DFS
        p = p->next;
    }
}
//������ȱ���

void BFS(Graph &G, int node)
{
    int Queue[MAX];
    int front = 0, rear = 0;
    visit[node] = 1;
    printf("%d", G.list[node].data);//����������ĵ�
    Queue[rear] = node;
    rear++;//����֮��ͽ������
    EdgeNode *p;
    while(front != rear)//���зǿ�
    {
        int a = Queue[front];
        front++;//��һ��Ԫ�س���
        for(EdgeNode *p = G.list[a].first; p != NULL; p = p->next)//��δ���ʵ��ڽӵ�
        {
            if(visit[p->adj] == 0)//δ���ʵ��ڷ��ʺ�����
            {
                visit[p->adj] = 1;
                printf("%d", G.list[p->adj].data);//������ʵĵ�
                Queue[rear] = p->adj;
                rear++;//�������ĵ�����
            }
        }
    }
}
//������ȱ���

int main() {
    Graph G;
    CreateGraph(G);
    int node;
    printf("������һ�����㿪ʼ����\n");
    scanf("%d", &node);
    for(int i = 0; i < G.nodenum; i++) visit[i] = 0;//��ʼ�����ж���Ϊδ����
    node = Find(G, node);
    printf("������ȱ����Ľ���ǣ�");
    DFS(G, node);
    printf("\n");
    for(int i = 0; i < G.nodenum; i++) visit[i] = 0;//��ʼ�����ж���Ϊδ����
    printf("������ȱ����Ľ���ǣ�");
    BFS(G, node);
    printf("\n");
    system("pause");
    return 0;
}
