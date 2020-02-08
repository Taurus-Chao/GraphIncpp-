#include"GraphByList.h"
#include<iostream>
///////////////////////////////Vertex类成员函数////////////////////////////////////
void Vertex::addNeighbor(Vertex* neighbor, int weight )//添加邻居
{
	auto iter = neighborList.begin();
	for (; iter != neighborList.end();iter++)//先判断新添加的节点是否在list中
	{
		if (neighbor->name == iter->first->name)break;
	}
	if (iter == neighborList.end())
	{
		neighborList.push_back(make_pair(neighbor, weight));
	}
	else
		iter->second = weight;//若已在list中则更新权值
}

void Vertex::getConnections(vector<Vertex*> &res)//获得所有邻居，存储到传入的res中
{
	for (auto tmp : neighborList)
		res.push_back(tmp.first);
}

string  Vertex::getName()//返回name
{
	return name;
}

int  Vertex::getWeight(Vertex* neighbor)//返回某个邻居的权值
{
	auto iter = neighborList.begin();
	for (; iter != neighborList.end(); iter++)//先判断新添加的节点是否在list中
	{
		if (neighbor == iter->first)return iter->second;
	}
	return -1;//节点不在邻居中
}
void Vertex::setDistance(int dis) //设置成员distance的值
{
	distance = dis;
}
int Vertex::getDistance()//获得成员distance的值
{
	return distance;
}
void Vertex::setPrevious(Vertex* pre)//设置成员previous
{
	previous = pre;
}
Vertex* Vertex::getPrevious() //返回成员previous
{
	return previous;
}
void Vertex::setVisited()//设置visited为True
{
	visited = true;
}
bool Vertex::getVisited()//返回成员visited
{
	return visited;
}
////////////////////////////////GraphByList类成员函数//////////////////////////
bool Graph::isDirected()//返回图是否有向
{
	return directed;
}
int Graph::vertexCount()//返回节点数目
{
	return vertices.size();
}
void Graph::addVertex(string str)//添加节点
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)//先判断新添加的节点是否在list中
	{
		if ((*iter)->getName()==str)break;
	}
	if (iter == vertices.end())//节点不存在，创建节点并push到list中
	{
		Vertex* ver = new Vertex(str);
		vertices.push_back(ver);
	}
	else
		cout<<"Already exist.";//已在list
}
Vertex* Graph::getVertex(string str)//获得指定节点的指针（不安全）
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)
	{
		if ((*iter)->getName() == str)return *iter;
	}
	if (iter == vertices.end())
	{
		cout << "Do not exist.";//不在list
		return nullptr;
	}	
}
void Graph::addEdge(string frm, string to, int cost )//添加边
{
	//若不在verticies应该先创建节点
	auto iterf = vertices.begin();
	for (; iterf != vertices.end(); iterf++)
	{
		if ((*iterf)->getName() == frm)break;
	}
	if (iterf == vertices.end())
	{
		Vertex* ver = new Vertex(frm);
		vertices.push_back(ver);
		iterf = vertices.end();
		iterf--;
	}
	auto itert = vertices.begin();
	for (; itert != vertices.end(); itert++)
	{
		if ((*itert)->getName() == to)break;
	}
	if (itert == vertices.end())
	{
		Vertex* ver = new Vertex(to);
		vertices.push_back(ver);
		itert = vertices.end();
		itert--;
	}
	(*iterf)->addNeighbor(*itert, cost);
	if (!directed)
		(*itert)->addNeighbor(*iterf, cost);
}
void Graph::getVertices(vector<string>&res)//返回所有节点的name到res中，不返回指针保证图内部节点的不可见
{
	for (auto tmp : vertices)
		res.push_back(tmp->getName());
}
void Graph::getEdges(vector<pair<string, int>>&res)//获得所有边的name和权
{
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++)
	{
		string path = "";
		vector<Vertex*>tmp;
		(*iter)->getConnections(tmp);
		for (auto iterin = tmp.begin(); iterin != tmp.end(); iterin++)
		{
			path = (*iter)->getName() +"->"+ (*iterin)->getName();
			int w = (*iter)->getWeight(*iterin);
			res.push_back(make_pair(path, w));
		}
	}
}
void Graph::getneighbors(string str, vector<string>&res)//返回节点邻居的name到res中
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)
	{
		if ((*iter)->getName() == str)break;
	}
	if (iter == vertices.end())
	{
		cout << "Do not exist.";//不在list
	}
	else
	{
		vector<Vertex*>tmp;
		(*iter)->getConnections(tmp);
		for (auto itert = tmp.begin(); itert != tmp.end(); itert++)
		{
			res.push_back((*itert)->getName());
		}
	}

}

