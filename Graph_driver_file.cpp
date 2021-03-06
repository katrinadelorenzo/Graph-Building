#include <iostream>
#include <vector>
#include <list>
#include <assert.h>
#include "Graph.h"

using namespace std;

int main()
{

	//1. Read undirected graph and test BFS and DFS on it
	string graphFile("undirected_graph.txt");
	cout <<"The file name is" << graphFile<<endl;
	Graph G1;

	G1.InitializeFromFile (graphFile);
	G1.Display();

	cout <<"Enter the node to start BFS from:";
	NodeType srcNode;
	cin >> srcNode;
	unordered_map<NodeType,NodeType> pred;
	unordered_map<NodeType,int> d;
	
	if (G1.FindNode (srcNode)==-1)
		cout <<"There is no node "<<srcNode<<" in the graph\n";
	else
	  G1.BFS_Explore (srcNode, pred, d);

	cout <<"Press any key to continue:";
	char res;
	cin >> res;

	//Todo: test DFS 


	//2. Read directed graph and test BFS and DFS on it
	string graphFile2("directed_graph.txt");
	cout <<"The file name is" << graphFile2<<endl;
	Graph G2;

	G2.InitializeFromFile (graphFile2);
	G2.Display();

	//Todo: test BFS and DFS 

	//3. Read getting dressed graph and test DFS, topological sorting on it
	string graphFile3("dressing.txt");
	cout <<"The file name is" << graphFile3<<endl;
	Graph G3;

	G3.InitializeFromFile (graphFile3);
	G3.Display();

	//Todo: test DFS and topological sorting 
}
