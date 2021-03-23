#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <assert.h>

using namespace std;
typedef string NodeType;

//A graph where each node is a string 
class Graph{
public:
  
  Graph(){
    directed=true;
  }
  
  //Create a graph object with the given nodes
  //and initialize the adjacent lists to empty 
  Graph (NodeType nodeArray[], int len, bool d);
  
  /* load a graph from a text file which specifies a graph in the 
   * following format 
   true
   5 A B C D E 
   A -> B
   C -> D
   e -> A
  */
  void InitializeFromFile(string fileName); 
  
  //Precondition: from and to nodes are in the vector of nodes 
  void AddEdge (const NodeType & from, const NodeType & to);
  
  //return the adjacent list of node u 
  //list<NodeType> AdjacentNodes (const NodeType & u);
  
  int FindNode (const NodeType & u);
  
  void Display();
  
  //Explore and visit all vertices of the graph that are
  //reachable from node s in BFS order
  // When finish: Display
  //     * the depth of all reachable vertices (i.e., shortest distance to s)
  //     * the predecessors of all reachable vertices (BFS tree)
  void BFS_Explore (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,int> & d);
  
  bool IsPath (vector<NodeType> n, bool & isCycle);

  void ShortestHopPath (NodeType s, NodeType t, vector<NodeType> & path);

  void DFS (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,int> \
& d, int & time);

  void DFS_Visit (NodeType s, unordered_map<NodeType,NodeType> & pred, unordered_map<NodeType,int> & d, int & time);

  void DFS (bool gen_topoSort, list< NodeType > & topoOrder);
  
private:
  bool directed; //true: directed graph, false: undirected graph 
  

  vector<NodeType> nodes;
  
  //For a node u, 
  //adjacentLists[u] is the adjacent list of node u
  //
  //for undirected graph, we store each edge twice, for example,
  // if node a and b are connected by an edge, 
  //   b is in the adjacent list of a, and a is in the adjacent list of b
  unordered_map<NodeType, list<NodeType>> adjacentLists; 
  
};

