#include"Graph_exercise.h"
#include<stack>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<deque>
#include<unordered_set>
using namespace std;
///////////////////////////////将矩阵中于x，y位置相连且相同的值置换成newval
void floodFill(int *mat,int sizex,int sizey, int x, int y, int newval)
{
	int ori = *(mat + sizey*x + y);
	floodFill_helper(mat, sizex, sizey, x, y, newval, ori);
}
void floodFill_helper(int *mat, int sizex, int sizey, int x, int y, int newval, int originval)//递归还需要一个起始的值
{
	if (x >= sizex || y >= sizey || *(mat + sizey*x + y) != originval)return;
	*(mat + sizey*x + y) = newval;
	int dx = 0, dy = 0,n=4;
	while (n)
	{
		switch (n)
		{
		case 4:
			dx = 1; dy = 0; break;
		case 3:
			dx = -1; dy = 0; break;
		case 2:
			dx = 0; dy = -1; break;
		case 1:
			dx = 0; dy = 1; break;
		}
		n--;
		floodFill_helper(mat, sizex, sizey, x + dx, y + dy, newval, originval);
	}
}

////////////////////////////朋友圈问题.矩阵中为1代表认识，0代表不认识，找出图中有几个圈子,用栈实现。
int friendCircle(int *mat, int size)
{
	int count=0;
	for (int i = 0; i < size; i++)
	{
		if (*(mat + size*i + i) != 1)continue;
		count++;
		stack<int> friends;
		friends.push(i);
		while (!friends.empty())
		{
			int tmp = friends.top();
			friends.pop();
			*(mat + size*tmp + tmp) = 0;//将对角线元素为0的项视为已访问过
			for (int j = 0; j < size; j++)
			{
				if (*(mat + size*j + j) != 1)continue;//判断是否已访问过
				if (*(mat + size*tmp + j) == 1)
					friends.push(j);
			}
		}
	}
	return count;
}

/////////////////////////////////给出矩阵，1为陆地，0为海洋，确定岛屿的数目
int numofIslands(int *grid, int row, int col)
{
	int count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (*(grid + i*col + j) != 1)continue;
			numofIslands_dfs(grid, row,col,i,j);
			count++;
		}
	}
	return count;
}
void numofIslands_dfs(int *grid, int row, int col, int x, int y)//采用dfs方式对所有节点遍历
{
	if (x < 0 || x >= row || y < 0 || y >= col || *(grid + x*col + y) != 1)return;
	*(grid + x*col + y) = 2;//用2来代表已经访问过此节点。
	numofIslands_dfs(grid, row, col, x+1, y);
	numofIslands_dfs(grid, row, col, x-1, y);
	numofIslands_dfs(grid, row, col, x, y+1);
	numofIslands_dfs(grid, row, col, x, y-1);
}

/////////////////////////////////给出矩阵，1为陆地，0为海洋，确定最大岛屿的面积
int maxAreaofIslands(int *grid, int row, int col)
{
	int maxarea = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (*(grid + i*col + j) != 1)continue;
			maxarea=max(maxarea,maxAreaofIslands_dfs(grid, row, col, i, j));
		}
	}
	return maxarea;
}
int maxAreaofIslands_dfs(int *grid, int row, int col, int x, int y)//采用dfs方式对所有节点遍历
{
	if (x < 0 || x >= row || y < 0 || y >= col || *(grid + x*col + y) != 1)return 0;
	*(grid + x*col + y) = 2;//用2来代表已经访问过此节点。
	return 1 + maxAreaofIslands_dfs(grid, row, col, x + 1, y) + maxAreaofIslands_dfs(grid, row, col, x - 1, y)
		+ maxAreaofIslands_dfs(grid, row, col, x, y + 1) + maxAreaofIslands_dfs(grid, row, col, x, y - 1);
}

////////////////////////////给定id，返回对应员工及其下属的工资和。
int getSalary(vector<Employee>& emps, int id)
{
	unordered_map<int, Employee>m;//建立一个哈希表，帮助快速查询
	for (int i = 0; i < emps.size(); i++)
	{
		m[emps[i].getId()] = emps[i];
	}
	stack<Employee>s;//采用栈进行dfs(也可用递归，但是哈希表不好传入)
	s.push(m[id]);
	int sum = 0;
	while (!s.empty())
	{
		Employee tmp = s.top();
		s.pop();
		sum += tmp.getSalary();
		vector<int> res;
		tmp.getSub(res);
		if (res.empty())continue;
		for (auto it : res)
			s.push(m[it]);
	}
	return sum;
}

////////////////////////////////给出每个顶点的邻居节点，判断图是否为二分图
bool isBipartite(vector<vector<int>> &vec)
{
	vector<int>visited(vec.size(), 0);//记录节点，0未访问，-1属于组1，1属于组2
	for (int i = 0; i < vec.size(); i++)
	{
		if (visited[i] == 0)visited[i] = -1;//未访问过的都先标记为组1
		if (!isBipartite_dfs(vec, i, visited))return false;
	}
	return true;
}
bool isBipartite_dfs(vector<vector<int>> &vec, int id, vector<int> &visited)//采用dfs遍历所有可能
{
	for (int i = 0; i < vec[id].size(); i++)
	{
		if (visited[vec[id][i]] == 0)//邻居是未访问过的节点，则根据当前节点的visited值取反设置，并dfs递归邻居
		{
			visited[vec[id][i]] = visited[id] * (-1);
			if (!isBipartite_dfs(vec, vec[id][i], visited))return false;
		}
		else//若邻居已访问过，则要看是否符合要求，符合则循环下一个邻居(不用对他dfs！)，不符合返回false
		{
			if (visited[vec[id][i]] == visited[id])return false;
		}
	}
	return true;
}

/////////////////////////////找出既能到太平洋也能到大西洋的点
void pacificAtlantic(int *mat, int m, int n, vector<pair<int, int>> &res)//m为行数，n为列数
{
	int *pvisited = new int[m*n];
	int *avisited = new int[m*n];
	memset(pvisited, 0, sizeof(int) * m*n);
	memset(avisited, 0, sizeof(int) * m*n);
	for (int i = 0; i < m ; i++)
	{
		pacificAtlantic_dfs(mat, i, 0, pvisited, m, n);
		pacificAtlantic_dfs(mat, i, n-1, avisited, m, n);
	}
	for (int j = 0; j < n; j++)
	{
		pacificAtlantic_dfs(mat, 0, j, pvisited, m, n);
		pacificAtlantic_dfs(mat, m - 1,j, avisited, m, n);
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (*(pvisited + i*n + j) == 1 && *(avisited + i*n + j) == 1)
				res.push_back(make_pair(i, j));
		}
	}
	delete[] pvisited;
	delete[] avisited;
}
void pacificAtlantic_dfs(int *mat, int i, int j, int *visited, int m, int n)
{
	*(visited + i*n + j) = 1;
	int dx = 0, dy = 0, c = 4,x,y;
	while (c)
	{
		switch (c)
		{
		case 4:
			dx = 1; dy = 0; break;
		case 3:
			dx = -1; dy = 0; break;
		case 2:
			dx = 0; dy = -1; break;
		case 1:
			dx = 0; dy = 1; break;
		}
		c--;
		x = i + dx;
		y = j + dy;
		if (x >= 0 && x < m&&y >= 0 && y<n &&*(visited + x*n + y) != 1 && *(mat + x*n + y) >=*(mat + i*n + j))
			pacificAtlantic_dfs(mat, x, y, visited, m, n);
	}
}

////////////////////////////////////////////////在矩阵中寻找最长的递增路径
int longersIncreasingPath(int *mat, int m, int n)
{
	int res = 0;
	int *cache = new int[m*n];//采用动态规划的思想，用来记录已经找到的以各点为起点的递增路径长度.用空间换时间
	memset(cache, 0, sizeof(int)*m*n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res=max(res,longersIncreasingPath_dfs(mat,m,n,i,j,cache));
		}
	}
	delete[] cache;
	return res;
}
int longersIncreasingPath_dfs(int *mat, int m, int n, int i, int j, int *cache)
{
	if (*(cache + i*n + j) != 0)return *(cache + i*n + j);
	int x, y, dx, dy, c = 4;
	int tmp = 1;
	while (c)
	{
		switch (c)
		{
		case 4:
			dx = 1; dy = 0; break;
		case 3:
			dx = -1; dy = 0; break;
		case 2:
			dx = 0; dy = -1; break;
		case 1:
			dx = 0; dy = 1; break;
		}
		c--;
		x =i+ dx; y =i+ dy;
		if(x>=0&&x<m&&y>=0&&y<n&&*(mat + x*n + y)>*(mat + i*n + j))
			tmp = max(tmp,1+ longersIncreasingPath_dfs(mat, m, n, x, y, cache));
	}
	*(cache + i*n + j) = tmp;
	return tmp;
}

/////////////////////////////////////////////寻找矩阵中每个元素到最近的0的距离
void updateMatrixdfs(int *mat, int m, int n, int *res)//结果在res矩阵中，采用dfs的方法
{
	memset(res, 0, sizeof(int)*m*n);
	deque<pair<int, int>>d;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (*(mat + i*n + j) != 0)
			{
				*(res + i*n + j) = INT_MAX;
			}
			else
			{
				d.push_back(make_pair(i,j));
			}
		}
	}
	while (!d.empty())
	{
		pair<int, int>tmp = d.front();
		d.pop_front();
		int x, y, dx, dy, c = 4,z= *(res + tmp.first*n + tmp.second);
		while (c)
		{
			switch (c)
			{
			case 4:
				dx = 1; dy = 0; break;
			case 3:
				dx = -1; dy = 0; break;
			case 2:
				dx = 0; dy = -1; break;
			case 1:
				dx = 0; dy = 1; break;
			}
			c--;
			x = tmp.first + dx; y = tmp.second + dy;
			if (x >= 0 && x < m&&y >= 0 && y<n&&*(res + x*n + y)>(z+1))
			{
				*(res + x*n + y) = z + 1;
				d.push_back(make_pair(x, y));
			}
		}
	}
}
/////////////////////////////////账户合并
void accountMerge(Account *accounts, int m, vector<Account> &res)
{
	unordered_map<string, vector<int>>accountmap;
	for (int i = 0; i < m; i++)//先建立一个映射关系，从邮箱号到Account对应数组下表
	{
		vector<string> tmp;
		accounts[i].getEmails(tmp);
		for (auto it : tmp)
		{
			if (accountmap.find(it) == accountmap.end())
			{
				vector<int>st;
				accountmap.insert(make_pair(it, st));
				accountmap[it].push_back(i);
			}
			else
			{
				accountmap[it].push_back(i);
			}
		}
	}
	//for (auto it : accountmap)
	//{
	//	cout << it.first << ':';
	//	for (auto t : it.second)
	//		cout <<','<< t;
	//	cout << endl;
	//}
	unordered_set<int>accountset;
	for (int i = 0; i < m; i++)//对每个账户做合并
	{
		if (accountset.find(i) != accountset.end())continue;//set中是已合并的
		unordered_set<string> emails;//用于存放此账户对应的email，不重复。
		accountMerge_dfs(accounts,accountset, accountmap,i,emails);
		vector<string>resemails;
		for (auto e : emails)
		{
			resemails.push_back(e);
		}
		Account atmp(accounts[i].getName(), resemails);
		res.push_back(atmp);
	}
}
void accountMerge_dfs(Account *accounts, unordered_set<int> &accountset, unordered_map<string, vector<int>> &accountmap, int i, unordered_set<string>  &emails)
{
	if (accountset.find(i) != accountset.end())return;
	accountset.insert(i);
	vector<string>tmp;
	accounts[i].getEmails(tmp);//获取本账户所有的email
	for (auto email : tmp)
	{
		emails.insert(email);
		for (auto actnum : accountmap[email])//邻居就是本账户email对应的所有账户。
		{
			accountMerge_dfs(accounts, accountset, accountmap, actnum, emails);
		}
	}
}

//////////////////////////////////////////单词梯子，每次只能变化一个字母，能否通过单词数组中的单词变化到目标单词？最短次数是多少？(-1表示不能)
int ladderLength(vector<string> &wordlist, string beginword, string endword)
{
	unordered_set<string>wordset;//把单词数组转换为set，加快查询速度
	for (auto w : wordlist)
	{
		wordset.insert(w);
	}	
	wordset.insert(endword);//把终点单词放进搜索区域内。
	unordered_map<string, int>wordmapvisited;//用来记录已访问的单词和距离
	deque<string>wordqueue;//采用bfs搜索方式
	wordqueue.push_back(beginword);
	wordmapvisited[beginword] = 0;
	while (!wordqueue.empty())
	{
		string tmp = wordqueue.front();
		if (tmp == endword)return wordmapvisited[tmp];
		wordqueue.pop_front();
		for (int i = 0; i < tmp.length(); i++)
		{	
			for (int j = 0; j < 26; j++)
			{
				string word = tmp;
				char x = 'a' + j;
				word[i] = x;
				if (wordset.find(word) != wordset.end())
				{
					if (wordmapvisited.find(word) == wordmapvisited.end())
					{
						wordmapvisited[word] = wordmapvisited[tmp] + 1;
						wordqueue.push_back(word);
					}
				}
			}
		}
	}
	return -1;
}

void findLadders(vector<string> &wordlist, string beginword, string endword, vector<vector<string>> &res)//找到这些最短的ladder并返回到res中
{
	unordered_set<string>wordset;//把单词数组转换为set，加快查询速度
	for (auto w : wordlist)
	{
		wordset.insert(w);
	}
	wordset.insert(endword);//把终点单词放进搜索区域内。
	unordered_map<string, pair<vector<string>,int>>wordmapvisited;//用来记录已访问的单词和距离,value是一个存放父节点和距离的pair
	deque<string>wordqueue;//采用bfs搜索方式
	wordqueue.push_back(beginword);
	vector<string> v;
	wordmapvisited[beginword] = make_pair(v, 0);
	while (!wordqueue.empty())
	{
		string tmp = wordqueue.front();
		if (tmp == endword)
		{
			vector<string>v;
			recursionget(beginword,endword,v,wordmapvisited,res);
			return;
		}
		wordqueue.pop_front();
		for (int i = 0; i < tmp.length(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				string word = tmp;
				char x = 'a' + j;
				word[i] = x;
				if (wordset.find(word) != wordset.end())
				{
					if (wordmapvisited.find(word) == wordmapvisited.end())
					{
						vector<string> v;
						v.push_back(tmp);
						wordmapvisited[word] = make_pair(v, wordmapvisited[tmp].second + 1);
						wordqueue.push_back(word);
					}
					else
					{
						if ((wordmapvisited[word].second) == (wordmapvisited[tmp].second + 1))
							wordmapvisited[word].first.push_back(tmp);
					}
				}
			}
		}
	}
	cout << "No ladders!";
}

void recursionget(string startword,string word, vector<string>tmp, unordered_map<string, pair<vector<string>, int>>&wordmapvisited, vector<vector<string>> &res)//递归的获得结果
{
	tmp.push_back(word);
	if (word == startword)
	{
		vector<string>ws;
		ws.assign(tmp.rbegin(), tmp.rend());
		res.push_back(ws);
		return;
	}
	vector<string>wordlist = wordmapvisited[word].first;
	for (int i = 0; i < wordlist.size(); i++)
	{
		recursionget(startword, wordlist[i], tmp, wordmapvisited, res);
	}
}
