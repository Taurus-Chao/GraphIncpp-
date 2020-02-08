#include"AlgorithmInGraph.h"
#include<stack>
#include<deque>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include<queue>

///////////////////////////////////////采用深度优先搜索的循环方式来寻找从start到end的路径
void MyGraph::findPath_DFS_Iterative(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	//DFS用栈
	stack<Vertex*>verstack;
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>映射
	verstack.push(frm);
	while (!verstack.empty())
	{
		Vertex* tmp = verstack.top();
		verstack.pop();
		if (tmp->getName() == end)//找到路径，依次打印出来
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

/////////////////////////////////采用深度优先搜索的递归方式来寻找从start到end的路径
void MyGraph::findPath_DFS_Recursive(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>映射
	findPath_DFS_Recursive_helper(frm, to, visitset, parentmap);
	//打印路径(如果存在)
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

///////////////////////////////////////采用广度优先搜索的循环方式来寻找从start到end的路径
void MyGraph::findPath_BFS(string start, string end)
{
	Vertex* frm = getVertex(start);
	Vertex* to = getVertex(end);
	//BFS用队列
	deque<Vertex*>verdeque;
	unordered_set<string>visitset;
	unordered_map < string, string > parentmap;//map<curr,parent>映射
	verdeque.push_back(frm);
	while (!verdeque.empty())
	{
		Vertex* tmp = verdeque.front();
		verdeque.pop_front();
		if (tmp->getName() == end)//找到路径，依次打印出来
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
/////////////////////////////找到图中连通图的个数,采用深度优先搜索
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
				if (visitset.find(t) == visitset.end())//对于临界点，如果没有访问过，则加入到栈中
				{
					verstack.push(t);
				}
			}
		}
	}
	return count;
}

////////////////////////////////单源最短路径Dijkstra算法。更新所有节点到source节点的距离distance和对应前驱节点previous.

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
	frm->setDistance(0);//将源点距离设置为0，默认是INT_MAX表示不可达。
	priority_queue<Vertex*, vector<Vertex*>, mycompfunc>q;//采用自定义比较函数根据节点的distance来构造堆
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
				if (t->getDistance() > (tmp->getDistance() + tmp->getWeight(t)))//满足更小的距离，更新距离和前驱节点
				{
					//对于需要更新的节点t，必须先确定优先队列中是否已经有了这个节点。如果有，则需要将它pop出来，计算distance后重新插入。
					//因为c++priority_queue优先队列里的元素不允许更改，必须先pop出来才能修改。
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

///////////////////////////////////////////打印出到source节点的最短路径
void MyGraph::printShortestPathToSource(string des)
{
	Vertex *to = getVertex(des);
	printShortestPathToSource_helper(to);
}
void MyGraph::printShortestPathToSource_helper(Vertex* ver)//递归实现打印最短路径
{
	if (ver->getPrevious() == nullptr){ cout << ver->getName(); return; }//节点初始化时previous前驱节点为nullptr。source的前驱节点没有更改过
	printShortestPathToSource_helper(ver->getPrevious());
	cout << "->" << ver->getName();
}