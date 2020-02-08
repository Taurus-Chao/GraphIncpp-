#include"GraphByList.h"
#include<iostream>
///////////////////////////////Vertex���Ա����////////////////////////////////////
void Vertex::addNeighbor(Vertex* neighbor, int weight )//����ھ�
{
	auto iter = neighborList.begin();
	for (; iter != neighborList.end();iter++)//���ж�����ӵĽڵ��Ƿ���list��
	{
		if (neighbor->name == iter->first->name)break;
	}
	if (iter == neighborList.end())
	{
		neighborList.push_back(make_pair(neighbor, weight));
	}
	else
		iter->second = weight;//������list�������Ȩֵ
}

void Vertex::getConnections(vector<Vertex*> &res)//��������ھӣ��洢�������res��
{
	for (auto tmp : neighborList)
		res.push_back(tmp.first);
}

string  Vertex::getName()//����name
{
	return name;
}

int  Vertex::getWeight(Vertex* neighbor)//����ĳ���ھӵ�Ȩֵ
{
	auto iter = neighborList.begin();
	for (; iter != neighborList.end(); iter++)//���ж�����ӵĽڵ��Ƿ���list��
	{
		if (neighbor == iter->first)return iter->second;
	}
	return -1;//�ڵ㲻���ھ���
}
void Vertex::setDistance(int dis) //���ó�Աdistance��ֵ
{
	distance = dis;
}
int Vertex::getDistance()//��ó�Աdistance��ֵ
{
	return distance;
}
void Vertex::setPrevious(Vertex* pre)//���ó�Աprevious
{
	previous = pre;
}
Vertex* Vertex::getPrevious() //���س�Աprevious
{
	return previous;
}
void Vertex::setVisited()//����visitedΪTrue
{
	visited = true;
}
bool Vertex::getVisited()//���س�Աvisited
{
	return visited;
}
////////////////////////////////GraphByList���Ա����//////////////////////////
bool Graph::isDirected()//����ͼ�Ƿ�����
{
	return directed;
}
int Graph::vertexCount()//���ؽڵ���Ŀ
{
	return vertices.size();
}
void Graph::addVertex(string str)//��ӽڵ�
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)//���ж�����ӵĽڵ��Ƿ���list��
	{
		if ((*iter)->getName()==str)break;
	}
	if (iter == vertices.end())//�ڵ㲻���ڣ������ڵ㲢push��list��
	{
		Vertex* ver = new Vertex(str);
		vertices.push_back(ver);
	}
	else
		cout<<"Already exist.";//����list
}
Vertex* Graph::getVertex(string str)//���ָ���ڵ��ָ�루����ȫ��
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)
	{
		if ((*iter)->getName() == str)return *iter;
	}
	if (iter == vertices.end())
	{
		cout << "Do not exist.";//����list
		return nullptr;
	}	
}
void Graph::addEdge(string frm, string to, int cost )//��ӱ�
{
	//������verticiesӦ���ȴ����ڵ�
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
void Graph::getVertices(vector<string>&res)//�������нڵ��name��res�У�������ָ�뱣֤ͼ�ڲ��ڵ�Ĳ��ɼ�
{
	for (auto tmp : vertices)
		res.push_back(tmp->getName());
}
void Graph::getEdges(vector<pair<string, int>>&res)//������бߵ�name��Ȩ
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
void Graph::getneighbors(string str, vector<string>&res)//���ؽڵ��ھӵ�name��res��
{
	auto iter = vertices.begin();
	for (; iter != vertices.end(); iter++)
	{
		if ((*iter)->getName() == str)break;
	}
	if (iter == vertices.end())
	{
		cout << "Do not exist.";//����list
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

