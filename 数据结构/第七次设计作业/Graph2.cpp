#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Graph
{
    int data[MAX];//��һ���������洢���ж���
    int edge[MAX][MAX];//�ڽӾ��� 
    int nodenum, edgenum;
}Graph;
//�����ڽӾ���Ĵ洢�ṹ

int Find(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.data[i] == node) 
            return i;
    return -1;
}
//�����ڶ��������е�λ��

void CreateGraph(Graph &G)
{
    printf("�����붥�����\n");
    scanf("%d", &G.nodenum);
    printf("��������һ����������ÿ������,���������ֱ�ʾ���ÿո�ָ�\n");
    for(int i = 0; i < G.nodenum; i++)
        scanf("%d", &G.data[i]);
    for(int i = 0; i < G.nodenum; i++)
        for(int j = 0; j < G.nodenum; j++)
            G.edge[i][j] = 0;
    printf("������ߵ�����\n");
    scanf("%d", &G.edgenum);
    printf("ÿ������һ���ߵ������˵�,�ÿո�ֿ�\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a = Find(G, a);
        b = Find(G, b);
        G.edge[a][b] = 1;
        G.edge[b][a] = 1;
    }//��ȡÿһ���ߣ��洢���ڽӾ���
}

int visit[MAX];

int Next(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.edge[node][i] == 1 && visit[i] == 0)//���ڽӵ㣬�һ�û������
            return i;//�����ڽӵ�
    return -1;//û�з��ϵķ���-1
}
//�����װ�������ڲ���һ��������δ�����ʵ��ٽ��

void DFS(Graph &G, int node)
{
    visit[node] = 1;
    printf("%d", G.data[node]);
    int p;
    while(Next(G, node) != -1)//��δ���ʵ��ڽӵ�
    {
        p = Next(G, node);
        DFS(G, p);//������ڽӵ����������ȱ���
        p = Next(G, p);
    }
}
//������ȱ���

void BFS(Graph &G, int node)
{
    int Queue[MAX];
    int front = 0, rear = 0;//��ʼ��һ������
    visit[node] = 1;
    printf("%d", G.data[node]);
    Queue[rear] = node;
    rear++;//��������������
    while(front != rear)
    {
        int a = Queue[front];
        front++;//���зǿճ���
        int p;
        while(Next(G, a) != -1)//��δ���ʵ��ڽӵ����
        {
            p = Next(G, a);
            visit[p] = 1;
            printf("%d", G.data[p]);
            Queue[rear] = p;
            rear++;//���ʺ�������
            p = Next(G, p);
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