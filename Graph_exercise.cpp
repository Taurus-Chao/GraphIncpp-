#include"Graph_exercise.h"
#include<stack>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<deque>
#include<unordered_set>
using namespace std;
///////////////////////////////����������x��yλ����������ͬ��ֵ�û���newval
void floodFill(int *mat,int sizex,int sizey, int x, int y, int newval)
{
	int ori = *(mat + sizey*x + y);
	floodFill_helper(mat, sizex, sizey, x, y, newval, ori);
}
void floodFill_helper(int *mat, int sizex, int sizey, int x, int y, int newval, int originval)//�ݹ黹��Ҫһ����ʼ��ֵ
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

////////////////////////////����Ȧ����.������Ϊ1������ʶ��0������ʶ���ҳ�ͼ���м���Ȧ��,��ջʵ�֡�
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
			*(mat + size*tmp + tmp) = 0;//���Խ���Ԫ��Ϊ0������Ϊ�ѷ��ʹ�
			for (int j = 0; j < size; j++)
			{
				if (*(mat + size*j + j) != 1)continue;//�ж��Ƿ��ѷ��ʹ�
				if (*(mat + size*tmp + j) == 1)
					friends.push(j);
			}
		}
	}
	return count;
}

/////////////////////////////////��������1Ϊ½�أ�0Ϊ����ȷ���������Ŀ
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
void numofIslands_dfs(int *grid, int row, int col, int x, int y)//����dfs��ʽ�����нڵ����
{
	if (x < 0 || x >= row || y < 0 || y >= col || *(grid + x*col + y) != 1)return;
	*(grid + x*col + y) = 2;//��2�������Ѿ����ʹ��˽ڵ㡣
	numofIslands_dfs(grid, row, col, x+1, y);
	numofIslands_dfs(grid, row, col, x-1, y);
	numofIslands_dfs(grid, row, col, x, y+1);
	numofIslands_dfs(grid, row, col, x, y-1);
}

/////////////////////////////////��������1Ϊ½�أ�0Ϊ����ȷ�����������
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
int maxAreaofIslands_dfs(int *grid, int row, int col, int x, int y)//����dfs��ʽ�����нڵ����
{
	if (x < 0 || x >= row || y < 0 || y >= col || *(grid + x*col + y) != 1)return 0;
	*(grid + x*col + y) = 2;//��2�������Ѿ����ʹ��˽ڵ㡣
	return 1 + maxAreaofIslands_dfs(grid, row, col, x + 1, y) + maxAreaofIslands_dfs(grid, row, col, x - 1, y)
		+ maxAreaofIslands_dfs(grid, row, col, x, y + 1) + maxAreaofIslands_dfs(grid, row, col, x, y - 1);
}

////////////////////////////����id�����ض�ӦԱ�����������Ĺ��ʺ͡�
int getSalary(vector<Employee>& emps, int id)
{
	unordered_map<int, Employee>m;//����һ����ϣ���������ٲ�ѯ
	for (int i = 0; i < emps.size(); i++)
	{
		m[emps[i].getId()] = emps[i];
	}
	stack<Employee>s;//����ջ����dfs(Ҳ���õݹ飬���ǹ�ϣ���ô���)
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

////////////////////////////////����ÿ��������ھӽڵ㣬�ж�ͼ�Ƿ�Ϊ����ͼ
bool isBipartite(vector<vector<int>> &vec)
{
	vector<int>visited(vec.size(), 0);//��¼�ڵ㣬0δ���ʣ�-1������1��1������2
	for (int i = 0; i < vec.size(); i++)
	{
		if (visited[i] == 0)visited[i] = -1;//δ���ʹ��Ķ��ȱ��Ϊ��1
		if (!isBipartite_dfs(vec, i, visited))return false;
	}
	return true;
}
bool isBipartite_dfs(vector<vector<int>> &vec, int id, vector<int> &visited)//����dfs�������п���
{
	for (int i = 0; i < vec[id].size(); i++)
	{
		if (visited[vec[id][i]] == 0)//�ھ���δ���ʹ��Ľڵ㣬����ݵ�ǰ�ڵ��visitedֵȡ�����ã���dfs�ݹ��ھ�
		{
			visited[vec[id][i]] = visited[id] * (-1);
			if (!isBipartite_dfs(vec, vec[id][i], visited))return false;
		}
		else//���ھ��ѷ��ʹ�����Ҫ���Ƿ����Ҫ�󣬷�����ѭ����һ���ھ�(���ö���dfs��)�������Ϸ���false
		{
			if (visited[vec[id][i]] == visited[id])return false;
		}
	}
	return true;
}

/////////////////////////////�ҳ����ܵ�̫ƽ��Ҳ�ܵ�������ĵ�
void pacificAtlantic(int *mat, int m, int n, vector<pair<int, int>> &res)//mΪ������nΪ����
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

////////////////////////////////////////////////�ھ�����Ѱ����ĵ���·��
int longersIncreasingPath(int *mat, int m, int n)
{
	int res = 0;
	int *cache = new int[m*n];//���ö�̬�滮��˼�룬������¼�Ѿ��ҵ����Ը���Ϊ���ĵ���·������.�ÿռ任ʱ��
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

/////////////////////////////////////////////Ѱ�Ҿ�����ÿ��Ԫ�ص������0�ľ���
void updateMatrixdfs(int *mat, int m, int n, int *res)//�����res�����У�����dfs�ķ���
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
/////////////////////////////////�˻��ϲ�
void accountMerge(Account *accounts, int m, vector<Account> &res)
{
	unordered_map<string, vector<int>>accountmap;
	for (int i = 0; i < m; i++)//�Ƚ���һ��ӳ���ϵ��������ŵ�Account��Ӧ�����±�
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
	for (int i = 0; i < m; i++)//��ÿ���˻����ϲ�
	{
		if (accountset.find(i) != accountset.end())continue;//set�����Ѻϲ���
		unordered_set<string> emails;//���ڴ�Ŵ��˻���Ӧ��email�����ظ���
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
	accounts[i].getEmails(tmp);//��ȡ���˻����е�email
	for (auto email : tmp)
	{
		emails.insert(email);
		for (auto actnum : accountmap[email])//�ھӾ��Ǳ��˻�email��Ӧ�������˻���
		{
			accountMerge_dfs(accounts, accountset, accountmap, actnum, emails);
		}
	}
}

//////////////////////////////////////////�������ӣ�ÿ��ֻ�ܱ仯һ����ĸ���ܷ�ͨ�����������еĵ��ʱ仯��Ŀ�굥�ʣ���̴����Ƕ��٣�(-1��ʾ����)
int ladderLength(vector<string> &wordlist, string beginword, string endword)
{
	unordered_set<string>wordset;//�ѵ�������ת��Ϊset���ӿ��ѯ�ٶ�
	for (auto w : wordlist)
	{
		wordset.insert(w);
	}	
	wordset.insert(endword);//���յ㵥�ʷŽ����������ڡ�
	unordered_map<string, int>wordmapvisited;//������¼�ѷ��ʵĵ��ʺ;���
	deque<string>wordqueue;//����bfs������ʽ
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

void findLadders(vector<string> &wordlist, string beginword, string endword, vector<vector<string>> &res)//�ҵ���Щ��̵�ladder�����ص�res��
{
	unordered_set<string>wordset;//�ѵ�������ת��Ϊset���ӿ��ѯ�ٶ�
	for (auto w : wordlist)
	{
		wordset.insert(w);
	}
	wordset.insert(endword);//���յ㵥�ʷŽ����������ڡ�
	unordered_map<string, pair<vector<string>,int>>wordmapvisited;//������¼�ѷ��ʵĵ��ʺ;���,value��һ����Ÿ��ڵ�;����pair
	deque<string>wordqueue;//����bfs������ʽ
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

void recursionget(string startword,string word, vector<string>tmp, unordered_map<string, pair<vector<string>, int>>&wordmapvisited, vector<vector<string>> &res)//�ݹ�Ļ�ý��
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
