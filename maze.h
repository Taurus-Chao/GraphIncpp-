#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include<string>
using namespace std;
class Point{
public:
	Point(int a, int b) :x(a), y(b),distance(INT_MAX){}
	int getx(){ return x; }
	int gety(){ return y; }
	int getdis(){ return distance; }
	string getpath(){ return path; }
	void setpath(string str){ path = str; }
	void setdis(int k){ distance = k; }
	bool operator==(const Point &p){ return (x == p.x)&&(y == p.y); }
	bool operator>(const Point p)const{ return distance > p.distance; }
private:
	int x;//�к�
	int y;//�к�
	int distance;//����BFS�����·��
	string path;//��¼�ӿ�ʼ�㵽�˵��н��ķ���˳��
};

bool isWaydfs(int *mat, int len, Point start, Point end);//�Թ�mat���Ƿ���ڴ�start��end��ͨ·,DFS�ݹ鷽ʽ
bool isWaydfs_helper(int *mat, Point start, Point end, int* visited, int len);
bool isWaybfs(int *mat, int len, Point start, Point end);//�Թ�mat���Ƿ���ڴ�start��end��ͨ·,BFSѭ����ʽ

bool isWay2Walldfs(int *mat, int len, Point start, Point end);//�Թ�mat��,ֻ��������ǽ�ں�ı䷽���Ƿ���ڴ�start��end��ͨ·,DFS�ݹ鷽ʽ
bool isWay2Walldfs_helper(int *mat, Point start, Point end, int* visited, int len);

int theShortestPath(int *mat, int len, Point start, Point end);//�Թ�mat��Ѱ�Ҵ�start��end�����ͨ·,���ؾ��롣BFS�Ӷ�ʵ��

string theShortest2WallPathPrint(int *mat, int len, Point start, Point end);//�Թ�mat��,ֻ��������ǽ�ں�ı䷽��,Ѱ�Ҵ�start��end�����ͨ·,����ӡ·������������Ϊudlr
#endif