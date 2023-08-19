#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MAXCOST 99999

typedef struct Graph
{
    int data[MAX];//��һ���������洢���ж���
    int edge[MAX][MAX];//�ڽӾ��� 
    int nodenum = 5, edgenum;
}Graph;
//�����ڽӾ���Ĵ洢�ṹ

void CreateGraph(Graph &G)
{
    printf("��ʼ��5������Ϊ��0 1 2 3 4\n");
    for(int i = 0; i < G.nodenum; i++)
        G.data[i] = i;
    for(int i = 0; i < G.nodenum; i++)
        for(int j = 0; j < G.nodenum; j++)
            G.edge[i][j] = MAXCOST;
    printf("������ߵ�����\n");
    scanf("%d", &G.edgenum);
    printf("ÿ������һ���ߵ������˵��Ȩֵ,�ÿո�ֿ�\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G.edge[a][b] = c;
        G.edge[b][a] = c;
    }//��ȡÿһ���ߣ��洢���ڽӾ���
}

void Tree(Graph &G)
{
    int cost[MAX];//�洢ɨ�赽����̱ߣ��±��Ǳߵ�һ���˵�
    int from[MAX] = {0};//from���飬ֵΪ���±�Ϊ�˵�ɨ�赽����̱ߵ�����һ���˵�
    int min, node, sum = 0;
    for(int i = 1; i < G.nodenum; i++)//��ʼ��0Ϊ���
        cost[i] = G.edge[0][i];
    for(int i = 1; i < G.nodenum; i++)
    {
        min = MAXCOST;//min��ʼ��Ϊ���
        node = 0;//��̱ߵ�һ���˵�
        for(int j = 1; j < G.nodenum; j++)
        {
            if(cost[j] < min && cost[j] != 0)
            {
                min = cost[j];
                node = j;
            }//�õ���̱ߣ����¶˵�node
        }
        printf("%d - %d: %d\n", from[node], node, min);
        sum += min;
        cost[node] = 0;
        for(int j = 1; j < G.nodenum; j++)//��node�����ɨ����̱�
        {
            if(G.edge[node][j] < cost[j])
            {
                cost[j] = G.edge[node][j];
                from[j] = node;
            }//����cost��from
        }
    }
    printf("������С����Ϊ��%d\n", sum);
}
//Prim�㷨ʵ����С������

int main(){
    Graph G;
    CreateGraph(G);
    printf("��С�����õ��ı�:\n");
    Tree(G);
    system("pause");
    return 0;
}