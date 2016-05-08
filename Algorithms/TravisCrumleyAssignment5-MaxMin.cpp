/*****************************************************************************
Program file name: TravisCrumleyAssignment5-MaxMin.cpp	  OS: Windows 10  Assignment: #5
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 10/21/2015
Compiler: Visual Studio 2015

Assistance/references:
Description: Implement Max/Min Algorithms
Inputs:
Outputs: Output of Maximum of predefined array

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
#include <stdlib.h>
#include <time.h>
using namespace std;

template <typename Type>
void MaxMin2(int i, int j, const Type a[], Type& max, Type& min)
{
	// I'm assuming that I'm operating on global array a[1:n]
	// i and j are used to split the array into pieces
	// a[i:j] is then operated on

	if (i == j)
	{
		max = min = a[i]; //Base Case
	}
	else if (i == j - 1)
	{
		if (a[i] < a[j])
		{
			max = a[j];
			min = a[i];
		}
		else
		{
			max = a[i];
			min = a[j];
		}
	}
	else
	{
		// Divide it up into the sets n/2
		// First find where to split it
		int mid = (i + j + 1) / 2; //Added 1 b/c indexing at 0
		Type max1, min1;

		//Solve the sub cases
		MaxMin2(i, mid, a, max, min);
		MaxMin2(mid + 1, j, a, max1, min1);

		//Combine
		if (max < max1)
		{
			max = max1;
		}
		if (min > min1)
		{
			min = min1;
		}
	}
}

template <typename Type>
void MaxMin3(int n, const Type a[], Type& max, Type& min)
{
	// I'm assuming that I'm operating on global array a[1:n]
	// i and j are used to split the array into pieces
	// a[i:j] is then operated on
	if (a[0] > a[1])
	{
		max = a[0];
		min = a[1];
	}
	else
	{
		max = a[1];
		min = a[0];
	}
	for (size_t i = 2; i < n; i+= 2)
	{
		if (a[i] > a[i+1])
		{
			if (max < a[i])
			{
				max = a[i];
			}
			if (min > a[i + 1])
			{
				min = a[i + 1];
			}
		}
		else
		{
			if (max < a[i + 1])
			{
				max = a[i + 1];
			}
			if (min > a[i])
			{
				min = a[i];
			}
		}
	}
}

int main()
{
	//Array to use for this little program
	while (true)
	{
		srand(time(NULL));
		const int length = 32000;
		int a[length];

		for (size_t i = 0; i < length; i++)
		{
			a[i] = rand();
			//cout << "a[" << i << "]: " << a[i] << endl;
		}

		int max = 0;
		int min = 0;

		auto start_time = std::chrono::high_resolution_clock::now();
		MaxMin2(0, length - 1, a, max, min); //Recursive
		auto end_time = std::chrono::high_resolution_clock::now();

		cout << "For Recursive (MaxMin2): " << endl;
		cout << "Max: " << max << "\nMin: " << min << endl;
		cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;

		max = 0;
		min = 0;

		start_time = chrono::high_resolution_clock::now();
		MaxMin3(length, a, max, min); //Iterative
		end_time = chrono::high_resolution_clock::now();

		cout << "For Iterative (MaxMin3): " << endl;
		cout << "Max: " << max << "\nMin: " << min << endl;
		cout << "Seconds: " << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;

		int temp = 0;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}