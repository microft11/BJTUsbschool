#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct EdgeNode
{
    int adj;
    struct EdgeNode* next;
}EdgeNode;

typedef struct Node
{
    int data;
    EdgeNode* first;
}Node, List[MAXSIZE];

typedef struct
{
    List list;
    int nodenum, edgenum;
}Graph;
//定义邻接表存储结构

typedef struct {
    EdgeNode data[MAXSIZE];
    int front,rear;
} SqQueue;

void InitQueue(SqQueue& Q)
{
    Q.front = Q.rear = 0;
}

bool QueueEmpty(SqQueue Q){
    if( Q.front == Q.rear){
        return true;
    }
    return false;
}

bool EnQueue(SqQueue& Q, EdgeNode e){
    if( (Q.rear + 1) % MAXSIZE == Q.front ){
        return false;
    }
    Q.data[Q.rear] = e;
    Q.rear = ( Q.rear + 1) % MAXSIZE;//队尾指针加1取模，这步操作很容易写错
    return true;    
}


EdgeNode DeQueue(SqQueue& Q)
{
    EdgeNode e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;//队头指针加1取模
    return e;
}



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
	bool visited[MAXSIZE];
	
    EdgeNode *p;
    p = G.list[node1].first;//获取指定起点的邻接点
    EdgeNode* e, k;
    
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, *p);
    
    while(QueueEmpty(Q))
    {
        e = DeQueue(Q);
		visited[e -> adj] = true;
		p = G.list[e -> adj].first;
		for(; p != NULL; p -> p -> next)
		{
			k = p;
			if(k -> adj == node2)
			    return 1;
			else if(!visited[k -> adj])
			    Enqueue(Q, k);		
		}		
	}
	return 0;
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
