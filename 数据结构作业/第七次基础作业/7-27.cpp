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
//定义邻接表存储结构

int visit[MAX] = {0};//初始化所有点为未访问

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
    scanf("%d", &G.edgeenum);
    int a, b;
    EdgeNode *p;
    printf("在每一行输入每一条边的起点和终点,空格分开\n");
    for(int i = 0; i < G.edgeenum; i++)
    {
        scanf("%d %d", &a, &b);
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->adj = b;//有向弧指向的点
        p->next = G.list[a].first;
        G.list[a].first = p;
    }
}

int Find(Graph &G, int node1, int node2, int k)
{
    if(node1 == node2 &&k == 0) return 1;//当两个点重合且k=0，则找到这样的路径，返回1
    else if(k > 0)//k不为0，路径查找继续
    {
        visit[node1] = 1;//访问过的点标记为1
        EdgeNode *p;
        for(p = G.list[node1].first; p != NULL; p = p->next)//从当前点的邻接点开始继续查找
        {
            if(visit[p->adj] == 0)//如果这个点没有被访问
                if(Find(G, p->adj, node2, k-1))//继续调用查找路径的函数
                    return 1;
        }
        visit[node1] = 0;
    }
    return 0;//没找到这样的路径返回0
}

int main()
{
    Graph G;
    CreateGraph(G);
    printf("请问要查找哪两个点之间的通路以及他们的路径长度(三个数用空格分开)\n");
    int node1, node2, k;
    scanf("%d %d %d", &node1, &node2, &k);
    if(Find(G, node1, node2, k))
        printf("存在这样的路径\n");
    else
        printf("没找到这样的路径\n");
    system("pause"); 
    return 0;
}