/*
Program file name : Travis.Crumley.cpp		OS: Windows 8          		Assignment # : 2
Programmer : Travis Crumley				    Class : CPTR 143			Date : 4/10/2014
Compiler : Visual Studio 2013

Assistance / references : 
Lectures posted on common drive(K : \common)
Chapter 16 of Data Structures Textbook
PDFs in Reading folder of K drive

Description : A C++ Class for creating graphs and using depth first and breadth first 
searches to see if they are connected at all. Also gives the ability to look at data
of said graph if desired.

Inputs : Menu Selections and Graph Data entered by user
Outputs : Data from Graphs as well as notifications of connectedness and extra information

Special Comments : I started out using the class from the book and since I didn't understand
it fully I instead morphed it into using a matrix like we did in class and used the lecture
notes for that. I used vectors in this example because they're awesome but I could do the 
same thing with normal arrays if needed quite easily.

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~
Assignment Requirements ___ / 3.0
Code Format / Cosmetics ___ / 3.0
Header & Code Comments : ___ / 2.0
Output Format / Cosmetics ___ / 2.0

***Does Not Compile*** : ___(-10.0)
***Late Work Deduction*** : ___(-0.5 / day)
Total Grade : ___ / 10.0

*****************************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//Assisting classes:
//Queue:
template<class T>
class Queue
{
private:
	T* Q;
	int size;
	int front;
	int rear;
public:
	Queue(int = 10);
	bool emptyQ();
	bool fullQ();
	void addQ(T);
	void addQ(T*);
	T delQ();
	int lengthQ();
	void writeQ();
	void clrQ();
};

template<class T>
Queue<T>::Queue(int setSize)
{
	size = setSize;
	Q = new T[size];
	front = rear = 0;
}

template<class T>
bool Queue<T>::emptyQ()
{
	return front == rear;
}

template<class T>
bool Queue<T>::fullQ()
{
	return front == (rear + 1) % size;
}

template<class T>
void Queue<T>::addQ(T data)
{
	if (fullQ())
		cout << " Queue is full. \n";
	else
	{
		rear = (rear + 1) % size;
		Q[rear] = data;
	}
}

template<class T>
void Queue<T>::addQ(T* data)
{
	if (fullQ())
		cout << " Queue is full. \n";
	else
	{
		rear = (rear + 1) % size;
		Q[rear] = data;
	}
}

template<class T>
T Queue<T>::delQ()
{
	if (emptyQ())
	{
		cout << "Queue is empty.\n";
		return Q[0];
	}
	front = (front + 1) % size; // eqv. front++; front %= size;
	return Q[front];
}

template<class T>
int Queue<T>::lengthQ()
{
	return (rear - front + size) % size;
}

template<class T>
void Queue<T>::writeQ()
{

	cout << "Queue:  ";
	for (int i = 0; i < size; i++)
	{
		//The following is logic for determining if the data in the element
		//is still relevant to us (aka in our queue)
		if ((i > front && i <= rear) || (i < front && i <= rear && rear < front) || (i > front && front > rear))
		{
			cout << Q[i] << " ";
		}
		else
			cout << "@ ";
	}

	cout << endl;

}

template<class T>
void Queue<T>::clrQ()
{
	front = rear = 0;
}
/*****************************************************************************/
/********************************NEW CODE BELOW ******************************/
/*****************************************************************************/

//Creating Graphs Class
template <class T>
class Graph
{
private:
	//Creating Classes within Graphs
	//Nested Classes like this allow them to share stuff like the typedef of EdgePointer
	//Need to create an edge node class to handle our edges
	template <class T>
	class EdgeNode
	{
	public:
		//0 is garbage for both of these for nice looping variable usage
		int vertex[3];		// 1 and 2 are vertices linked by this edge
		EdgeNode * link[3]; // 1 and 2 are links to other edges
	};

	typedef EdgeNode<T> * EdgePointer;

	//Need to create a vertex class as well
	template <class T>
	class VertexInfo
	{
	public:
		T data; //Data in vertex
		EdgePointer first; //pointer to first edge node
	};

	//Needed data members
	vector< vector<bool> > adjacencyMatrix;
	vector<VertexInfo<T>> dataList;

	int numVertices, numEdges;

public:
	T data(int k) const;									/* Retrieves data from a given vertex*/
	void build(istream &in);	/*Input Graph*/
	void DFS(int start, vector<bool> &unvisited);			/*Depth First Search starting at vertex start*/
	void BFS(int start, vector<bool> &unvisited);			/*Breadth First Search*/
	bool isConnectedDFS();										/*Check if graph is connected with DFS*/
	bool isConnectedBFS();										/*Check if graph is connected with BFS*/
};

//Definition of data()
template <class T>
inline T Graph<T>::data(int k) const
{
	return dataList[k].data;
}

//Definition of read()
template <class T>
void Graph<T>::build(istream &in)
{
	cout << "Enter number of vertices and number of edges in graph: ";
	cin >> numVertices >> numEdges;
	
	Graph<T>::VertexInfo<T> vi;

	//Put a garbage 0-th value so indices start with 1
	dataList.push_back(vi);

	//Create vertex labels
	cout << "Enter label of vertex:\n";
	for (int i = 1; i <= numVertices; i++)
	{
		cout << " " << i << ": ";
		in >> vi.data;
		vi.first = 0;
		dataList.push_back(vi);
	}
	//Allocate our adjacency matrix
	//Have to add one so it can start at 1 instead of 0
	adjacencyMatrix.resize(numVertices + 1);
	for (int i = 1; i <= numVertices; i++)
	{
		//Grow columns by numVertices for each row
		adjacencyMatrix[i].resize(numVertices + 1);
	}

	int startpoint; //startpoint of an edge
	int endpoint;   //endpoint of an edge
	//Create edge lists
	cout << "Enter endpoints of edge\n";
	for (int i = 1; i <= numEdges; i++)
	{
		cout << " " << i << ": ";
		in >> startpoint;
		in >> endpoint;
		adjacencyMatrix[startpoint][endpoint] = true;
		adjacencyMatrix[endpoint][startpoint] = true;
	}
}

//Check if any nodes are left unvisisted
bool anyLeft(const vector<bool> & unvisited)
{
	for (int i = 1; i < unvisited.size(); i++)
	{
		if (unvisited[i])
		{
			//Found an unvisited node
			return true;
		}
	}
	//Nothing unvisited, so nothing left
	return false;
}

//Definition of DFS (Depth First Search)
template <class T>
void Graph<T>::DFS(int start, vector<bool> & unvisited)
{
	//Mark start visited
	unvisited[start] = false;

	for (int i = 1; i <= numVertices; i++)
	{
		if (adjacencyMatrix[start][i] == true && unvisited[i])
		{
			DFS(i, unvisited);
		}
	}
}

//Definition of BFS (Breadth First Search)
template <class T>
void Graph<T>::BFS(int start, vector<bool> & unvisited)
{
	Queue<int> vertexQueue;
	//Add the start vertex to our queue
	vertexQueue.addQ(start);
	int curVertex;
	//cout << "Got to BFS outer loop" << endl;
	do {
		//Delete my current vertex, change it to visited
		curVertex = vertexQueue.delQ();
		unvisited[curVertex] = false;

		//cout << "Got to BFS inner loop" << endl;
		//Check our adjacencyMatrix and run over all the vertices on a level
		for (int i = 1; i <= numVertices; i++)
		{
			if (adjacencyMatrix[curVertex][i] == true)
			{
				if (unvisited[i])
				{
					vertexQueue.addQ(i);
					unvisited[i] = false;
				}
			}
		}
		//cout << "Got past BFS inner loop" << endl;
	} while (anyLeft(unvisited) && !vertexQueue.emptyQ());
	//cout << "Got past BFS outer loop" << endl;
}

template <class T>
inline bool Graph<T>::isConnectedDFS()
{
	//This should be pretty self-explanatory. Just call the DFS
	//and then check to see if anything wasn't visited
	//more menu stuff branches off from there, does essentially
	//the same thing again but outputs the unreachable data
	vector<bool> unvisited(numVertices + 1, true);
	DFS(1, unvisited);

	cout << "Graph is ";
	if (!anyLeft(unvisited))
	{
		cout << "Connected according to DFS.\n";
	}
	else
	{
		cout << "not connected according to DFS.\n"
			"Would you like to see which vertices are not\n"
			"reachable from vertex 1 (" << data(1) << ") -- (Y or N)? ";
		char response;
		cin >> response;
		if (response == 'y' || response == 'Y')
		{
			cout << "They are the following: \n";
			vector<bool> unreachable(numVertices + 1, true);
			DFS(1, unreachable);
			for (int i = 1; i < unreachable.size(); i++)
			{
				if (unreachable[i])
				{
					cout << "Vertex " << i << " (" << data(i) << ")\n";
				}
				cout << endl;
			}
		}
	}
	return !anyLeft(unvisited);
}

template <class T>
inline bool Graph<T>::isConnectedBFS()
{
	//This should be pretty self-explanatory. Just call the BFS
	//and then check to see if anything wasn't visited
	//more menu stuff branches off from there, does essentially
	//the same thing again but outputs the unreachable data
	vector<bool> unvisited(numVertices + 1, true);
	BFS(1, unvisited);

	cout << "Graph is ";
	if (!anyLeft(unvisited))
	{
		cout << "Connected according to BFS.\n";
	}
	else
	{
		cout << "not connected according to BFS.\n"
			"Would you like to see which vertices are not\n"
			"reachable from vertex 1 (" << data(1) << ") -- (Y or N)? ";
		char response;
		cin >> response;
		if (response == 'y' || response == 'Y')
		{
			cout << "They are the following: \n";
			vector<bool> unreachable(numVertices + 1, true);
			BFS(1, unreachable);
			for (int i = 1; i < unreachable.size(); i++)
			{
				if (unreachable[i])
				{
					cout << "Vertex " << i << " (" << data(i) << ")\n";
				}
				cout << endl;
			}
		}
	}
	return !anyLeft(unvisited);
}

int main()
{
	char stop; //<-- Because VS auto closes console, should look into fixing that

	//Create an instance of our class and then play with it
	Graph <char> g;
	g.build(cin);
	g.isConnectedDFS();
	g.isConnectedBFS();
	
	cin >> stop; //See above note

	return 0;
}
