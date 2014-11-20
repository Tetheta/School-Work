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
#include <vector>

using namespace std;

float uni() //Returns rand decimal on [0,1)
{
	return float(rand()) / RAND_MAX;
}

int random(int n) {
	return rand() % n;
}

void createMatrices(int n, float m, int wMax, int wMin)
{
	srand(777);
	float q = 0.0f;
	cout << "Number of Vertices is: " << n << endl;
	cout << "Number of Edges is: " << m << endl;
	cout << "Max weight is: " << wMax << endl;
	cout << "Min weight is: " << wMin << endl;
	float tempN = (float)n;
	int mCount = 0;
	//q = m / ((tempN+1.75)*(tempN+1)); //uni will be <= q, this is because q*n(n-1)=m
	//cout << "q is: " << q << endl;

	//Creating the directed graph adjacency matrix

	cout << endl;
	cout << "Adjacency Matrix: " << endl;
	//Initialize Adjacency Matrix
	vector< vector<int> > A;
	A.resize(n + 1);
	for (int i = 1; i < n + 1; i++)
	{
		//Grow columns by numVertices for each row
		A[i].resize(n + 1);
	}
	//Initialize cost matrix
	vector< vector<int> > C;
	C.resize(n + 1);
	for (int i = 1; i < n + 1; i++)
	{
		//Grow columns by numVertices for each row
		C[i].resize(n + 1);
	}

	int i, j = 0;
	for (int k = 1; k <= m; k++)
	{
		do
		{
			i = 1 + random(n);
			j = 1 + random(n);
		} while (A[i][j] == 1);
		A[i][j] = 1;
		C[i][j] = wMin + random(wMax - wMin + 1);
	}

	
	for (int i = 1; i <= n; i++)
	{
		//A[i][i] = 0; //So no self-loops
		for (int j = 1; j <= n; j++)
		{
			/*
			if (uni() <= q && mCount <= m)
			{
				A[i][j] = 1;
				C[i][j] = wMin + random(wMax - wMin + 1);
				mCount++;
			}
			else
			{
				A[i][j] = 0;
			}
			*/
			cout << A[i][j] << "   ";
		}
		cout << endl;
	}
	

	//Creating the directed graph cost matrix

	cout << endl;
	cout << "Cost Matrix: " << endl;

	for (int i = 1; i <= n; i++)
	{
		//C[i][i] = 0; //So no self-loops
		for (int j = 1; j <= n; j++)
		{
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
		cout << endl;
	}
}
int main()
{
	char stop; //<-- Because VS auto closes console, should look into fixing that

	int nTemp = 0;
	float mTemp = 0.0f;
	int wMaxTemp = 0;
	int wMinTemp = 0;
	cout << "Please enter the number of vertices: ";
	cin >> nTemp; //Number of vertices

	//m = n - 1 + random((n*n - 3 * n + 4) / 2); //For a rand # of edges
	cout << endl << "Please enter the number of edges: ";
	cin >> mTemp;
	cout << endl << "Please enter the maximum weight: ";
	cin >> wMaxTemp;
	cout << endl << "Please enter the minimum weight: ";
	cin >> wMinTemp;
	createMatrices(nTemp, mTemp, wMaxTemp, wMinTemp);

	cin >> stop; //See above note

	return 0;
}
