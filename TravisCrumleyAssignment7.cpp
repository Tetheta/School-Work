/*****************************************************************************
Program file name: TravisCrumleyAssignment7.cpp	  OS: Windows 10  Assignment: #7
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 10/25/2015
Compiler: Visual Studio 2015

Assistance/references:
Description: Implement Sorting Algorithms
Inputs:
Outputs: Output of Sorted Array

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
#include <queue>
#include <vector>
#include <utility> // for swap
#include <chrono>
#include <stdlib.h>
#include <time.h>
using namespace std;

int Partition(int a[], int left, int right)
{
	int pivot = a[left];
	int i = left + 1;
	int j = right;
	while (i <= j)
	{
		while (i <= j && a[i] <= pivot)
			i++;

		while (i <= j && a[j] > pivot)
			j--;

		if (i < j)
		{
			swap(a[i], a[j]);
		}
	}
	swap(a[i - 1], a[left]);
	return i - 1;
}

void QuickSort_Recursive(int* a, int left, int right)
{
	if (left < right)
	{
		int pivot = Partition(a, left, right);

		if (pivot > 1)
			QuickSort_Recursive(a, left, pivot - 1);

		if (pivot + 1 < right)
			QuickSort_Recursive(a, pivot + 1, right);
	}
}

// Much slower than the recursive version
// Not sure if that's just true or if I'm implementing it
// badly, lots of stuff has to be created so that might be it
void QuickSort_Iterative(int *a, int left, int right)
{
	if (left >= right)
		return; // Invalid index range

	std::vector<std::pair<int, int> > list;

	int srcleft = left;
	int srcright = right;

	list.push_back(std::pair<int, int>(left, right));
	int pivot = 0;
	while (1)
	{
		if (list.size() == 0)
			break;

		left = list.back().first;
		right = list.back().second;
		list.pop_back();

		pivot = Partition(a, left, right);

		std::pair<int, int> p;
		if(pivot - 1 > left)
			list.push_back(std::pair<int, int>(left, pivot - 1));

		if (pivot + 1 < right)
			list.push_back(std::pair<int, int>(pivot + 1, right));
	}
}

/* RADIX SORT SECTION */
int getMax(int a[], int n)
{
	int max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
	}
	return max;
}

void RadixSort(int a[], int start, int end)
{
	int n = end;
	int** q = new int*[2];
	for (int i = 0; i < 2; i++)
	{
		q[i] = new int[n];
	}
	int qNmbr = 0;
	int qSize[] = { 0,0 };
	int x = (int)log2f(getMax(a, n));
	for (int k = 0; k <= x; k++)
	{
		//Reinitialize queues
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < n; j++)
			{
				q[i][j] = 0;
			}
		}
		qSize[0] = qSize[1] = 0;


		for (int i = 0; i <= n; i++)
		{
			qNmbr = (a[i] >> k) & 1;
			q[qNmbr][qSize[qNmbr]++] = a[i];
		}
		//Copy queues to the array
		int i = 0;
		for (qNmbr = 0; qNmbr < 2; qNmbr++)
		{
			for (int j = 0; j < qSize[qNmbr]; j++)
			{
				a[i++] = q[qNmbr][j];
			}
		}
	}
}

int main()
{
	while (true)
	{
		srand(time(NULL));
		
		const int length = 2048;
		const int modNum = length;
		int a[length];

		//cout << "Array before Quicksort Recursive:\n";
		for (size_t i = 0; i < length; i++)
		{
			a[i] = rand() % modNum;
			//cout << "a[" << i << "]: " << a[i] << endl;
		}

		auto start_time1 = std::chrono::high_resolution_clock::now();
		QuickSort_Recursive(a, 0, length - 1);
		auto end_time1 = std::chrono::high_resolution_clock::now();

		cout << "Length: " << length << endl;
		cout << "For Quicksort Recursive: " << endl;
		cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time1 - start_time1).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time1 - start_time1).count() << endl;
		/*cout << "Sorted Array:" << endl;
		for (size_t i = 0; i < length; i++)
		{
			cout << "a[" << i << "]: " << a[i] << endl;
		}*/

		//cout << endl;
		//cout << "Array before Quicksort Interactive:\n";
		//for (size_t i = 0; i < length; i++)
		//{
		//	a[i] = rand() % modNum;
		//	cout << "a[" << i << "]: " << a[i] << endl;
		//}

		//auto start_time = std::chrono::high_resolution_clock::now();
		//QuickSort_Iterative(a, 0, length - 1);
		//auto end_time = std::chrono::high_resolution_clock::now();

		//cout << "For Quicksort Iterative: " << endl;
		//cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
		//cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
		//cout << "Sorted Array:" << endl;
		//for (size_t i = 0; i < length; i++)
		//{
		//	cout << "a[" << i << "]: " << a[i] << endl;
		//}

		cout << endl;
		//cout << "Array before Radix Sort:\n";
		for (size_t i = 0; i < length; i++)
		{
			a[i] = rand() % modNum;
			//cout << "a[" << i << "]: " << a[i] << endl;
		}

		auto start_time2 = std::chrono::high_resolution_clock::now();
		RadixSort(a, 0, length - 1);
		auto end_time2 = std::chrono::high_resolution_clock::now();

		cout << "For Radix Sort: " << endl;
		cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time2 - start_time2).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time2 - start_time2).count() << endl;
		/*cout << "Sorted Array:" << endl;
		for (size_t i = 0; i < length; i++)
		{
			cout << "a[" << i << "]: " << a[i] << endl;
		}*/

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}