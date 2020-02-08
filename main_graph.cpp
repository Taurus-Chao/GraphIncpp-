#include"AlgorithmInGraph.h"
#include<iostream>

using namespace std;

int main()
{
	vector < pair<string, int>>res;
	vector<string>resv;
	MyGraph g;
	g.addVertex("beijing");
	g.addVertex("shanghai");
	g.addVertex("shenzhen");
	g.addVertex("guangzhou");
	g.addVertex("nanjing");
	g.addVertex("hangzhou");
	g.addEdge("shanghai", "beijing", 1);
	g.addEdge("beijing", "guangzhou", 10);
	//g.addEdge("shanghai", "beijing", 201);
	//g.addEdge("shanghai", "hangzhou", 25);
	//g.addEdge("shanghai", "shenzhen", 23);
	g.addEdge("shanghai", "nanjing", 1);
	//g.addEdge("shanghai", "guangzhou", 120);
	//g.addEdge("beijing", "nanjing", 110);
	//g.addEdge("beijing", "shenzhen", 102);
	g.addEdge("beijing", "hangzhou", 1);
	g.addEdge("hangzhou", "nanjing", 2);
	g.addEdge("nanjing", "shenzhen", 10);
	g.addEdge("guangzhou", "shenzhen", 10);
	g.addEdge("beijing", "Washington", 999);
	g.addEdge("NewYork", "Washington",42);
	g.addEdge("SanFrancisco", "NewYork", 132);

	g.addEdge("Chicago", "NewJersey");

	g.getneighbors("nanjing",resv);
	g.getEdges(res);
	//for (auto it : res)cout << it.first<<'\t'<<it.second<<endl;

	//for (auto it : resv)cout << it << endl;

	//g.findPath_DFS_Iterative("beijing", "shanghai");

	//cout << g.findNumofConnectedGraph();

	g.dijkstra("beijing");
	g.printShortestPathToSource("shenzhen");
	
	system("pause");
}

