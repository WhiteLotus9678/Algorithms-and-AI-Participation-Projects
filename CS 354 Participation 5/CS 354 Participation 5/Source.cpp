#include<iostream>
#include<list>
#include<string>

using namespace std;

string node[] = { "u", "v", "x", "y", "w", "z" };

class Graph
{
	int V;    // # of nodes
	list<int> *adj;    // Pointer to an adjacency lists for edges
	void DFSVisit(int v, bool visited[]);  // A function used by DFS
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void DFS();    // DFS traversal of the vertices reachable from v
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSVisit(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << node[v] << " ";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSVisit(*i, visited);
}

// DFS traversal of the vertices reachable from v. 
// It uses recursive DFSUtil()
void Graph::DFS()
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print DFS traversal
	for (int i = 0; i < V; i++) {
		if (!visited[i]) {
			DFSVisit(i, visited);
		}
	}

}

int main()
{
	// Create a graph given in the above diagram
	//string node[] = { "u", "v", "x", "y", "w", "z" };
	//                   0    1    2    3    4    5
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(2, 1);
	g.addEdge(1, 3);
	g.addEdge(3, 2);
	g.addEdge(4, 3);
	g.addEdge(4, 5);
	g.addEdge(5, 5);

	cout << "Depth First Traversal (starting from node U) \n";
	g.DFS();
	cout << endl;

	system("pause");

	return 0;
}