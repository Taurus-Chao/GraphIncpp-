#include"maze.h"
#include<deque>
#include<queue>
#include<functional>
bool isWaydfs(int *mat, int len, Point start, Point end)//�Թ�mat���Ƿ���ڴ�start��end��ͨ·
{
	int *visited = new int[len*len];//������¼�Ƿ���ʹ��ľ��󣬳�ʼΪ0��������1
	memset(visited, 0, sizeof(int)*len*len);
	bool flag = isWaydfs_helper(mat, start, end, visited, len);
	delete[] visited;
	return flag;
}
bool isWaydfs_helper(int *mat, Point start, Point end, int* visited, int len)
{
	if (*(mat + len*start.getx() + start.gety()) == 1)return false;//��·��ͨ������false
	if (start == end)return true;
	*(visited + len*start.getx() + start.gety()) = 1;//�����ѷ���
	int i = 0;
	while (i < 4)//�������ھӽ��д���
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
	return false;//�˵������ھӶ��޷�����end������false
}

bool isWaybfs(int *mat, int len, Point start, Point end)//�Թ�mat���Ƿ���ڴ�start��end��ͨ·,BFSѭ����ʽ
{
	deque<Point>pd;
	int *visited = new int[len*len];//������¼�Ƿ���ʹ��ľ��󣬳�ʼΪ0��������1
	memset(visited, 0, sizeof(int)*len*len);
	pd.push_back(start);
	while (!pd.empty())
	{
		Point tmp = pd.front();
		pd.pop_front();
		if (tmp == end)return true;
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//�˽ڵ��Ƕ��ϵĵ�
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//�����ѷ���

		int i = 0;
		while (i < 4)//�������ھӽ��д���
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

bool isWay2Walldfs(int *mat, int len, Point start, Point end)//�Թ�mat��,ֻ��������ǽ�ں�ı䷽���Ƿ���ڴ�start��end��ͨ·,DFS�ݹ鷽ʽ
{
	int *visited = new int[len*len];//������¼�Ƿ���ʹ��ľ��󣬳�ʼΪ0��������1
	memset(visited, 0, sizeof(int)*len*len);
	bool flag = isWay2Walldfs_helper(mat, start, end, visited, len);
	delete[] visited;
	return flag;
}
bool isWay2Walldfs_helper(int *mat, Point start, Point end, int* visited, int len)
{
	if (*(mat + len*start.getx() + start.gety()) == 1)return false;//��·��ͨ������false
	if (start == end)return true;
	*(visited + len*start.getx() + start.gety()) = 1;//�����ѷ���
	int i = 0;
	while (i < 4)//�������ھӽ��д���
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
		while (*(mat + len*x + y) != 1&&x != -1 && y != -1 && x != len  && y != len )//ֻҪû������ǽ���ߵ��߾�һֱǰ��
		{
			x += dx;
			y += dy;
			if (x == end.getx() && y == end.gety())return true;//��;����Ŀ�ĵط���true
		}
		x -= dx;
		y -= dy;
		if (*(visited + len*x + y) == 0)
			if (isWay2Walldfs_helper(mat, Point(x, y), end, visited, len))
				return true;
	}
	return false;//�˵������ھӶ��޷�����end������false
}

int theShortestPath(int *mat, int len, Point start, Point end)//�Թ�mat����Ѱ�Ҵ�start��end�����ͨ·,���ؾ��롣BFS�Ӷ�ʵ��
{
	priority_queue<Point, deque<Point>, greater<Point>>q;
	int *visited = new int[len*len];//������¼�Ƿ���ʹ��ľ��󣬳�ʼΪ0��������1
	memset(visited, 0, sizeof(int)*len*len);
	start.setdis(0);
	q.push(start);
	while (!q.empty())
	{
		Point tmp = q.top();
		q.pop();
		if (tmp == end)return tmp.getdis();
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//�˽ڵ��Ƕ��ϵĵ�
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//�����ѷ���
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
	return -1;//û�ҵ�ͨ·
}

string theShortest2WallPathPrint(int *mat, int len, Point start, Point end)//�Թ�mat��,ֻ��������ǽ�ں�ı䷽��,Ѱ�Ҵ�start��end�����ͨ·,����ӡ·������������Ϊudlr
{
	priority_queue<Point, deque<Point>, greater<Point>>q;
	int *visited = new int[len*len];//������¼�Ƿ���ʹ��ľ��󣬳�ʼΪ0��������1
	memset(visited, 0, sizeof(int)*len*len);
	start.setdis(0);
	q.push(start);
	while (!q.empty())
	{
		Point tmp = q.top();
		q.pop();
		if (tmp == end)return tmp.getpath();
		*(visited + len*tmp.getx() + tmp.gety()) = 1;//�����ѷ���
		if (*(mat + len*tmp.getx() + tmp.gety()) == 1)continue;//�˽ڵ��Ƕ��ϵĵ�
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
					break;//��;����Ŀ�ĵز��ܷ��أ�Ҫ�ȷŵ�����������С�ŷ���
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
	return "None";//û�ҵ�ͨ·
}