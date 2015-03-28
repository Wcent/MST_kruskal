// MST_kruskal.cpp : 定义控制台应用程序的入口点。
//

// 最小生成树，kruskal算法
//

#include <iostream>
#include <stdlib.h>

using namespace std;

// 边结构
typedef struct
{
	int s_v; //起点
	int e_v; //终点
	int w;   //权值
}Edge;


int MST_kruskal(int (* graphy)[8], int vertexs, int numOfEdges); //最小生成树kruskal算法
int find(int *p, int v); // 并查集中的查找函数
void sort(Edge *pArray, int len); //冒泡排序

int main()
{
	int g[8][8];
	memset(g, -1, sizeof(int)*8*8);
	g[1][2] = 3;
	g[1][6] = 1;
	g[2][3] = 2;
	g[2][4] = 1;
	g[3][4] = 3;
	g[3][5] = 1;
	g[3][6] = 1;
	g[3][7] = 3;
	g[4][5] = 1;
	g[5][7] = 2;

	cout<<"The minimun spanning tree is: "<<MST_kruskal(g, 8, 10)<<endl;

	return 0;
}

// ~ Minimum Spanning Tree 最小生成树算法
int MST_kruskal(int (* graphy)[8], int vertexs, int numOfEdges)
{
	Edge *pEdges = new Edge[numOfEdges];
	int k = 0;
	for(int i=0; i<vertexs; i++)
	{
		for(int j=0; j<vertexs; j++)
		{
			if(graphy[i][j] > 0)
			{
				pEdges[k].s_v = i;
				pEdges[k].e_v = j;
				pEdges[k].w   = graphy[i][j];
				k++;
			}
		}
	}

	// 预处理：所有的边升序排好
	sort(pEdges, numOfEdges);

	// 并查集初始化，各顶点自成集合，那根不同
	int root[8];
	for(i=0; i<8; i++)
		root[i] = i;

	int count = vertexs - 2;
	int sum = 0;
	int x, y;
	for(i=0; count > 0 && i < numOfEdges; i++)
	{
		// 剩余边集中选最小边，判断边两个端点是否已在同一集合，即该边是否已访问过
		x = find(root, pEdges[i].s_v);
		y = find(root, pEdges[i].e_v);
		if(x == y)
			continue;

		// 访问后顶点合并在同一访问过的集合中
		else if(x < y)
			root[y] = x;
		else
			root[x] = y;
		sum += pEdges[i].w;
		count--;
	}
	delete [] pEdges;
	
	if(count)
		return -1;
	else
		return sum;
}

// 带路径压缩的查找
int find(int *p, int v)
{
	if(v != p[v])
		p[v] = find(p, p[v]);
	return p[v];
}

// ~冒泡排序
void sort(Edge *pArray, int len)
{
	bool flag;
	for(int i=1; i<len; i++)
	{
		flag = false;
		for(int j=0; j<len-i; j++)
		{
			if(pArray[j].w > pArray[j+1].w)
			{
				Edge temp    = pArray[j];
				pArray[j]   = pArray[j+1];
				pArray[j+1] = temp;
				flag = true;
			}
		}
		if(flag == false)
			return;
	}
}
