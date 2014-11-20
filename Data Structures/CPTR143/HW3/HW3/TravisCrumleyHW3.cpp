/*
Program file name : Travis.Crumley.cpp		OS: Windows 8          		Assignment # : 3
Programmer : Travis Crumley				    Class : CPTR 143			Date : 4/20/2014
Compiler : Visual Studio 2013

Assistance / references :
Lectures posted on common drive(K : \common)
Chapter 16 of Data Structures Textbook
PDFs in Reading folder of K drive

Description : A C++ Program that creates a random Adjacency and Cost Matrix for a Directed Network
and then analyzes the path of vertex one with Dijkstra's Algorithm, and all of the vertexes
with the AllPairs function.

Inputs : Directed Network Parameters from user 
Outputs : Data from Directed Network as well as output from Dijkstra and AllPairs

Special Comments : Using vectors because they're amazing and using <algorithm> 
for the min function and srand with current time for pseudo-random generation.

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
#include <ctime>
#include <algorithm>

using namespace std;

int random(int n) {
	return rand() % n;
}

void Dijkstra(int v, vector<vector<int>> Cost, int n) {
	cout << "Dijkstra:" << endl;
	//Intitialize stuff I'll only need for this function
	vector<int> D;
	vector<bool> found;
	int w = 0;
	int u = 0;

	//Resize vectors so they can start at 1
	D.resize(n + 1);
	found.resize(n + 1);

	//Initialize vectors
	for (int i = 1; i <= n; i++)
	{
		found[i] = false;  //D[i] holds the shortest parth from v to 
		D[i] = Cost[v][i]; //All other vertices, i, based on Cost
	}

	found[v] = true; //found = true implies that the shortest path
	D[v] = 0;        //from v to all other vertices has been found
	//Find n-1 shortest paths from v to all other vertices
	int runMin;
	for (int times = 1; times < n - 1; times++)
	{
		//Find vertex u such that D[u] is the minimum for that path
		runMin = INT_MAX/2;
		for (int w = 1; w <= n; w++)
		{
			if (!found[w])
			{
				//If D[w] is lower, set it as the new runMin
				//Then set our minimum vertex to this vertex
				if (D[w] < runMin) 
				{
					runMin = D[w];
					u = w;
				}
			}
		}
		D[u] = runMin;

		found[u] = true; //Add u to solution set
		for (int w = 1; w <= n; w++)
		{
			if (!found[w])
			{
				//Set our D[w] to whatever the cost is for going
				//One extra step, doesn't go more than 2 steps in a path
				D[w] = min(D[w], D[u] + Cost[u][w]);
			}
		}
	}
	//Output
	for (int w = 1; w <= n; w++)
	{
		if (D[w] == INT_MAX / 2)
		{
			cout << "INF ";
		}
		else
		{
			cout << D[w];
			if (D[w] < 10)
			{
				cout << "   ";
			}
			else if (D[w] < 100)
			{
				cout << "  ";
			}
			else
			{
				cout << " ";
			}
		}
	}
	cout << endl;
}

//allPairs algorithm to create 
void allPairs(vector<vector<int>> Cost, vector<vector<int>> T, int n)
{
	cout << "All Pairs:" << endl;
	for (int k = 1; k <= n ; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				T[i][j] = min(T[i][j], T[i][k] + T[k][j]);
			}

		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (T[i][j] == INT_MAX / 2)
			{
				cout << "INF ";
			}
			else
			{
				cout << T[i][j];
				if (T[i][j] < 10)
				{
					cout << "   ";
				}
				else if (T[i][j] < 100)
				{
					cout << "  ";
				}
				else
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void createMatrices(int n, float m, int wMax, int wMin)
{
	srand(time(0)*time(0));
	//srand(777); For testing purposes
	cout << "Number of Vertices is: " << n << endl;
	cout << "Number of Edges is: " << m << endl;
	cout << "Max weight is: " << wMax << endl;
	cout << "Min weight is: " << wMin << endl;

	//Initialize Adjacency Matrix
	vector< vector<int> > A;
	A.resize(n + 1); //Resize so it starts at 1
	for (int i = 1; i < n + 1; i++)
	{
		//Grow columns by numVertices for each row
		A[i].resize(n + 1);
	}
	//Initialize cost matrix
	vector< vector<int> > C;
	C.resize(n + 1); //Resize so it starts at 1
	for (int i = 1; i < n + 1; i++)
	{
		//Grow columns by numVertices for each row
		C[i].resize(n + 1);
	}
	//Create initial cost matrix (infinity (aka INT_MAX) in every value)
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			C[i][j] = INT_MAX/2;
		}
	}

	//Create the matrices
	int i, j = 0;
	for (int k = 1; k <= m; k++)
	{
		//While we have edges left to place, find a random path and place an edge there
		do
		{
			i = 1 + random(n);
			j = 1 + random(n);
		} while ((A[i][j] == 1) || (i == j)); //Added i = j to take out loops
		A[i][j] = 1;							  //There is a path here
		C[i][j] = wMin + random(wMax - wMin + 1); //Create cost for this path
	}

	//Output the matrices
	cout << endl;
	cout << "Adjacency Matrix: " << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << A[i][j] << "   ";
		}
		cout << endl;
	}
	
	cout << endl;
	cout << "Cost Matrix: " << endl;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (C[i][j] == INT_MAX/2)
			{
				cout << "INF ";
			}
			else
			{
				//All of the if statements are for formatting purposes
				cout << C[i][j];
				if (C[i][j] < 10)
				{
					cout << "   ";
				}
				else if (C[i][j] < 100)
				{
					cout << "  ";
				}
				else
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	//Show outputs for the shortest path algorithms
	cout << endl;
	Dijkstra(1, C, n);
	cout << endl;
	allPairs(C, C, n);
}

//Not actually used because of u assignment, wasn't worth it
//Ended up just placing it directly into the algorithm
int MinPath(vector<int> D, vector<int> found, int n, int u){
	int runMin = INT_MAX/2;
	for (int w = 1; w <= n; w++)
	{
		if (!found[w])
		{
			if (D[w] < runMin)
			{
				runMin = D[w];
				u = w;
			}
		}
	}
	
	return runMin;
}



int main()
{
	char stop; //<-- Because VS auto closes console

	//Declare a bunch of variables we can input from user to generate network
	int nTemp = 0;
	float mTemp = 0.0f;
	int wMaxTemp = 0;
	int wMinTemp = 0;
	cout << "Please enter the number of vertices: ";
	cin >> nTemp; //Number of vertices

	cout << endl << "Please enter the number of edges: ";
	cin >> mTemp;
	cout << endl << "Please enter the maximum weight: ";
	cin >> wMaxTemp;
	cout << endl << "Please enter the minimum weight: ";
	cin >> wMinTemp;
	cout << endl;
	createMatrices(nTemp, mTemp, wMaxTemp, wMinTemp); //Actual creation/output is here

	cin >> stop; //<-- Because VS auto closes console

	return 0;
}
