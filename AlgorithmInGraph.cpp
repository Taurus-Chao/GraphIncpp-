#include"AlgorithmInGraph.h"
#include<stack>
#include<deque>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include<queue>

///////////////////////////////////////�����������������ѭ����ʽ��Ѱ�Ҵ�start��end��·��
void MyGraph::findPath_DFS_Iterative(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	//DFS��ջ
	stack<Vertex*>verstack;
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>ӳ��
	verstack.push(frm);
	while (!verstack.empty())
	{
		Vertex* tmp = verstack.top();
		verstack.pop();
		if (tmp->getName() == end)//�ҵ�·�������δ�ӡ����
		{
			list<string>namelist;
			namelist.push_front(end);
			while (namelist.front() != start)
			{
				namelist.push_front(parentmap[namelist.front()]);
			}
			for (auto iter = namelist.begin(); iter != --namelist.end(); iter++)
			{
				cout << *iter << "->";
			}
			cout << namelist.back();
			return;
		}
		visitset.insert(tmp->getName());
		vector<Vertex*>res;
		tmp->getConnections(res);
		for (auto t : res)
		{
			if (visitset.find(t->getName()) == visitset.end())
			{
				verstack.push(t);
				parentmap[t->getName()] = tmp->getName();
			}
		}
	}
	cout << "Do not exist!";
}

/////////////////////////////////����������������ĵݹ鷽ʽ��Ѱ�Ҵ�start��end��·��
void MyGraph::findPath_DFS_Recursive(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>ӳ��
	findPath_DFS_Recursive_helper(frm, to, visitset, parentmap);
	//��ӡ·��(�������)
	if (parentmap.find(end) != parentmap.end())
	{
		list<string>namelist;
		namelist.push_front(end);
		while (namelist.front() != start)
		{
			namelist.push_front(parentmap[namelist.front()]);
		}
		for (auto iter = namelist.begin(); iter != --namelist.end(); iter++)
		{
			cout << *iter << "->";
		}
		cout << namelist.back();
	}
	else cout << "Do not exist path!";
	return;
}

void MyGraph::findPath_DFS_Recursive_helper(Vertex* frm, Vertex* to, unordered_set<string> &visitset, unordered_map<string, string> &parentmap)
{
	if (frm == to)return;
	visitset.insert(frm->getName());
	vector<Vertex*>res;
	frm->getConnections(res);
	for (auto t : res)
	{
		if (visitset.find(t->getName()) == visitset.end())
		{
			parentmap[t->getName()] = frm->getName();
			findPath_DFS_Recursive_helper(t, to, visitset, parentmap);
		}
	}
}

///////////////////////////////////////���ù������������ѭ����ʽ��Ѱ�Ҵ�start��end��·��
void MyGraph::findPath_BFS(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	//BFS�ö���
	deque<Vertex*>verdeque;
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>ӳ��
	verdeque.push_back(frm);
	while (!verdeque.empty())
	{
		Vertex* tmp = verdeque.front();
		verdeque.pop_front();
		if (tmp->getName() == end)//�ҵ�·�������δ�ӡ����
		{
			list<string>namelist;
			namelist.push_front(end);
			while (namelist.front() != start)
			{
				namelist.push_front(parentmap[namelist.front()]);
			}
			for (auto iter = namelist.begin(); iter != --namelist.end(); iter++)
			{
				cout << *iter << "->";
			}
			cout << namelist.back();
			return;
		}
		visitset.insert(tmp->getName());
		vector<Vertex*>res;
		tmp->getConnections(res);
		for (auto t : res)
		{
			if (visitset.find(t->getName()) == visitset.end())
			{
				verdeque.push_back(t);
				parentmap[t->getName()] = tmp->getName();
			}
		}
	}
	cout << "Do not exist!";
}
/////////////////////////////�ҵ�ͼ����ͨͼ�ĸ���,���������������
int MyGraph::findNumofConnectedGraph()
{
	unordered_set<string>visitset;
	int count = 0;
	vector<string>Vertices;
	stack<string>verstack;
	getVertices(Vertices);
	for (auto iter = Vertices.begin(); iter != Vertices.end(); iter++)
	{
		if (visitset.find(*iter) != visitset.end())continue;
		count++;
		verstack.push(*iter);
		while (!verstack.empty())
		{
			string tmp = verstack.top();
			verstack.pop();
			visitset.insert(tmp);
			vector<string>res;
			getneighbors(tmp, res);
			for (auto t : res)
			{
				if (visitset.find(t) == visitset.end())//�����ٽ�㣬���û�з��ʹ�������뵽ջ��
				{
					verstack.push(t);
				}
			}
		}
	}
	return count;
}

////////////////////////////////��Դ���·��Dijkstra�㷨���������нڵ㵽source�ڵ�ľ���distance�Ͷ�Ӧǰ���ڵ�previous.

class mycompfunc
{
public:
	bool operator()(Vertex* v1, Vertex* v2)
	{
		return v1->getDistance() > v2->getDistance();
	}
};

void MyGraph::dijkstra(string source)
{
	Vertex* frm = getVertex(source);
	frm->setDistance(0);//��Դ���������Ϊ0��Ĭ����INT_MAX��ʾ���ɴ
	priority_queue<Vertex*, vector<Vertex*>, mycompfunc>q;//�����Զ���ȽϺ������ݽڵ��distance�������
	q.push(frm);
	while (!q.empty())
	{
		Vertex *tmp = q.top();
		q.pop();
		if (tmp->getVisited() == true)continue;
		tmp->setVisited();
		vector<Vertex*>res;
		tmp->getConnections(res);
		for (auto t : res)
		{
			if (t->getVisited() == false)
			{
				if (t->getDistance() > (tmp->getDistance() + tmp->getWeight(t)))//�����С�ľ��룬���¾����ǰ���ڵ�
				{
					//������Ҫ���µĽڵ�t��������ȷ�����ȶ������Ƿ��Ѿ���������ڵ㡣����У�����Ҫ����pop����������distance�����²��롣
					//��Ϊc++priority_queue���ȶ������Ԫ�ز�������ģ�������pop���������޸ġ�
					priority_queue<Vertex*, vector<Vertex*>, mycompfunc>qtmp;
					while (!q.empty())
					{
						if (q.top() == t)
						{
							q.pop();
						}
						else
						{
							qtmp.push(q.top());
							q.pop();
						}
					}
					t->setPrevious(tmp);
					t->setDistance(tmp->getDistance() + tmp->getWeight(t));
					qtmp.push(t);
					qtmp.swap(q);
				}
			}
		}
	}
}

///////////////////////////////////////////��ӡ����source�ڵ�����·��
void MyGraph::printShortestPathToSource(string des)
{
	Vertex *to = getVertex(des);
	printShortestPathToSource_helper(to);
}
void MyGraph::printShortestPathToSource_helper(Vertex* ver)//�ݹ�ʵ�ִ�ӡ���·��
{
	if (ver->getPrevious() == nullptr){ cout << ver->getName(); return; }//�ڵ��ʼ��ʱpreviousǰ���ڵ�Ϊnullptr��source��ǰ���ڵ�û�и��Ĺ�
	printShortestPathToSource_helper(ver->getPrevious());
	cout << "->" << ver->getName();
}