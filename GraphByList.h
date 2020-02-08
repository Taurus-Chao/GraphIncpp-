//图的邻接表实现，实际中更常用。
#ifndef GRAPHBYLIST_H
#define GRAPHBYLIST_H
#include<list>
#include<vector>
#include<string>
using namespace std;

class Vertex{
public:
	Vertex(string str) :name(str), visited(false), previous(nullptr), distance(INT_MAX){}
	void addNeighbor(Vertex* neighbor, int weight = 0);//添加邻居
	void getConnections(vector<Vertex*> &res);//获得所有邻居(指针，是可修改的)，存储到传入的res中
	string getName();//返回name
	int getWeight(Vertex* neighbor);//返回与某个邻居的边的权值
	void setDistance(int dis); //设置成员distance的值
	int getDistance();//获得成员distance的值
	void setPrevious(Vertex* pre); //设置成员previous
	Vertex* getPrevious(); //返回成员previous
	void setVisited();//设置visited为True
	bool getVisited();//返回成员visited
private:
	string name;
	list<pair<Vertex*, int>>neighborList;//邻接节点的指针和权值
	bool visited;
	Vertex* previous;
	int distance;
};
class Graph{
public:
	Graph() :directed(false){}
	bool isDirected();//返回图是否有向
	int vertexCount();//返回节点数目
	void addVertex(string str);//添加节点
	Vertex* getVertex(string str);//获得指定节点的指针（不安全）
	void addEdge(string frm, string to,int cost = 0);//添加边
	void getVertices(vector<string>&res);//返回所有节点的name到res中，不返回指针保证图内部节点的不可见
	void getEdges(vector<pair<string, int>>&res);//获得所有边的name和权
	void getneighbors(string ver, vector<string>&res);//返回节点邻居的name到res中
private:
	bool directed;//图是否有向
	list<Vertex*>vertices;//也可采用hash表将name和Vertex* 映射，可以更快的查询
};

#endif