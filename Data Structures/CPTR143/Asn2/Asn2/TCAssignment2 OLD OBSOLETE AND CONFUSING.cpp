/*
Program file name : Assignment #8 			OS: Windows 8          		Assignment # : 8
Programmer : Travis Crumley & Brian Clark    Class : Data Structures II		Date : 2/26/2014
Compiler : Visual Studio 2013

Assistance / references : In class work posted on common drive(K : \common)
Description : A C++ Class for singly linked lists called ListSL

Inputs : Menu Selections and Data entered by user
Outputs : Data from nodes as well as commands or notifications

Special Comments :

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
#include <vector>
#include <cstdlib>

using namespace std;


//Assisting classes:
//Stack
template <class T>
class Stack
{
private:
	T *stk;
	int top, size;
public:
	Stack(void);
	Stack(int);
	bool empty();
	bool full();
	void push(T);
	void push(T*);
	T pop();
	void writeStack();

};

template <class T>
Stack<T>::Stack(void)
{
	size = 10;
	stk = new T[size];
	top = -1;
}

template <class T>
Stack<T>::Stack(int setSize)
{
	size = setSize;
	stk = new T[size];
	top = -1;
}

template <class T>
bool Stack<T>::empty() {
	if (top < 0)
		return true;
	else
		return false;
}

template <class T>
bool Stack<T>::full()
{
	if (top >= size - 1)
		return true;
	else
		return false;
}
template <class T>
void Stack<T>::push(T data)
{
	if (!full())
		stk[++top] = data;
	else
		cout << "Stack is full\n";
}

template <class T>
void Stack<T>::push(T* data)
{
	if (!full())
		stk[++top] = data;
	else
		cout << "Stack is full\n";
}

template <class T>
T Stack<T>::pop()
{
	static T nothing;
	if (empty())
	{
		cout << "Stack underflow\n";
		return nothing;
	}
	else
		return stk[top--];
}

template <class T>
void Stack<T>::writeStack()
{
	int i = top;
	if (i == -1) cout << "Stack is empty\n";
	else
	while (i >= 0) cout << stk[i--] << endl;
}

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
/*****************************************************************************/
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
		//By tradition we ignore the 0th vertex, makes you able to say 1 and 2 instead
		int vertex[3];		//1 and 2 are indices
		EdgeNode * link[3];
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
	vector<VertexInfo<T>> myEdgeLists;

	//Private Function Member
	//void DFSAux(int start, vector<bool> &unvisited); 

public:
	T data(int k) const;									/* Retrieves data from a given vertex*/
	void read(istream &in, int numVertices, int numEdges);	/*Input Graph*/
	void DFS(int start, vector<bool> &unvisited);			/*Depth First Search starting at vertex start*/
	void BFS(int start, vector<bool> &unvisited);			/*Breadth First Search*/
	bool isConnectedDFS();										/*Check if graph is connected with DFS*/
	bool isConnectedBFS();										/*Check if graph is connected with BFS*/
};

//Definition of data()
template <class T>
inline T Graph<T>::data(int k) const
{
	return myEdgeLists[k].data;
}

//Definition of read()
template <class T>
void Graph<T>::read(istream &in, int numVertices, int numEdges)
{
	Graph<T>::VertexInfo<T> vi;

	//Put a garbage 0-th value so indices start with 1
	myEdgeLists.push_back(vi);

	//Create "head nodes"
	//NEED TO REDO ALL OF THIS PROBABLY
	cout << "Enter label of vertex:\n";
	for (int i = 1; i <= numVertices; i++)
	{
		cout << " " << i << ": ";
		in >> vi.data;
		vi.first = 0;
		myEdgeLists.push_back(vi);
	}

	int endpoint; //endpoint of an edge
	//Create edge lists
	cout << "Enter endpoints of edge\n";
	for (int i = 1; i <= numEdges; i++)
	{
		cout << " " << i << ": ";
		EdgePointer newPtr = new EdgeNode<T>;
		for (int j = 1; j <= 2; j++)
		{
			in >> endpoint;
			//intert new edge node at beginning of edge list for endpoint
			newPtr->vertex[j] = endpoint;
			newPtr->link[j] = myEdgeLists[endpoint].first;
			myEdgeLists[endpoint].first = newPtr;
		}
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
		//Nothing unvisited, so nothing left
		return false;
	}
}

//Definition of DFS (Depth First Search)
template <class T>
void Graph<T>::DFS(int start, vector<bool> & unvisited)
{
	//Mark start visited and init pointer to its first edge node
	unvisited[start] = false;

	Graph<T>::EdgePointer ptr = myEdgeLists[start].first;
	while (anyLeft(unvisited) && ptr != 0)
	{
		//Determine which end of edge is the start
		int startEnd = 1, otherEnd = 2; //Assume a default
		if (ptr->vertex[1] != start)	//Actually the reverse is true
		{
			startEnd = 2; otherEnd = 1;
		}

		//Start new recursive DFS from vertex at the other end if it hasn't already been visited
		int newStart = ptr->vertex[otherEnd];
		if (unvisited[newStart])
		{
			DFS(newStart, unvisited);
			//Move to next edge node
			ptr = ptr->link[startEnd];
		}
	}
}

//Definition of BFS (Breadth First Search)
template <class T>
void Graph<T>::BFS(int start, vector<bool> & unvisited)
{
	Queue<int> vertexQueue;
	//Mark start visited and init pointer to its first edge node
	Graph<T>::EdgePointer ptr = myEdgeLists[start].first;
	//Add the start vertex to our queue
	vertexQueue.addQ(start);

	do {
		//Delete my current vertex, change it to visited
		unvisited[vertexQueue.delQ()] = false;

		//Determine which end of edge is the start
		int startEnd = 1, otherEnd = 2; //Assume a default
		if (ptr->vertex[1] != start)	//Actually the reverse is true
		{
			startEnd = 2; otherEnd = 1;
		}
		//Change our pointer to our new starting position
		int newStart = ptr->vertex[otherEnd];
		if (unvisited[newStart])
		{
			vertexQueue.addQ(newStart);
			ptr = ptr->link[startEnd];
		}
	} while (anyLeft(unvisited) && !vertexQueue.emptyQ());
}

template <class T>
inline bool Graph<T>::isConnectedDFS()
{
	vector<bool> unvisited(myEdgeLists.size(), true);
	DFS(1, unvisited);
	return !anyLeft(unvisited);
}

template <class T>
inline bool Graph<T>::isConnectedBFS()
{
	vector<bool> unvisited(myEdgeLists.size(), true);
	BFS(1, unvisited);
	return !anyLeft(unvisited);
}

int main()
{
	char stop;

	int numVertices, numEdges;

	cout << "Enter number of vertices and number of edges in graph: ";
	cin >> numVertices >> numEdges;
	Graph <char> g;
	g.read(cin, numVertices, numEdges);

	cout << "Graph is ";
	if (g.isConnectedDFS())
	{
		cout << "Connected according to DFS.\n";
	}
	else
	{
		cout << "not connected according to DFS.\n"
			"Would you like to see which vertices are not\n"
			"reachable from vertex 1 (" << g.data(1) << ") -- (Y or N)? ";
		char response;
		cin >> response;
		if (response == 'y' || response == 'Y')
		{
			cout << "They are the following: \n";
			vector<bool> unreachable(numVertices + 1, true);
			for (int i = 1; i < unreachable.size(); i++)
			{
				if (unreachable[i])
				{
					cout << "Vertex " << i << " (" << g.data(i) << ")\n";
				}
				cout << endl;
			}
		}
	}

	cout << "Graph is ";
	if (g.isConnectedBFS())
	{
		cout << "Connected according to BFS.\n";
	}
	else
	{
		cout << "not connected according to BFS.\n"
			"Would you like to see which vertices are not\n"
			"reachable from vertex 1 (" << g.data(1) << ") -- (Y or N)? ";
		char response;
		cin >> response;
		if (response == 'y' || response == 'Y')
		{
			cout << "They are the following: \n";
			vector<bool> unreachable(numVertices + 1, true);
			for (int i = 1; i < unreachable.size(); i++)
			{
				if (unreachable[i])
				{
					cout << "Vertex " << i << " (" << g.data(i) << ")\n";
				}
				cout << endl;
			}
		}
	}

	cin >> stop;

	return 0;
}
