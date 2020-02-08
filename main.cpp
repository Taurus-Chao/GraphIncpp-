#include"Graph_exercise.h"
#include<iostream>
#include<unordered_map>
using namespace std;

int main()
{
	//int image[3][3] = { 1,1,1,
	//					1,1,0,
	//					1,0,1 };
	//floodFill((int *)image, 3, 3, 1, 1, 2);
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//		cout << image[i][j];
	//	cout << endl;
	//}

	//int f[4][4] = { 1,0,0,1,
	//			    0,1,0,0,
	//			    0,0,1,1,
	//				1,0,1,1};
	//cout <<friendCircle((int *)f, 4);

	//int graph[4][4] = { 1,1,0,1,
	//					1,1,0,0,
	//					1,1,1,1,
	//					1,0,0,0};
	//cout << numofIslands((int *)graph, 4, 4);

	//int graph[4][4] = { 1,1,0,0,
	//					0,0,0,0,
	//					1,0,1,1,
	//					1,0,0,0};
	//cout << maxAreaofIslands((int *)graph, 4, 4);

	//vector<int>v1 = { 2,3 };
	//Employee e1(1,10,v1);
	//Employee e2(2, 3);
	//Employee e3(3, 3);
	//vector<Employee>emps = { e1,e2,e3 };
	//cout << getSalary(emps, 1);

	//vector<vector<int>>v1 = { {1,2,3},{0,2},{1,3},{0,2} };
	//cout << isBipartite(v1);

	//int mat[5][5] =
	//{ 1,2,2,3,4
	//,3,2,3,4,4
	//,2,4,5,3,1
	//,6,7,1,4,5
	//,5,1,1,2,1 };
	//vector<pair<int, int>>res;
	//pacificAtlantic((int *)mat, 5, 5, res);
	//for (auto it : res)cout << it.first << ',' << it.second << endl;

	/*int nums[3][3] =
	{ 9,9,4
	,6,6,8
	,2,1,1 };
	cout << longersIncreasingPath((int *)nums, 3, 3);*/

	//int mat[3][3] =
	//{
	//	0,0,0,
	//	0,1,0,
	//	1,1,1
	//};
	//int res[3][3];
	//updateMatrixdfs((int *)mat, 3, 3, (int *)res);
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//		cout << res[i][j] << '\t';
	//	cout << endl;
	//}


	/*vector<string> v0 = { "johnsmith@mail.com","john00@mail.com" };
	vector<string> v1 = { "johnnybravo@mail.com" };
	vector<string> v2 = { "johnsmith@mail.com","john_newyork@mail.com" };
	vector<string> v3 = { "mary@mail.com" };
	Account a0("John", v0);
	Account a1("John", v1);
	Account a2("John", v2);
	Account a3("Mary", v3);
	Account accounts[4] = { a0,a1,a2,a3 };
	vector<Account> res;
	accountMerge(accounts, 4, res);
	vector<string>tmp;
	for (auto it : res)
	{
		it.getEmails(tmp);
		cout << it.getName() << ":";
		for (auto t : tmp)
			cout << t << "    ";
		cout << endl;
	}*/

	vector<string> wordlist = { "hot","dot","dog","lot","log","cog" };
	string beginword = "hit";
	string endword = "cog";
	vector<vector<string>>res;
	findLadders(wordlist,beginword,endword,res);
	for (auto t1 : res)
	{
		for (auto t2 : t1)
			cout << t2 << ",";
		cout << endl;
	}
}