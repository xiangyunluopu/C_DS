#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <malloc.h>

#define MAX 100
#define VertexType char

typedef struct E_node
{
	int adjvex;
	struct E_node* next;
}Edge_node;

typedef struct V_node
{
	VertexType data;
	Edge_node* firstedge;
}VexHeadNode;

typedef struct
{
	VexHeadNode adjlist[MAX];
	int n, e;
}AdjList;

int Eff_Len(Edge_node* p)
{
	int len;
	for (len = 0; p != NULL; len += 1, p = p->next);
	return len;
}

void sort_adj(AdjList* G)
{
	int i;
	for (i = 0; i < G->n; i += 1)
	{
		Edge_node* p = G->adjlist[i].firstedge;
		if (p)
		{
			int j;
			int len = Eff_Len(p);
			for (j = len; j > 1; j -= 1)
			{
				int k;
				Edge_node* pp1 = p;
				Edge_node* pp2 = pp1->next;
				char flag = 1;
				for (k = 1; k < j; k += 1, pp1 = pp2, pp2 = pp2->next)
				{
					if (pp2->adjvex > pp1->adjvex)
					{
						int tmp = pp1->adjvex;
						pp1->adjvex = pp2->adjvex;
						pp2->adjvex = tmp;
						if (flag)
							flag = 0;
					}
				}
				if (flag)
					break;
			}
		}
	}
}

void disp_adj(AdjList* G)
{
	int i = G->n;
	while (i--)
	{
		printf("%c", G->adjlist[i].data);
		Edge_node* p = G->adjlist[i].firstedge;
		while (p)
		{
			printf(" --> %d", p->adjvex);
			p = p->next;
		}
		printf(" --> NULL\n");
	}

}

char arr1[MAX];

void DFS(AdjList* G, int vi)
{
	if (arr1[vi])
	{
		printf("%c ", G->adjlist[vi].data);
		Edge_node* p = G->adjlist[vi].firstedge;
		arr1[vi] = 0;
		while (p)
		{
			DFS(G, p->adjvex);
			p = p->next;
		}
	}
}

void BFS(AdjList* G, int vi)
{
	int q[MAX];
	
	int front, rear;
	front = rear = 0;
	front = front + 1;
	q[front] = vi;

	while (front != rear)
	{
		rear = (rear + 1) % MAX;
		vi = q[rear];
		if (arr1[vi])
		{
			printf("%d ", vi);
			arr1[vi] = 0;
		}
		Edge_node* p = G->adjlist[vi].firstedge;
		while (p)
		{
			if (arr1[p->adjvex])
			{
				front = (front + 1) % MAX;
				q[front] = p->adjvex;
			}
			p = p->next;
		}
	}

}

int main(void)
{
	AdjList G;
	Edge_node* p;
	int i, v1, v2;
	printf("建立无向图邻接表\n");
	printf("请输入顶点的个数:"); scanf("%d", &G.n);
	printf("请输入边的个数:"); scanf("%d", &G.e);

	printf("请输入各个顶点的信息\n");
	for (i = 0; i < G.n; i += 1)
	{
		getchar();
		printf("第%d个顶点:", i); scanf("%c", &G.adjlist[i].data);
		G.adjlist[i].firstedge = NULL;
	}

	printf("请输入各个边的信息\n");
	for (i = 1; i <= G.e; i += 1)
	{
		printf("第%d条边(v1 v2):", i); scanf("%d %d", &v1, &v2);
		p = (Edge_node*)malloc(sizeof(Edge_node));
		p->adjvex = v2;
		p->next = G.adjlist[v1].firstedge;
		G.adjlist[v1].firstedge = p;
		
		p = (Edge_node*)malloc(sizeof(Edge_node));
		p->adjvex = v1;
		p->next = G.adjlist[v2].firstedge;
		G.adjlist[v2].firstedge = p;
	}
	sort_adj(&G);
	disp_adj(&G);
	for (i = 0; i < G.n; i += 1)
	{
		arr1[i] = 1;
	}
	DFS(&G, 0);
	for (i = 0; i < G.n; i += 1)
	{
		arr1[i] = 1;
	}
	printf("\n");
	BFS(&G, 0);
	return 0;
}

//#include <stdio.h>
//
//int main(void)
//{
//	int a = 0;
//	int* p = &a;
//
//	if (p)
//	{
//		printf("hello,world\n");
//	}
//	p = NULL;
//	if (!p)
//	{
//		printf("hello,world\n");
//	}
//
//	return 0;
//}