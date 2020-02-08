#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>
using namespace std;
/////////////////////����ͼ�۵�һЩ��ϰ��Ŀ

//����������x��yλ����������ͬ��ֵ�û���newval
void floodFill(int *mat,int sizex,int sizey, int x, int y,int newval);
void floodFill_helper(int *mat, int sizex,int sizey, int x, int y, int newval, int originval);//�ݹ黹��Ҫһ����ʼ��ֵ

//����Ȧ����.������Ϊ1������ʶ��0������ʶ���ҳ�ͼ���м���Ȧ��
int friendCircle(int *mat, int size);

//��������1Ϊ½�أ�0Ϊ����ȷ���������Ŀ
int numofIslands(int *grid, int row, int col);
void numofIslands_dfs(int *grid, int row, int col,int x,int y);//����dfs��ʽ�����нڵ����

//��������1Ϊ½�أ�0Ϊ����ȷ�����������
int maxAreaofIslands(int *grid, int row, int col);
int maxAreaofIslands_dfs(int *grid, int row, int col, int x, int y);//����dfs��ʽ�����нڵ����

//����Ա���ඨ�壬��Ա���������顣����Ա����ȷ����Ա���������������й���֮�͡�
class Employee {
public:
	Employee(int identity , int money , vector<int>& vec)
	{
		id = identity;
		salary = money;
		subordinates.assign(vec.begin(), vec.end());
	}
	Employee(int identity=0, int money=0)//����Ҫ�в������κβ����Ĺ��캯�������ں�����unordered_map
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
	vector<int> subordinates;//����Ա����ID����
};
int getSalary(vector<Employee>& emps,int id);//����id�����ض�ӦԱ�����������Ĺ��ʺ͡�

//����ÿ��������ھӽڵ㣬�ж�ͼ�Ƿ�Ϊ����ͼ
bool isBipartite(vector<vector<int>> &vec);
bool isBipartite_dfs(vector<vector<int>> &vec,int id,vector<int> &visited);//����dfs�������п���

//�ҳ����ܵ�̫ƽ��Ҳ�ܵ�������ĵ�
void pacificAtlantic(int *mat, int m, int n, vector<pair<int, int>> &res);
void pacificAtlantic_dfs(int *mat, int i, int j, int *visited, int m, int n);

//�ھ�����Ѱ����ĵ���·��
int longersIncreasingPath(int *mat, int m, int n);
int longersIncreasingPath_dfs(int *mat, int m, int n, int i, int j, int *cache);

//Ѱ�Ҿ�����ÿ��Ԫ�ص������0�ľ���
void updateMatrixdfs(int *mat, int m, int n, int *res);//�����res�����У�����dfs�ķ���

//�˻��ϲ�
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

//�������ӣ�ÿ��ֻ�ܱ仯һ����ĸ���ܷ�ͨ�����������еĵ��ʱ仯��Ŀ�굥�ʣ���̴����Ƕ��٣�(-1��ʾ����)
int ladderLength(vector<string> &wordlist, string beginword, string endword);
void findLadders(vector<string> &wordlist, string beginword, string endword,vector<vector<string>> &res);//�ҵ���Щ��̵�ladder�����ص�res��
void recursionget(string startword, string word, vector<string>tmp, unordered_map<string, pair<vector<string>, int>>&wordmapvisited, vector<vector<string>> &res);//�ݹ�Ļ�ý��

