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
//定义邻接表存储结构

void CreateGraph(Graph &G)
{
    printf("请输入顶点数\n");
    scanf("%d", &G.nodenum);
    printf("生成顶点依次为：");
    for(int i = 0; i < G.nodenum; i++)
    {
        G.list[i].data = 0;
        G.list[i].first = NULL;
        printf("%d ", i);
    }
    printf("\n");
    printf("请输入边的条数\n");
    scanf("%d", &G.edgenum);
    int a, b;
    EdgeNode *p;
    printf("每行输入一条边的起点和终点,用空格分开\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        scanf("%d %d", &a, &b);
        p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->adj = b;
        p->next = G.list[a].first;
        G.list[a].first = p;
    }//边的数据存储到邻接表
}

int Find(Graph &G, int node1, int node2)
{
    EdgeNode *p;
    p = G.list[node1].first;//获取指定起点的邻接点
    while(p)//以起点的邻接点继续
    {
        if(p->adj != node2 && Find(G, p->adj, node2))//如果这个点不是指定的终点，则继续对当前点的邻接点调用Find
            return 1;
        if(p->adj == node2)
            return 1;//如果这个点是指定的终点，则找到通路，返回1
        p = p->next;//没找到下一个邻接点
    }
    return 0;//没找到返回0
}

int main()
{
    Graph G;
    CreateGraph(G);
    printf("请问要查找哪两个点之间的通路(用空格分开)\n");
    int node1, node2;
    scanf("%d %d", &node1, &node2);
    if(Find(G, node1, node2))
        printf("存在通路\n");
    else
        printf("不存在通路\n");
    system("pause"); 
    return 0;
}

