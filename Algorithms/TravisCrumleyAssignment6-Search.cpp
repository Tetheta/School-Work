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
	// i and j are used to split the array into pieces
	// a[i:j] is then operated on

	
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