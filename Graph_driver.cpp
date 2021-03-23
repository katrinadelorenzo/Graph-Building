#include <iostream>
#include <vector>
#include <list>
#include <assert.h>
#include "Graph.h"

using namespace std;

int main()
{

	cout <<"Now let's build a graph!\n";
	
	cout <<"Enter the number of nodes in the graph:";
	int N;
	do{ 
		cin >> N;
	} while (N<=0);

	//Read in nodes 
	string * nodes = new string[N];
        for (int i=0;i<N;i++)
	{
		cout <<"Enter "<<i<<"-th node (a string): ";
		cin >> nodes[i];
	}	

	//Directed or not 
	cout <<"Is it directed or not (Y/N)";
	char answer;
	do {
	   cin >> answer;
	} while (answer!='Y' && answer!='N');

	Graph graph(nodes,N,answer=='Y');
					//if answer=='Y' directed 

	//read in edges 
	cout <<"Enter the number of edges: ";
	int M;
	do {
		cin >> M;
	} while (M<0);

	string fromNode, toNode;
	for (int i=0;i<M;i++)
	{
		cout <<"Enter the "<<i<<"-th edge: from which node:";
		cin >> fromNode;
		cout <<"to which node:";
		cin >> toNode;

		graph.AddEdge (fromNode, toNode);
	}

	graph.Display();

	cout <<"Performing BFS from "<<nodes[0]<<endl;
	graph.BFS_Explore (nodes[0]);
	

	cout <<"Enter a graph from a text!\n";
	cout <<"The file name:";
	string fileName;
	cin >>fileName;
	cout <<"The file name is" << fileName;
	Graph graphEx;

	graphEx.InitializeFromFile (fileName);
	graphEx.Display();

}
