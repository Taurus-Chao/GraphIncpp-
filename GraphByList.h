//ͼ���ڽӱ�ʵ�֣�ʵ���и����á�
#ifndef GRAPHBYLIST_H
#define GRAPHBYLIST_H
#include<list>
#include<vector>
#include<string>
using namespace std;

class Vertex{
public:
	Vertex(string str) :name(str), visited(false), previous(nullptr), distance(INT_MAX){}
	void addNeighbor(Vertex* neighbor, int weight = 0);//����ھ�
	void getConnections(vector<Vertex*> &res);//��������ھ�(ָ�룬�ǿ��޸ĵ�)���洢�������res��
	string getName();//����name
	int getWeight(Vertex* neighbor);//������ĳ���ھӵıߵ�Ȩֵ
	void setDistance(int dis); //���ó�Աdistance��ֵ
	int getDistance();//��ó�Աdistance��ֵ
	void setPrevious(Vertex* pre); //���ó�Աprevious
	Vertex* getPrevious(); //���س�Աprevious
	void setVisited();//����visitedΪTrue
	bool getVisited();//���س�Աvisited
private:
	string name;
	list<pair<Vertex*, int>>neighborList;//�ڽӽڵ��ָ���Ȩֵ
	bool visited;
	Vertex* previous;
	int distance;
};
class Graph{
public:
	Graph() :directed(false){}
	bool isDirected();//����ͼ�Ƿ�����
	int vertexCount();//���ؽڵ���Ŀ
	void addVertex(string str);//��ӽڵ�
	Vertex* getVertex(string str);//���ָ���ڵ��ָ�루����ȫ��
	void addEdge(string frm, string to,int cost = 0);//��ӱ�
	void getVertices(vector<string>&res);//�������нڵ��name��res�У�������ָ�뱣֤ͼ�ڲ��ڵ�Ĳ��ɼ�
	void getEdges(vector<pair<string, int>>&res);//������бߵ�name��Ȩ
	void getneighbors(string ver, vector<string>&res);//���ؽڵ��ھӵ�name��res��
private:
	bool directed;//ͼ�Ƿ�����
	list<Vertex*>vertices;//Ҳ�ɲ���hash��name��Vertex* ӳ�䣬���Ը���Ĳ�ѯ
};

#endif