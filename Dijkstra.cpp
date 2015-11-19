#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;
const int MAX_VERTEX_NUM = 101;
const int MAX = 1000;


class MGraph
{	
public: 
	int vexs[MAX_VERTEX_NUM];
	int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	MGraph(int vexnum,double edgenum):m_vexnum(vexnum),m_edgenum(edgenum){};
	int getVexnum(){return m_vexnum;}
	double getEdgenum(){return m_edgenum;}
private:
	int m_vexnum;
	double m_edgenum;
};

void CreateDN_AM(MGraph *G,int n,double e) //初始化一个稀疏矩阵           
{
    int i,j;
    for(i=0;i<n;i++)
        G->vexs[i]=i;
	srand( (unsigned)time( NULL ) );            
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            G->edges[i][j]=rand()%1000;
	for(i=0;i<e/2;i++)//假设有一半未连接
	{
		int x=rand()%n;
		int y=rand()%n;
		G->edges[x][y]=MAX;
	}
	for(i=0;i<n;i++)
		G->edges[i][i]=0;
	for(i = 0;i < n;i++)
		for(j = i;j >= 0;j--)
			G->edges[i][j] = G->edges[j][i];
}

void FindMIN_way(MGraph *G,int **_minpath)
{	
	for(int i = 0;i < G->getVexnum();i++)
	{
		for(int j = 0;j < G->getVexnum();j++)
		{
			for(int k = 0;k < G->getVexnum();k++)
			{
				if(G->edges[i][k] + G->edges[k][j] < G->edges[i][j])
				{
					G->edges[i][j] = G->edges[i][k] + G->edges[k][j];
					_minpath[i][j] = k;
				}
			}
		}
	}
	/*for(int i = 0;i < G->getVexnum();i++)//_minpath[j][i]=k;_minpath[i][j]=-1
	{
		for(int j = 0;j < G->getVexnum();j++)
		{
			if(_minpath[i][j] = -1)
				_minpath[i][j] = _minpath[j][i];
			if(_minpath[j][i] = -1)
				_minpath[j][i] = _minpath[i][j];
		}
	}*/
	int FirstPoint,LastPoint;
	cout << "请输入查询的次数 :";
	int count;
	cin >> count;
	
	for(int i = 0;i < count;i++)
	{
		cout << "请输入要查询的两点(0-" << G->getVexnum()-1 << "):" ;
		cin >> FirstPoint;
		cin >> LastPoint;
		cout << "最短路径为：";
		cout << G->edges[FirstPoint][LastPoint] <<endl;
		cout << LastPoint;
		while( _minpath[FirstPoint][LastPoint] != -1)
		{
			cout << " <- " << _minpath[FirstPoint][LastPoint];
			LastPoint = _minpath[FirstPoint][LastPoint];
		}
		cout << " <- " << FirstPoint << endl;
	}
}

int main(void)
{
	int n = MAX_VERTEX_NUM-1;
	double e = n*n;
	MGraph *p = NULL;
	p = new MGraph(n,e);
	CreateDN_AM(p,n,e);
	int **_minpath = new int *[n]; 
	for(int i = 0;i < n;i++) 
		_minpath[i] = new int[n]; 
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			_minpath[i][j]=-1;
	FindMIN_way(p,_minpath);
	p = NULL;
	delete p;
	for(int i=0;i<n;i++) 
		delete[] _minpath[i]; 
	delete[] _minpath;
	system("pause");
	return 0;
}
