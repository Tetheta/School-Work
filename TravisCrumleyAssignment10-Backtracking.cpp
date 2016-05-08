/*****************************************************************************
Program file name: TravisCrumleyAssignment10-Backtracking.cpp	  OS: Windows 10  Assignment: #10
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 11/08/2015
Compiler: Visual Studio 2015

Assistance/references:
Description: Implement Backtracking for N-Queens problem 1-15
Inputs:
Outputs:

Special Comments:

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~

Assignment Requirements: ___/3.0

Code Format/Cosmetics: ___/3.0

Header & Code Comments: ___/2.0

Output Format/Cosmetics: ___/2.0
***Does Not Compile***: ___ (-10.0)
***Late Work Deduction***: ___ (-0.5/day)
Total Grade: ___/10.0

*****************************************************************************/

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

// Defines
#define OUTPUT

bool Place(vector<int> x, int k, int i)
// Returns true if a queen can be placed in the kth row and ith column.
// Otherwise it returns false. x[] is a passed vector whose first (k-1) values have been set.
// abs(r) returns the absolute value of r.
{
	for (int j = 1; j < k; j++)
	{
		if ((x[j] == i)						// Two in the same column
			|| (abs(x[j]-i) == abs(j-k)))	//Or the same diagonal
		{
			return false;
		}
	}
	return true;
}

vector<int> D1Flip(vector<int> a, int n)
{
	vector<int> b = a;
	for (int i = 1; i <= n; i++)
	{
		a[b[i]] = i;
	}
	return a;
}

vector<int> VFlip(vector<int> a, int n)
{
	vector<int> b = a;
	for (int i = 1; i <= n; i++)
	{
		a[i] = b[n + 1 - i];
	}
	return a;
}

bool NonIso(vector<int> vec, int n)
// Returns true if the global vector is non-isomorphic (not the same)
// to a previously generated vector
{
	vector<int> temp = vec;
	temp = D1Flip(temp, n);
	if (temp < vec)
	{
		return false;
	}
	for (int i = 1; i <= 3; i++)
	{
		temp = VFlip(temp, n);
		if (temp < vec)
		{
			return false;
		}
		temp = D1Flip(temp, n);
		if (temp < vec)
		{
			return false;
		}
	}
	return true;
}

void NQueens(vector<int> x, int k, int n, int &counter)
// Using backtracking, this procedure prints all possible placements of n queens on an
// nxn chessboard so that they are nonattacking.
{
	for (int i = 1; i <= n; i++)
	{
		if (Place(x, k, i))
		{
			x[k] = i;
			if (k == n)
			{
				//Check if it's non-isomorphic to previous vectors
				if (NonIso(x, n))
				{
#ifdef OUTPUT
					// Print out a little chart of the chess board
					for (int row = 1; row <= n; row++)
					{
						for (int col = 1; col <= n; col++)
						{
							if (x[row] == col)
							{
								cout << x[row];// << " ";
							}
							else
							{
								cout << "=";// ";
							}
						}
						cout << endl; // end the column
					}
					cout << endl; //End the chart
#endif
					counter++;
				}
			}
			else
			{
				NQueens(x, k + 1, n, counter);
			}
		}
	}
}

int main()
{
	vector<int> x = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //16 spots (So we can index at 1)
	int counter = 0;
	for (size_t i = 1; i <= 8; i++)
	{
		counter = 0;
		cout << "For " << i << ": " << endl;
		auto start_time = std::chrono::high_resolution_clock::now();
		NQueens(x, 1, i, counter);
		auto end_time = std::chrono::high_resolution_clock::now();
		cout << "Count: " << counter << endl;
		cout << endl;
		cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
		cout << endl;
	}
	
}