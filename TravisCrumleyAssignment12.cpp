/*****************************************************************************
Program file name: TravisCrumleyAssignment12.cpp	  OS: Windows 10  Assignment: #12
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 11/20/2015
Compiler: Visual Studio 2015

Assistance/references:
Description:
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
#include <iomanip>
#include <omp.h>
#include <limits>

typedef std::numeric_limits< double > dbl; //For max precision

using namespace std;

// Question #1:
int bitCount(int w)
{
	int c = 0;
	while (w != 0)
	{
		c++;
		w = w & (w - 1);
	}
	return c;
}

// Question #2:
long double partialSum(long double k)
{
	long double sum = 0;
	bool isNeg = false;  // By default start non-negative
	if ((int)k % 2 != 0) // If it's odd
	{
		isNeg = true; // Change to negative start
	}

	for (long double i = k; i >= 0; i--)
	{
		if (isNeg) 
		{
			sum -= 1 / (3 * i + 1);
		}
		else
		{
			sum += 1 / (3 * i + 1);
		}
		isNeg = !isNeg;
	}

	return sum;
}

// Question #3:
long int power(long int m, long int n)
// Computes m^n
{
	int numMults = 0;
	if (n == 0)
	{
		cout << "Number of multiplications: " << numMults << endl;
		return 1; // m^0 = 1
	}
	while ((n & 1) == 0) // Consume any leading 0's, squaring m.
	{
		m = m * m;
		numMults++;
		n = n >> 1;
	}
	long int p = m;		 // Set p to m and consume the 1-bit
	n = n >> 1;		     // Effectively bypassing setting p to 1
	while (n > 0)		 // Resume the normal binary method
	{
		m = m * m;
		numMults++;
		if ((n & 1) == 1)
		{
			p = p * m;
			numMults++;
		}
		n = n >> 1;
	}
	cout << "Number of multiplications: " << numMults << endl;
	return p;		    // p is m^n
}

// Question #4:
int add(int m, int n)
{
	if (m == 0)
	{
		if (n == 0)
		{
			return 0;
		}
		else
		{
			return 1 + add(0, n - 1);
		}
	}
	else if (n == 0)
	{
		return 1 + add(m - 1, 0);
	}
	else
	{
		return 1 + add(m - 1, 1 + add(0, n - 1));
	}
}

int main()
{
	cout << "\nQuestion 1:\n";
	cout << "Bitcount of 1123414124" << bitCount(1123414124) << endl;

	cout << "\nQuestion 2:\n";
	cout.precision(dbl::max_digits10);
	cout << fixed;
	for (int i = 0; i < 9; i++)
	{
		cout << "Partial sum for k = 10^" << i << " : " << partialSum(pow(10, i)) << endl;
	}

	cout << "\nQuestion 3:\n";
	for (int i = 0; i <= 10; i++)
	{
		cout << "2^" << i << ": " << power(2, i) << endl;
	}


	cout << "\nQuestion 4:\n";
	int n = 1;
	int k = 10;
	//add(2350, 2351); // Max it can handle
	for (int i = 0; i <= 3; i++)
	{
		auto start_time = chrono::high_resolution_clock::now();
		cout << "For 10^" << i << ": " << add(n, n) << endl;
		auto end_time = chrono::high_resolution_clock::now();
		cout << "Seconds: " << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << endl;
		cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
		cout << endl;
		n *= 10;
	}
}