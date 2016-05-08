/*****************************************************************************
Program file name: TravisCrumleyAssignment11.cpp	  OS: Windows 10  Assignment: #11
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 11/08/2015
Compiler: Visual Studio 2015

Assistance/references:
Description: Implement various items
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

void MyNumbers2(int n)
{
	int total = 0;
	int numsToRemove = 0;
	// Creating My Sieve for generating lucky numbers
	bool *a;
	a = new bool[n + 1];

	// Initialize everything to true
	for (int m = 1; m <= n; m++)
	{
		a[m] = true;
	}
	// Remove every next number a that isn't crossed out, and every
	// subsequent a-1th  surviving number until a-1 numbers have been crossed out
	for (int i = 1; i <= n; i++)
	{
		if (a[i])
		{
			numsToRemove = i - 1;
			int count = 0;
			for (int j = 1; j <= n; j++)
			{
				if (numsToRemove > 0)
				{
					if (a[j])
						// If it's a surviving number, update the count
					{
						count++;
						if (count == i - 1)
							// If the count is i, remove that number
						{
							a[j] = false;
							count = 0;
							numsToRemove--;
							total++;
						}
					}
					// If it's not a surviving number, skip it
				}

			}
		}
	}

	cout << "My Numbers2: \n";
	for (int j = 1; j <= n; j++)
	{
		if (a[j])
		{
			cout << j << ", ";
		}
	}
	cout << endl << "Total: " << n - total << endl;

	delete[] a;
}

void MyNumbers(int n)
{
	int total = 0;
	int numsToRemove = 0;
	// Creating My Sieve for generating lucky numbers
	bool *a;
	a = new bool[n + 1];

	// Initialize everything to true
	for (int m = 1; m <= n; m++)
	{
		a[m] = true;
	}
	// Remove every even number
	for (int i = 2; i <= n; i+= 2)
	{
		a[i] = false;
		total++;
	}
	// Remove every next number a that isn't crossed out, and every
	// subsequent a-1th  surviving number until a-1 numbers have been crossed out
	for (int i = 2; i <= n; i++)
	{
		if (a[i])
		{
			numsToRemove = i - 1;
			int count = 0;
			for (int j = 1; j <= n; j++)
			{
				if (numsToRemove > 0)
				{
					if (a[j])
						// If it's a surviving number, update the count
					{
						count++;
						if (count == i - 1)
							// If the count is i, remove that number
						{
							a[j] = false;
							count = 0;
							numsToRemove--;
							total++;
						}
					}
					// If it's not a surviving number, skip it
				}

			}
		}
	}

	cout << "My Numbers: \n";
	for (int j = 1; j <= n; j++)
	{
		if (a[j])
		{
			cout << j << ", ";
		}
	}
	cout << endl << "Total: " << n - total << endl;

	delete[] a;
}

void LuckyNumbers(int n)
{
	int total = 0;
	// Creating Ulam's Sieve for generating lucky numbers
	bool *a;
	a = new bool[n+1];

	// Initialize everything to true
	for (int m = 1; m <= n; m++)
	{
		a[m] = true;
	}
	// Remove every next number a that isn't crossed out, and every
	// subsequent ath surviving number
	for (int i = 2; i <= n; i++)
	{
		if (a[i])
		{
			int count = 0;
			for (int j = 1; j <= n; j++)
			{
				if (a[j])
				// If it's a surviving number, update the count
				{
					count++;
					if (count == i)
						// If the count is i, remove that number
					{
						a[j] = false;
						count = 0;
						total++;
					}
				}
				// If it's not a surviving number, skip it
			}
		}
	}
	a[2] = false;

	cout << "Lucky Numbers: \n";
	for (int j = 1; j <= n; j++)
	{
		if (a[j])
		{
			cout << j << ", ";
		}
	}
	cout << endl << "Total: " << n - total << endl;

	delete[] a;
}

bool IsPrimeMillerRabin(int n, int alpha)
{
	// Returns 1 if n is a prime and 0 otherwise
	// alpha is the probability parameter

	int q = n - 1;
	for (int i = 1; i <= (alpha*log(n)); i++)
	{
		int m = q, y = 1;
		int a = rand() % q + 1;
		// Choose a random number in the range [1, n-1]
		int z = a;
		// Compute a^n-1 mod n
		while (m > 0)
		{
			while (m % 2 == 0)
			{
				int x = z;
				z = (z*z) % n;
				// If x is a nontrivial square
				// root of 1, n is not prime
				if ((z == 1) && (x != 1) && (x != q))
				{
					return 0;
				}
				m /= 2;
			}
			m--;
			y = (y*z) % n;
		}
		if (y != 1)
		{
			return 0;
		}
		// If a^n-1 mod n is not 1, n is not prime
	}
	return 1;
}

int main()
{
	srand(time(0));
	auto start_time = std::chrono::high_resolution_clock::now();
	LuckyNumbers(1000);
	auto end_time = std::chrono::high_resolution_clock::now();
	cout << endl;
	cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
	cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
	cout << endl;

	start_time = std::chrono::high_resolution_clock::now();
	cout << "IsPrime: " << IsPrimeMillerRabin(7, rand()) << endl;
	end_time = std::chrono::high_resolution_clock::now();
	cout << endl;
	cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
	cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
	cout << endl;

	start_time = std::chrono::high_resolution_clock::now();
	MyNumbers(1000);
	end_time = std::chrono::high_resolution_clock::now();
	cout << endl;
	cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
	cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
	cout << endl;

	start_time = std::chrono::high_resolution_clock::now();
	MyNumbers2(1000);
	end_time = std::chrono::high_resolution_clock::now();
	cout << endl;
	cout << "Seconds: " << chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
	cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
	cout << endl;

}