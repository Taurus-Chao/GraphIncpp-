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
	int x;//行号
	int y;//列号
	int distance;//用于BFS找最短路径
	string path;//记录从开始点到此点行进的方向顺序
};

bool isWaydfs(int *mat, int len, Point start, Point end);//迷宫mat中是否存在从start到end的通路,DFS递归方式
bool isWaydfs_helper(int *mat, Point start, Point end, int* visited, int len);
bool isWaybfs(int *mat, int len, Point start, Point end);//迷宫mat中是否存在从start到end的通路,BFS循环方式

bool isWay2Walldfs(int *mat, int len, Point start, Point end);//迷宫mat中,只能在碰到墙壁后改变方向，是否存在从start到end的通路,DFS递归方式
bool isWay2Walldfs_helper(int *mat, Point start, Point end, int* visited, int len);

int theShortestPath(int *mat, int len, Point start, Point end);//迷宫mat中寻找从start到end的最短通路,返回距离。BFS加堆实现

string theShortest2WallPathPrint(int *mat, int len, Point start, Point end);//迷宫mat中,只能在碰到墙壁后改变方向,寻找从start到end的最短通路,并打印路径。上下左右为udlr
#endif