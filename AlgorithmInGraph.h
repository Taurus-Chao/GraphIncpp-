#ifndef ALGORITHMINGRAPH_H
#define ALGORITHMINGRAPH_H
#include"GraphByList.h"
#include<unordered_map>
#include<unordered_set>
class MyGraph :public Graph{
public:
	void findPath_DFS_Iterative(string start, string end);//�����������������ѭ����ʽ��Ѱ�Ҵ�start��end��·��
	void findPath_DFS_Recursive(string start, string end);//����������������ĵݹ鷽ʽ��Ѱ�Ҵ�start��end��·��
	void findPath_BFS(string start, string end);//���ù������������Ѱ�Ҵ�start��end��·��.BFS�޷����õݹ�ʵ��
	int findNumofConnectedGraph();//�ҵ�ͼ����ͨͼ�ĸ���,���������������
	void dijkstra(string source);//��Դ���·��Dijkstra�㷨���������нڵ㵽source�ڵ�ľ���distance�Ͷ�Ӧǰ���ڵ�previous
	void printShortestPathToSource(string des);//��ӡ����source�ڵ�����·��
private:
	void findPath_DFS_Recursive_helper(Vertex* frm, Vertex* to, unordered_set<string> &visitset, unordered_map<string, string> &parentmap);
	void printShortestPathToSource_helper(Vertex* ver);//�ݹ�ʵ�ִ�ӡ���·��
};

#endif