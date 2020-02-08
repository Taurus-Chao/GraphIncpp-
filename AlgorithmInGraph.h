#ifndef ALGORITHMINGRAPH_H
#define ALGORITHMINGRAPH_H
#include"GraphByList.h"
#include<unordered_map>
#include<unordered_set>
class MyGraph :public Graph{
public:
	void findPath_DFS_Iterative(string start, string end);//采用深度优先搜索的循环方式来寻找从start到end的路径
	void findPath_DFS_Recursive(string start, string end);//采用深度优先搜索的递归方式来寻找从start到end的路径
	void findPath_BFS(string start, string end);//采用广度优先搜索来寻找从start到end的路径.BFS无法采用递归实现
	int findNumofConnectedGraph();//找到图中连通图的个数,采用深度优先搜索
	void dijkstra(string source);//单源最短路径Dijkstra算法。更新所有节点到source节点的距离distance和对应前驱节点previous
	void printShortestPathToSource(string des);//打印出到source节点的最短路径
private:
	void findPath_DFS_Recursive_helper(Vertex* frm, Vertex* to, unordered_set<string> &visitset, unordered_map<string, string> &parentmap);
	void printShortestPathToSource_helper(Vertex* ver);//递归实现打印最短路径
};

#endif