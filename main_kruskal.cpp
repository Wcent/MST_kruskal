// MST_kruskal.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ��С��������kruskal�㷨
//

#include <iostream>
#include <stdlib.h>

using namespace std;

// �߽ṹ
typedef struct
{
	int s_v; //���
	int e_v; //�յ�
	int w;   //Ȩֵ
}Edge;


int MST_kruskal(int (* graphy)[8], int vertexs, int numOfEdges); //��С������kruskal�㷨
int find(int *p, int v); // ���鼯�еĲ��Һ���
void sort(Edge *pArray, int len); //ð������

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

// ~ Minimum Spanning Tree ��С�������㷨
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

	// Ԥ�������еı������ź�
	sort(pEdges, numOfEdges);

	// ���鼯��ʼ�����������Գɼ��ϣ��Ǹ���ͬ
	int root[8];
	for(i=0; i<8; i++)
		root[i] = i;

	int count = vertexs - 2;
	int sum = 0;
	int x, y;
	for(i=0; count > 0 && i < numOfEdges; i++)
	{
		// ʣ��߼���ѡ��С�ߣ��жϱ������˵��Ƿ�����ͬһ���ϣ����ñ��Ƿ��ѷ��ʹ�
		x = find(root, pEdges[i].s_v);
		y = find(root, pEdges[i].e_v);
		if(x == y)
			continue;

		// ���ʺ󶥵�ϲ���ͬһ���ʹ��ļ�����
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

// ��·��ѹ���Ĳ���
int find(int *p, int v)
{
	if(v != p[v])
		p[v] = find(p, p[v]);
	return p[v];
}

// ~ð������
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
