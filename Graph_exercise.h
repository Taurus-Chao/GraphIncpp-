#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>
using namespace std;
/////////////////////关于图论的一些练习题目

//将矩阵中于x，y位置相连且相同的值置换成newval
void floodFill(int *mat,int sizex,int sizey, int x, int y,int newval);
void floodFill_helper(int *mat, int sizex,int sizey, int x, int y, int newval, int originval);//递归还需要一个起始的值

//朋友圈问题.矩阵中为1代表认识，0代表不认识，找出图中有几个圈子
int friendCircle(int *mat, int size);

//给出矩阵，1为陆地，0为海洋，确定岛屿的数目
int numofIslands(int *grid, int row, int col);
void numofIslands_dfs(int *grid, int row, int col,int x,int y);//采用dfs方式对所有节点遍历

//给出矩阵，1为陆地，0为海洋，确定最大岛屿的面积
int maxAreaofIslands(int *grid, int row, int col);
int maxAreaofIslands_dfs(int *grid, int row, int col, int x, int y);//采用dfs方式对所有节点遍历

//给出员工类定义，和员工对象数组。根据员工号确定此员工及其下属的所有工资之和。
class Employee {
public:
	Employee(int identity , int money , vector<int>& vec)
	{
		id = identity;
		salary = money;
		subordinates.assign(vec.begin(), vec.end());
	}
	Employee(int identity=0, int money=0)//必须要有不接受任何参数的构造函数才能在后面用unordered_map
	{
		id = identity;
		salary = money;
		subordinates.clear();
	}
	int getId()
	{
		return id;
	}
	void getSub(vector<int> &res)
	{
		res.assign(subordinates.begin(), subordinates.end());
	}
	int getSalary()
	{
		return salary;
	}
private:
	int id;
	int salary;
	vector<int> subordinates;//下属员工的ID数组
};
int getSalary(vector<Employee>& emps,int id);//给定id，返回对应员工及其下属的工资和。

//给出每个顶点的邻居节点，判断图是否为二分图
bool isBipartite(vector<vector<int>> &vec);
bool isBipartite_dfs(vector<vector<int>> &vec,int id,vector<int> &visited);//采用dfs遍历所有可能

//找出既能到太平洋也能到大西洋的点
void pacificAtlantic(int *mat, int m, int n, vector<pair<int, int>> &res);
void pacificAtlantic_dfs(int *mat, int i, int j, int *visited, int m, int n);

//在矩阵中寻找最长的递增路径
int longersIncreasingPath(int *mat, int m, int n);
int longersIncreasingPath_dfs(int *mat, int m, int n, int i, int j, int *cache);

//寻找矩阵中每个元素到最近的0的距离
void updateMatrixdfs(int *mat, int m, int n, int *res);//结果在res矩阵中，采用dfs的方法

//账户合并
class Account {
public:
	Account(string str,vector<string> &v)
	{
		name = str;
		emails=v;
	}
	void getEmails(vector<string> &res)
	{
		res = emails;
	}
	string getName()
	{
		return name;
	}
private:
	string name;
	vector<string>emails;
};
void accountMerge(Account *accounts, int m, vector<Account> &res);
void accountMerge_dfs(Account *accounts, unordered_set<int> &accountset, unordered_map<string, vector<int>> &accountmap, int i, unordered_set<string> &emails);

//单词梯子，每次只能变化一个字母，能否通过单词数组中的单词变化到目标单词？最短次数是多少？(-1表示不能)
int ladderLength(vector<string> &wordlist, string beginword, string endword);
void findLadders(vector<string> &wordlist, string beginword, string endword,vector<vector<string>> &res);//找到这些最短的ladder并返回到res中
void recursionget(string startword, string word, vector<string>tmp, unordered_map<string, pair<vector<string>, int>>&wordmapvisited, vector<vector<string>> &res);//递归的获得结果

