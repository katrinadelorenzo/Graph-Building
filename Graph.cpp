#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <assert.h>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;
#include "Graph.h"


//Create a graph object with the given nodes
//and initialize the adjacent lists to empty 
Graph::Graph (NodeType nodeArray[], int len, bool d)
{
  for (int i=0;i<len;i++)
    {
      nodes.push_back (nodeArray[i]);
      
      //Initialize adjacent list of nodes[i] to be an empty list 
      list<NodeType> emptyList;
      adjacentLists[nodeArray[i]] = emptyList;
    }
  directed = d;
  
}

/*
  the text file specify a graph as follows:
  true
  5 A B C D E
  A -> B
  C -> D
  e -> A
*/
void Graph::InitializeFromFile(string fileName){
  ifstream input; 
  string word;
  
  cout <<"Loading graph from " << fileName<<endl;
  input.open (fileName);
  if (!input.is_open()){
    cout <<"Failed to open file " << fileName<<endl;
    exit(1);
  }
  
  
  //read a string, if it's "true" set directed to true;
  //                if it's "false", set directed to false.
  input >> word;
  if (word=="true" || word=="TRUE")
    directed = true;
  else  if (word=="False" || word=="false" || word=="FALSE")
    directed= false; 
  
  cout <<"The file is " <<word<<endl;
  
  //read an integer value (the number of vertices in the graph)
  int nodeNum;
  input >> nodeNum;
  cout <<"With "<<nodeNum<<" nodes"<<endl;
  
  /* for loop to read the given number of node
     for each node read in, store it in "nodes" vector,
     and initialize the adjacent list for the node to empty
     list
  */
  NodeType node;
  for (int i=0;i<nodeNum;i++)
    {
      input >> node;
     nodes.push_back (node);
      
      list<NodeType> emptyList;
      adjacentLists[node] = emptyList;
    }
  
  //cout <<"Read edges!\n";
  /*
    read one edge a time (by reading one node, 
    one string and another node)
    and insert the edge into the graph by calling
    AddEdge
  */
  NodeType fromNode, toNode;
  while (input >> fromNode >> word >> toNode)
    {
      /*
	cout <<"Read an edge" << fromNode << " "<<
	word<<" " <<toNode;
      */
      
      AddEdge (fromNode, toNode);
    }
  
  //close the file
  input.close();
}

//Precondition: from and to nodes are in the vector of nodes 
//
void Graph::AddEdge (const NodeType & from, const NodeType & to)
{
  int cnt=0;
  int fromIndex, toIndex;
  
  //Find from and to nodes in the nodes vector 
  for (int i=0;i<nodes.size();i++)
    {
      if (nodes[i]==from)
	{
	  cnt++;
	}
      if (nodes[i]==to)
	{
	  cnt++;
	}
      
    }
  
  //check precondition
  assert (cnt==2);
  
  adjacentLists[from].push_back(to);
  if (!directed) 
    adjacentLists[to].push_back (from);
  
}

/*
//return the adjacent list of node u 
list<NodeType> Graph::AdjacentNodes (const NodeType & u)
{
return adjacentLists[u]; 
}
*/

int Graph::FindNode (const NodeType & u)
{
  for (int i=0;i<nodes.size();i++)
    {
      if (nodes[i]==u)
	return i;
    }
  
  return -1;
}

void Graph::Display()
{
  list<NodeType>::iterator it;
  
  if (directed) 
    cout <<"Directed Graph:\n";
  else
    cout <<"Undirected Graph:\n";
  
  cout <<"Vertex: {";
  
  for (int i=0;i<nodes.size();i++)
    {
      cout <<nodes[i]<<"(out-degree="<<adjacentLists[nodes[i]].size()<<") ";
    }
  cout <<"}"<<endl;
  
  cout <<"Edges:\n{";
  for (int i=0;i<nodes.size();i++)
    {
      list<NodeType> & adjList = adjacentLists[nodes[i]];
      for (it=adjList.begin();it!=adjList.end();it++)
	if (directed) 
	  cout <<"   " <<nodes[i]<<"->"<<*it<<","<<endl;
	else
	  {
	    if (i<=FindNode((*it)))
	      cout <<"   " <<nodes[i]<<"-"<<*it<<","<<endl;
	  }
    }
  cout <<"}\n";
  
}

//Explore and visit all vertices of the graph that are
//reachable from node s in BFS order
// When finish: Display
//     * the depth of all reachable vertices (i.e., shortest distance to s)
//     * the predecessors of all reachable vertices (BFS tree)
void Graph::BFS_Explore (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,int> &d)
{
  typedef enum Color{
		     White=0, 
		     Gray=1, 
		     Black=2} Color;
  //unordered_map<NodeType,int> d; //the depth/hop count of all nodes from s
  //unordered_map<NodeType,NodeType> pred; // pred[u] is the node that leads us to u 
  unordered_map<NodeType,Color> color; //color[u] will be White, Gray, Black
  queue<NodeType> Q;
  
  // initialize all nodes to white
  for (int i=0;i<nodes.size();i++)
    {
      color[nodes[i]]=White;
      d[nodes[i]]=99999;
    }
  
  //source node init
  color[s]=Gray;
  d[s]=0;
  //insert s into Q
  Q.push(s);
  
  //While-loop...
  while (Q.size()!=0){
    //get the node in the front of queue
    NodeType u=Q.front();
    Q.pop();
    
    //For each node v in Adjacency list of u
    // if it's white, do .... 
    list<NodeType> adjNodes = adjacentLists[u];
    for (NodeType v:adjNodes){
      
      if (color[v]==White)
	{
	  color[v]=Gray;
	  d[v]=d[u]+1;
	  pred[v]=u;
	  Q.push(v);
	}
    }
    color[u]=Black;
    
  }
  
  //Display color, depth, predecessor 
  for (int i=0;i<nodes.size();i++)
    {
      cout <<"Node " << nodes[i]<< " is ";
      if (color[nodes[i]]==White)
	cout <<" white ";
      else if (color[nodes[i]]==Gray)
	cout <<" gray ";
      else if (color[nodes[i]]==Black)
	cout <<" black ";
      cout <<". depth is " << d[nodes[i]];
      cout <<". Predecessor is "<< pred[nodes[i]]<<endl;
    }

  
}
/* Check if the given sequence of nodes is a path of the graph
   @param: vector<NodeType> nodes
   @param: isCycle is set to true if the sequence of nodes is a cycle 
   @return true if n[0],n[1],...n[n.size()-1] is a path, false otherwise
*/
bool Graph::IsPath (vector<NodeType> n, bool & isCycle)
{
  for (int i = 0; i < n.size() -2; i++)
    {
      NodeType node1 = n[i];
      NodeType node2 = n[i+1];
      
      //iterator to iterate through NodeType
      vector<NodeType>:: iterator it;
      list<NodeType> adjList;

      adjList = adjacentLists[node1];

      bool found = false;

      for (NodeType v:adjList)
	{
	  if (v == node2)
	    {
	      found = true;
	      break;
	    }
	}
      //check if n[i] and n[i+1] are connected by an edge
      if (!found)
	return false;

      
      //check to see if path is a cycle as well
    }
  if( n[0]==n[n.size()-1] && n.size()>2)

    isCycle = true;
  
  else
    
    isCycle = false;
  
  return true;
}
/* find shortest hop path from node s to node t 
   Note: call BFS_Explore() and then use predecessor info to find the path 
   that leads to node t (from s)
   postcondition: 
   if there is a path from s to t, then 
   path[0]==s, path[path.size()-1]==t 
   if there is no path, then path.size()==0
*/
void Graph::ShortestHopPath (NodeType s, NodeType t, vector<NodeType> & path)
{
  unordered_map<NodeType,NodeType> pred;
  unordered_map<NodeType,int> d;
  
  BFS_Explore(s, pred, d);
  
  cout <<"Path length is " << d[t] << endl;
  
  //starting from t, go to pred[t], from pred[t] goto its pred, and so on and on              
  //until we reach s                                                                          
  NodeType curNode = t;
  NodeType prevNode;
  do{
    path.insert (path.begin(),curNode);
    
    prevNode = pred[curNode];
    curNode = prevNode;
    
    
  } while (curNode!=s);
  
  path.insert (path.begin(),s);

  if (path.size() == 0)
    cout << "No path exists" << endl;
  ShortestHopPath(s,t,path);
}

//Explore and visit all vertices of the graph 
// by calling DFS_Visit from a randomly chosen vertex,
// and then if there are vertices still not visited, call
// DFS_Visit from a randomly chosen unvisited vertex, and so on...
// When finish: Display 
//         * the predecessor of all vertices (DFS tree/forest)
//         * the discover and finish time of each vertices 
//         * whether the graph has cycle or not 
void Graph::DFS (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,\
		 int> &d, int & time)
{
  typedef enum Color{
                     White=0,
                     Gray=1,
                     Black=2} Color;
  unordered_map<NodeType,Color> color; //color[u] will be White, Gray, Black                        

  
  time = 0;
  for (int i=0;i<nodes.size();i++)
    {
      color[nodes[i]]=White;
      pred[nodes[i]] = Gray;
    }
  for (int i=0;i<nodes.size();i++)
    {
      if (color[nodes[i]] == White)
	DFS_Visit(s, pred, d, time);
    }
}

//Explore and visit all vertices of the graph that are 
//reachable from node s in DFS order 
// Whenever a back edge is found, 
//	i.e., when you explore neighbors of node u, and find a node v which 
//	has been visited already (i.e., not WHITE) and also v is an ancestor of u. 
//	(Hint: v is an ancestor of u if and only if v is parent of 
//	u, or parent of parent of u, or parent of parent of parent of u)
void Graph::DFS_Visit (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,int> &d, int & time)
{
  typedef enum Color{
                     White=0,
                     Gray=1,
                     Black=2} Color;
  //unordered_map<NodeType,int> d; //the depth/hop count of all nodes from s                        
  //unordered_map<NodeType,NodeType> pred; // pred[u] is the node that leads us to u                
  unordered_map<NodeType,Color> color; //color[u] will be White, Gray, Black
  
  // initialize all nodes to white                                                                  
  for (int i=0;i<nodes.size();i++)
    {
      color[nodes[i]]=White;
      d[nodes[i]]=99999;
    }
  
  //source node init                                                                                 
  color[s]=Gray;
  d[s]=time;
  time = time+1;
  unordered_map<NodeType,int> f;
  list<NodeType> adjNodes = adjacentLists[s];
  for (NodeType v:adjNodes){

      if (color[v]==Gray)
        {
          pred[v] = s;
	  DFS_Visit(s, pred, d, time);
        }
    }
    color[s]=Black;
    time = time+1;
    f[s] = time;
}

//^ You will need more parameters... 
// if gen_topoSort is set to true, and the graph is DAG, 
// topoOrder will be set to a topological ordering of all nodes in graph
void Graph::DFS (bool gen_topoSort, list< NodeType > & topoOrder)
{
  // vector to store departure time of vertex. 
    vector<int> departure(V, -1); 
  
    // Mark all the vertices as not visited 
    vector<bool> visited(V, false); 
    int time = -1; 
  
    // perform DFS on all unvisited vertices 
    for(int i = 0; i < V; i++) 
        if(!visited[i]) 
            DFS(i, visited, departure, time); 
      
    // Print vertices in topological order 
    for(int i = V - 1; i >= 0; i--) 
        cout << departure[i] << " "; 
}
