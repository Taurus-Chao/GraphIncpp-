#include"maze.h"
#include<deque>
#include<queue>
#include<functional>
bool isWaydfs(int *mat, int len, Point start, Point end)//迷宫mat中是否存在从start到end的通路
{
	int *visited = new int[len*len];//用来记录是否访问过的矩阵，初始为0，访问置1
	memset(visited, 0, sizeof(int)*len*len);
	bool flag = isWaydfs_helper(mat, start, end, visited, len);
	delete[] visited;
	return flag;
}
bool isWaydfs_helper(int *mat, Point start, Point end, int* visited, int len)
{
	if (*(mat + len*start.getx() + start.gety()) == 1)return false;//此路不通，返回false
	if (start == end)return true;
	*(visited + len*start.getx() + start.gety()) = 1;//设置已访问
	int i = 0;
	while (i < 4)//对所有邻居进行处理
	{
		int dx;
		int dy;
		switch (i)
		{
		case 0:
			dx = 1; dy = 0; break;
		case 1:
			dx = -1; dy = 0; break;
		case 2:
			dx = 0; dy = 1; break;
		case 3:
			dx = 0; dy = -1; break;
		}
		i++;
		int x = start.getx() + dx;
		int y = start.gety() + dy;
		if (x >= 0 && x < len&&y>=0&&y<len)
		{
			if (*(visited + len*x + y) == 0)
				if (isWaydfs_helper(mat, Point(x, y), end, visited, len))
					return true;
		}
	}
	return false;//此点所有邻居都无法到达end，返回false
}

bool isWaybfs(int *mat, int len, Point start, Point end)//迷宫mat中是否存在从start到end的通路,BFS循环方式
{
	deque<Point>pd;
	int *visited = new int[len*len];//用来记录是否访问过的矩阵，初始为0，访问置1
	memset(visited, 0, sizeof(int)*len*len);
	pd.push_back(start);
	while (!pd.empty())
	{
		Point tmp = pd.front();
		pd.pop_front();
		if (tmp == end)return true;
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//此节点是堵上的点
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//设置已访问

		int i = 0;
		while (i < 4)//对所有邻居进行处理
		{
			int dx;
			int dy;
			switch (i)
			{
			case 0:
				dx = 1; dy = 0; break;
			case 1:
				dx = -1; dy = 0; break;
			case 2:
				dx = 0; dy = 1; break;
			case 3:
				dx = 0; dy = -1; break;
			}
			i++;
			int x = tmp.getx() + dx;
			int y = tmp.gety() + dy;
			if (*(visited + len*x + y) == 0)
			{
				if (x >= 0 && x < len&&y >= 0 && y<len)
				{
					if (*(visited + len*x + y) == 0)
						pd.push_back(Point(x, y));
				}
			}
		}
	}
	delete[] visited;
	return false;
}

bool isWay2Walldfs(int *mat, int len, Point start, Point end)//迷宫mat中,只能在碰到墙壁后改变方向，是否存在从start到end的通路,DFS递归方式
{
	int *visited = new int[len*len];//用来记录是否访问过的矩阵，初始为0，访问置1
	memset(visited, 0, sizeof(int)*len*len);
	bool flag = isWay2Walldfs_helper(mat, start, end, visited, len);
	delete[] visited;
	return flag;
}
bool isWay2Walldfs_helper(int *mat, Point start, Point end, int* visited, int len)
{
	if (*(mat + len*start.getx() + start.gety()) == 1)return false;//此路不通，返回false
	if (start == end)return true;
	*(visited + len*start.getx() + start.gety()) = 1;//设置已访问
	int i = 0;
	while (i < 4)//对所有邻居进行处理
	{
		int dx;
		int dy;
		switch (i)
		{
		case 0:
			dx = 1; dy = 0; break;
		case 1:
			dx = -1; dy = 0; break;
		case 2:
			dx = 0; dy = 1; break;
		case 3:
			dx = 0; dy = -1; break;
		}
		i++;
		int x = start.getx()+dx;
		int y = start.gety()+dy;
		while (*(mat + len*x + y) != 1&&x != -1 && y != -1 && x != len  && y != len )//只要没有碰到墙或走到边就一直前进
		{
			x += dx;
			y += dy;
			if (x == end.getx() && y == end.gety())return true;//中途经过目的地返回true
		}
		x -= dx;
		y -= dy;
		if (*(visited + len*x + y) == 0)
			if (isWay2Walldfs_helper(mat, Point(x, y), end, visited, len))
				return true;
	}
	return false;//此点所有邻居都无法到达end，返回false
}

int theShortestPath(int *mat, int len, Point start, Point end)//迷宫mat中是寻找从start到end的最短通路,返回距离。BFS加堆实现
{
	priority_queue<Point, deque<Point>, greater<Point>>q;
	int *visited = new int[len*len];//用来记录是否访问过的矩阵，初始为0，访问置1
	memset(visited, 0, sizeof(int)*len*len);
	start.setdis(0);
	q.push(start);
	while (!q.empty())
	{
		Point tmp = q.top();
		q.pop();
		if (tmp == end)return tmp.getdis();
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//此节点是堵上的点
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//设置已访问
		int i = 0;
		while (i < 4)
		{
			int dx, dy;
			switch (i)
			{
			case 0:
				dx = 1; dy = 0; break;
			case 1:
				dx = -1; dy = 0; break;
			case 2:
				dx = 0; dy = 1; break;
			case 3:
				dx = 0; dy = -1; break;
			}
			i++;
			int x = tmp.getx() + dx;
			int y = tmp.gety() + dy;
			if (*(visited + len*x + y) == 0)
			{
				if (x >= 0 && x < len&&y >= 0 && y < len)
				{
					Point neighbor(x, y);
					neighbor.setdis(tmp.getdis() + 1);
					q.push(neighbor);
				}
			}
	
		}
	}
	delete[]visited;
	return -1;//没找到通路
}

string theShortest2WallPathPrint(int *mat, int len, Point start, Point end)//迷宫mat中,只能在碰到墙壁后改变方向,寻找从start到end的最短通路,并打印路径。上下左右为udlr
{
	priority_queue<Point, deque<Point>, greater<Point>>q;
	int *visited = new int[len*len];//用来记录是否访问过的矩阵，初始为0，访问置1
	memset(visited, 0, sizeof(int)*len*len);
	start.setdis(0);
	q.push(start);
	while (!q.empty())
	{
		Point tmp = q.top();
		q.pop();
		if (tmp == end)return tmp.getpath();
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//设置已访问
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//此节点是堵上的点
		int i = 0;
		string dir = "";
		while (i < 4)
		{
			int dx, dy;
			switch (i)
			{
			case 0:
				dx = 1; dy = 0; dir = "d"; break;
			case 1:
				dx = -1; dy = 0; dir = "u"; break;
			case 2:
				dx = 0; dy = 1; dir = "r"; break;
			case 3:
				dx = 0; dy = -1; dir = "l"; break;
			}
			i++;
			int x = tmp.getx() + dx;
			int y = tmp.gety() + dy;
			int d = 0;
			while ((*(mat + len*x + y) != 1)&&x != -1 && x != len&&y != -1 && y != len)
			{
				x += dx; y += dy; d++;
				if (x == end.getx() && y == end.gety())
				{
					x += dx; y += dy;
					break;//中途经过目的地不能返回，要先放到堆里，其代价最小才返回
				}
			}
			x -= dx; y -= dy;
			if (*(visited + len*x + y) == 0)
			{
				Point neighbor(x, y);
				neighbor.setdis(tmp.getdis() + d);
				neighbor.setpath(tmp.getpath() + dir);
				q.push(neighbor);
			}
		}
	}
	delete[]visited;
	return "None";//没找到通路
}